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

    fp1 = fopen(  "/home/root/LL7_Test/Log/Connect_Test.log" , "a+" ) ;
    //fp1 = fopen(  "/home/richard/Richard/UBike_LL7_test/LL7_Auto_test/Log/Connect_Test.log" , "a+" ) ;
    if ( fp1 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1) ;
    }

    char *now = asctime(nPtr) ;
    fprintf( fp1 , "%s" , "=======================================\n") ;
    fflush(fp1) ;
    fprintf( fp1 , "%s" , now ) ;
    fflush(fp1) ;

    struct sockaddr_un client ;
    //Socket()
    int sd = socket( AF_UNIX , SOCK_STREAM , 0 ) ;
    if( sd < 0 ) {
        fprintf( fp1 , "%s" , "Socket Create Failed ! \n") ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Socket Create ! \n") ;
        fflush(fp1) ;
    client.sun_family = AF_UNIX ;
    strcpy( client.sun_path , SOCK_PATH ) ;

    //Connect()
    int con = connect( sd , (struct sockaddr *)&client , sizeof(client) ) ;
    if ( con < 0 ) {
        fprintf( fp1 , "%s" , "Fail\n") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Connect\n") ;

    fclose(fp1) ;
    close(sd) ;
    return 0 ;

}
