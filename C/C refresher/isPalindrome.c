#include <stdio.h>

int isPalindrome(char str[], int length);

int main(){

    char notPalindrome[] = {'n','o','t'};
    char palindrome[] = {'a','t','o','m','o','t','a'};

    printf("%d\n", isPalindrome(notPalindrome, 3));
    printf("%d\n", isPalindrome(palindrome, 7));

    return 0;
}

int isPalindrome(char str[], int length){
    int start = 0, end = length - 1;

    while(str[start] == str[end]){
        start++;
        end--;
        if(start >= end){
            return 1;
        }
    }
    return 0;
}
