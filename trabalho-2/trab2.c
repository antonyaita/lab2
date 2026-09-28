#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastro_equipes(int **equipes, int ***pontuacao, int *n_equipes, int *n_etapas);
int *identificar_equipes(int n_equipes);
int **matriz_pontuacao(int n_equipes, int n_etapas);

int *calcular_totais(int **pontuacao, int n_equipes, int n_etapas);
float *calcular_medias(int *totais, int n_equipes, int n_etapas);

void exibir_classificacao(int *equipes, int *totais, float *medias, int n_equipes);
void exibir_resultados(int *equipes, int **pontuacao, int *totais, float *medias, int n_equipes, int n_etapas);
void exibir_desempenho_etapas(int *equipes, int **pontuacao, int n_equipes, int n_etapas);

int menu();

void liberar_matriz(int **matriz, int n_equipes);

void cadastro_equipes(int **equipes, int ***pontuacao, int *n_equipes, int *n_etapas)
{
    printf("Quantas equipes irao participar? ");
    scanf("%d", n_equipes);

    printf("Quantas etapas irao acontecer? ");
    scanf("%d", n_etapas);

    *equipes = identificar_equipes(*n_equipes);
    *pontuacao = matriz_pontuacao(*n_equipes, *n_etapas);
}

int *identificar_equipes(int n_equipes)
{
    int i;
    int *equipes = (int *)malloc(n_equipes * sizeof(int));

    if (equipes == NULL)
    {
        printf("Erro: Memoria insuficiente.\n");
        exit(1);
    }

    printf("\n");

    for (i = 0; i < n_equipes; i++)
    {
        printf("Informe o identificador da equipe %d: ", i + 1);
        scanf("%d", &equipes[i]);
    }

    return equipes;
}

int **matriz_pontuacao(int n_equipes, int n_etapas)
{
    int i, j;
    int **pontuacao = (int **)malloc(n_equipes * sizeof(int *));

    if (pontuacao == NULL)
    {
        printf("Erro: Memoria insuficiente para as linhas da matriz.\n");
        exit(1);
    }

    for (i = 0; i < n_equipes; i++)
    {
        pontuacao[i] = (int *)malloc(n_etapas * sizeof(int));
        if (pontuacao[i] == NULL)
        {
            printf("Erro: Memoria insuficiente para as colunas da matriz.\n");
            exit(1);
        }
    }

    printf("\n");

    for (i = 0; i < n_equipes; i++)
    {
        for (j = 0; j < n_etapas; j++)
        {
            printf("Digite a pontuacao da equipe %d na etapa %d: ", i + 1, j + 1);
            scanf("%d", &pontuacao[i][j]);
        }
    }

    return pontuacao;
}

int *calcular_totais(int **pontuacao, int n_equipes, int n_etapas)
{
    int i, j;
    int *totais = (int *)malloc(n_equipes * sizeof(int));

    if (totais == NULL)
    {
        printf("Erro: Memoria insuficiente para os totais.\n");
        exit(1);
    }

    for (i = 0; i < n_equipes; i++)
    {
        totais[i] = 0;
        for (j = 0; j < n_etapas; j++)
        {
            totais[i] += pontuacao[i][j];
        }
    }

    return totais;
}

float *calcular_medias(int *totais, int n_equipes, int n_etapas)
{
    int i;
    float *medias = (float *)malloc(n_equipes * sizeof(float));

    if (medias == NULL)
    {
        printf("Erro: Memoria insuficiente para as medias.\n");
        exit(1);
    }

    for (i = 0; i < n_equipes; i++)
    {
        medias[i] = (float)totais[i] / n_etapas;
    }

    return medias;
}

void exibir_classificacao(int *equipes, int *totais, float *medias, int n_equipes)
{
    int i, j, tmp_id, tmp_tot;
    float tmp_med;

    int *ids = (int *)malloc(n_equipes * sizeof(int));
    int *tot = (int *)malloc(n_equipes * sizeof(int));
    float *med = (float *)malloc(n_equipes * sizeof(float));

    if (ids == NULL || tot == NULL || med == NULL)
    {
        printf("Erro: Memoria insuficiente para a classificacao.\n");
        exit(1);
    }

    for (i = 0; i < n_equipes; i++)
    {
        ids[i] = equipes[i];
        tot[i] = totais[i];
        med[i] = medias[i];
    }

    for (i = 0; i < n_equipes - 1; i++)
    {
        for (j = 0; j < n_equipes - 1 - i; j++)
        {
            if (tot[j] < tot[j + 1])
            {
                tmp_id = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = tmp_id;

                tmp_tot = tot[j];
                tot[j] = tot[j + 1];
                tot[j + 1] = tmp_tot;

                tmp_med = med[j];
                med[j] = med[j + 1];
                med[j + 1] = tmp_med;
            }
        }
    }

    printf("\n--- RELATORIO 2: CLASSIFICACAO FINAL ---\n");
    printf("POSICAO\tEQUIPE\tTOTAL\tMEDIA\n");
    for (i = 0; i < n_equipes; i++)
    {
        printf("%d\t%d\t%d\t%.2f\n", i + 1, ids[i], tot[i], med[i]);
    }

    free(ids);
    free(tot);
    free(med);
}

