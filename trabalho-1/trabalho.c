// estado completo de uma partida em andamento
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POS 13
#define N_ESCUDOS 3

// implementação de um cronômetro
typedef struct timespec crono;

// estado completo de uma partida em andamento
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
} EstadoJogo;

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

int main()
{
    configura_terminal();

    EstadoJogo jogo;
    jogo.pontos = 0;
    jogo.tiros = 30;
    jogo.arma = '0';

    char tecla = 0;
    while (tecla != 27)
    { // 27 = Esc
        tecla = lechar();
        printf(" %d %d %c   \r", jogo.pontos, jogo.tiros, jogo.arma);
    }

    normaliza_terminal();
    return 0;
}