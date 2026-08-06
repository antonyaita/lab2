#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_POS 13
#define N_ESCUDOS 3

// implementação de um cronômetro
typedef struct timespec crono;

// Registro UOU
typedef struct 
{
    int pontos;
    int onda;
    int eh_noturno;

    int n_pos;
    char pos[MAX_POS];

    int tiros;
    int por_nascer;
    char arma;

    double intervalo;
    crono cronometro;

    int partida_terminou;
} Estado;

// inicializa um cronômetro com a hora atual
void crono_inicia(crono *c) 
{
    clock_gettime(CLOCK_MONOTONIC, c);
}

// retorna o tempo passado desde que o cronômetro *c foi iniciado, em segundos
double crono_parcial(crono *c) 
{
    crono agora;
    clock_gettime(CLOCK_MONOTONIC, &agora);

    double segundos = agora.tv_sec - c->tv_sec;
    double nanosegundos = agora.tv_nsec - c->tv_nsec;
    return segundos + 1e-9 * nanosegundos;
}

// configura o terminal para o modo "cru", para permitir a leitura
//   de cada caractere digitado sem esperar pelo "enter".
void configura_terminal() 
{
    if (system("stty raw opost -echo min 0 time 1") != 0)
    {
        perror("erro na execução de system(\"stty\")");
        fprintf(stderr, "você tem o programa stty instalado?\n");
        exit(1);
    };
    if (setvbuf(stdin, NULL, _IONBF, 0) != 0)
    {
        perror("erro na execução de setvbuf()");
        exit(1);
    }
}

// configura o terminal para o modo normal, com bufferização por linha.
void normaliza_terminal() 
{
    system("stty sane");
}

// lê um caractere do teclado.
// retorna o código do caractere lido ou 0 casa nada tenha sido digitado.
// só funciona corretamente se o terminal estiver em modo "cru".
char lechar() 
{
    fflush(stdout);
    char c;
    if (fread(&c, 1, 1, stdin) == 1)
        return c;
    return 0;
}

void inicializa_estado(Estado *jogo)
{
    jogo->arma = '0';
    jogo->eh_noturno = 0;
}

void inicia_onda(Estado *jogo) { }

// avança jogo->arma para a próxima arma da sequência válida
void troca_arma(Estado *jogo)
{
    const char *armas = jogo->eh_noturno ? "02468n" : "0123456789n";
    const char *posicao_atual = strchr(armas, jogo->arma);
    int indice = posicao_atual - armas;
    indice = (indice + 1) % strlen(armas);
    jogo->arma = armas[indice];
}

void processar_teclado(Estado *jogo) { 
    char tecla = lechar();
    
    switch (tecla)
    {
    case 27:
        jogo->partida_terminou = 1;
        break;
    
    case 9:
        troca_arma(jogo);
        break;

    default:
        break;
    }

}
void processar_tempo(Estado *jogo) { }
void apresenta(Estado *jogo) { }
int onda_terminou(Estado *jogo) { return 1; }
void mostra_resumo_onda(Estado *jogo) { }
void espera_confirmacao() { }

void joga_onda(Estado *jogo) {
    while (!onda_terminou(jogo) && !jogo->partida_terminou) {
        processar_teclado(jogo);
        processar_tempo(jogo);
        apresenta(jogo);
    }
}

void joga_partida(Estado *jogo) {
    jogo->pontos = 0;
    jogo->onda = 0;
    jogo->partida_terminou = 0;

    while (!jogo->partida_terminou) {
        jogo->onda++;
        inicia_onda(jogo);
        joga_onda(jogo);
        if (!jogo->partida_terminou) {
            mostra_resumo_onda(jogo);
            espera_confirmacao();
        }
    }
}

int main() 
{
    configura_terminal();

    Estado jogo;
    inicializa_estado(&jogo);
    joga_partida(&jogo);

    normaliza_terminal();
    return 0;
}