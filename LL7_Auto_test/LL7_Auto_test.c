/* LL7_UBike Test */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

FILE *fp1 ;
int main( int argc , char argv[ ] )
{
    time_t t1 = time(NULL) ;
    struct tm *nPtr = localtime(&t1) ;
    int year = nPtr->tm_year + 1900 ;
    int month = nPtr->tm_mon + 1 ;
    int mday = nPtr->tm_mday ;
    char Log_name[20] = {0} ;

    sprintf( Log_name , "%04u_%02u_%02u" , year , month , mday ) ;
    printf("==========%s========== \n " , Log_name ) ;

    char log[]  = ".log" ;
    strcat( Log_name , log ) ;
    fp1 = fopen( Log_name , "a+" ) ;
    if ( fp1 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1);
    }

    char *now = asctime(nPtr) ;
    printf(now) ;
    fprintf( fp1 , "%s" , "=======================================\n") ;
    fflush(fp1) ;
    fprintf( fp1 , "%s" , now ) ;
    fflush(fp1) ;


    /** 1. 開啟待測程式 */
    system("sh run_program.sh") ;
    fprintf( fp1 , "%s" , "待測程式\"LL7_UBike\"開啟成功！\n" ) ;
    fflush(fp1) ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;
    printf("%s" , "-------------------------------\n") ;
    sleep(2) ;

    /** 2. Client連線-斷線 */
    printf("<Connect Test . . . >\n") ;
    fprintf( fp1 , "%s" , "<Connect Test . . . >\n" ) ;
    fflush( fp1) ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;
    int i ;
    for ( i = 0 ; i < 10 ; i++ ) {
        system("./single_connect") ;
    }
    // 分析Log
    system("./connect_parser") ;

    /** 3. Client讀寫 */
    printf("<Correct Data Write/Read Test . . . >\n") ;
    fprintf( fp1 , "%s" , "<Correct Data Write/Read Test . . . >\n" ) ;
    fflush( fp1) ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;
    for( i = 0 ; i < 10 ; i++ ) {
        system("./single_w_r") ;
    }
     // 分析Log
    system("./write_read_parser") ;

    /** 4. Client傳輸重複資料 */
    printf("%s" , "<Repeat Data Test . . . >\n") ;
    fprintf( fp1 , "%s" , "<Repeat Data Test . . . >\n" ) ;
    fflush( fp1) ;
    system("./repeat_data") ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;

    // 分析Log
    system("./repeat_data_parser") ;

    /** 5. Api test : 7-segment led 0~9 */
    printf("%s" , "<APi Test . . . >\n" ) ;
    fprintf( fp1 , "%s" , "<APi Test . . . >\n" ) ;
    fflush( fp1) ;
    system("./Api_test") ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;

    // 分析Log
    system("./api_parser") ;

    /** 6. Error data test : */
    printf("%s" , "<Error Data Test Test . . . >\n" ) ;
    fprintf( fp1 , "%s" , "<Error Data Test Test . . . >\n" ) ;
    fflush( fp1) ;
    system("./error_data") ;
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;

    // 分析Log
    system("./error_data_parser") ;


    system("sh ./kill.sh") ;

    fclose(fp1) ;
    return 0 ;
}

