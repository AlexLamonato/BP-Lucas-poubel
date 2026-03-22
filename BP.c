#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <math.h>

typedef struct{
    char N[36];
    float Valor;
    int T;
}Dados;

// DRE
float DRE_Completo(float *receita_liquida, float *lucro_bruto, float *lucro_operacional);

// =========================

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int QA, QP, QV, i;
    float SA = 0, SP = 0, Soma_PL = 0;

    float receita_liquida = 0, lucro_bruto = 0, lucro_operacional = 0;

    printf("========================================\n");
    printf("               DRE                      \n");
    printf("========================================\n\n");

    float lucro_liquido = DRE_Completo(&receita_liquida, &lucro_bruto, &lucro_operacional);

    printf("\n========================================\n");
    printf("        BALANCO PATRIMONIAL             \n");
    printf("========================================\n\n");

    do {
        printf("Quantidade de ativos: ");
        scanf("%d", &QA);
    } while(QA <= 0);

    do {
        printf("Quantidade de passivos: ");
        scanf("%d", &QP);
    } while(QP <= 0);

    do {
        printf("Quantidade de contas do PL: ");
        scanf("%d", &QV);
    } while(QV <= 0);

    Dados A[QA], P[QP], PL[QV];

    float Ativo_Circulante = 0;
    float Passivo_Circulante = 0;
    float Estoque = 0;

    system("cls");

    // =========================
    // ATIVOS
    // =========================

    printf("=========== ATIVOS ===========\n");
    printf("[1] Estoque | [0] Outros\n\n");

    for(i = 0; i < QA; i++)
    {
        printf("Ativo %d\n", i+1);

        printf("Nome: ");
        scanf(" %[^\n]", A[i].N);

        printf("Valor (R$): ");
        scanf("%f", &A[i].Valor);

        printf("Tipo (1 = Circulante / 2 = Nao Circulante): ");
        scanf("%d", &A[i].T);

        SA += A[i].Valor;

        if(A[i].T == 1)
        {
            Ativo_Circulante += A[i].Valor;

            printf("Eh estoque? ");
            int e;
            scanf("%d", &e);
            if(e == 1)
                Estoque += A[i].Valor;
        }

        printf("\n");
    }

    // =========================
    // PASSIVOS
    // =========================

    printf("=========== PASSIVOS ===========\n\n");

    for(i = 0; i < QP; i++)
    {
        printf("Passivo %d\n", i+1);

        printf("Nome: ");
        scanf(" %[^\n]", P[i].N);

        printf("Valor (R$): ");
        scanf("%f", &P[i].Valor);

        printf("Tipo (1 = Circulante / 2 = Nao Circulante): ");
        scanf("%d", &P[i].T);

        SP += P[i].Valor;

        if(P[i].T == 1)
            Passivo_Circulante += P[i].Valor;

        printf("\n");
    }

    // =========================
    // PL
    // =========================

    printf("=========== PATRIMONIO LIQUIDO ===========\n");
    printf("(Nao incluir lucro do exercicio, ele sera adicionado automaticamente)\n\n");

    for(i = 0; i < QV; i++)
    {
        printf("Conta %d\n", i+1);

        printf("Nome: ");
        scanf(" %[^\n]", PL[i].N);

        printf("Valor (R$): ");
        scanf("%f", &PL[i].Valor);

        Soma_PL += PL[i].Valor;

        printf("\n");
    }

    // Lucro entra automaticamente
    Soma_PL += lucro_liquido;

    // =========================
    // RESULTADO
    // =========================

    system("cls");

    printf("========================================\n");
    printf("              RESULTADO                 \n");
    printf("========================================\n\n");

    printf("Total de Ativos.............: %.2f\n", SA);
    printf("Total de Passivos...........: %.2f\n", SP);
    printf("Patrimonio Liquido..........: %.2f\n", Soma_PL);

    printf("\nEquacao: Ativo = Passivo + PL\n");
    printf("Diferenca...................: %.2f\n", SA - (SP + Soma_PL));

    // =========================
    // INDICES
    // =========================

    printf("\n========================================\n");
    printf("               INDICES                  \n");
    printf("========================================\n\n");

    // Liquidez Corrente
    if(Passivo_Circulante != 0)
        printf("Liquidez Corrente..........: %.2f\n", Ativo_Circulante / Passivo_Circulante);
    else
        printf("Liquidez Corrente..........: N/A\n");

    // Liquidez Seca
    if(Passivo_Circulante != 0)
        printf("Liquidez Seca..............: %.2f\n", (Ativo_Circulante - Estoque) / Passivo_Circulante);
    else
        printf("Liquidez Seca..............: N/A\n");

    // Endividamento
    if(SA != 0)
        printf("Endividamento Geral........: %.2f\n", SP / SA);
    else
        printf("Endividamento Geral........: N/A\n");

    // Rentabilidade
    if(receita_liquida != 0)
    {
        printf("Margem Bruta...............: %.2f\n", lucro_bruto / receita_liquida);
        printf("Margem Operacional.........: %.2f\n", lucro_operacional / receita_liquida);
        printf("Margem Liquida.............: %.2f\n", lucro_liquido / receita_liquida);
    }
    else
    {
        printf("Margens....................: N/A\n");
    }

    printf("\n========================================\n");

    return 0;
}

// =========================
// DRE
// =========================

float DRE_Completo(float *receita_liquida, float *lucro_bruto, float *lucro_operacional)
{
    float receita_bruta, descontos, custos;
    float despesas_operacionais;
    float receitas_financeiras, despesas_financeiras;
    float outras_receitas;

    printf("Receita Bruta: ");
    scanf("%f", &receita_bruta);

    printf("Descontos: ");
    scanf("%f", &descontos);

    *receita_liquida = receita_bruta - fabs(descontos);

    printf("Custos: ");
    scanf("%f", &custos);

    *lucro_bruto = *receita_liquida - fabs(custos);

    printf("Despesas Operacionais: ");
    scanf("%f", &despesas_operacionais);

    *lucro_operacional = *lucro_bruto - fabs(despesas_operacionais);

    printf("Receitas Financeiras: ");
    scanf("%f", &receitas_financeiras);

    printf("Despesas Financeiras: ");
    scanf("%f", &despesas_financeiras);

    printf("Outras Receitas: ");
    scanf("%f", &outras_receitas);

    float lucro_liquido = *lucro_operacional
                        + receitas_financeiras
                        - fabs(despesas_financeiras)
                        + outras_receitas;

    return lucro_liquido;
}