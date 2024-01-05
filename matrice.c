#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 10

int n1 = 3, m1 = 3;  // Dimensions de la matrice B
int n2 = 3, m2 = 3;  // Dimensions de la matrice C

int B[3][3];         // Matrice B
int C[3][3];         // Matrice C
int A[3][3];         // Matrice résultante A
int T[3];            // Tampon T

pthread_barrier_t barrier;

void *producer(void *arg) {
    int row = *((int *)arg);

    for (int j = 0; j < m2; ++j) {
        int result = 0;
        for (int k = 0; k < m1; ++k) {
            result += B[row][k] * C[k][j];
        }

        // Stocker le résultat dans le tampon T
        T[j] = result;

        // Attendre les autres producteurs avant la mise à jour de la matrice A
        pthread_barrier_wait(&barrier);

        // Mettre à jour la matrice résultante A
        A[row][j] = T[j];
    }

    pthread_exit(NULL);
}

int main() {
    // Initialiser les matrices B et C avec des valeurs aléatoires
    // ...

    pthread_t producer_threads[MAX_THREADS];
    int thread_args[MAX_THREADS];

    pthread_barrier_init(&barrier, NULL, m2);

    // Créer les threads producteurs
    for (int i = 0; i < n1; ++i) {
        thread_args[i] = i;
        pthread_create(&producer_threads[i], NULL, producer, (void *)&thread_args[i]);
    }

    // Attendre la fin des threads producteurs
    for (int i = 0; i < n1; ++i) {
        pthread_join(producer_threads[i], NULL);
    }

    // Afficher la matrice résultante A
    printf("Matrice résultante A :\n");
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
