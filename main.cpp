#include <iostream>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <string>

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


string hangangFetch(){
    int sock;
    struct sockaddr_in client;
    int PORT = 80;

    struct hostent * host = gethostbyname("hangang.dkserver.wo.tc");
    if ( (host == NULL) || (host->h_addr == NULL) ) {
        cout << "Error retrieving DNS information." << endl;
        exit(1);
    }

    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        cout << "Error creating socket." << endl;
        exit(1);
    }

    if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock);
        cout << "Could not connect" << endl;
        exit(1);
    }

    stringstream ss;
    ss << "GET /" << " HTTP/1.0\r\n"
       << "Host: hangang.dkserver.wo.tc\r\n"
       << "Accept: application/json\r\n"
       << "\r\n\r\n";

    string request = ss.str();

    if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
        cout << "Error sending request." << endl;
        exit(1);
    }

    cout << endl << endl;

    char cur;
    while (read(sock, &cur, 1) > 0){
        cout << cur;
    }

    return "return";
}
void hangangMain(){
    string c = hangangFetch();
}

int main(void){
    int name_read;
    char name_bf[BLKSIZE];

    getUserNameFromKeyboard(name_bf, name_read);

    char h[] = {"23"};
    char w[] = {"17"};


    pid_t hangang_fork = fork();
    if(hangang_fork == -1){
        perror("Failed to fork");
        return 1;
    }
    if(hangang_fork == 0){
        //  child
        while(1){
            hangangMain();
            sleep( 1 );
        }
    } else {
        //  parent
        while(1){
            cout << "\r" << flush;
            printCurrentStatus(name_bf, name_read, h, 2, w, 2);
            cout << flush;
            sleep( 10 );
        }
    }
}