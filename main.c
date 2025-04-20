#include "main.h"

#define MAX_STRING 100

int main(int argc, char *argv[]) {

    //inicializar a estrutura
    pStack pilha = NULL;

    //inicializar as variáveis
    int result = 0; //retorna o valor de SUCCESS (0) ou FAIL (1)
    int qtd_elementos = 0; //quantos elementos terá na pilha
    int tipo = 0; //tipo de elemento: 0 = int, 1 = float e 2 = string
    int sizedata; //variável que recebe o tamanho do tipo de dado
    int valor_int;
    float valor_float;
    char buffer[MAX_STRING];

    //solicitar ao usuário o tamanho máximo da pilha
    printf("Digite a quantidade de dados a serem inseridos na pilha:\n");
    //ao invés de usar fscanf e ter que limpa o buffer com while (getchar() != '\n'); usa fgets para ler e sscanf para pegar o dado e armazenar na variável
    fgets(buffer, MAX_STRING, stdin); //armazena o que o usuário digitou no buffer
    //verifica se a leitura do que o usuário digitou falhou
    if (sscanf(buffer, "%d", &qtd_elementos) != 1) {
        printf("Erro ao ler quantidade.\n");
        return 1;
    }

    //solicitar ao usuário o tipo de elemento a ser empilhado
    printf("Digite o tipo de dado (0=int, 1=float, 2=string):\n");
    fgets(buffer, MAX_STRING, stdin);
    //verifica se a leitura do que o usuário digitou falhou
    if (sscanf(buffer, "%d", &tipo) != 1) {
        printf("Erro ao ler tipo de dado.\n");
        return 1;
    }

    //verifica o tipo indicado, e define o tamanho de acordo
    if(tipo == 0){
        sizedata = sizeof(int);
    }else if(tipo == 1){
        sizedata = sizeof(float);
    }else{
        sizedata = sizeof(char) * MAX_STRING;
    }

    //inicializa a pilha
    result = stack(&pilha, qtd_elementos, sizedata);
    //se retornar falha, printa mensagem ao usuário
    if(result != SUCCESS){
        printf("Erro ao criar a pilha");
        return 1;
    }

    //recebendo os elementos e empilhando
    for(int i = 0; i < qtd_elementos; i++){
        printf("Digite o valor:\n");
        //lê uma linha do usuário e armazena em buffer (suporta espaços, diferente do scanf)
        fgets(buffer, MAX_STRING, stdin);
        
        //função rápida para substituir o \n, que fgets coloca, por \0, precisa de string.h
        buffer[strcspn(buffer, "\n")] = '\0';

        //verifica o tipo de dado e empilha
        if (tipo == 0){
            //tenta extrair um inteiro da string que o usuário digitou
            //se conseguir extrair (sscanf retorna 1)
            if (sscanf(buffer, "%d", &valor_int) == 1)
                //empilha o número inteiro
                push(pilha, &valor_int);
            else
                printf("Valor inválido para tipo inteiro. Ignorado.\n");
        }else if(tipo == 1){
            //tenta extrair um float da string que o usuário digitou
            //se conseguir extrair (sscanf retorna 1)
            if (sscanf(buffer, "%f", &valor_float) == 1)
                //empilha o float
                push(pilha, &valor_float);
            else
                printf("Valor inválido para tipo float. Ignorado.\n");
        }else {//é string
            //empilha direto do buffer
            push(pilha, buffer);
        }

    }

    // Retorna uma cópia do dado do topo por tipo de dado
    if (tipo == 0) {
        //variável que recebe o valor do topo
        int topo_int;
        //verifica se a função conseguiu retornar o topo e o armazenar na variável topo_int
        if (top(pilha, &topo_int) == SUCCESS)
            printf("Topo: %d\n", topo_int);
    } else if (tipo == 1) {
        float topo_float;
        //verifica se a função conseguiu retornar o topo e o armazenar na variável topo_float
        if (top(pilha, &topo_float) == SUCCESS)
            printf("Topo: %.2f\n", topo_float);
    } else {
        //cria um array para a string
        char topo_str[MAX_STRING];
        //verifica se retornou o topo e coloca em topo_str
        if (top(pilha, topo_str) == SUCCESS)
            printf("Topo: %s\n", topo_str);
    }
    

    // Desempilhando por tipo, mesma lógica do topo
    printf("\nDesempilhando todos:\n");
    //enquando for possível desempilhar (while(1) indica sucesso), quando falhar = 0, para de desempilhar
    while (1) {
        if (tipo == 0) {
            int valor;
            //se desempilhou, retorna o valor desempilhado para imprimir
            if (pop(pilha, &valor) != SUCCESS) break;
            printf("Pop: %d\n", valor);
        } else if (tipo == 1) {
            float valor;
            if (pop(pilha, &valor) != SUCCESS) break;
            printf("Pop: %.2f\n", valor);
        } else {
            char valor[MAX_STRING];
            if (pop(pilha, valor) != SUCCESS) break;
            printf("Pop: %s\n", valor);
        }
    }

    //primeo remove todos os dados da pilha mantendo o descritor alocado
    cleanStack(pilha);
    //depois "Destrutor": libera memória da estrutura
    unstack(&pilha);
  
    return 0;
}