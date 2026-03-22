#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

typedef struct{
    char N[36];
    float Valor;
    int T;
}Dados;

int Maior_0(int V);
void Titulo1();
void Titulo2();
void Titulo3();
void Circulante(int X, Dados B[X]);
void Nao_Circulante(int X, Dados B[X]);

// NOVA DRE
void DRE_Completo();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int QA, QP, QV;
    int i, j;

    float SA = 0, SP = 0, Soma_PL = 0;

    // =========================
    // DRE PRIMEIRO
    // =========================

    DRE_Completo();

    // =========================
    // BALANÇO PATRIMONIAL
    // =========================

    do
    {
        printf("=======================\n");
        printf("  BALANCO PATRIMONIAL\n");
        printf("=======================\n\n");

        printf("- Quantidade de ativos: ");
        scanf("%d", &QA);

        printf("- Quantidade de passivos: ");
        scanf("%d", &QP);

        printf("- Quantidade de PL: ");
        scanf("%d", &QV);

    }while((QA < 1) || (QP < 1) || (QV < 1));

    Dados A[QA], P[QP], PL[QV];

    system("cls");

    Titulo1();

    for(i = 0; i < QA; i++)
    {
        printf("Nome: ");
        scanf(" %[^\n]s", A[i].N);

        printf("Valor(R$): ");
        scanf("%f", &A[i].Valor);

        printf("Tipo (1 circulante / 2 nao): ");
        scanf("%d", &A[i].T);

        SA += A[i].Valor;

        system("cls");
        Titulo1();
    }

    system("cls");

    Titulo2();

    for(i = 0; i < QP; i++)
    {
        printf("Nome: ");
        scanf(" %[^\n]s", P[i].N);

        printf("Valor(R$): ");
        scanf("%f", &P[i].Valor);

        printf("Tipo (1 circulante / 2 nao): ");
        scanf("%d", &P[i].T);

        SP += P[i].Valor;
    }

    system("cls");

    Titulo3();

    for(i = 0; i < QV; i++)
    {
        printf("Nome: ");
        scanf(" %[^\n]s", PL[i].N);

        printf("Valor(R$): ");
        scanf("%f", &PL[i].Valor);

        Soma_PL += PL[i].Valor;
    }

    system("cls");

    printf("=======================\n");
    printf(" RESULTADO DO BALANCO \n");
    printf("=======================\n\n");

    printf("*ATIVOS*\n");
    printf("Circulantes:\n");
    Circulante(QA, A);

    printf("\nNao circulantes:\n");
    Nao_Circulante(QA, A);

    printf("\nTotal Ativos: %.2f\n\n", SA);

    printf("*PASSIVOS + PL*\n");

    printf("Passivos circulantes:\n");
    Circulante(QP, P);

    printf("\nPassivos nao circulantes:\n");
    Nao_Circulante(QP, P);

    printf("\nPatrimonio Liquido:\n");
    for(i = 0; i < QV; i++)
    {
        printf("- %s: %.2f\n", PL[i].N, PL[i].Valor);
    }

    printf("\nTotal Passivos: %.2f\n", SP);
    printf("Total PL: %.2f\n", Soma_PL);

    printf("\nPassivos + PL: %.2f\n", SP + Soma_PL);

    printf("\n-----------------------\n");
    printf("BP = %.2f\n", SA - (SP + Soma_PL));
    printf("-----------------------\n");

    return 0;
}

// =========================
// DRE COMPLETA
// =========================

void DRE_Completo()
{
    float receita_bruta;
    float descontos;
    float receita_liquida;

    float custos;
    float lucro_bruto;

    float despesas_operacionais;

    float resultado_financeiro;
    float outras_receitas;

    float lucro_liquido;

    printf("=======================\n");
    printf("          DRE          \n");
    printf("=======================\n\n");

    // ENTRADA POR BLOCOS
    printf("Receita Bruta (Vendas + Servicos): ");
    scanf("%f", &receita_bruta);

    printf("Descontos sobre vendas: ");
    scanf("%f", &descontos);

    receita_liquida = receita_bruta - descontos;

    printf("Custos (CMV + CSP): ");
    scanf("%f", &custos);

    lucro_bruto = receita_liquida - custos;

    printf("Despesas Operacionais (total): ");
    scanf("%f", &despesas_operacionais);

    printf("Resultado Financeiro (Receitas - Despesas Fin.): ");
    scanf("%f", &resultado_financeiro);

    printf("Outras Receitas: ");
    scanf("%f", &outras_receitas);

    // RESULTADO FINAL
    lucro_liquido = lucro_bruto
                    - despesas_operacionais
                    + resultado_financeiro
                    + outras_receitas;

    system("cls");

    // =========================
    // EXIBIÇÃO FORMATADA
    // =========================

    printf("=======================\n");
    printf("      DRE FINAL        \n");
    printf("=======================\n\n");

    printf("Receita Bruta: %.2f\n", receita_bruta);
    printf("(-) Descontos sobre Vendas: %.2f\n", descontos);
    printf("(=) Receita Liquida: %.2f\n\n", receita_liquida);

    printf("(-) Custos: %.2f\n", custos);
    printf("(=) Lucro Bruto: %.2f\n\n", lucro_bruto);

    printf("(-) Despesas Operacionais: %.2f\n", despesas_operacionais);
    printf("(+) Resultado Financeiro: %.2f\n", resultado_financeiro);
    printf("(+) Outras Receitas: %.2f\n\n", outras_receitas);

    printf("=======================\n");
    printf("LUCRO LIQUIDO DO EXERCICIO: %.2f\n", lucro_liquido);
    printf("=======================\n");

    if(lucro_liquido > 0)
        printf("Resultado: LUCRO\n");
    else if(lucro_liquido < 0)
        printf("Resultado: PREJUIZO\n");
    else
        printf("Resultado: EMPATE\n");

    printf("\n");

    system("pause");
    system("cls");
}

// =========================
// FUNÇÕES AUXILIARES
// =========================

int Maior_0(int V)
{
    if(V < 1)
        return 0;
    return 1;
}

void Titulo1()
{
    printf("=======================\n");
    printf("       ATIVOS          \n");
    printf("=======================\n\n");
}

void Titulo2()
{
    printf("=======================\n");
    printf("      PASSIVOS         \n");
    printf("=======================\n\n");
}

void Titulo3()
{
    printf("=======================\n");
    printf("  PATRIMONIO LIQUIDO  \n");
    printf("=======================\n\n");
}

void Circulante(int X, Dados B[X])
{
    int i;
    for(i = 0; i < X; i++)
    {
        if(B[i].T == 1)
            printf("- %s: %.2f\n", B[i].N, B[i].Valor);
    }
}

void Nao_Circulante(int X, Dados B[X])
{
    int i;
    for(i = 0; i < X; i++)
    {
        if(B[i].T == 2)
            printf("- %s: %.2f\n", B[i].N, B[i].Valor);
    }
}