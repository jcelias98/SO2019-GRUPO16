#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

/*
01. monteCarloPi(n)
02. |   acertos ← 0
03. |   para i ← 0 até n
04. |   |   x ← sorteie um número real entre 0 e 1
05. |   |   y ← sorteie um número real entre 0 e 1
06. |   |   se(x * x + y * y < 1)
07. |   |   |   acertos ← acertos + 1
08. |   |   fim_se
09. |   fim_para
10. |   retorne 4 * acertos / n
11. fim_monteCarloPi
*/
void pi_monteCarlo(int iterations, mpf_t *pi) {
	int acertos = 0;
	int i;
	double x;
	double y;
	mpf_t aux;
	mpf_init(aux);

	for (i = 0; i < iterations; i++)
	{
		x = (float)(random())/(float)(RAND_MAX);
		y = (float)(random())/(float)(RAND_MAX);
		if(x*x+y*y < 1) {
			acertos = acertos + 1;
		}
	}
	//pi = 4.0*acertos/iterations;
	mpf_set_d(aux, acertos);
	mpf_mul_ui(aux, aux, 4.0);
	mpf_div_ui(*pi, aux, iterations);
	mpf_clear(aux);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    mpf_t pi;
    mpf_init(pi);


    pi_monteCarlo(100000000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);

	return 0;
}
