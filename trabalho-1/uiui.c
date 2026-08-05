#include <stdio.h>
#include <stdlib.h>

void joga_partida(estado_t *est)
{
    laco() {
        processar_teclado();
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