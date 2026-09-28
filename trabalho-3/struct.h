typedef enum
{
    AGENDADA,
    EXECUTADA
} StatusConsulta;

typedef struct data
{
    int dia, mes, ano;
    int hora, minuto;
} Data;

typedef struct medico
{
    char crm[7];
    char nome[50];
    char especialidade[50];
    char telefone[20];
    struct medico *prox;
} Medico;

typedef struct paciente
{
    char cpf[12];
    char nome[50];
    char telefone[20];
    struct paciente *prox;
} Paciente;

typedef struct consulta
{
    Paciente *paciente;
    Medico *medico;
    Data data_hora;
    char convenio[50];
    StatusConsulta status;
    char descricao[500];
    struct consulta *prox;
} Consulta;

Medico *criar_medico();
Medico *insere_medico(Medico *medico);
Paciente *busca_crm(Medico *novo, char *crm);
void imprime_medico(Medico *l);

Paciente *criar_paciente();
Paciente *insere_paciente(Paciente *paciente);
Paciente *busca_cpf(Paciente *novo, char *cpf);
void imprime_paciente(Paciente *l);

Consulta *criar_consulta();
Consulta *insere_consulta(Medico *medico, Paciente *paciente, Consulta *consulta);