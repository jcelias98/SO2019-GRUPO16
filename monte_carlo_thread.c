#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define NUMTHREADS 4
#define ITERATIONS 100000000
#define RANDOM_MAX 	(0x80000000 - 1)	

typedef int numero_randomico;

//Gera o proximo numero pseudo-aleatorio e atualiza a variavel r
numero_randomico randomize(numero_randomico* r){
	return *r = (1103515245*(*r)+ 12345) % 0x80000000;
}

void* monte_carlo_thread(void* acertos_void) {
	numero_randomico r;
	int *acertos;
	int i;
	double x;
	double y;

    acertos = (int*)acertos_void;
    *acertos = 0;
    
    r = rand();	

	for (i = 0; i < ITERATIONS/NUMTHREADS; i++)
	{
		x = (double) randomize(&r)/RANDOM_MAX;
		y = (double) randomize(&r)/RANDOM_MAX;
		if(x*x+y*y < 1) {
			*acertos += 1;
		}
	}
	pthread_exit(NULL);
}

void pi_monteCarlo(int iterations, mpf_t *pi) {
	srand(time(NULL));
	int i, acertos_total = 0;
	double x, y;
	mpf_t aux;
	mpf_init(aux);
	pthread_t id_threads[NUMTHREADS];
	int acertos[NUMTHREADS];

	//Cria as threads
	for(i = 0; i < NUMTHREADS; i++) {
		pthread_create(&id_threads[i], NULL, monte_carlo_thread, &acertos[i]);
	}
	
	//Aguardar o fim da execucao das threads
	for(i = 0; i < NUMTHREADS; i++) {
		pthread_join(id_threads[i], NULL);
	}

	for(i = 0; i < NUMTHREADS; i++) {
		acertos_total += acertos[i];
	}

	//pi = 4.0*acertos/iterations;
	mpf_set_d(aux, acertos_total);
	mpf_mul_ui(aux, aux, 4.0);
	mpf_div_ui(*pi, aux, ITERATIONS);
	mpf_clear(aux);
	
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));
    mpf_t pi;
    mpf_init(pi);
    
    pi_monteCarlo(ITERATIONS, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);

	return 0;
}