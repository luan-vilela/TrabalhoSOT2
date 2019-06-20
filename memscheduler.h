/**
 * # Membros do grupo:
 *      - LUAN VILELA LOPES
 *      - GIOVANNI PRATTO
 * 
 *  # Todos o trabalho está em arquivo separado.
 *      - memscheduler.h é o cabeçalho e contém variáveis globais
 *      - Trabalho-T1-SO.c contém o arquivo main()
 *      - O restante são arquivos de métodos usados pela main
 * 
 * 
 *  # Para compilar entrar na pasta do trabalho e rodar
 *      - gcc *.c -o main -lpthread
 *  
 * 
 *  # Para executar.
 *      - ./main
*/

#ifndef _MEMSCHEDULER_H_
#define _MEMSCHEDULER_H_

#include <semaphore.h>
#include <stdbool.h>
#include <time.h>

// Processos struct
typedef struct processId{
    int id;
    int np;
    int tc;
    int tb;
    struct processId *next;
    struct processId *previous;
}process;

//argumentos passos no pthreads
typedef struct arg_struct {
    int seed;
    int frame;
    int n;
    int tq;
    process **filaEntrada;
    process **filaProntos;
}arguments;

//Registrador de memória
typedef struct page{
    int id;
    int endereco;
    bool validador;
    bool referencia;
    struct page *next;
}pagetable;

int myTime;

//declarando um semáforo
// Garante que a thread criação de processos vai iníciar somente após 
// pelo menos 1 processo ser iniciado
sem_t S_processos;


/****************************************************************
 *   AQUI FICA O CABEÇALHO DE TODOS OS MÉTODOS
 ****************************************************************/
void *_createProcess(void *node);
void *_createInitialProcess(void *node);
void createNode(int id, int tp, int tc, int tb, process **node);

void updateTime();
void restartTime();
void espera();

// uso geral
void ** moveProcess(process **local, process ** destino, process *processo);
process * alloca_node();
process * getProcess(process **fila);
process * disconnectBrothers(process *node);


void * _fcfs(void *node);
void * _RR(void *node);

void _removeProcess(int id, process **fila);


int _swapper(process *node, int local);
int getTime();

int swapon(int local);
int findProcess(int id, int local);
process * getProcessToRR(process **fila);
void _despachante(process *fila);

/****************************************************************
 *   MÉTODOS QUE PRECISÃO SER IMPLEMENTADOS
 * 
 * Esses são os métodos que devem ser implementados...
 * Aqui são os métodos principais, vocês podem fazer submétodos
 * igual o que fiz, createNode. Onde o _createProcess é o principal
 * e createNode é usado por ele.
 * Os tipos de retorno não estão definidos, ou seja, pode ser alterado
 * como desajar.
 ****************************************************************/

void _timered();



// talvez faça um outra thread para ficar falando o que acontece
void _printer();


#endif