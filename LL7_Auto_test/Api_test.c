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

    fp1 = fopen(  "/home/root/LL7_Test/Log/Api_Test.log" , "a+" ) ;
    if ( fp1 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1) ;
    }

    char *now = asctime(nPtr) ;
    fprintf( fp1 , "%s" , "-------------------------\n" ) ;
    fflush(fp1) ;
    fprintf( fp1 , "%s" , now ) ;
    fflush(fp1) ;


    struct sockaddr_un client ;
    //Socket()
    int sd = socket( AF_UNIX , SOCK_STREAM , 0 ) ;
    if( sd < 0 ) {
        perror("socket") ;
        fprintf(fp1 , "%s" , "Create Socket Failed\n") ;
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
        fprintf(fp1 , "%s" , "Connect Failed \n" ) ;
        fflush( fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
    int snd , rcv ;
    char reply[4000] = {0} ;

    //Self_Test
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
        fprintf( fp1 , "%s" , "Send data1 Failed ! <Sf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;

    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }
    // number 0
    char num0[] = "{\"Function\":\"L7Show\",\"Number\":\"0\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num0_len = strlen(num0) ;
    char buf0 [ 11 + (int)num0_len + 1 ] ;
    memset( buf0 , 0 , sizeof(buf0) ) ;
    snprintf( buf0 , sizeof(buf0) ,"<S>%08X" , num0_len ) ;
    strncat( buf0 , num0 ,sizeof(buf0) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf0 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf0 , sizeof(buf0) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number0 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send number0 Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    // number 1
    char num1[] = "{\"Function\":\"L7Show\",\"Number\":\"1\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num1_len = strlen(num1) ;
    char buf1 [ 11 + (int)num1_len + 1 ] ;
    memset( buf1 , 0 , sizeof(buf1) ) ;
    snprintf( buf1 , sizeof(buf1) ,"<S>%08X" , num1_len ) ;
    strncat( buf1 , num1 ,sizeof(buf1) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf1 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf1 , sizeof(buf1) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number1 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 2
    char num2[] = "{\"Function\":\"L7Show\",\"Number\":\"2\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num2_len = strlen(num2) ;
    char buf2 [ 11 + (int)num2_len + 1 ] ;
    memset( buf2 , 0 , sizeof(buf2) ) ;
    snprintf( buf2 , sizeof(buf2) ,"<S>%08X" , num2_len ) ;
    strncat( buf2 , num2 ,sizeof(buf2) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf2 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf2 , sizeof(buf2) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number2 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    // number 3
    char num3[] = "{\"Function\":\"L7Show\",\"Number\":\"3\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num3_len = strlen(num3) ;
    char buf3 [ 11 + (int)num3_len + 1 ] ;
    memset( buf3 , 0 , sizeof(buf3) ) ;
    snprintf( buf3 , sizeof(buf3) ,"<S>%08X" , num3_len ) ;
    strncat( buf3 , num3 ,sizeof(buf3) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf3 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf3 , sizeof(buf3) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number3 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    // number 4
      char num4[] = "{\"Function\":\"L7Show\",\"Number\":\"4\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num4_len = strlen(num4) ;
    char buf4 [ 11 + (int)num4_len + 1 ] ;
    memset( buf4 , 0 , sizeof(buf4) ) ;
    snprintf( buf4 , sizeof(buf4) ,"<S>%08X" , num4_len ) ;
    strncat( buf4 , num4 ,sizeof(buf4) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf4 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf4 , sizeof(buf4) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number4 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 5
    char num5[] = "{\"Function\":\"L7Show\",\"Number\":\"5\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num5_len = strlen(num5) ;
    char buf5 [ 11 + (int)num5_len + 1 ] ;
    memset( buf5 , 0 , sizeof(buf5) ) ;
    snprintf( buf5 , sizeof(buf5) ,"<S>%08X" , num5_len ) ;
    strncat( buf5 , num5 ,sizeof(buf5) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf5 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf5 , sizeof(buf5) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number5 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 6
    char num6[] = "{\"Function\":\"L7Show\",\"Number\":\"6\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num6_len = strlen(num6) ;
    char buf6 [ 11 + (int)num6_len + 1 ] ;
    memset( buf6 , 0 , sizeof(buf6) ) ;
    snprintf( buf6 , sizeof(buf6) ,"<S>%08X" , num6_len ) ;
    strncat( buf6 , num6 ,sizeof(buf6) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf6 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf6 , sizeof(buf6) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number6 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 7
    char num7[] = "{\"Function\":\"L7Show\",\"Number\":\"7\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num7_len = strlen(num7) ;
    char buf7 [ 11 + (int)num7_len + 1 ] ;
    memset( buf7 , 0 , sizeof(buf7) ) ;
    snprintf( buf7 , sizeof(buf7) ,"<S>%08X" , num7_len ) ;
    strncat( buf7 , num7 ,sizeof(buf7) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf7 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf7 , sizeof(buf7) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number7 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 8
    char num8[] = "{\"Function\":\"L7Show\",\"Number\":\"8\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num8_len = strlen(num8) ;
    char buf8 [ 11 + (int)num8_len + 1 ] ;
    memset( buf8 , 0 , sizeof(buf8) ) ;
    snprintf( buf8 , sizeof(buf8) ,"<S>%08X" , num8_len ) ;
    strncat( buf8 , num8 , sizeof(buf8) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf8 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf8 , sizeof(buf8) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number8 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 9
    char num9[] = "{\"Function\":\"L7Show\",\"Number\":\"9\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num9_len = strlen(num9) ;
    char buf9 [ 11 + (int)num9_len + 1 ] ;
    memset( buf9 , 0 , sizeof(buf9) ) ;
    snprintf( buf9 , sizeof(buf9) ,"<S>%08X" , num9_len ) ;
    strncat( buf9 , num9 , sizeof(buf9) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf9 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf9 , sizeof(buf9) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number9 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        printf("Server close connection!\n");
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    //number 11
    char num11[] = "{\"Function\":\"L7Show\",\"Number\":\"11\",\"TimeEnd\":\"3E8\",\"QryMd5\":\"12345678945612341234567894561234\"}" ;
    unsigned long int num11_len = strlen(num11) ;
    char buf11 [ 11 + (int)num11_len + 1 ] ;
    memset( buf11 , 0 , sizeof(buf11) ) ;
    snprintf( buf11 , sizeof(buf11) ,"<S>%08X" , num11_len ) ;
    strncat( buf11 , num11 , sizeof(buf11) ) ;
    fprintf( fp1 , "Send data : %s\n" , buf11 ) ;
    fflush(fp1) ;
    // 傳資料
    snd = send( sd , buf11 , sizeof(buf11) , 0 ) ;
    if( snd < 0 ) {
        fprintf( fp1 , "%s" , "Send number11 Failed ! <Sf>\n ") ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    }
        fprintf( fp1 , "%s" , "Send Success ! <Ss>\n") ;
        fflush(fp1) ;
    //收資料
    rcv = recv( sd , reply , sizeof(reply) , 0 ) ;
    if ( rcv < 0 ) {
        fprintf( fp1 , "%s" , "Receive reply Failed ! <Rf>\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1) ;
    } else if ( rcv > 0 ) {
        fprintf( fp1 , "Receive reply : %s <Rs>\n" , reply ) ;
        fflush(fp1) ;
    } else{
        fprintf( fp1 , "%s" , " Interrupt the connection!\n" ) ;
        fflush(fp1) ;
        fclose(fp1) ;
        close(sd) ;
        exit(1);
    }

    fclose(fp1) ;
    close(sd) ;
    return 0 ;
}
