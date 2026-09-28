#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"

int menu(int flag)
{
    printf("\n================ SISTEMA CLINICO ================\n");
    printf("1 - Cadastrar Medico\n");
    printf("2 - Cadastrar Paciente\n");
    printf("3 - Agendar Consulta\n");
    printf("------------------- RELATORIOS -------------------\n");
    printf("4 - [R1] Consultas por Dia\n");
    printf("5 - [R2] Consultas por Paciente\n");
    printf("6 - [R3] Descricao de uma Consulta\n");
    printf("7 - [R4] Pacientes por Especialidade e Mes\n");
    printf("8 - [R5] Pacientes por Medico (Todos)\n");
    printf("--------------------------------------------------\n");
    printf("0 - Sair\n");
    printf("==================================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &flag);
    return flag;
}

void executa_opcao(int opcao, Medico **medicos, Paciente **pacientes, Consulta **consultas)
{
    switch (opcao)
    {
    case 1:
        *medicos = insere_medico(*medicos);
        printf("\nProcedimento de cadastro de medico finalizado.\n");
        break;

    case 2:
        *pacientes = insere_paciente(*pacientes);
        printf("\nProcedimento de cadastro de paciente finalizado.\n");
        break;

    case 3:
        *consultas = insere_consulta(*medicos, *pacientes, *consultas);
        printf("\n[Em desenvolvimento] Agendamento de consulta...\n");
        break;

    case 4:
        printf("\n[Em desenvolvimento] Relatorio R1...\n");
        break;

    case 5:
        printf("\n[Em desenvolvimento] Relatorio R2...\n");
        break;

    case 6:
        printf("\n[Em desenvolvimento] Relatorio R3...\n");
        break;

    case 7:
        printf("\n[Em desenvolvimento] Relatorio R4...\n");
        break;

    case 8:
        printf("\n[Em desenvolvimento] Relatorio R5...\n");
        break;

    case 0:
        printf("\nSaindo do sistema... Ate logo!\n");
        break;

    default:
        printf("\nOpcao invalida! Tente novamente.\n");
        break;
    }
}

int main()
{
    Medico *teste_medico = criar_medico();

    Paciente *teste_paciente = criar_paciente();

    Consulta *teste_consulta = criar_consulta();

    int flag;

    do
    {
        flag = menu(flag);
        executa_opcao(flag, &teste_medico, &teste_paciente, &teste_consulta);
    } while (flag != 0);

    return 0;
}