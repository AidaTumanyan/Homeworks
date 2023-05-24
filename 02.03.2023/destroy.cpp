#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdio>
#include <cerrno>

int main(){

	const char* file_name = "key.txt";
	key_t key = ftok(file_name, 'K');

	if (key == -1){

		std::cerr<<"failed to generate key";

	}

	int shmid = shmget(key, 1024, 0666);

	        if (shmid  == -1){

                std::cerr<<"failed to get shared memory";

        }
 	  
	if(shmctl(shmid, IPC_RMID, NULL) == -1){

		std::cerr<<"failed to mark for deletion";


	}

	else{

		std::cout<<"marked for deletion";

	}


	remove("key.txt");

}





