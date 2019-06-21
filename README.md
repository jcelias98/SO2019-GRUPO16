# SO2019-GRUPO16
Cálculo Aproximado de pi e do algoritmo Black Scholes com programação sequencial paralela
Forma de compilação:
Para os algoritmos que estimam pi(Gauss Legendre, Borwein e Monte Carlo):
-
```
gcc nome_programa.c -o nome_programa -lm -lgmp -lpthread
```
Método de execução normal:
```
./nome_programa
```

Método de execução para que a saída seja printada no arquivo saida.txt.
```
./nome_programa<entrada_pi.txt>saida_pi.txt
