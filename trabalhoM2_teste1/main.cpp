#include <pthread.h>
#include <stdio.h>
#include <intrin.h>
#include<iostream>

#pragma intrinsic(__rdtsc)

#define NUM_THREADS 25
using namespace std;

int ind, j, soma = 0, mat[5][7];

void *runner(void *param);

int main(int argc, char *argv[]) {
    unsigned __int64 start, finish;

   int i, scope;   pthread_t tid[NUM_THREADS];

   pthread_attr_t attr;
   /* get the default attributes */
   pthread_attr_init(&attr);
   /* first inquire on the current scope */
   if (pthread_attr_getscope(&attr, &scope) != 0)
      fprintf(stderr, "Unable to get scheduling scope\n");
   else {
      if (scope == PTHREAD_SCOPE_PROCESS)
         printf("PTHREAD_SCOPE_PROCESS\n");
      else if (scope == PTHREAD_SCOPE_SYSTEM)
         printf("PTHREAD_SCOPE_SYSTEM\n");
      else
        fprintf(stderr, "Illegal scope value.\n");
   }
   /* set the scheduling algorithm to PCS or SCS */

   //pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

   /* create the threads */

   start = __rdtsc();

   for (i = 0; i < NUM_THREADS; i++){
      pthread_create(&tid[i],&attr,runner,NULL);
   }

   /* now join on each thread */
   for (i = 0; i < NUM_THREADS; i++) {
      pthread_join(tid[i], NULL);
   }

    finish = __rdtsc();

    printf_s("\n%I64d ticks\n", (finish-start));
}

/* Each thread will begin control in this function */
void *runner(void *param){

   for(ind = 0; ind < 5; ind++){
        for(j = 0; j < 7; j++){
            mat[ind][j] = rand() % 100;
        }
    }

    for(ind = 0; ind < 5; ind++){
        for(j = 0; j < 7; j++){
            soma += mat[ind][j];
            printf("%2d ", mat[ind][j]);
        }
        printf("\n");
    }
    printf("\n\nSoma total: %d\n\n", soma);
    printf("Olá da thread\n");
    pthread_exit(0);
}
