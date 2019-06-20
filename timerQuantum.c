/**
 *  Arquivo responsavél por todos os métodos Timer.
 * 
*/
#include <stdio.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>

// acada segundo ele incrementa o tempo
void updateTime(){
    //colocar semáfaro
    // Inicia timer em 0
    restartTime();
    while (1){
        sleep(1);
        myTime++;

    }
}

// retorna tempo atual
int getTime(){
    return myTime;
}

// Zera tempo
void restartTime(){
    myTime = 0;
}

// espera 1 segundo
void espera(){
    sleep(1);
}