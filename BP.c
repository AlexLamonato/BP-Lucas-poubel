#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <math.h>

typedef struct{
    char N[36];
    float Valor;
    int T;    // 1 = Circulante / 2 = Não Circulante
    int Tag;  // Identificador para índices específicos
} Dados;

// DRE
float DRE_Completo(float *receita_liquida, float *lucro_bruto, float *lucro_operacional, float *custos);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int QA, QP, QV, i;
    float SA = 0, SP = 0, Soma_PL = 0;
    float receita_liquida = 0, lucro_bruto = 0, lucro_operacional = 0, custos_vendas = 0;

    printf("========================================\n");
    printf("               DRE                      \n");
    printf("========================================\n\n");

    float lucro_liquido = DRE_Completo(&receita_liquida, &lucro_bruto, &lucro_operacional, &custos_vendas);

    printf("\n========================================\n");
    printf("        BALANCO PATRIMONIAL             \n");
    printf("========================================\n\n");

    do { printf("Quantidade de ativos: "); scanf("%d", &QA); } while(QA <= 0);
    do { printf("Quantidade de passivos: "); scanf("%d", &QP); } while(QP <= 0);
    do { printf("Quantidade de contas do PL: "); scanf("%d", &QV); } while(QV <= 0);

    Dados A[QA], P[QP], PL[QV];
    float Ativo_Circulante = 0, Passivo_Circulante = 0;
    float Estoque = 0, Contas_Receber = 0, Fornecedores = 0;

    system("cls");

    // ATIVOS
    printf("=========== ATIVOS ===========\n");
    printf("Tags: [1] Estoque | [2] Contas a Receber | [0] Outros\n\n");
    for(i = 0; i < QA; i++) {
        printf("Ativo %d - Nome: ", i+1);
        scanf(" %[^\n]", A[i].N);
        printf("Valor (R$): ");
        scanf("%f", &A[i].Valor);
        printf("Tipo (1=Circ, 2=Nao Circ): ");
        scanf("%d", &A[i].T);
        printf("Tag (0, 1 ou 2): ");
        scanf("%d", &A[i].Tag);

        SA += A[i].Valor;
        if(A[i].T == 1) {
            Ativo_Circulante += A[i].Valor;
            if(A[i].Tag == 1) Estoque += A[i].Valor;
            if(A[i].Tag == 2) Contas_Receber += A[i].Valor;
        }
        printf("\n");
    }

    // PASSIVOS
    printf("=========== PASSIVOS ===========\n");
    printf("Tags: [1] Fornecedores | [0] Outros\n\n");
    for(i = 0; i < QP; i++) {
        printf("Passivo %d - Nome: ", i+1);
        scanf(" %[^\n]", P[i].N);
        printf("Valor (R$): ");
        scanf("%f", &P[i].Valor);
        printf("Tipo (1=Circ, 2=Nao Circ): ");
        scanf("%d", &P[i].T);
        printf("Tag (0 ou 1): ");
        scanf("%d", &P[i].Tag);

        SP += P[i].Valor;
        if(P[i].T == 1) {
            Passivo_Circulante += P[i].Valor;
            if(P[i].Tag == 1) Fornecedores += P[i].Valor;
        }
        printf("\n");
    }

    // PATRIMÔNIO LÍQUIDO
    printf("=========== PATRIMONIO LIQUIDO ===========\n\n");
    for(i = 0; i < QV; i++) {
        printf("Conta %d - Nome: ", i+1);
        scanf(" %[^\n]", PL[i].N);
        printf("Valor (R$): ");
        scanf("%f", &PL[i].Valor);
        Soma_PL += PL[i].Valor;
        printf("\n");
    }
    Soma_PL += lucro_liquido;

    system("cls");
    printf("========================================\n");
    printf("              RESULTADO                 \n");
    printf("========================================\n");
    printf("Total Ativos: %.2f | Total Passivos: %.2f | PL: %.2f\n", SA, SP, Soma_PL);
    printf("Diferenca (A - P - PL): %.2f\n", SA - (SP + Soma_PL));

    // CÁLCULO DOS ÍNDICES
    printf("\n========================================\n");
    printf("               INDICES                  \n");
    printf("========================================\n");

    // 1. Grupo Liquidez
    printf("\n--- LIQUIDEZ ---\n");
    if(Passivo_Circulante != 0) {
        printf("Liquidez Corrente: %.2f\n", Ativo_Circulante / Passivo_Circulante);
        printf("Liquidez Seca:     %.2f\n", (Ativo_Circulante - Estoque) / Passivo_Circulante);
    }

    // 2. Grupo Atividade
    printf("\n--- ATIVIDADE ---\n");
    if(Estoque != 0) 
        printf("Giro do Estoque:          %.2f\n", fabs(custos_vendas / Estoque));
    if(receita_liquida != 0) 
        printf("Prazo Medio Recebimento:  %.2f dias\n", (Contas_Receber / (receita_liquida / 365)));
    if(custos_vendas != 0)
        printf("Prazo Medio Pagamento:    %.2f dias\n", fabs(Fornecedores / (custos_vendas / 365))); // Usando custos como proxy de compras
    if(SA != 0)
        printf("Giro do Ativo Total:      %.2f\n", receita_liquida / SA);

    // 3. Grupo Endividamento
    printf("\n--- ENDIVIDAMENTO ---\n");
    if(SA != 0)
        printf("Endividamento Geral:      %.2f\n", SP / SA);

    // 4. Grupo Rentabilidade
    printf("\n--- RENTABILIDADE ---\n");
    if(receita_liquida != 0) {
        printf("Margem Bruta:             %.2f%%\n", (lucro_bruto / receita_liquida) * 100);
        printf("Margem Operacional:       %.2f%%\n", (lucro_operacional / receita_liquida) * 100);
        printf("Margem Liquida:           %.2f%%\n", (lucro_liquido / receita_liquida) * 100);
    }

    printf("\n========================================\n");
    return 0;
}

float DRE_Completo(float *receita_liquida, float *lucro_bruto, float *lucro_operacional, float *custos)
{
    float receita_bruta, descontos, despesas_op, rec_fin, desp_fin, outras_rec;

    printf("Receita Bruta: "); scanf("%f", &receita_bruta);
    printf("Descontos: "); scanf("%f", &descontos);
    *receita_liquida = receita_bruta - fabs(descontos);

    printf("Custos (CMV): "); scanf("%f", custos);
    *lucro_bruto = *receita_liquida - fabs(*custos);

    printf("Despesas Operacionais: "); scanf("%f", &despesas_op);
    *lucro_operacional = *lucro_bruto - fabs(despesas_op);

    printf("Receitas Financeiras: "); scanf("%f", &rec_fin);
    printf("Despesas Financeiras: "); scanf("%f", &desp_fin);
    printf("Outras Receitas: "); scanf("%f", &outras_rec);

    return *lucro_operacional + rec_fin - fabs(desp_fin) + outras_rec;
}