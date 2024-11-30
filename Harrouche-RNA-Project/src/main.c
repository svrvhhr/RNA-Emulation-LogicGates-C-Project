#include "../include/rna.h"
#include "../include/utils.h"
#include <pthread.h>
#include <string.h>
#include <time.h>

pthread_mutex_t mutex; 

void *train_logic_gate(void *args);

int main() {
    srand(time(NULL));
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, train_logic_gate, "AND");
    pthread_create(&threads[1], NULL, train_logic_gate, "OR");
    pthread_create(&threads[2], NULL, train_logic_gate, "XOR");

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
