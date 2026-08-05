#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    
};


void joga_partida(estado_t *est)
{
    laco() {
        processar_teclado(est);
        processar_tempo(est);
        apresenta(est);
    }
}

void joga_partida(estado_t *est)
{
    while(!est->terminou_partida){
        joga_onda(est);
    }
}


int main()
{
    estado_t estado ;
    iniciar_tela();
    inicializa_estado(&estado);
    while (!estado_terminou) {
        joga_partida(&estado.terminou);
    }
    desnicializa_tela();
}