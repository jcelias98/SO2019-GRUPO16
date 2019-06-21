#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define NUMTHREADS 4

struct parametros {
	double *S;
	double *E;
	double *r;
	double *o;
	double *T;
	int *M;
	double *trials;
    double *sum;
};


double sumDes (double *trials, double mean, int tamVec) {
	int i;
	double sumDes = 0;
	for (i = 0; i < tamVec; i++)
	{
		sumDes = sumDes + pow((trials[i]-mean),2);
	}
	return sumDes;
}

void* blackScholes_thread(void* argumentos) {
	struct parametros *my_data;
	my_data =  (struct parametros *) argumentos;
	
    int i;
	double t;
	double max;
	double sum=0;

    for (i = 0; i < (*(my_data->M))/NUMTHREADS; i++)
	{
        double ran = (double)(random())/(double)(RAND_MAX);
        //t = S*exp((r-1.0/2*o*o)*T + o*sqrt(T)*ran); 
		t = (*(my_data->S))*exp(((*(my_data->r))-1.0/2*(*(my_data->o))*(*(my_data->o)))*(*(my_data->T)) + (*(my_data->o))*sqrt((*(my_data->T)))*ran); 
		if(t-(*(my_data->E))>0) {
			max = t-(*(my_data->E));
		}
		else {
			max = 0;
		}
        //trials[i] = exp(-r*T)*max; 
		((my_data->trials[i])) = exp(-(*(my_data->r))*(*(my_data->T)))*max;
        sum = sum + (my_data->trials[i]);  
              
	}
    (*my_data->sum)=sum;     
	pthread_exit(NULL);
}


void blackScholes(double S, double E, double r, double o, double T, int M) {

    pthread_t id_threads[NUMTHREADS];
    struct parametros objList[NUMTHREADS];
    int i;
    double totalSum=0;
    double totalSumDes=0;
    double sum[NUMTHREADS];
	
    //Inicializar os parâmetros
    for(i = 0; i < NUMTHREADS; i++) {
    	objList[i].S=&S;
    	objList[i].E=&E;
    	objList[i].r=&r;
    	objList[i].o=&o;
    	objList[i].T=&T;
    	objList[i].M=&M;
	    //trials = (double *) malloc(M*sizeof(double)); 
        objList[i].trials = (double *) malloc(M/NUMTHREADS*sizeof(double));
        objList[i].sum=&sum[i];
    }	

    //Cria as threads
    for(i = 0; i < NUMTHREADS; i++) {
    	pthread_create(&id_threads[i], NULL, blackScholes_thread, &(objList[i]));
    }
	
    //Aguardar o fim da execucao das threads
    for(i = 0; i < NUMTHREADS; i++) {
    	pthread_join(id_threads[i], NULL);
    }
    //Calculando mean
    for(i = 0; i < NUMTHREADS; i++) {
    	totalSum = totalSum + sum[i];
    }

    double mean = totalSum/M;
 
    //Calculando stddev
    for(i = 0; i < NUMTHREADS; i++) {
    	totalSumDes = totalSumDes + sumDes (objList[i].trials, mean, M/NUMTHREADS);
    }

    double stddev = sqrt(totalSumDes/M);
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

