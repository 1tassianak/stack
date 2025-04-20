#ifndef STACK_PRI_H
#define STACK_PRI_H

typedef struct PE{
    void* dados; //ponteiro para os dados genéricos que serão armazenados
    int topo; //índice do topo (posição da próxima inserção de dados)
    int tamanho_max; //capacidade máxima da pilha
    int size_data; //tamanho de cada elemento em bytes
}PE;

#endif /*STACK_PRI_H*/