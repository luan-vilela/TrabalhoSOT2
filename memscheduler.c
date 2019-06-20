/**
 * Arquivo responsável por todos os métodos de auxílio
 * aos métodos principais.
 * 
 *  - Contém métodos como alloca_node que é responsável na criação de novos nós
 * da fila.
 *  - getProcessToRR que devolve o ultimo método da fila de prontos para o escalondor RR. Assim podendo trabalhar com 
 * TBs corretos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

// aloca um processo e devolve ele
process * alloca_node(){
    process *newProcess;
    newProcess = (process *)malloc(sizeof(process));
    newProcess->previous = NULL;
    newProcess->next = NULL;
    return newProcess;
}

// Pega o processo de menor tc da fila
// e retorna ele.
process * getProcess(process **fila){
    process *newProcess, *aux, **begin;
    // newProcess = alloca_node();
    // aux = alloca_node();

    begin = fila;
    aux = *fila;
    newProcess = *begin;
    // Percorre a fila
    while(aux->next != NULL){
        if(newProcess->tc > aux->next->tc)
            newProcess = aux->next;
        aux = aux->next;
    }

    fila = begin;
    return newProcess;
}

// Recebe uma fila local, uma fila destino e um processo;
void ** moveProcess(process **local, process ** destino, process *processo){
    process **cabeca, *aux;
    cabeca = local;
    aux = *local;

    while(aux->next != NULL && processo->id != aux->id){
        aux = aux->next;
    }

    if(processo->id == aux->id){
        // ultimo item da fila
        if(aux->previous == NULL && aux->next == NULL){
            *local = NULL;
        }
        // cabeça da fila
        else if(aux->next != NULL && aux->previous == NULL){
            aux->next->previous = NULL;
            *local = aux->next;
        }
        // final da fila
        else if(aux->previous != NULL && aux->next == NULL){
            aux->previous->next = NULL;
            local = cabeca;
        }
        // meio da fila
        else{
            aux->next->previous = aux->previous;
            aux->previous->next = aux->next;
            local = cabeca;
        }
        aux = disconnectBrothers(aux);
        processo = disconnectBrothers(processo);

        if(*destino == NULL){
            *destino = processo;
        }
        else{
            processo->next = *destino;
            (*destino)->previous = processo;
            *destino = processo;
        }
    }

}


// Desconecta irmãos do processo
process * disconnectBrothers(process *node){
    node->next = NULL;
    node->previous = NULL;
    return node;
}

// Remove 1 processo da fila.
// Não da free
void _removeProcess(int id, process **fila){
    process *aux, **begin;
    
    begin = fila;
    //aux = alloca_node();
    if(*fila != NULL){
        aux = *fila;

        while (id != aux->id && aux != NULL){
            aux = aux->next;
        }
    
        if(aux->id == id){
            // testa se é o ultimo processo na fila
            if(aux->previous == NULL && aux->next == NULL){
                *fila = NULL;
            }
            // testa se é o início da fila
            else if(aux->previous == NULL){
                aux->next->previous = NULL;
                *fila = aux->next;

            }
            // testa se é o final da fila
            else if(aux->next == NULL){
                aux->previous->next = NULL;
                fila = begin;
            }
            // testa se é meio da fila
            else{
                aux->previous->next = aux->next;
                aux->next->previous = aux->previous;
                fila = begin;            
            }
        }

    }
    else{
        printf("Não existe processo para ser removido!\n");
    }

}
