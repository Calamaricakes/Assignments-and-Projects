
#ifndef ASSIGNMENT1
#define ASSIGNMENT1

#include <stdio.h>
#define RESPONSE_200_JPEG "HTTP/1.0 200 OK\r\nContent-Type: image/jpeg\r\n\r\n"
#define RESPONSE_404 "HTTP/1.0 404\r\n"

#define SEND_BUFFER 10000
#define RECEIVE_BUFFER 10000
#define ROOT_SIZE 256
#define PATH_SIZE 256
#define FILE_TYPE_SIZE 10
#define CHAR_SIZE 1

#define TYPE_404 0
#define HTML_TYPE 1
#define CSS_TYPE 2
#define JS_TYPE 3
#define JPEG_TYPE 4

#define SUCCESS 1
#define BACKLOG 10
#define ERROR -1

typedef struct{
    int connfd;
    char web_root[ROOT_SIZE];
} data_node;

void *process_request(void* data_ptr);
int process_path(char* received, char* root, char* full_path);
int check_file_type(char* file_str);
int read_file_into_buffer_and_send(FILE* fp, int connfd, int file_type);
int send_response(int connfd, int file_type);
int open_file(FILE** fp, int file_type, char* file_path);

#endif

