#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <pthread.h>

struct parametros_a {
   mpf_t *a;
   mpf_t *b;
   mpf_t *a_next;
};

struct parametros_b {
   mpf_t *a;
   mpf_t *b;
   mpf_t *b_next;
};

void* calcula_a_next(void* arg_a) {
    //mpf_t a, b, *a_next;
    struct parametros_a *my_data;
    my_data =  (struct parametros_a *) arg_a;
    mpf_add(*(my_data->a_next), *(my_data->a), *(my_data->b));
    mpf_div_ui(*(my_data->a_next), *(my_data->a_next), 2);
    pthread_exit(NULL);
}

void* calcula_b_next(void* arg_b) {
    struct parametros_b *my_data;
    my_data =  (struct parametros_b *) arg_b;
    mpf_mul(*(my_data->b_next), *(my_data->a), *(my_data->b));
    mpf_sqrt (*(my_data->b_next), *(my_data->b_next));
    pthread_exit(NULL);
}

void calcula_t_next(mpf_t a, mpf_t a_next, mpf_t t, mpf_t *t_next, mpf_t *p, mpf_t aux) {
    //aux = a - a_next; //evita o uso de pow(a, 2)
    mpf_sub(aux, a, a_next);
    //t_next = t - p * aux * aux;
    mpf_pow_ui(aux, aux, 2);
    mpf_mul(aux, aux, *p);
    mpf_sub(*t_next, t, aux);
    //p = 2 * p;
    mpf_mul_ui(*p, *p, 2);
}
//Calcula numericamente o valor de PI
void pi_legendre(int iterations, mpf_t*pi){
    //inicializações
    mpf_set_default_prec (pow(10, 5));

    //double a = 1;
    mpf_t a;
    mpf_init_set_d(a, 1.0);
    //double b = sqrt(2)/2;
    double raiz = sqrt(0.5);
    mpf_t b;
    mpf_init_set_d(b, raiz);
    //double t = 0.25;
    mpf_t t;
    mpf_init_set_d(t, 0.25);
    //double p = 1;
    mpf_t p;
    mpf_init_set_d(p, 1.0);

    //double a_next, b_next, t_next, aux;
    mpf_t a_next, b_next, t_next, aux;
    mpf_init(a_next);
    mpf_init(b_next);
    mpf_init(t_next);
    mpf_init(aux);
    
    int i;
    for(i = 0; i < iterations; i++){
        //a_next = (a + b)/2;
        struct parametros_a obj1;
  
        pthread_t id1;
        obj1.a=&a;
        obj1.b=&b;
        obj1.a_next= &a_next;
        pthread_create(&id1, NULL, calcula_a_next, &obj1);

        struct parametros_b obj2;
        pthread_t id2;
        obj2.a=&a;
        obj2.b=&b;
        obj2.b_next=&b_next;
        pthread_create(&id2, NULL, calcula_b_next, &obj2);

        pthread_join(id1,NULL);
        pthread_join(id2,NULL);

        calcula_t_next(a, a_next, t, &t_next, &p, aux); 
        
        //a = a_next;
        mpf_set(a, a_next);
        //b = b_next;
        mpf_set(b, b_next);
        //t = t_next;
        mpf_set(t, t_next);
    }
    //aux = (a + b)/2; //evita o uso de pow(a, 2)
    mpf_add(aux, a, b);
    mpf_div_ui(aux, aux, 2);
    mpf_mul(aux, aux, aux);
    mpf_div(*pi, aux, t);
    
}
int main() {
    mpf_t pi;
    mpf_init(pi);
    pi_legendre(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}