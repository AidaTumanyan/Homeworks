#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <cerrno>

int main(){

	const char* file_name = "key.txt";
        const int size = 1024;
	

	int fd = open(file_name, O_CREAT | O_RDWR, 0666);

	if(fd == -1){


		std::cerr<< "failed to creat file"<<strerror(errno);

		return 1;

	}


	key_t key = ftok(file_name, 'K');

	if(key == -1){

		std::cerr<< "failed to generate key"<<strerror(errno);

		return 1;

	}

	int shmid = shmget(key, size, 0666 | IPC_CREAT | IPC_EXCL);
	void* s = shmat(shmid, NULL, 0);

	if(shmid == -1){

                std::cerr<< "failed to creat shared memory"<<strerror(errno);

                return 1;

        }

	std::cout<<"Shared memory initialized";



	

	}
