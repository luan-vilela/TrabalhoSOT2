/**
 *  Arquivo responsável por todos os métodos que cria processos
 * e coloca na fila de entrada.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>

/**
 * Cria processos dinamicamente na memória
 * Devolve um struct do tipo process ordenado
 * com base no tc informado
 * */
void *_createProcess(void *node){
    process * processoAux;
    int n = 0;
    //cria listFrame
    createListFrame(((arguments*)node)->n);
    
    // Só entra aqui após pelo menos 1 processo ser criado digitado
    sem_wait(&S_processos);
    while( ((arguments*)node)->filaEntrada != NULL && ((arguments*)node)->n > n){
        // Verifica se existe algum processo que esteja no tempo de criação

        processoAux = getProcess( ((arguments*)node)->filaEntrada );

        if(processoAux != NULL){
            if( processoAux->tc <= getTime()){
                // move processo da fila de entrada para fila de prontos
                moveProcess( ((arguments*)node)->filaEntrada, ((arguments*)node)->filaProntos, processoAux);
                printf("%s - Criador de processos criou o processo %d e o colocou na fila de prontos\n", __TIME__, processoAux->id);
                n++;
                sem_post(&S_escalonador);
            }
        }

    }

}
// Criador de fila de entrada
// Fica aguardando entradas n
void *_createInitialProcess(void *node){

    int i;
    // variáveis para criação do processo
    int id, np, tc, tb;
    for(i = 0; i < ((arguments*)node)->n; i++){
        scanf("%d %d %d %d", &id, &np, &tc, &tb);
        createNode(id,np,tc,tb,((arguments*)node)->filaEntrada);
        sem_post(&S_processos);
    }

}
/**
 * Aloca processos em uma fila
*/
void createNode(int id, int np, int tc, int tb, process **node){
    process *newProcess;
    newProcess = alloca_node();
    
    newProcess->id = id;
    newProcess->np = np;
    newProcess->pagetable = NULL;
    newProcess->pagetable = createPage(np, newProcess->pagetable);
    newProcess->tc = tc;
    newProcess->tb = tb;

    if(*node == NULL){
        *node = newProcess;        
    }
    // sem ordenação apenas coloca fila de entrada
    else{
        newProcess->next = *node;
        (*node)->previous = newProcess;
        *node = newProcess;
    }
}

// cria tabela de página
// N é o endereço da memória física
Pagetable * createPage(int n, Pagetable *L){
    int i;
    for(i = 0; i < n; i++){
        Pagetable *newPage;
        newPage = (Pagetable *)malloc(sizeof(Pagetable));
        newPage->idpage = n - (1 + i);
        newPage->idframe = -1;
        newPage->validador = false;
        newPage->validador = false;
        
        // empilha page table
        if(L != NULL)
            newPage->next = L;
        L = newPage;
    }
    return L;
}

void createListFrame(int numFrame){
    nframe.nframe = numFrame;
    nframe.idProcess = NULL;

    int i;
    for(i = 0; i < numFrame; i++){
        quadro *newPage;
        newPage = (quadro *)malloc(sizeof(quadro));
        newPage->id = -1;
        newPage->next = NULL;

        if(nframe.idProcess != NULL)
            newPage->next = nframe.idProcess;
        nframe.idProcess = newPage;
    }    
}