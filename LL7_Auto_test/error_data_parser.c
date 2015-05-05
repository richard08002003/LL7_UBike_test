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
    fp2 = fopen( "/home/root/LL7_Test/Log/Error_Data_Test.log" , "r" ) ;
    if ( fp2 == NULL ) {
        printf("檔案開啟失敗！\n") ;
        exit(1) ;
    }

    int Ss = 0  , Sf = 0 , Rs = 0 , Rf = 0 , Rtn = 0 ;
    fprintf( fp1 , "%s" , "Api_test Parser . . .\n" ) ;
    fflush(fp1) ;
    unsigned char str[200] = {0} ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Send Success mark parser : <Ss>
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "<Ss>") )  {
                Ss++ ;
                fprintf( fp1 ,  "%s" , "Ss : " ) ;
                fflush(fp1) ;
                fprintf( fp1 , "%d\n"  , Ss ) ;
                fflush(fp1) ;
            }
    }
    fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Send Fail mark parser : <Sf>
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "<Sf>") )  {
                Sf++ ;
                fprintf( fp1 , "%s" , "Sf : " ) ;
                fflush(fp1) ;
                fprintf( fp1 ,"%d\n"  , Sf ) ;
                fflush(fp1) ;
            }
    }
    fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Receive Success mark parser : <Rs>
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "<Rs>") )  {
                Rs++ ;
                fprintf( fp1 , "%s" , "Rs : " ) ;
                fflush(fp1) ;
                fprintf( fp1 , "%d\n"  , Rs ) ;
                fflush(fp1) ;
            }
    }
    fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //Receive Fail mark parser : <Rf>
    while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "<Rf>") )  {
                Rf++ ;
                fprintf( fp1 , "%s" , "Rf : " ) ;
                fflush(fp1) ;
                fprintf( fp1 , "%d\n"  , Rf ) ;
                fflush(fp1) ;
            }
    }
    fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;
    fseek( fp2 , 0 , SEEK_SET ) ;
    //RtnCode : 9000 Api Success
     while( fgets( str , sizeof(str) , fp2 ) != NULL )
    {
            if ( strstr(str , "9000") )  {
                Rtn++ ;
                fprintf( fp1 , "%s" , "Rtn : " ) ;
                fflush(fp1) ;
                fprintf( fp1 , "%d\n"  , Rtn ) ;
                fflush(fp1) ;
            }
    }
    fprintf(fp1 , "%c" , '\n' ) ;
    fflush(fp1) ;


      if ( Ss == 12 ) {
            if ( Rs == 12 ) {
                if ( Rtn == 0 ) {
                    printf("RtnCode 9000 times : %d\n" , Rtn ) ;
                    fprintf( fp1 , "%s" , "RtnCode 9000 times :") ;
                    fflush(fp1) ;
                    fprintf( fp1 , "%d\n" , Rtn ) ;
                    fflush(fp1) ;
                    printf("<<< Error Data Test Success >>> \n") ;
                    printf("-------------------------------\n") ;
                    fprintf( fp1 , "%s" , "<<< Error Data Test Success >>> \n" ) ;
                    fflush(fp1) ;
                }
            }
        } else {
        printf("Send Succes times : %d\n" , Ss ) ;
        fprintf( fp1 , "%s" , "Send Success times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , Ss ) ;
        fflush(fp1) ;

        printf("Send Failed times : %d\n" , Sf ) ;
        fprintf( fp1 , "%s" , "Send Failed times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , Sf ) ;
        fflush(fp1) ;

        printf("Receive Succes times : %d\n" , Rs ) ;
        fprintf( fp1 , "%s" , "Receive Success times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , Rs ) ;
        fflush(fp1) ;

        printf("Receive Failed times : %d\n" , Rf ) ;
        fprintf( fp1 , "%s" , "Receive Failed times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , Rf ) ;
        fflush(fp1) ;

        printf("RtnCode 9000 times : %d\n" , Rtn ) ;
        fprintf( fp1 , "%s" , "RtnCode 9000 Failed times :") ;
        fflush(fp1) ;
        fprintf( fp1 , "%d\n" , Rtn ) ;
        fflush(fp1) ;

        printf("<<< Error Data Test Failed >>> \n") ;
        printf("-------------------------------\n") ;
        fprintf( fp1 , "%s" , "<<< Error Data Test Failed >>> \n" ) ;
        fflush(fp1) ;
    }
    fprintf(fp1 , "%s" , "---------------------------------------\n" ) ;
    fflush(fp1) ;


fclose(fp1) ;
fclose(fp2) ;
return 0 ;
}

