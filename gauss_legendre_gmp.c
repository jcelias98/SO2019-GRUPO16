#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

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
    mpf_t rop;
    mpf_init(rop); 
    mpf_t rop2;
    mpf_init(rop2);
    for(i = 0; i < iterations; i++){
        //a_next = (a + b)/2;
        mpf_add(rop, a, b);
        mpf_div_ui(a_next, rop, 2);

        //b_next = sqrt(a * b);
        mpf_mul(rop2, a, b);
        mpf_sqrt (b_next, rop2);

        //aux = a - a_next; //evita o uso de pow(a, 2)
        mpf_sub(aux, a, a_next);

        //t_next = t - p * aux * aux;
        mpf_pow_ui(aux, aux, 2);
        mpf_mul(aux, aux, p);
        mpf_sub(t_next, t, aux);
         
        //atualização das variáveis
        //p = 2 * p;
        mpf_mul_ui(p, p, 2);
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
    
    //mpf_out_str(stdout, 10, 7, aux);

    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
    mpf_clear (a_next);
    mpf_clear (b_next);
    mpf_clear (t_next);
    mpf_clear(aux);
    mpf_clear(rop);
    mpf_clear(rop2);


}
int main() {
	mpf_t pi;
	mpf_init(pi);
	pi_legendre(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}