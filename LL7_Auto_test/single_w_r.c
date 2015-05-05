#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#define SOCK_PATH "/usr/local/UBike/ipc/LL7_UBike.ipc"
FILE *fp1 ;
int main(void)
{
    time_t t1 = time(NULL) ;
    struct tm *nPtr = localtime(&t1) ;
    int year = nPtr->tm_year + 1900 ;
    int month = nPtr->tm_mon + 1 ;
    int mday = nPtr->tm_mday ;

    fp1 = fopen(  "/home/root/LL7_Test/Log/Write_Read_Test.log" , "a+" ) ;
    if ( fp1 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1) ;
    }

    char *now = asctime(nPtr) ;
    fprintf( fp1 , "%s" , "<=======================================>\n") ;
    fflush(fp1) ;
    fprintf( fp1 , "%s" , now ) ;
    fflush(fp1) ;

    struct sockaddr_un client ;
    //Socket()
    int sd = socket( AF_UNIX , SOCK_STREAM , 0 ) ;
    if( sd < 0 ) {
        perror("socket") ;
        fprintf( fp1 , "%s" , "Create Socket Failed !\n") ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    }
    client.sun_family = AF_UNIX ;
    strcpy( client.sun_path , SOCK_PATH ) ;

    //Connect()
    int con = connect( sd , (struct sockaddr *)&client , sizeof(client) ) ;
    if ( con < 0 ) {
        perror("connect") ;
        fprintf( fp1 , "%s" , "Connect Failed !\n") ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    }

    int snd , rcv ;
    char reply[4000] = {0} ;
    // 傳送正確格式的資料
    char data1[] = "{\"Function\":\"SelfTest\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data1_len = strlen(data1) ;
    char buf [ 11 + (int)data1_len + 1 ] ;
    memset( buf , 0 , sizeof(buf) ) ;
    snprintf( buf , sizeof(buf) ,"<S>%08X" , data1_len ) ;
    strncat( buf , data1 , sizeof(buf) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf ) ;
    fflush(fp1) ;
    snd = send( sd , buf , sizeof(buf) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send Failed ! <Sf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;

    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection ! \n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }


    fclose(fp1) ;
    close(sd) ;
    return 0 ;

}
