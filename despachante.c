/**
 *  Arquivo responsavél por todos os métodos do despachante.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

void _despachante(process *fila){
    // sorteia uma idpage
    int idpage = rand() % fila->np;


   // sem_post(&S);
    
}

// Retorn a 1 caso tenha falha de página
int bitV(int idpage, Pagetable *pagetable){
    int controle = 0;

    for(int i = 0; i < idpage; i++){
        pagetable = pagetable->next;
    }
    // Falha de página
    if(pagetable->validador == false){
        controle = 1;
    }


    return controle;
}


    // while (nframe.idProcess != NULL){
    //     printf("%d ", nframe.idProcess->id);
    //     nframe.idProcess = nframe.idProcess->next;
    // }