Aluno: Kamylo Serafim Porto
Matrícula: 22101934

-------------------------------------------------
  PROJETO 1 - IMPLEMENTAÇÃO PRODUTOR/CONSUMIDOR  
-------------------------------------------------

Implementação do semáforo:
- A implementação foi feita de modo que, quando 
 uma thread tenta subtrair de uma variável de 
 semáforo que está zerada, essa thread recebe um 
 delay de 1 tick, e ocorre um escalonamento para 
 outra tarefa.
- Dessa forma, a thread fica bloqueada durante 
 aquele período de tick
- A função para inicializar um semáforo é 
 denominada semaphore_init(), e as funções para 
 somar e subtrair do buffer do semáforo são sem_up()
 e sem_down().

Implementação do produtor/consumidor:
- Foi decidido criar variáveis constantes para 
 facilitar a alteração de parâmetros, como o número 
 de produtores e consumidores, intervalos de espera 
 para produzir/consumir e o tempo entre essas ações.
- Além disso, foi criada uma variável chamada buffer, 
 que armazena a quantidade de "itens" que o "armazém" 
 possui.
- Outra informação importante é que os produtores 
 possuem prioridades ímpares (1, 3, 5, ...) e os 
 consumidores possuem prioridades pares maiores que 0
 (2, 4, 6, ...), fazendo com que o escalonador sempre 
 alterne entre uma thread produtora e uma consumidora.