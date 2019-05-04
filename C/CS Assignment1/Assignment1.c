#include <Assignment1.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

int main(int argc, char* argv[]){
  	int listenfd = 0, connfd = 0, port;
  	char send_buff[SEND_BUFFER], web_root[ROOT_SIZE];
  	struct sockaddr_in serv_addr;
	data_node* data_ptr;

  	// assign port and copy web root from arguments
  	port = atoi(argv[1]);
  	strcpy(web_root, argv[2]);

  	// set up socket
  	listenfd = socket(AF_INET, SOCK_STREAM, 0);
  	memset(&serv_addr, '0', sizeof(serv_addr));
  	memset(&send_buff, '0', sizeof(send_buff));

  	// set up socket properties
  	serv_addr.sin_family = AF_INET; 		// specify IP protocol (IP4 OR IP6)
  	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 	// allow the socket to listen on any IP address
  	serv_addr.sin_port = htons(port); 		// set port to listen on port

  	// bind to socket
  	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
  		printf("socket bind error\n");
  		exit(1);
  	}

  	// listen on socket
  	if(listen(listenfd, BACKLOG) < 0){
  		printf("listen error\n");
  		exit(1);
  	}

	pthread_t thread_id;

  	while(1){

		printf("Waiting..\n");

		// accept connection
		if((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0){
            printf("accept error\n");
		}

        if((data_ptr = (data_node*)malloc(sizeof(data_node))) == NULL){
	    	send_response(connfd, TYPE_404);
            close(connfd);
    		continue;
    	}

		//copy socket id and web_root into struct
   		data_ptr->connfd = connfd;
    	strcpy(data_ptr->web_root, web_root);

		//create a thread for the request
		if( (pthread_create(&thread_id, NULL, process_request, data_ptr)) != 0){
    		printf("Thread creation failure\n");
            send_response(connfd, TYPE_404);
            free(data_ptr);
            close(connfd);
    	}
  	}
}

void* process_request(void* data_ptr){

    data_node* reference_ptr = (data_node*) data_ptr;
    FILE* fp = NULL;
  	int file_type, response_type;
  	char full_path[PATH_SIZE], receive_buff[RECEIVE_BUFFER];

    int connfd = reference_ptr->connfd;
    char* web_root = reference_ptr->web_root;

    printf("web_root: %s\n", web_root);
    // receive request into receive_buff
    if(recv(connfd, receive_buff, sizeof(receive_buff), 0) < 1){
        printf("receive error\n");

        //clean up
        close(connfd);
        free(data_ptr);
        return;  // do not continue with process
	}

    // process the request string and return the file type and the file path
    file_type = process_path(receive_buff, web_root, full_path);

    // open the file specified by full path
    if(open_file(&fp, file_type, full_path) != SUCCESS ){
        printf("file open unsuccessful\n");
        send_response(connfd, ERROR);

        //clean up
        close(connfd);
        free(data_ptr);
        return;
    }

    // send header response
    if((response_type = send_response(connfd, file_type)) == SUCCESS){
        printf("header response sent\n");
    }
    else{
        printf("404 response sent\n");

        //clean up
        close(connfd);
        free(data_ptr);
        return;
    }

    // send data
		if(read_file_into_buffer_and_send(fp, connfd, file_type) != SUCCESS){
        printf("unable to load into buffer\n");

        //clean up
        close(connfd);
        free(data_ptr);
        return;
    }

    //clean up
    close(connfd);
    free(data_ptr);
    return;
}

int process_path(char* received, char* root, char* full_path){

  	int path_index, resource_index, file_index, file_type_index;
  	int file_type;
  	char resource[PATH_SIZE], file_str[FILE_TYPE_SIZE];

  	// copy contents of root to path
  	strcpy(full_path, root);

  	// get to index with resource string
  	for( path_index = 0; received[path_index] != '/'; path_index++);

  	// copy resource string into resource
  	for( resource_index = 0; received[path_index] != ' '; path_index++, resource_index++){
    		resource[resource_index] = received[path_index];

    		if(resource[resource_index] == '.'){
      			file_index = resource_index;
    		}
  	}

  	//null resource string
  	resource[resource_index] = '\0';

  	// add resource string to webroot
  	strcat(full_path, resource);

  	printf("full_path: %s\n", full_path);

  	for(file_type_index = 0; resource[file_index] != '\0'; file_index++, file_type_index++){
    		file_str[file_type_index] = resource[file_index];
  	}

  	//null file string
  	file_str[file_type_index] = '\0';

  	// check the file type
  	file_type = check_file_type(file_str);

  	return file_type;
}

int check_file_type(char* file_str){

  	int i = 0;

  	while(file_str[i] != '\0'){
    		file_str[i] = tolower(file_str[i]);
    		i++;
  	}

  	if(strcmp(file_str, ".html") == 0){
    		return HTML_TYPE;
  	}
  	else if(strcmp(file_str, ".css") == 0){
    		return CSS_TYPE;
  	}
  	else if(strcmp(file_str, ".js") == 0){
    		return JS_TYPE;
  	}
  	else if (strcmp(file_str, ".jpg") == 0){
    		return JPEG_TYPE;
  	}
  	return ERROR;

}

int send_response(int connfd, int file_type){

    // send header response according to the file type requested
    if(file_type == HTML_TYPE){
  			send(connfd, RESPONSE_200_HTML, strlen(RESPONSE_200_HTML), 0);
        return SUCCESS;
	}
	else if(file_type == CSS_TYPE){
  		send(connfd, RESPONSE_200_CSS, strlen(RESPONSE_200_CSS), 0);
	    return SUCCESS;
    }
	else if(file_type == JS_TYPE){
		send(connfd, RESPONSE_200_JS, strlen(RESPONSE_200_JS), 0);
        return SUCCESS;
	}
	else if(file_type == JPEG_TYPE){
	    send(connfd, RESPONSE_200_JPEG, strlen(RESPONSE_200_JPEG), 0);
        return SUCCESS;
	}
	else{
    //failed send 404
  		send(connfd, RESPONSE_404, strlen(RESPONSE_404), 0);
        return TYPE_404;
    }
}


int read_file_into_buffer_and_send(FILE* fp, int connfd, int file_type){

    unsigned long file_len;
    char* send_buff[SEND_BUFFER];
    int bytes_read;

    if(file_type != JPEG_TYPE){
  			bytes_read = fread(send_buff, CHAR_SIZE, sizeof(send_buff), fp);
        send(connfd, send_buff, bytes_read, 0);
        return SUCCESS;
    }
		else if(file_type > 0){
  			fseek(fp, 0, SEEK_END);
  			file_len = ftell(fp);
  			fseek(fp, 0, SEEK_SET);
  			fread(send_buff, file_len, sizeof(send_buff), fp);
        send(connfd, send_buff, file_len, 0);
        return SUCCESS;
		}
    return ERROR;
}

int open_file(FILE**fp, int file_type, char* file_path){

    if( file_type != JPEG_TYPE ){
    		if((*fp = fopen(file_path, "r")) != NULL){
          printf("file opened 'r'\n");
          return SUCCESS;
    		}
        else{
          printf("cannot open file 'r'\n");
        }
   	}
   	else{
    		if((*fp = fopen(file_path, "rb")) != NULL){
            printf("file opened 'rb'\n");
      			return SUCCESS;
    		}
        else{
          printf("cannot open file 'rb'\n");
        }
   	}
    return ERROR;
}
