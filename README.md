# SO2019-GRUPO16: Cálculo Aproximado de pi e algoritmo Black Scholes com programação sequencial e paralela
Neste trabalho, são apresentadas as implementações de três algoritmos para estimar o número pi. Os algoritmos da literatura: Gauss-Legendre, Borwein e Monte Carlo serão comparados em termos de tempo de execução e precisão com relação à suas implementações sequencial e paralela.
Em seguida serão discutidos os resultados para os valores do algoritmo de Black Scholes sequencial e paralelo, utilizado para determinar o preço de derivativos de ações no mercado financeiro.

## Formas de compilação:
### Gauss-Legendre
#### Gauss-Legendre Sequencial
```
gcc gauss_legendre_gmp.c -o gauss_legendre_gmp -lm -lgmp 
```
Método de execução para que o valor de pi seja printado no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./gauss_legendre_gmp < entrada_pi.txt > saida_pi.txt
```
#### Gauss-Legendre Paralelo
```
gcc gauss_pthread.c -o gauss_pthread -lm -lgmp -lpthread
```
Método de execução para que a saída seja printada no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./gauss_pthread < entrada.txt > saida.txt
```
### Borwein
#### Borwein Sequencial
```
gcc borwein_gmp.c -o borwein_gmp -lm -lgmp 
```
Método de execução para que o valor de pi seja printado no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./borwein_gmp < entrada_pi.txt > saida_pi.txt
```
### Borwein Paralelo
```
gcc borwein_pthread.c -o borwein_pthread -lm -lgmp -lpthread
```
Método de execução para que a saída seja printada no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./borwein_pthread < entrada.txt > saida.txt
```
### Monte Carlo
#### Monte Carlo Sequencial
```
gcc monte_carlo.c -o monte_carlo -lm -lgmp 
```
Método de execução para que o valor de pi seja printado no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./monte_carlo < entrada_pi.txt > saida_pi.txt
```
### Monte Carlo Paralelo
```
gcc monte_carlo_thread.c -o monte_carlo_thread -lm -lgmp -lpthread
```
Método de execução para que a saída seja printada no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./monte_carlo_thread < entrada.txt > saida.txt
```
### Black Scholes
#### Black Scholes Sequencial
```
gcc black_scholes.c -o black_scholes -lm 
```
Método de execução para que o valores sejam printados no arquivo saida_blackscholes.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./black_scholes < entrada_blackscholes.txt > saida_blackscholes.txt
```
### Black Scholes Paralelo
```
gcc black_scholes_pthread.c -o black_scholes_pthread -lm -lpthread
```
Método de execução para que o valores sejam printados no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./black_scholes_pthread < entrada_blackscholes.txt > saida_blackscholes.txt
```
