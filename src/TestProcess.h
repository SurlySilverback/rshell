#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "Command.h"

class TestProcess : public Command {

    private:

        char* flag;
        char* path;

    public:

        TestProcess(char* flag, char* path)
        {
            this->flag = flag;
            this->path = path;
        }


        bool execute()
        {
            struct stat statbuf;

            switch(flag)
            {
                case "-d":
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
                break;

                case "-f":
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
		break;

		default:
		    if ( stat( path, &statbuf ) != -1 )
		    {
			std::cout << "(True)" << std::endl;
		        return true;
		    }
		    else
		    {
			std::cout << "(False)" << std::endl;
		    }
	    }
        }
};
