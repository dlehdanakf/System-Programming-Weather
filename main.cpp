#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <string>

#define BLKSIZE 1024

using namespace std;

void getUserNameFromKeyboard(char* buf, int &bytesread){
    while (((bytesread = read(STDIN_FILENO, buf, BLKSIZE)) == -1) && (errno == EINTR)) ; /* handle interruption by signal */
}

int main(void){

    int name_read;
    int name_write;
    char name_bf[BLKSIZE];
    char welcome[] = {"님 안녕하세요"};

    getUserNameFromKeyboard(name_bf, name_read);

    while(((name_write = write(STDOUT_FILENO, name_bf, name_read - 1)) == -1 ) && (errno == EINTR)) ;
    while(((name_write = write(STDOUT_FILENO, welcome, sizeof(welcome) - 1)) == -1 ) && (errno == EINTR)) ;

}