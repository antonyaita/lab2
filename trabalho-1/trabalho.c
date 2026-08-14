#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 2
#define NEGRITO "\033[1m"
#define RESET "\033[0m"

typedef struct
{
    int codigo;
    char nome[81];
    float altura;
    float peso;
    float IMC;
    char faixa[15];

} Pessoa;

void faixa(Pessoa pessoa[]);
void calculadora(Pessoa pessoa[]);

void leitor(Pessoa pessoa[]);
void escreva(Pessoa pessoa[]);
void nome_sobrepeso(Pessoa pessoa[]);
void codigo_obesidade(Pessoa pessoa[]);
float media_pesos(Pessoa pessoa[]);
void acima_media(Pessoa pessoa[], float media_peso);
void nao_normal(Pessoa pessoa[]);
void normal_abaixo(Pessoa pessoa[], float media_peso);
void maior_imc(Pessoa pessoa[]);
void menor_imc(Pessoa pessoa[]);

void casos(Pessoa pessoa[], int relatorio);
int menu(Pessoa pessoa[], int relatorio);

void faixa(Pessoa pessoa[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        if (pessoa[i].IMC < 18.5)
        {
            strcpy(pessoa[i].faixa, "Magreza");
        }
        else if (pessoa[i].IMC >= 18.5 && pessoa[i].IMC < 25)
        {
            strcpy(pessoa[i].faixa, "Normal");
        }
        else if (pessoa[i].IMC >= 25 && pessoa[i].IMC < 30)
        {
            strcpy(pessoa[i].faixa, "Sobrepeso");
        }
        else
        {
            strcpy(pessoa[i].faixa, "Obesidade");
        }
    }
}

void calculadora(Pessoa pessoa[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        float conversao = pessoa[i].altura / 100;
        pessoa[i].IMC = pessoa[i].peso / (conversao * conversao);
    }

    faixa(pessoa);
}

void leitor(Pessoa pessoa[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        printf("\n--- Pessoa %d ---\n", i + 1);
        printf("Digite o código da pessoa: ");
        scanf("%i", &pessoa[i].codigo);

        printf("Digite o Nome da pessoa: ");
        scanf(" %80[^\n]", pessoa[i].nome);

        printf("Digite o Peso da pessoa: ");
        scanf("%f", &pessoa[i].peso);

        printf("Digite a Altura (em cm) da pessoa: ");
        scanf("%f", &pessoa[i].altura);
    }
    calculadora(pessoa);
}

void casos(Pessoa pessoa[], int relatorio)
{
    float media_peso;

    switch (relatorio)
    {
    case 1:
        escreva(pessoa);
        break;
    case 2:
        nome_sobrepeso(pessoa);
        break;
    case 3:
        codigo_obesidade(pessoa);
        break;
    case 4:
        media_peso = media_pesos(pessoa);
        break;
    case 5:
        media_peso = media_pesos(pessoa);
        acima_media(pessoa, media_peso);
        break;
    case 6:
        nao_normal(pessoa);
        break;
    case 7:
        media_peso = media_pesos(pessoa);
        normal_abaixo(pessoa, media_peso);
        break;
    case 8:
        maior_imc(pessoa);
        break;
    case 9:
        menor_imc(pessoa);
        break;
    default:
        printf("\nOpcao invalida!\n");
        break;
    }
}

int menu(Pessoa pessoa[], int relatorio)
{
    printf("\n------------- MENU -------------\n");
    printf("1)Os dados de todas as pessoas\n");
    printf("2)O nome das pessoas que estão com " NEGRITO "sobrepeso\n" RESET);
    printf("3)O código das pessoas que estão com " NEGRITO "obesidade\n" RESET);
    printf("4)O valor médio dos pesos\n");
    printf("5)A quantidade de pessoas que tem peso acima do valor " NEGRITO "médio dos pesos\n" RESET);
    printf("6)A quantidade de pessoas que não estão na faixa " NEGRITO "normal de peso\n" RESET);
    printf("7)O nome das pessoas que tem peso " NEGRITO "normal" RESET " e que pesam menos do que o valor " NEGRITO "médio dos pesos\n" RESET);
    printf("8)O nome da(s) pessoa(s) que obteve (obtiveram) o " NEGRITO "maior IMC\n" RESET);
    printf("9)O código da(s) pessoa (s) que obteve (obtiveram) o " NEGRITO "menor IMC\n" RESET);

    printf("\nDigite o numero do relatorio que voce quer acessar: ");
    scanf("%d", &relatorio);

    casos(pessoa, relatorio);

    return relatorio;
}

