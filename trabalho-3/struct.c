#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"

Medico *criar_medico()
{
    return NULL;
}

Medico *insere_medico(Medico *medico)
{
    Medico *novo = (Medico *)malloc(sizeof(Medico));
    if (novo == NULL)
    {
        printf("Deu ruim\n");
        exit(1);
    }

    printf("\nDigite o CRM do medico: ");
    scanf(" %6s", novo->crm);

    if (busca_crm(medico, novo->crm))
    {
        printf("\n[Erro] CRM ja cadastrado! Insercao cancelada.\n");
        free(novo);
        return medico;
    }

    printf("Digite o Nome do medico: ");
    scanf(" %[^\n]", novo->nome);

    printf("Digite o Especialidade do medico: ");
    scanf(" %[^\n]", novo->especialidade);

    printf("Digite o Telefone do medico: ");
    scanf(" %[^\n]", novo->telefone);

    novo->prox = medico;

    return novo;
}

Medico *busca_crm(Medico *novo, char *crm)
{
    Medico *atual;

    for (atual = novo; atual != NULL; atual = atual->prox)
    {
        if (strcmp(atual->crm, crm) == 0)
        {
            return atual;
        }
    }

    return NULL;
}

void imprime_medico(Medico *l)
{
    Medico *p;

    if (l == NULL)
    {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    for (p = l; p != NULL; p = p->prox)
    {
        printf("\nCRM: %s | Nome: %s | Especialidade: %s | Telefone: %s\n", p->crm, p->nome, p->especialidade, p->telefone);
    }
}

Paciente *criar_paciente()
{
    return NULL;
}

Paciente *insere_paciente(Paciente *paciente)
{
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    if (novo == NULL)
    {
        printf("Deu ruim\n");
        exit(1);
    }

    printf("\nDigite o CPF do paciente: ");
    scanf(" %11s", novo->cpf);

    if (busca_cpf(paciente, novo->cpf))
    {
        printf("\n[Erro] CPF ja cadastrado! Insercao cancelada.\n");
        free(novo);
        return paciente;
    }

    printf("Digite o Nome do paciente: ");
    scanf(" %[^\n]", novo->nome);

    printf("Digite o Telefone do paciente: ");
    scanf(" %[^\n]", novo->telefone);

    novo->prox = paciente;

    return novo;
}

Paciente *busca_cpf(Paciente *novo, char *cpf)
{
    Paciente *atual;

    for (atual = novo; atual != NULL; atual = atual->prox)
    {
        if (strcmp(atual->cpf, cpf) == 0)
        {
            return atual;
        }
    }

    return NULL;
}

void imprime_paciente(Paciente *l)
{
    Paciente *p;

    if (l == NULL)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    for (p = l; p != NULL; p = p->prox)
    {
        printf("CPF: %s | Nome: %s | Telefone: %s\n", p->cpf, p->nome, p->telefone);
    }
}

Consulta *criar_consulta()
{
    return NULL;
}

Consulta *insere_consulta(Medico *medico, Paciente *paciente, Consulta *consulta)
{
    Medico *medico_encontrado = (Medico *)malloc(sizeof(Medico));
    medico_encontrado = medico;
    printf("Digite o crm do medico da consulta: ");
    scanf("%6s", medico_encontrado->crm);
    Medico *medico_encontrado = busca_crm(medico, medico_encontrado->crm);
}