# Lista duplamente encadeada - Histórico de Pedidos do Dia
## Guarda todos os pedidos já fechados.
## É necessário navegar para frente e para trás (consultar o pedido anterior/próximo)
## Buscar por número de pedido
## Remover um pedido cancelado no meio da lista.
## Apenas uma lista duplamente encadeada permite deslocamento nos dois sentidos com custo O(1) por passo.

# Fila encadeada simples - Fila de Preparo da Cozinha
## Os pedidos devem ser preparados na ordem de chegada (política FIFO — First In, First Out).
## O primeiro pedido feito é o primeiro a ser preparado.
## O pedido é enfileirado ao ser fechado
## e desenfileirado quando a cozinha inicia o preparo.

# Pilha encadeada simples - Pilha de Ações (Desfazer) e Pilha de Retirada
## Duas aplicações válidas — o grupo pode escolher uma ou implementar as duas:

## • Desfazer (undo):
### cada alteração no pedido em construção (adicionar item, remover item, aplicar desconto) é empilhada; "desfazer" desempilha a última ação.

## • Pilha de retirada:
### pedidos prontos são empilhados na bancada (o último que fica pronto é retirado primeiro, simulando uma bandeja em que só se pode retirar do topo).