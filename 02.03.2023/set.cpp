#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdio>
#include <cerrno>
#include <string>
#include <cstring>

int main(){

        const char* file_name = "key.txt";
        key_t key = ftok(file_name, 'K');

        if (key == -1){

                std::cerr<<"failed to generate key";

        }

        int shmid = shmget(key, 1024, 0666);

                if (shmidif (shmid == -1) {

                std::cerr << "Failed to get shared memory "<< strerror(errno)<<std::endl;
        return 1;
    }
  == -1){



                std::cerr<<"failed to get shared memory";

        }

	auto *shared_memory = shmat(shmid, NULL, 0);

	if(shared_memory == reinterpret_cast<void*>(-1)){

		std::cerr<< "failed to attach shared memory";
			return 1;


	}

	std::string input;
        std::string input_string;

 
     	std::size_t string_size = 0;
    
	while (std::cin >> input) {

        if (input == "q") {
            
		break;
        }
       
       	if (string_size >= 1024) {
       
	   	std::cout << "Not enough memory" << std::endl;
           
	       	break;
        }

        else {
        
	    	if (string_size == 0) {
            
		    	input_string += input;
               
		       	string_size += input.size();
            }

            else {

                input_string += ("." + input);
               
	       	string_size += input.size() + 1;
            }
        }
    }

    input_string += '\0';
    string_size++;

    memcpy(shared_memory, input_string.c_str(), string_size);

    std::cout << "Data written in memory" << std::endl;

    shmdt(shared_memory);

    return 0;
}

