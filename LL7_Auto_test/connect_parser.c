#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *fp1 , *fp2 ;
int main()
{
    time_t t1 = time(NULL) ;
    struct tm *nPtr = localtime(&t1) ;
    int year = nPtr->tm_year + 1900 ;
    int month = nPtr->tm_mon + 1 ;
    int mday = nPtr->tm_mday ;
    char Log_name[20] = {0} ;
    sprintf( Log_name , "%04u_%02u_%02u" , year , month , mday ) ;
    char log[]  = ".log" ;
    strcat( Log_name , log ) ;

    fp1 = fopen( Log_name , "a+") ;
    if ( fp1 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1);
    }

    fp2 = fopen( "/home/root/LL7_Test/Log/Connect_Test.log" , "r" ) ;
    //fp2 = fopen( "/home/richard/Richard/UBike_LL7_test/LL7_Auto_test/Log/Connect_Test.log" , "r" ) ;
    if ( fp2 == NULL ) {
            printf("Connect_Test.log檔案開啟失敗！\n") ;
            exit(1) ;
    }
    int cs = 0  , cf = 0 ;
    char str[200] = {0}  ;
    fprintf( fp1 , "%s" , "Connect_Log Parser . . .\n" ) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Connect Success mark parser : Connect
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
        if ( strstr(str , "Connect") )  {
            cs++ ;
            fprintf( fp1 ,  "%s" , "Connect : " ) ;
            fflush(fp1) ;
            fprintf( fp1 , "%d\n"  , cs ) ;
            fflush(fp1) ;
        }
    }
     fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Connect Fail mark parser : Fail
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "Fail") )  {
                cf++ ;
                fprintf( fp1 , "%s" , "Fail: " ) ;
                fflush(fp1) ;
                fprintf( fp1 ,"%d\n"  , cf ) ;
                fflush(fp1) ;
            }
    }
    fprintf( fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;

    if ( cf == 0 ) {
        if ( cs == 10 ) {
            printf("Success times : %d\n" , cs ) ;
            fprintf( fp1 , "%s" , "Success times :") ;
            fflush(fp1) ;
            fprintf( fp1 , "%d\n" , cs ) ;
            fflush(fp1) ;
            printf("<<< Connect Test Success >>> \n") ;
            printf("-------------------------------\n") ;
            fprintf( fp1 , "%s" , "<<< Connect Test Success >>> \n" ) ;
            fflush(fp1) ;
        }
    } else {
        printf("Succes times : %d\n" , cs ) ;
        fprintf( fp1 , "%s" , "Success times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , cs ) ;
        fflush(fp1) ;

        printf("Failed times : %d\n" , cf ) ;
        fprintf( fp1 , "%s" , "Failed times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , cf ) ;
        fflush(fp1) ;

        printf("<<< Connect Test Failed >>> \n") ;
        printf("-------------------------------\n") ;
        fprintf( fp1 , "%s" , "<<< Connect Test Failed >>> \n" ) ;
        fflush(fp1) ;
    }

    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;

    fclose(fp1) ;
    fclose(fp2) ;
    return 0 ;
}
