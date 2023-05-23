#include <iostream>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_10 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_50 = PTHREAD_COND_INITIALIZER;

void* second(void*) {

    pthread_mutex_lock(&mutex);

    pthread_cond_wait(&cond_10, &mutex);
    std::cout << ">10" << std::endl;

    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond_50, &mutex);

    std::cout << ">50" << std::endl;
    pthread_mutex_unlock(&mutex);

    return NULL;

}

int main() {
    pthread_t other_thread;
    pthread_create(&other_thread, NULL, second, NULL);

    int input_char;
    while (std::cin >> input_char) {
        count++;

        if (count > 10) {
            pthread_cond_signal(&cond_10);
        }

        if (count > 50) {
            pthread_cond_signal(&cond_50);
        }

    }
                                      

    pthread_join(other_thread, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_10);
    pthread_cond_destroy(&cond_50);

    return 0;
}
             
