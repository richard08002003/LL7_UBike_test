/* Simple Write/Read Test */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/usr/local/UBike/ipc/LL7_UBike.ipc"
int main()
{

    struct sockaddr_un client ;
    //Socket()
    int sd = socket( AF_UNIX , SOCK_STREAM , 0 ) ;
    if( sd < 0 ) {
        perror("socket") ;
        exit(1) ;
    }
        printf("Socket Created ! \n") ;
    client.sun_family = AF_UNIX ;
    strcpy( client.sun_path , SOCK_PATH ) ;

    //Connect()
    int con = connect( sd , (struct sockaddr *)&client , sizeof(client) ) ;
    if ( con < 0 ) {
        perror("connect") ;
        exit(1) ;
    }
        printf("Connected ! \n") ;

    int snd , rcv ;
    char reply[4000] = {0} ;

    //Data
    #define data1  "{\"Function\":\"SelfTest\",\"QryMd5\":\"12345678945612341234567894561234\"}"

    unsigned long int data1_len = strlen(data1) ;
    char buf1 [ 11 + (int)data1_len + 1 ] ;
    memset( buf1 , 0 , sizeof(buf1) ) ;
    snprintf( buf1 , sizeof(buf1) ,"<S>%08X" , data1_len ) ;
    strncat( buf1 , data1 , sizeof(buf1) ) ;

    printf("傳送的資料 : %s\n" , buf1 ) ;
    snd = send( sd , buf1 , sizeof(buf1) , 0 ) ;
    if( snd < 0 ) {
        printf("Send data1 Failed ! \n") ;
        exit(1) ;
    }
        printf("Send Success ! \n") ;

    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        printf("Receive reply Failed ! \n") ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        printf("Receive reply : %s \n" , reply ) ;
    } else{
        printf("Server close connection!\n");
        exit(1);
    }

    close(sd) ;
    return 0 ;

}
