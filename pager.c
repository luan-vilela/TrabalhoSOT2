/**
 *  Arquivo responsavél por todos os métodos swapper.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

/**
 * Verifica se existe espaço na memória e coloca o
 * processo nela.
 * Retorna 1 para processos alocados
 * Retorna 0 para processos não alocados
*/
int _pager(int idpage, process *fila){
    
    // se retornar 1 já está na memória
    if(testaBit(idpage, fila->pagetable)){

    }
    else{
        "não está na pagina";
    }


}

int testaBit(int idpage, Pagetable *page){
    Pagetable *original = page;
    // pega a página com id
    for(int i = 0; i < idpage; i++)
        page = page->next;
    
    //já está na memória
    if(page->validador == true){
        page->referencia = true;
        page = original;
        return 1;
    }
    page = original;
    return 0;
}
