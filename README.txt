Aluno: Kamylo Serafim Porto
Matrícula: 22101934

---------------------------------------------------
  PROJETO 2 - IMPLEMENTAÇÃO ESCALONADOR PERIÓDICO 
---------------------------------------------------

- O escalonamento periódico implementado foi EDF.	

- Foi criado uma struct para cada tarefa periódica, 
 nela são armazenadas informações sobre custo, 
 deadline e período (absolutos e dinâmicos). Essa 
 struct foi implementada na Thread Control Block, 
 pois, nesta implementação, cada thread é uma 
 tarefa periódica.

- Além disso, as informações absolutas são aquelas 
 que não são alteradas durante o escalonamento das 
 tarefas, são intrínsecas a cada tarefa. Já as 
 dinâmicas são alteradas a cada tick.

- A função OS_calculate_next_periodic_task() tem 
 como objetivo calcular a tarefa, que ainda não foi 
 concluída, com o deadline mais próximo. Ela é 
 chamada sempre antes de uma tarefa ser escalonada 
 pela OS_sched(), ou seja, ela é chamada na OS_run() 
 (por conta do primeiro escalonamento) e pela 
 SysTick_Handler() (quando uma tarefa deve ser 
 escalonada).

- Além dessas duas funções, foram realizadas alterações
 na OS_tick() e na OS_sched(). Na OS_tick foi adicionado
 o compromisso de atualizar as variáveis dinâmicas das 
 tarefas. Já na OS_sched(), as tarefas passaram a ser 
 escalonadas pelo índice da tarefa com deadline mais 
 próximo, conforme calculado e definido na 
 OS_calculate_next_periodic_task().