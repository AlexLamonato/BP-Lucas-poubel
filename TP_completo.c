#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    char N[36];
    float Valor;
    int T;
} Dados;

int Maior_0(int V);
void Titulo1();
void Titulo2();
void Titulo3();
void Circulante(int X, Dados B[X]);
void Nao_Circulante(int X, Dados B[X]);
int Balanco_Patrimonial(float *SA2, float *SP2, float *SAC2, float *SPC2, float *E2, float *CRC2, float *F2);
int Demonstracao_Resultado_Exercicio(float *CMV2, float *RL2, float *LB2, float *LO2, float *LL2);
void Indices(float SA2, float SP2, float SAC2, float SPC2, float E2, float CRC2, float CMV2, float RL2, float LB2, float LO2, float LL2, float F2);

int main()
{
    int O;
    float SA = 0, SP = 0, SAC = 0, SPC = 0, E, CRC, F, C[2] = {0, 0}, CMV, RL, LB, LO, LL;

    do
    {
        printf("====================\n");
        printf("        MENU          *Os Indices que serao calculados terao como base o ultimo BP e DRE registrado*\n");
        printf("====================\n\n");
        printf("1 - BP\n");
        printf("2 - DRE\n");
        printf("3 - Indices\n");
        printf("4 - Sair\n\n");
        printf("Escolha: ");
        scanf("%d", &O);

        system("cls");

        switch(O)
        {
            case 1:
                SA = SP = SAC = SPC = 0;
                C[0] = Balanco_Patrimonial(&SA, &SP, &SAC, &SPC, &E, &CRC, &F);
                system("pause");
                break;

            case 2:
                C[1] = Demonstracao_Resultado_Exercicio(&CMV, &RL, &LB, &LO, &LL);
                system("pause");
                break;

            case 3:
                if(C[0] == 1 && C[1] == 1)
                {
                    Indices(SA, SP, SAC, SPC, E, CRC, CMV, RL, LB, LO, LL, F);
                }
                else
                {
                    printf("Voce precisa fazer o BP e a DRE primeiro!\n\n");
                }
                system("pause");
                break;
        }

        system("cls");

    } while(O != 4);

    printf("Saindo do sistema...\n");

    return 0;
}

int Maior_0(int V)
{
    if(V < 1)
    {
        printf("\n*Por favor, insira um valor maior que 0*\n\n\n");
        system("pause");
        system("cls");
        return 0;
    }
    return 1;
}

void Titulo1()
{
    printf("=======================\n");
    printf("  BALANCO PATRIMONIAL  : Dados dos ativos\n");
    printf("=======================\n\n");
}

void Titulo2()
{
    printf("=======================\n");
    printf("  BALANCO PATRIMONIAL  : Dados dos passivos\n");
    printf("=======================\n\n");
}

