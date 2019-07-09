#include <stdio.h>

char* removeChar(char str[], char character);

int main(){

    char notPalindrome[] = {'n','o','t', '\0'};
    char palindrome[] = {'a','t','o','m','o','t','a','\0'};

    printf("%s", removeChar(palindrome, 'o'));

    return 0;
}

char* removeChar(char str[], char character){
    int index = 0;

    while(str[index] != '\0'){

        if(str[index] == character){
            int dex = index;

            while(str[dex] != '\0'){
                str[dex] = str[dex + 1];
                dex++;
            }
            continue;
        }
        index++;
    }
    return str;

}
