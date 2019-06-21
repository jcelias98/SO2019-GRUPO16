# SO2019-GRUPO16
Cálculo Aproximado de pi e do algoritmo Black Scholes com programação sequencial paralela.

Forma de compilação:

Para os algoritmos que estimam pi(Gauss Legendre, Borwein e Monte Carlo):

Implementação Sequencial
```
gcc nome_programa.c -o nome_programa -lm -lgmp 
```
Forma de execução normal:
```
./nome_programa
```
Método de execução para que a saída seja printada no arquivo saida.txt e o tempo de execução seja calculado.
```
/usr/bin/time -f "%e" ./nomedoprograma < entrada.txt > saida.txt


Implementação Paralela
```
gcc nome_programa.c -o nome_programa -lm -lgmp -lpthread
```
Forma de execução normal:
```
./nome_programa
```
Método de execução para que a saída seja printada no arquivo saida.txt e o tempo de execução seja calculado.
```
/usr/bin/time -f "%e" ./nomedoprograma < entrada.txt > saida.txt
