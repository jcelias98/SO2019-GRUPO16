#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define RANDOM_MAX 	(0x80000000 - 1)	

typedef int numero_randomico;

//Gera o proximo numero pseudo-aleatorio e atualiza a variavel r
numero_randomico randomize(numero_randomico* r){
	return *r = (1103515245*(*r)+ 12345) % 0x80000000;
}

double media (double *trials, int M) {
	int i;
	double sum = 0;
	double mean;
	for (i = 0; i < M; i++) {
		sum = sum + trials[i];
	}
	mean = sum/M;
    return mean;
}

double desvioPadrao (double *trials, double mean, int M) {
	int i;
	double sum = 0;
	double stddev;
	for (i = 0; i < M; i++)
	{
		sum = sum + pow((trials[i]-mean),2);
	}
	stddev = sqrt(sum/M);
	return stddev;
}
void blackScholes(double S, double E, double r, double o, double T, int M) {
	numero_randomico r1;
	int i;
	double t;
	double max;
	double *trials = NULL;
	trials = (double *) malloc(M*sizeof(double));
	r1 = rand();	
	for (i = 0; i <= M-1; i++)
	{
        double ran = (double) randomize(&r1)/RANDOM_MAX;
		t = S*exp((r-1.0/2*o*o)*T + o*sqrt(T)*ran); 
		if(t-E>0) {
			max = t-E;
		}
		else {
			max = 0;
		}
		trials[i] = exp(-r*T)*max;

	}
	double mean = media(trials, M);
    double stddev = desvioPadrao(trials, mean, M);
	double confwidth = 1.96*stddev/sqrt(M);
	double confmin = (mean - confwidth);
	double confmax = (mean + confwidth);
	printf("Confidence interval: (%lf, %lf)\n", confmin, confmax);
}


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	double S, E, r, o, T, M;
	scanf("%lf%lf%lf%lf%lf%lf", &S, &E, &r, &o, &T, &M);
	printf("S        %.0lf\n", S);
	printf("E        %.0lf\n", E);
	printf("r        %.0lf\n", r);
	printf("sigma    %.0lf\n", o);
	printf("T        %.0lf\n", T);
	printf("M        %.0lf\n", M);
	blackScholes(S, E, r, o, T, M);
	return 0;
}