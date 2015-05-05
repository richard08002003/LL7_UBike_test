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

    fp1 = fopen(  "/home/root/LL7_Test/Log/Repeat_data_Test.log" , "a+" ) ;
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
        perror("socket") ;
        fprintf( fp1 , "%s" , "Create Socket Failed ! \n" ) ;
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
        fprintf( fp1 , "%s" , "Connect Failed ! \n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1) ;
    }

    int snd , rcv ;
    char reply[4000] = {0} ;

    //data1
    char data1[] = "{\"Function\":\"L7Show\",\"Number\":\"0\",\"Number\":\"1\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data1_len = strlen(data1) ;
    char buf1 [ 11 + (int)data1_len + 1 ] ;
    memset( buf1 , 0 , sizeof(buf1) ) ;
    snprintf( buf1 , sizeof(buf1) ,"<S>%08X" , data1_len ) ;
    strncat( buf1 , data1 , sizeof(buf1) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf1) ;
    fflush(fp1) ;
    snd = send( sd , buf1 , sizeof(buf1) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data1 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    //data2
    char data2[] = "{\"Function\":\"L7Show\",\"Number\":\"2\",\"Number\":\"3\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data2_len = strlen(data2) ;
    char buf2 [ 11 + (int)data2_len + 1 ] ;
    memset( buf2 , 0 , sizeof(buf2) ) ;
    snprintf( buf2 , sizeof(buf2) ,"<S>%08X" , data2_len ) ;
    strncat( buf2 , data2 , sizeof(buf2) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf2 ) ;
    fflush(fp1) ;
    snd = send( sd , buf2 , sizeof(buf2) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data2 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    //data3
    char data3[] = "{\"Function\":\"L7Show\",\"Number\":\"4\",\"Number\":\"5\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data3_len = strlen(data3) ;
    char buf3 [ 11 + (int)data3_len + 1 ] ;
    memset( buf3 , 0 , sizeof(buf3) ) ;
    snprintf( buf3 , sizeof(buf3) ,"<S>%08X" , data3_len ) ;
    strncat( buf3 , data3 , sizeof(buf3) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf3 ) ;
    fflush(fp1) ;
    snd = send( sd , buf3 , sizeof(buf3) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data3 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    //data4
    char data4[] = "{\"Function\":\"L7Show\",\"Number\":\"6\",\"Number\":\"7\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data4_len = strlen(data4) ;
    char buf4 [ 11 + (int)data4_len + 1 ] ;
    memset( buf4 , 0 , sizeof(buf4) ) ;
    snprintf( buf4 , sizeof(buf4) ,"<S>%08X" , data4_len ) ;
    strncat( buf4 , data4 , sizeof(buf4) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf4 ) ;
    fflush(fp1) ;
    snd = send( sd , buf4 , sizeof(buf4) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data4 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    //data5
    char data5[] = "{\"Function\":\"L7Show\",\"Number\":\"8\",\"Number\":\"9\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data5_len = strlen(data5) ;
    char buf5 [ 11 + (int)data5_len + 1 ] ;
    memset( buf5 , 0 , sizeof(buf5) ) ;
    snprintf( buf5 , sizeof(buf5) ,"<S>%08X" , data5_len ) ;
    strncat( buf5 , data5 , sizeof(buf5) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf5 ) ;
    fflush(fp1) ;
    snd = send( sd , buf5 , sizeof(buf5) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data5 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    //data 6 : ERROR DATA
    char data6[] = "{\"Function\":\"L7Show\",\"Number\":\"10\",\"Number\":\"11\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int data6_len = strlen(data6) ;
    char buf6 [ 11 + (int)data6_len + 1 ] ;
    memset( buf6 , 0 , sizeof(buf6) ) ;
    snprintf( buf6 , sizeof(buf6) ,"<S>%08X" , data6_len ) ;
    strncat( buf6 , data6 , sizeof(buf6) ) ;

    fprintf( fp1 , "Send data : %s\n" , buf6 ) ;
    fflush(fp1) ;
    snd = send( sd , buf6 , sizeof(buf6) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send data6 Failed ! <Sf>\n" ) ;
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
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        exit(1);
    }

    fclose(fp1) ;
    close(sd) ;
    return 0 ;
}
