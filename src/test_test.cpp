#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int stat( const char* path, struct stat* buf );
int fstat( int fd, struct stat* buf );
int lstat( const char* path, struct stat* buf );


int main(){

    DIR *dip;
    struct dirent *dit;
    struct stat statbuf;
    std::string input_string; 	
    char* input_path;

    while (1)
    {
        std::cout << std::endl << "Input the filepath you wish to search for: ";
        getline(std::cin, input_string );
	    
        strcpy( input_path, input_string.c_str() );
        
	    if ( input_string == "exit" )
        {
	        exit(0);  
        }
         
        //std::cout << "statbuf.st_mode is: " << statbuf.st_mode << std::endl;
        
        if ( ( stat( input_path, &statbuf ) ) != -1 )
        {
            if ( S_ISREG(statbuf.st_mode) )
            {
                std::cout << "(True)";
            }
            
            else if ( S_ISDIR(statbuf.st_mode) )
            {
                std::cout << "(True)";
            }
        
            else
            {
                std::cout << "(False)";
            }
        }
 	
    }	

    return 0;
}