void exibir_resultados(int *equipes, int **pontuacao, int *totais, float *medias, int n_equipes, int n_etapas)
{
    int i, j;

    printf("\n--- RELATORIO 1: TABELA GERAL ---\n");
    printf("EQUIPE\t");
    for (i = 0; i < n_etapas; i++)
    {
        printf("ETAPA %d\t", i + 1);
    }
    printf("TOTAL\tMEDIA\n");

    for (i = 0; i < n_equipes; i++)
    {
        printf("%d\t", equipes[i]);
        for (j = 0; j < n_etapas; j++)
        {
            printf("%d\t", pontuacao[i][j]);
        }
        printf("%d\t%.2f\n", totais[i], medias[i]);
    }
}

void exibir_desempenho_etapas(int *equipes, int **pontuacao, int n_equipes, int n_etapas)
{
    int i, j, maior, menor, idx_maior, idx_menor, soma;

    printf("\n--- RELATORIO 3: DESEMPENHO POR ETAPA ---\n");

    for (j = 0; j < n_etapas; j++)
    {
        maior = pontuacao[0][j];
        menor = pontuacao[0][j];
        idx_maior = 0;
        idx_menor = 0;
        soma = 0;

        for (i = 0; i < n_equipes; i++)
        {
            soma += pontuacao[i][j];

            if (pontuacao[i][j] > maior)
            {
                maior = pontuacao[i][j];
                idx_maior = i;
            }
            if (pontuacao[i][j] < menor)
            {
                menor = pontuacao[i][j];
                idx_menor = i;
            }
        }

        printf("\nETAPA %d\n", j + 1);
        printf("Maior pontuacao: %d - Equipe %d\n", maior, equipes[idx_maior]);
        printf("Menor pontuacao: %d - Equipe %d\n", menor, equipes[idx_menor]);
        printf("Media da etapa: %.2f\n", (float)soma / n_equipes);
    }
}

int menu()
{
    int opcao;

    printf("\nQual relatorio voce quer?");
    printf("\n1 - Cadastrar identificao das equipes e pontuacoes");
    printf("\n2 - Exibir tabela geral (relatorio 1)");
    printf("\n3 - Exibir classificacao final (relatorio 2)");
    printf("\n4 - Exibir desempenho por etapa (relatorio 3)");
    printf("\n0 - Encerrar\n");

    scanf("%d", &opcao);
    return opcao;
}

void liberar_matriz(int **matriz, int n_equipes)
{
    int i;
    for (i = 0; i < n_equipes; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

int main()
{
    int **pontuacao = NULL;
    int *equipes = NULL;
    int *totais = NULL;
    float *medias = NULL;
    int n_equipes = 0, n_etapas = 0;
    int opcao, cadastrado = 0;

    do
    {
        opcao = menu();

        switch (opcao)
        {
        case 1:
            if (cadastrado)
            {
                free(equipes);
                liberar_matriz(pontuacao, n_equipes);
                free(totais);
                free(medias);
            }
            cadastro_equipes(&equipes, &pontuacao, &n_equipes, &n_etapas);
            totais = calcular_totais(pontuacao, n_equipes, n_etapas);
            medias = calcular_medias(totais, n_equipes, n_etapas);
            cadastrado = 1;
            break;

        case 2:
            if (!cadastrado)
                printf("\nCadastre as equipes primeiro (opcao 1).\n");
            else
                exibir_resultados(equipes, pontuacao, totais, medias, n_equipes, n_etapas);
            break;

        case 3:
            if (!cadastrado)
                printf("\nCadastre as equipes primeiro (opcao 1).\n");
            else
                exibir_classificacao(equipes, totais, medias, n_equipes);
            break;

        case 4:
            if (!cadastrado)
                printf("\nCadastre as equipes primeiro (opcao 1).\n");
            else
                exibir_desempenho_etapas(equipes, pontuacao, n_equipes, n_etapas);
            break;

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    if (cadastrado)
    {
        free(equipes);
        liberar_matriz(pontuacao, n_equipes);
        free(totais);
        free(medias);
    }

    return 0;
}
