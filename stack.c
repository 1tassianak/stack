#include "stack_pub.h"
#include "stack_pri.h"
#include <string.h> //para o memcpy

// "Construtor": aloca memória e inicializa as variáveis
int stack(ppStack pp, int size, int sizedata){
    //1 - Alocar memória para a estrutura PE
    //*pp = malloc(...) para alocar o que ele aponta (o pStack)
    *pp = malloc(sizeof(PE));

    //verificar se a alocação deu certo e não for NULL
    if (*pp == NULL) return FAIL;

    //2 - Alocar memória para os dados (void* dados)
    //como no main arg = (int*) malloc(sizeof(int)*(rlines)); já tem sizeof(int):
    (*pp)->dados = malloc(size * sizedata);
    
    //verificar a alocação para os dados genéricos
    if ((*pp)->dados == NULL) { //se for null
        free(*pp); //libera a estrutura
        return FAIL;
    }

    //3 - Acessar e inicializar os campos da estrutura
    (*pp)->topo = 0;
    (*pp)->tamanho_max = size;
    (*pp)->size_data = sizedata;

    return SUCCESS;

}

// "Destrutor": libera memória da estrutura
int unstack(ppStack pp){
    //verifica se o conteúdo de pp (a estrutura) é nulo e depois 
    //verifica se o ponteiro *pp (que aponta para a estrutura) é nulo
    if((pp == NULL || *pp == NULL)) return FAIL;

    //libera o ponteiro de dados
    free((*pp)->dados);
    //depois libera o ponteiro da estrutura
    free(*pp);

    //inicializa com NULL
    *pp = NULL;

    return SUCCESS;
}


// **** "Operações de manipulação" ****

// Empilha um elemento 
int push(pStack p, void *element){
    //1 - verifica se p é nulo e se element é nulo
    if(p == NULL || element == NULL) return FAIL;

    //2 - verifica se a pilha está cheia
    if(p->topo >= p->tamanho_max) return FAIL;

    //calcula o endereço onde o novo elemento deve ser inserido
    //usa (char *)p->dados para somar byte a byte
    void *destino = (char *)p->dados + (p->topo * p->size_data);

    //3 - copia o conteúdo de element para a pilha
    memcpy(destino, element, p->size_data);
        
    //4 - Atualizar o índice do topo
    p->topo++;

    return SUCCESS;
}

// Desempilha um elemento
int pop(pStack p, void *element){
    //1 - Verifica se a Stack está nula ou se o elemeto é nulo ou o índice topo é = 0
    if(p == NULL || element == NULL || p->topo == 0) return FAIL;

    //2 - diminui o índice de p->topo para acessar o elemento a ser removido
    p->topo--;

    //3 - calcula o endereço do elemento que está atualmente no topo
    void *origem = (char *)p->dados + (p->topo * p->size_data);

    //4 - copia o dado do topo para o elemento informado no parâmetro da função
    //e retorna o elemento para o element do main
    memcpy(element, origem, p->size_data);

    return SUCCESS;
}

// Remove todos os dados da pilha mantendo o descritor alocado.
int cleanStack(pStack p){
    //1 - verificar se a Stack existe
    if(p == NULL) return FAIL;

    //2 - libera os dados, não fazer free(p) pois o exercício pede para manter a estrutura da Stack
    free(p->dados);

    //3 - zera o ponteiro e define o índice do topo em 0
    p->dados = NULL;
    p->topo = 0;

    return SUCCESS;
}

// **** "Operações de acesso" ****

// Retorna uma cópia do dado do topo
int top(pStack p, void *top){

    //1 - verifica se a pStack ou o topo ou top estão vazios
    if(p == NULL || p->topo == 0 || top == NULL) return FAIL;

    //2 - calcula o endereço do elemento do topo (p->topo - 1), pois topo aponta para um índice vazio
    void *origem = (char *)p->dados + ((p->topo - 1) * p->size_data);

    //3 - copia o elemento do topo para o ponteiro top retornar o elemento para a main
    memcpy(top, origem, p->size_data);

    return SUCCESS;
}