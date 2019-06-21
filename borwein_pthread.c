#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>
#include <semaphore.h>


sem_t buffer_full, buffer_empty;
pthread_mutex_t mutex;

struct parametros_y {
   mpf_t *y;
   mpf_t *y_next;
};

struct parametros_a {
   mpf_t *a;
   mpf_t *y_next;
   int *i;
   mpf_t *a_next;
};

//calcula_y_next é o produtor
void* calcula_y_next (void *arg_y) {
    mpf_t y_aux2, num, den;
    struct parametros_y *my_data;
    my_data =  (struct parametros_y *) arg_y;
    mpf_init(y_aux2);
    mpf_init(num);
    mpf_init(den);
   
    //y_next = (1-pow((1-pow(y,4)),0.25))/(1+pow((1-pow(y,4)),0.25));
      
    mpf_pow_ui(y_aux2, *(my_data->y), 4);
    mpf_ui_sub (y_aux2, 1, y_aux2);
    mpf_sqrt(y_aux2, y_aux2);
    mpf_sqrt(y_aux2, y_aux2);
    mpf_ui_sub (num, 1, y_aux2);
    mpf_add_ui(den, y_aux2, 1);
    sem_wait(&buffer_full);
    //pthread_mutex_lock e pthread_mutex_unlock protegem o acesso de y_next à região crítica
    pthread_mutex_lock(&mutex); 
    mpf_div(*(my_data->y_next), num, den);
    pthread_mutex_unlock(&mutex); 
    sem_post(&buffer_empty);

    mpf_clear(y_aux2);
    mpf_clear(num);
    mpf_clear(den);

    pthread_exit(NULL);
}

//calcula_a_next é o consumidor
void* calcula_a_next (void *arg_a) {
    double aux4;  
    mpf_t a_aux2, a_aux3;
    
    struct parametros_a *my_data;
    my_data =  (struct parametros_a *) arg_a;
    mpf_init(a_aux2);
    mpf_init(a_aux3);
    //a_next = a*pow((1+y_next),4)    -     pow(2,(2*i+3))*y_next*(1+y_next+y_next*y_next);

    mpf_t ynext;
    mpf_init(ynext);
    sem_wait(&buffer_empty);
    pthread_mutex_lock(&mutex); 
    mpf_set(ynext, *(my_data->y_next));
    pthread_mutex_unlock(&mutex);
    sem_post(&buffer_full);
              
    
    mpf_add_ui(a_aux2,ynext , 1);
    mpf_pow_ui(a_aux2, a_aux2, 4);
    mpf_mul(a_aux2, *(my_data->a), a_aux2);
    aux4 = pow(2,(2* (*(my_data->i))+3));
    mpf_pow_ui(a_aux3, ynext, 2);
    mpf_add_ui(a_aux3, a_aux3, 1);
    mpf_add(a_aux3, a_aux3, ynext);
    mpf_mul(a_aux3, a_aux3, ynext);
    mpf_mul_ui(a_aux3, a_aux3, aux4);
    mpf_sub(*(my_data->a_next), a_aux2, a_aux3);
    mpf_clear(a_aux2);
    mpf_clear(a_aux3);

    pthread_exit(NULL);
}

 
void pi_borwein(int iterations, mpf_t *pi) {
    //inicializações
    mpf_set_default_prec (pow(10, 5));

    //double a = 6-4*sqrt(2);
    double a_aux = 6-4*sqrt(2);
    mpf_t a;
    mpf_init_set_d(a, a_aux);

    //double y = sqrt(2)-1;
    double y_aux = sqrt(2)-1;
    mpf_t y;
    mpf_init_set_d(y, y_aux);

    //double a_next, y_next; 
    mpf_t a_next, y_next;
    mpf_init(a_next);
    mpf_init(y_next);
     
    int i;
    //double aux4;  
    //mpf_t y_aux2, num, den, a_aux2, a_aux3;
    //mpf_init(y_aux2);
    //mpf_init(a_aux2);
    //mpf_init(a_aux3);
    //mpf_init(num);
    //mpf_init(den);
    struct parametros_y obj1;
    struct parametros_a obj2;
    pthread_t id1;
    pthread_t id2;

    sem_init(&buffer_full, 0, 1);
    sem_init(&buffer_empty, 0, 0); 
    pthread_mutex_init (&mutex,NULL);
 
    obj1.y=&y;
    obj1.y_next=&y_next;
    obj2.a=&a;
    obj2.y_next=&y_next;
    obj2.i=&i;
    obj2.a_next=&a_next;
 

    for(i = 0; i < iterations; i++){
        //printf("Iteração: %d\n", i);
 
        //Cria as threads
        //y_next = (1-pow((1-pow(y,4)),0.25))/(1+pow((1-pow(y,4)),0.25));
        //printf("hola");

        pthread_create(&id1, NULL, calcula_y_next, &obj1);
        //a_next = a*pow((1+y_next),4)-pow(2,(2*i+3))*y_next*(1+y_next+y_next*y_next);

        pthread_create(&id2, NULL, calcula_a_next, &obj2);

        //Aguardar o fim da execucao das threads
	    pthread_join(id1, NULL);
	    pthread_join(id2, NULL);
        
	    //a = a_next;
        mpf_set(a, a_next);
        //y = y_next;
        mpf_set(y, y_next);
    }

    mpf_ui_div(*pi, 1, a);

    mpf_clear(a);
    mpf_clear(y);
    mpf_clear(a_next);
    mpf_clear(y_next);

}

int main() {
    mpf_t pi;
    mpf_init(pi);
    pi_borwein(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}