void Titulo3()
{
    printf("=======================\n");
    printf("  BALANCO PATRIMONIAL  : Dados do patrimonio liquido\n");
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

int Balanco_Patrimonial(float *SA2, float *SP2, float *SAC2, float *SPC2, float *E2, float *CRC2, float *F2)
{
   int QA, QP, QV, i, j;
   float Soma_Patrimonio_Liquido = 0;

   do
   {
     printf("=======================\n");
     printf("  BALANCO PATRIMONIAL  : Ativos e Passivos\n");
     printf("=======================\n\n");

     printf("- Quantidade de ativos: ");
     scanf("%d", &QA);

     if(Maior_0(QA) == 1)
     {
       printf("- Quantidade de passivos: ");
       scanf("%d", &QP);

       if(Maior_0(QP) == 1)
       {
         printf("- Quantidade de valores do PL: ");
         scanf("%d", &QV);

         Maior_0(QV);
       }
     }
   }while((QA < 1) || (QP < 1) || (QV < 1));

   Dados A[QA], P[QP], Patrimonio_liquido[QV];

   system("cls");

   do
   {
     Titulo1();

     printf("Nome: Estoque (obrigatorio)\n");
     printf("Valor: ");
     scanf("%f", E2);

     if(*E2 < 0)
     {
       printf("\n*Por favor, insira um valor maior ou igual a 0*\n\n\n");

       system("pause");
       system("cls");
     }
     else
     {
       printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");
       printf("Nome: Contas a receber de clientes (obrigatorio)\n");
       printf("Valor: ");
       scanf("%f", CRC2);

       if(*CRC2 < 0)
       {
         printf("\n*Por favor, insira um valor maior ou igual a 0*\n\n\n");

         system("pause");
         system("cls");
       }
     }
   }while((*E2 < 0) || (*CRC2 < 0));

   printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

   for(i = 0; i < QA; i++)
   {
      printf("Nome: ");
      scanf(" %[^\n]s", A[i].N);
      printf("Valor(R$): ");
      scanf("%f", &A[i].Valor);

      if(A[i].Valor <= 0)
      {
        printf("\n*Por favor, insira um valor maior que 0*\n\n\n");

        system("pause");
        system("cls");

        Titulo1();

        printf("Nome: Estoque (obrigatorio)\n");
        printf("Valor: %.2f\n", *E2);
        printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");
        printf("Nome: Contas a receber de clientes (obrigatorio)\n");
        printf("Valor: %.2f\n", *CRC2);
        printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

        if(i > 0)
        {
          for(j = 0; j < i; j++)
          {
             printf("Nome: %s\n", A[j].N);
             printf("Valor(R$): %.2f\n", A[j].Valor);
             printf("Tipo (1 -> circulante / 2 -> não circulante): %d\n\n", A[j].T);
          }
        }

        i--;
      }
      else
      {
        printf("Tipo (1 -> circulante / 2 -> não circulante): ");
        scanf("%d", &A[i].T);

        if((A[i].T != 1) && (A[i].T != 2))
        {
          printf("\n*Esta opção não existe, por favor escolha novamente*\n\n\n");

          system("pause");
          system("cls");

          Titulo1();

          printf("Nome: Estoque (obrigatorio)\n");
          printf("Valor: %.2f\n", *E2);
          printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");
          printf("Nome: Contas a receber de clientes (obrigatorio)\n");
          printf("Valor: %.2f\n", *CRC2);
          printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

          if(i > 0)
          {
            for(j = 0; j < i; j++)
            {
               printf("Nome: %s\n", A[j].N);
               printf("Valor(R$): %.2f\n", A[j].Valor);
               printf("Tipo (1 -> circulante / 2 -> não circulante): %d\n\n", A[j].T);
            }
          }

          i--;
        }
        else
        {
          *SA2 = *SA2 + A[i].Valor;

          if(A[i].T == 1)
          {
            *SAC2 = *SAC2 + A[i].Valor;
          }

          printf("\n");
        }
      }
   }

   system("cls");

   do
   {
     Titulo2();

     printf("Nome: Fornecedores (obrigatorio)\n");
     printf("Valor: ");
     scanf("%f", F2);

     if(*F2 < 0)
     {
       printf("\n*Por favor, insira um valor maior ou igual a 0*\n\n\n");

       system("pause");
       system("cls");
     }
   }while(*F2 < 0);

   printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

   for(i = 0; i < QP; i++)
   {
      printf("Nome: ");
      scanf(" %[^\n]s", P[i].N);
      printf("Valor(R$): ");
      scanf("%f", &P[i].Valor);

      if(P[i].Valor <= 0)
      {
        printf("\n*Por favor, insira um valor maior que 0*\n\n\n");

        system("pause");
        system("cls");

        Titulo2();

        printf("Nome: Fornecedores (obrigatorio)\n");
        printf("Valor: %.2f\n ", *F2);
        printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

        if(i > 0)
        {
          for(j = 0; j < i; j++)
          {
             printf("Nome: %s\n", P[j].N);
             printf("Valor(R$): %.2f\n", P[j].Valor);
             printf("Tipo (1 -> circulante / 2 -> não circulante): %d\n\n", P[j].T);
          }
        }

        i--;
      }
      else
      {
        printf("Tipo (1 -> circulante / 2 -> não circulante): ");
        scanf("%d", &P[i].T);
        printf("\n");

        if((P[i].T != 1) && (P[i].T != 2))
        {
          printf("*Esta opção não existe, por favor escolha novamente*\n\n\n");

          system("pause");
          system("cls");

          Titulo2();

          printf("Nome: Fornecedores (obrigatorio)\n");
          printf("Valor: %.2f", *F2);
          printf("Tipo (1 -> circulante / 2 -> nao circulante): 1\n\n");

          if(i > 0)
          {
            for(j = 0; j < i; j++)
            {
               printf("Nome: %s\n", P[j].N);
               printf("Valor(R$): %.2f\n", P[j].Valor);
               printf("Tipo (1 -> circulante / 2 -> não circulante): %d\n\n", P[j].T);
            }
          }

          i--;
        }
        else
        {
          *SP2 = *SP2 + P[i].Valor;

          if(P[i].T == 1)
          {
            *SPC2 = *SPC2 + P[i].Valor;
          }
        }
      }
   }

   system("cls");

   Titulo3();

   for(i = 0; i < QV; i++)
   {
      printf("Nome: ");
      scanf(" %[^\n]s", Patrimonio_liquido[i].N);
      printf("Valor(R$): ");
      scanf("%f", &Patrimonio_liquido[i].Valor);

      if(Patrimonio_liquido[i].Valor <= 0)
      {
        printf("\n*Por favor, insira um valor maior que 0*\n\n\n");

        system("pause");
        system("cls");

        Titulo3();

        if(i > 0)
        {
          for(j = 0; j < i; j++)
          {
             printf("Nome: %s\n", Patrimonio_liquido[j].N);
             printf("Valor(R$): %.2f\n\n", Patrimonio_liquido[j].Valor);
          }
        }

        i--;
      }
      else
      {
        Soma_Patrimonio_Liquido = Soma_Patrimonio_Liquido + Patrimonio_liquido[i].Valor;

        printf("\n");
      }
   }

   system("cls");

   printf("=======================\n");
   printf("  BALANÇO PATRIMONIAL  : Resultados\n");
   printf("=======================\n\n");

   printf("-------------------------------\n");
   printf("*ATIVOS*\n");
   printf("-------------------------------\n");
   printf("Circulantes:\n");
   printf("- Estoque: %.2f\n", *E2);
   printf("- Contas a receber do cliente: %.2f\n", *CRC2);

   Circulante(QA, A);

   printf("\nNão circulantes:\n");

   Nao_Circulante(QA, A);

   printf("\nTotal: %.2f\n", *SA2);

   printf("-------------------------------\n");

   printf("-------------------------------\n");
   printf("*PASSIVOS + PL*\n");
   printf("-------------------------------\n");
   printf("Passivos circulantes:\n");
   printf("- Fornecedores: %.2f\n", *F2);

   Circulante(QP, P);

   printf("\nPassivos não circulantes:\n");

   Nao_Circulante(QP, P);

   printf("\nPatrimônio líquido:\n");

   for(i = 0; i < QV; i++)
   {
      printf("- %s: %.2f\n", Patrimonio_liquido[i].N, Patrimonio_liquido[i].Valor);
   }

   printf("\nTotal passivos: %.2f\n", *SP2);
   printf("\nTotal PL: %.2f\n", Soma_Patrimonio_Liquido);
   printf("\nPassivos + PL: %.2f\n", *SP2 + Soma_Patrimonio_Liquido);
   printf("-------------------------------\n");
   printf("\nBP = %.2f\n\n", *SA2 - (*SP2 + Soma_Patrimonio_Liquido));
   printf("-------------------------------\n\n\n");

   return 1;
}

int Demonstracao_Resultado_Exercicio(float *CMV2, float *RL2, float *LB2, float *LO2, float *LL2)
{
    float receita_bruta, descontos, despesas_operacionais, resultado_financeiro, outras_receitas;

    printf("=======================\n");
    printf("          DRE          \n");
    printf("=======================\n\n");

    printf("Receita Bruta: ");
    scanf("%f", &receita_bruta);

    printf("Descontos: ");
    scanf("%f", &descontos);

    *RL2 = receita_bruta - descontos;

    printf("Custos (CMV): ");
    scanf("%f", CMV2);

    *LB2 = *RL2 - *CMV2;

    printf("Despesas Operacionais: ");
    scanf("%f", &despesas_operacionais);

    printf("Resultado Financeiro: ");
    scanf("%f", &resultado_financeiro);

    printf("Outras Receitas: ");
    scanf("%f", &outras_receitas);

    *LO2 = *LB2 - despesas_operacionais;

    *LL2 = *LO2 + resultado_financeiro + outras_receitas;

    system("cls");

    printf("=======================\n");
    printf("      DRE FINAL        \n");
    printf("=======================\n\n");

    printf("Receita Liquida: %.2f\n", *RL2);
    printf("Lucro Bruto: %.2f\n", *LB2);
    printf("Lucro Operacional: %.2f\n", *LO2);
    printf("Lucro Liquido: %.2f\n", *LL2);

    printf("\n=======================\n");

    if(*LL2 > 0)
        printf("Resultado: LUCRO\n");
    else if(*LL2 < 0)
        printf("Resultado: PREJUIZO\n");
    else
        printf("Resultado: EMPATE\n");

    printf("\n");

    return 1;
}

void Indices(float SA2, float SP2, float SAC2, float SPC2, float E2, float CRC2, float CMV2, float RL2, float LB2, float LO2, float LL2, float F2)
{
    float Liquidez_Corrente = 0, Liquidez_Seca = 0, Giro_Estoque = 0, PMR = 0, PMP = 0, Giro_Ativo = 0, Endividamento = 0, Margem_Bruta = 0, Margem_Operacional = 0, Margem_Liquida = 0;

    printf("=======================\n");
    printf("        INDICES        \n");
    printf("=======================\n\n");

    printf("LIQUIDEZ\n");

    if(SPC2 != 0)
    {
        Liquidez_Corrente = SAC2 / SPC2;
        Liquidez_Seca = (SAC2 - E2) / SPC2;
    }

    printf("Liquidez Corrente: %.2f\n", Liquidez_Corrente);
    printf("Liquidez Seca: %.2f\n\n", Liquidez_Seca);

    printf("ATIVIDADE\n");

    if(E2 != 0)
        Giro_Estoque = CMV2 / E2;

    if(RL2 != 0)
    {
        PMR = CRC2 / (RL2 / 365);
        Giro_Ativo = RL2 / SA2;
    }

    if(CMV2 != 0)
        PMP = F2 / (CMV2 / 365);

    printf("Giro do Estoque: %.2f\n", Giro_Estoque);
    printf("Prazo Medio de Recebimento: %.2f dias\n", PMR);
    printf("Prazo Medio de Pagamento: %.2f dias\n", PMP);
    printf("Giro do Ativo Total: %.2f\n\n", Giro_Ativo);

    printf("ENDIVIDAMENTO\n");

    if(SA2 != 0)
        Endividamento = SP2 / SA2;

    printf("Endividamento Geral: %.2f\n\n", Endividamento);

    printf("RENTABILIDADE\n");

    if(RL2 != 0)
    {
        Margem_Bruta = (LB2 / RL2) * 100;
        Margem_Operacional = (LO2 / RL2) * 100;
        Margem_Liquida = (LL2 / RL2) * 100;
    }

    printf("Margem de Lucro Bruto: %.2f%%\n", Margem_Bruta);
    printf("Margem Operacional: %.2f%%\n", Margem_Operacional);
    printf("Margem Liquida: %.2f%%\n\n", Margem_Liquida);
}
