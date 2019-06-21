#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
 
//Calcula numericamente o valor de PI
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
    double aux4;  
    mpf_t y_aux2, num, den, a_aux2, a_aux3;
    mpf_init(y_aux2);
    mpf_init(a_aux2);
    mpf_init(a_aux3);
    mpf_init(num);
    mpf_init(den);

    for(i = 0; i < iterations; i++){
        //calcula as constantes da iteração i
        //y_next = (1-pow((1-pow(y,4)),0.25))/(1+pow((1-pow(y,4)),0.25));
        mpf_pow_ui(y_aux2, y, 4);
        mpf_ui_sub (y_aux2, 1, y_aux2);
        mpf_sqrt(y_aux2, y_aux2);
        mpf_sqrt(y_aux2, y_aux2);
        mpf_ui_sub (num, 1, y_aux2);
        mpf_add_ui(den, y_aux2, 1);
        mpf_div(y_next, num, den);
        //a_next = a*pow((1+y_next),4)-pow(2,(2*i+3))*y_next*(1+y_next+y_next*y_next);
        mpf_add_ui(a_aux2, y_next, 1);
        mpf_pow_ui(a_aux2, a_aux2, 4);
        mpf_mul(a_aux2, a, a_aux2);
        aux4 = pow(2,(2*i+3));
        mpf_pow_ui(a_aux3, y_next, 2);
        mpf_add_ui(a_aux3, a_aux3, 1);
        mpf_add(a_aux3, a_aux3, y_next);
        mpf_mul(a_aux3, a_aux3, y_next);
        mpf_mul_ui(a_aux3, a_aux3, aux4);
        mpf_sub(a_next, a_aux2, a_aux3);

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
    mpf_clear(y_aux2);
    mpf_clear(num);
    mpf_clear(den);
    mpf_clear(a_aux2);
    mpf_clear(a_aux3);

}
int main() {
    mpf_t pi;
    mpf_init(pi);
    pi_borwein(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}