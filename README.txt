Aluno: Kamylo Serafim Porto
Matrícula: 22101934

---------------------------------------------------
  PROJETO 2 - IMPLEMENTAÇÃO ESCALONADOR PERIÓDICO 
---------------------------------------------------

- Para a implementação foi criado uma struct para cada tarefa, nela 
 são armazenadas informações sobre custo

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