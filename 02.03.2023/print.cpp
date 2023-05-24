#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>



int main(){

	const char* file_name = "key.txt";
	key_t key = ftok(file_name, 'K');
	
       	if (key == -1) {

                std::cerr << "Failed to generate key "<< strerror(errno)<<std::endl;
        return 1;
    }

	auto shmid = shmget(key, 1024, 0);
	
       	if (shmid == -1) {
       
	       	std::cerr << "Failed to get shared memory "<< strerror(errno)<<std::endl;
        return 1;
    }

    auto *shared_memory = shmat(shmid, nullptr, 0666);

    if (shared_memory ==  reinterpret_cast<void*>(-1)) {
        
	    std::cerr << "Failed to attach shared memory "<< strerror(errno)<<std::endl;


	    return 1;

    }

    while (true) {
    

	    std::cout << "Shared memory content" << static_cast<char*>(shared_memory) << std::endl;
        sleep(5);

    }

    
    return 0;
}


