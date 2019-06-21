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

int bitV(int idpage, Pagetable *pagetable){


    for(int i = 0; i < idpage; i++){
        pagetable = pagetable->next;
    }

    if(pagetable->validador == false){
        pagetable->validador = true;
        pagetable->idframe = 100;
        pagetable->referencia = true;
        pagetable = L;
        return 1;
    }
    
    return 0;
}