void escreva(Pessoa pessoa[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        printf("\nCódigo da pessoa: %i", pessoa[i].codigo);
        printf("\nNome da pessoa: %s", pessoa[i].nome);
        printf("\nPeso da pessoa: %f", pessoa[i].peso);
        printf("\nAltutra da pessoa: %f", pessoa[i].altura);
        printf("\nIMC da pessoa: %f", pessoa[i].IMC);
        printf("\nFaixa da pessoa: %s\n", pessoa[i].faixa);
    }
}
void nome_sobrepeso(Pessoa pessoa[])
{
    int i;
    printf("\nPessoas com Sobrepeso:");
    for (i = 0; i < TAM; i++)
    {
        if (strcmp(pessoa[i].faixa, "Sobrepeso") == 0)
        {
            printf("\n- %s", pessoa[i].nome);
        }
    }
    printf("\n");
}

void codigo_obesidade(Pessoa pessoa[])
{
    int i;
    printf("\nCódigos das pessoas com Obesidade:");
    for (i = 0; i < TAM; i++)
    {
        if (strcmp(pessoa[i].faixa, "Obesidade") == 0)
        {
            printf("\n- %i", pessoa[i].codigo);
        }
    }
    printf("\n");
}

float media_pesos(Pessoa pessoa[])
{
    float cont = 0, media_peso;
    int i;
    for (i = 0; i < TAM; i++)
    {
        cont += pessoa[i].peso;
    }

    media_peso = cont / TAM;
    printf("\nO valor médio dos pesos é: %.2f kg\n", media_peso);
    return media_peso;
}

void acima_media(Pessoa pessoa[], float media_peso)
{
    int i;
    int contador = 0;

    for (i = 0; i < TAM; i++)
    {
        if (pessoa[i].peso > media_peso)
        {
            contador++;
        }
    }

    printf("\nQuantidade de pessoas acima do peso médio (%.2f kg): %d", media_peso, contador);
    printf("\n");
}

void nao_normal(Pessoa pessoa[])
{
    int i;
    int contador = 0;

    for (i = 0; i < TAM; i++)
    {
        if (strcmp(pessoa[i].faixa, "Normal") != 0)
        {
            contador++;
        }
    }

    printf("\nQuantidade de pessoas fora do peso normal: %d", contador);
    printf("\n");
}

void normal_abaixo(Pessoa pessoa[], float media_peso)
{
    int i;

    for (i = 0; i < TAM; i++)
    {
        if (strcmp(pessoa[i].faixa, "Normal") == 0 && pessoa[i].peso < media_peso)
        {
            printf("\n- %s", pessoa[i].nome);
        }
    }
}

void maior_imc(Pessoa pessoa[])
{
    int i;
    float maior_imc = pessoa[0].IMC;

    for (i = 1; i < TAM; i++)
    {
        if (pessoa[i].IMC > maior_imc)
        {
            maior_imc = pessoa[i].IMC;
        }
    }

    printf("Maior IMC encontrado: %.2f\n", maior_imc);
    printf("Pessoas com este IMC:\n");

    for (i = 0; i < TAM; i++)
    {
        if (pessoa[i].IMC == maior_imc)
        {
            printf("- %s\n", pessoa[i].nome);
        }
    }
}

void menor_imc(Pessoa pessoa[])
{
    int i;
    float menor_imc = pessoa[0].IMC;

    for (i = 1; i < TAM; i++)
    {
        if (pessoa[i].IMC < menor_imc)
        {
            menor_imc = pessoa[i].IMC;
        }
    }

    printf("Menor IMC encontrado: %.2f\n", menor_imc);
    printf("Pessoas com este IMC:\n");

    for (i = 0; i < TAM; i++)
    {
        if (pessoa[i].IMC == menor_imc)
        {
            printf("- %s\n", pessoa[i].nome);
        }
    }
}

int main()
{
    Pessoa *pessoa = (Pessoa *)malloc(TAM * sizeof(Pessoa));

    if (pessoa == NULL)
    {
        printf("Erro: Memória insuficiente!\n");
        return 1;
    }

    leitor(pessoa);

    int relatorio = -1;

    while (relatorio != 0)
    {
        relatorio = menu(pessoa, relatorio);
    }

    free(pessoa);
    return 0;
}
