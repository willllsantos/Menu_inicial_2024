#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

typedef struct
{
    char nome[100];
    char cpf[12];
    int quantidadePessoas, dia;
} Reserva;

void validarCpf(const char *cpf)
{
    if (strlen(cpf) != 11)
    {
        printf("CPF inválido! O CPF deve conter 11 dígitos.\n");
        return;
    }
}

void formatarCpf(const char *cpf, char *cpfFormato)
{
    int j = 0;

    for (int i = 0; i < 11; i++)
    {
        if (i == 3 || i == 6)
        {
            cpfFormato[j++] = '.';
        }
        else if (i == 9)
        {
            cpfFormato[j++] = '-';
        }
        cpfFormato[j++] = cpf[i];
    }
    cpfFormato[j] = '\0';
}

#define MAX_RESERVAS 2
#define DIAS_DA_SEMANA 4

int main()
{
    setlocale(LC_ALL,"");

    Reserva reservas[MAX_RESERVAS];
    int opcao, dia, totalReservas = 0;
    int reservasDia[DIAS_DA_SEMANA] = {0};
    int limiteReservasDia[DIAS_DA_SEMANA] = {2, 2, 2, 2};
    char resposta;
    int i;
    int totalPessoas[DIAS_DA_SEMANA] = {0};

    do
    {
        printf("--------------- Escolha uma opção ---------------\n\n");
        printf("1-Fazer reserva\n");
        printf("2-Listar reservas\n");
        printf("3-Total de pessoas por dia\n");
        printf("4-Sair\n\n");
        scanf("%d", &opcao);  // Lê a opção
        getchar();
        printf("\n");

        switch (opcao)
        {
        case 1:
            if (totalReservas < MAX_RESERVAS)
            {
                do
                {
                    printf("--------------- Fazer reserva ---------------\n\n");

                    printf("Informe o nome de quem vai reservar:\n");
                    fgets(reservas[totalReservas].nome, sizeof(reservas[totalReservas].nome), stdin);
                    reservas[totalReservas].nome[strcspn(reservas[totalReservas].nome, "\n")] = '\0';

                    printf("Informe o CPF do cliente:\n");
                    fgets(reservas[totalReservas].cpf, sizeof(reservas[totalReservas].cpf), stdin);
                    reservas[totalReservas].cpf[strcspn(reservas[totalReservas].cpf, "\n")] = 0;

                    validarCpf(reservas[totalReservas].cpf);

                    printf("Informe para quantas pessoas é a reserva:\n");
                    scanf("%d", &reservas[totalReservas].quantidadePessoas);
                    printf("\n");

                    bool diaValido = false;

                    do
                    {
                        printf("Para qual dia é reserva:\n");
                        printf("1-Quinta-feira\n");
                        printf("2-Sexta-feira\n");
                        printf("3-Sábado\n");
                        printf("4-Domingo\n\n");
                        scanf("%d", &dia);
                        printf("\n");

                        if (dia < 1 || dia > 4)
                        {
                            printf("\n----- Opção inválida -----\n\n");
                        }
                        else
                        {
                            if (reservasDia[dia - 1] < limiteReservasDia[dia - 1])
                            {
                                reservas[totalReservas].dia = dia;
                                reservasDia[dia - 1]++;
                                totalPessoas[dia - 1] += reservas[totalReservas].quantidadePessoas;
                                totalReservas++;

                                printf("Reserva registrada!\n\n");
                                diaValido = true;
                            }
                            else
                            {
                                printf("Limite de reservas excedido!\n");
                            }
                        }
                    }
                    while (!diaValido);

                    printf("Para continuar digite s/n:\n\n");
                    scanf(" %c", &resposta);

                }
                while (resposta == 's' || resposta == 'S');
            }
            else
            {
                printf("Limite de reservas excedido!\n");
            }
            break;

        case 2:
            printf("--------------- Listar reservas ---------------\n\n");

            for (i = 0; i < totalReservas; i++)
            {
                char cpfFormato[15];
                formatarCpf(reservas[i].cpf, cpfFormato);

                printf("Nome: %s\n", reservas[i].nome);
                printf("Cpf: %s\n", cpfFormato);
                printf("Quantidade de pessoas: %d\n", reservas[i].quantidadePessoas);
                printf("Dia: ");
                switch (reservas[i].dia)
                {
                case 1:
                    printf("Quinta");
                    break;
                case 2:
                    printf("Sexta");
                    break;
                case 3:
                    printf("Sábado");
                    break;
                case 4:
                    printf("Domingo");
                    break;
                default:
                    printf("Opção inválida!\n");
                }
                printf("---------------\n\n");
            }
            break;

        case 3:
            printf("--------------- Total de pessoas por dia ---------------\n\n");
            printf("Quinta-feira %d\n", totalPessoas[0]);
            printf("Sexta-feira %d\n", totalPessoas[1]);
            printf("Sábado %d\n", totalPessoas[2]);
            printf("Domingo %d\n", totalPessoas[3]);
            break;

        case 4:
            printf("Encerrando...\n");
            Sleep(2000);
           ExitProcess(0);
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }
    }
    while (opcao != 4);   // Loop principal

    return 0;
}
