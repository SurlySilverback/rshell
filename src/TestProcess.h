#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include "Command.h"

class TestProcess : public Command {

    private:

        char* flag;
        char* path;

    public:
        TestProcess(char* path) 
        {
            std::string default_flag = "-e";
            this->flag = new char;
            strcpy(this->flag, default_flag.c_str());
            this->path = path;
        }

        TestProcess(char* flag, char* path)
        {
            this->flag = flag;
            this->path = path;
        }

        bool execute()
        {
            struct stat statbuf;
            if (static_cast<std::string>(this->flag) == "-d") {
                if ( stat( path, &statbuf ) != -1 )
                {    
                    if ( S_ISDIR( statbuf.st_mode ) == true )
                    {
                        std::cout << "(True)" << std::endl;
			return true;
                    }
                    else
	            {
                        std::cout << "(False)" << std::endl;
			return false;
	            }
		}
                return false;
            }

            else if (static_cast<std::string>(this->flag) == "-f") {
                if ( stat( path, &statbuf ) != -1 )
		{
                    if ( S_ISREG( statbuf.st_mode ) == true )
	            {
                        std::cout << "(True)" << std::endl;
			return true;
	            }
                    else
		    {
	                std::cout << "(False)" << std::endl;
			return false;
		    }
		}
                return false;
	    }
            else {
                if ( stat( path, &statbuf ) != -1 )
		{
	            std::cout << "(True)" << std::endl;
		    return true;
		}
		else
		{
	            std::cout << "(False)" << std::endl;
                    return false;
		}
	    }
        }
 };
