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
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>


/************************************************
 * DEBUG
************************************************/
void imprimeFila(process *L){
    while(L!= NULL){
        printf("processo id: %d criado. Detalhes: \t id | \t np | \t tc | \t tb\n ", L->id);
        printf("\t\t\t\t\t %d \t %d \t %d\n", L->id, L->tc, L->tb);
        //Aguarda 1 segundo
        //sleep(1);
        L = L->next;
    }
}



/************************************************
 * FIM DEBUG
************************************************/


int main(){

    // tmp é um struct que contém quantidade de memória e os ids mapeados
    int i;
    // filas
    process *fila_entrada = NULL;
    process *fila_prontos = NULL;

    arguments *args;
    pthread_t *criador_de_processos;
    pthread_t *input_de_processos;
    pthread_t *escalonador_RR;
    pthread_t *Timer;
    // pthread_t *p;

    // Semáforos
    sem_init(&S_processos, 0, 0);
    // sem_init(&S, 0, 0);
    // sem_init(&S_despachante,0, 0);
    

    printf("%s - Início da observação\n", __TIME__);
    // ***********************************************
    //cria argumentos para enviar pelas threads
    args = (arguments *) malloc(sizeof(arguments));
    args->filaEntrada = &fila_entrada;
    args->filaProntos = &fila_prontos; 

    // Entrada de dados
    // Recebe tmp, n, tq
    scanf("%d %d %d %d", &args->seed, &nframe, &args->n, &args->tq);
    
    // Seta seed
    srand(args->seed);


    // Cria thread Timer
    Timer = (pthread_t *) malloc(sizeof(* Timer));
    pthread_create(Timer, NULL, (void *) updateTime, NULL);

    // Cria thread que fica ouvindo a entrada de processos
    input_de_processos = (pthread_t *) malloc(sizeof(* input_de_processos));
    pthread_create(input_de_processos, NULL, (void *) _createInitialProcess, (void *) args);
//    pthread_join(*input_de_processos, NULL);

    // Cria thread criador de processos
    criador_de_processos = (pthread_t *) malloc(sizeof(* criador_de_processos));
    pthread_create(criador_de_processos, NULL, (void *) _createProcess, (void *) args);

    // Cria thread Escalonador
    escalonador_RR = (pthread_t *) malloc(sizeof(* escalonador_RR));
    pthread_create(escalonador_RR, NULL, (void *) _RR, (void *) args);

    

    printf("Término da observação\n");




    printf("fila de entrada\n");
    imprimeFila(fila_entrada);
    pthread_join(*input_de_processos, NULL);
    
    printf("\n\n\n\n");
    
    pthread_join(*criador_de_processos, NULL);
    pthread_join(*escalonador_RR, NULL);
    //imprime fila de entrada
    printf("fila de prontos\n");
    imprimeFila(fila_prontos);

    return 0;

    // NÃO PODE USAR JOIN NO THREAD TIMER
    //pthread_join(*Timer, NULL);
}