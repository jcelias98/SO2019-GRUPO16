# SO2019-GRUPO16: Cálculo Aproximado de pi e algoritmo Black Scholes com programação sequencial e paralela
Neste trabalho, são apresentadas as implementações de três algoritmos para estimar o número pi. Os algoritmos da literatura: Gauss-Legendre, Borwein e Monte Carlo serão comparados em termos de tempo de execução e precisão com relação à suas implementações sequencial e paralela.
Em seguida serão discutidos os resultados para os valores do algoritmo de Black Scholes sequencial e paralelo, utilizado para determinar o preço de derivativos de ações no mercado financeiro.

## Forma de compilação:

Para os algoritmos que estimam pi(Gauss Legendre, Borwein e Monte Carlo):

### Implementação Sequencial
```
gcc nome_programa.c -o nome_programa -lm -lgmp 
```
Método de execução para que o valor de pi seja printado no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./nomedoprograma < entrada_pi.txt > saida_pi.txt
```
### Implementação Paralela
```
gcc nome_programa.c -o nome_programa -lm -lgmp -lpthread
```
Forma de execução normal:
```
./nome_programa
```
Método de execução para que a saída seja printada no arquivo saida.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./nomedoprograma < entrada.txt > saida.txt
```
### Black Scholes Sequencial
```
gcc black_scholes.c -o black_scholes -lm 
```
Método de execução para que o valores sejam printados no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./black_scholes < entrada_blackscholes.txt > saida_blackscholes.txt
```
### Black Scholes Paralelo
```
gcc black_scholes_pthread.c -o black_scholes_pthread -lm 
```
Método de execução para que o valores sejam printados no arquivo saida_pi.txt e o tempo de execução seja printado:
```
/usr/bin/time -f "%e" ./black_scholes_pthread < entrada_blackscholes.txt > saida_blackscholes.txt
```
