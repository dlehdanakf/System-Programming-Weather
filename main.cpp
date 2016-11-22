#include <iostream>
#include <errno.h>
#include <unistd.h>

#define BLKSIZE 1024

using namespace std;

void getUserNameFromKeyboard(char* buf, int &bytesread){
    while (((bytesread = read(STDIN_FILENO, buf, BLKSIZE)) == -1) && (errno == EINTR)) ; /* handle interruption by signal */
}

void printCurrentStatus(char* name_bf, int name_length, char* hangang_bf, int hangang_length, char* weather_bf, int weather_length){

    int state;
    char after_name[] = {"님 안녕하세요. 한강온도 : "};
    char after_hangang[] = {"3 ºC | 실외온도 : "};
    char after_weather[] = {" ºC"};

    while(((state = write(STDOUT_FILENO, name_bf, name_length - 1)) == -1 ) && (errno == EINTR)) ;
    while(((state = write(STDOUT_FILENO, after_name, sizeof(after_name) - 1)) == -1 ) && (errno == EINTR)) ;
    while(((state = write(STDOUT_FILENO, hangang_bf, hangang_length)) == -1 ) && (errno == EINTR)) ;
    while(((state = write(STDOUT_FILENO, after_hangang, sizeof(after_hangang) - 1)) == -1 ) && (errno == EINTR)) ;
    while(((state = write(STDOUT_FILENO, weather_bf, weather_length)) == -1 ) && (errno == EINTR)) ;
    while(((state = write(STDOUT_FILENO, after_weather, sizeof(after_weather) - 1)) == -1 ) && (errno == EINTR)) ;
}

int main(void){
    int name_read;
    int name_write;
    char name_bf[BLKSIZE];

    getUserNameFromKeyboard(name_bf, name_read);

    char h[] = {"23"};
    char w[] = {"17"};

    printCurrentStatus(name_bf, name_read, h, 2, w, 2);
}