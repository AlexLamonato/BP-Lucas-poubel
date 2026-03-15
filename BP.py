import os

def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')

def maior_0(v):
    if v < 1:
        print("\n*Por favor, insira um valor maior que 0*\n")
        input("Pressione Enter para continuar...")
        limpar_tela()
        return False
    return True

def exibir_titulo(texto):
    print("=======================")
    print(f"  BALANÇO PATRIMONIAL  : {texto}")
    print("=======================\n")

def filtrar_por_tipo(lista, tipo_alvo):
    """Substitui as funções Circulante e Nao_Circulante do C"""
    for item in lista:
        if item['T'] == tipo_alvo:
            print(f"- {item['N']}: {item['Valor']:.2f}")

def main():
    qa = qp = qv = 0
    
    # Loop de validação inicial
    while True:
        exibir_titulo("Ativos e Passivos")
        try:
            qa = int(input("- Quantidade de ativos: "))
            if not maior_0(qa): continue
            
            qp = int(input("- Quantidade de passivos: "))
            if not maior_0(qp): continue
            
            qv = int(input("- Quantidade de valores do PL: "))
            if not maior_0(qv): continue
            break
        except ValueError:
            print("Entrada inválida! Digite números inteiros.")

    ativos = []
    passivos = []
    patrimonio_liquido = []
    
    # Coleta de Ativos
    limpar_tela()
    i = 0
    while i < qa:
        exibir_titulo("Dados dos ativos")
        # Mostra o que já foi digitado para manter a lógica do seu código C
        for item in ativos:
            print(f"Nome: {item['N']}\nValor(R$): {item['Valor']:.2f}\nTipo: {item['T']}\n")
            
        nome = input("Nome: ")
        try:
            valor = float(input("Valor(R$): "))
            if valor <= 0:
                print("\n*Por favor, insira um valor maior que 0*")
                input("Pressione Enter...")
                limpar_tela()
                continue
                
            tipo = int(input("Tipo (1 -> circulante / 2 -> não circulante): "))
            if tipo not in [1, 2]:
                print("*Esta opção não existe*")
                input("Pressione Enter...")
                limpar_tela()
                continue
            
            ativos.append({'N': nome, 'Valor': valor, 'T': tipo})
            i += 1
            limpar_tela()
        except ValueError:
            print("Valor inválido!")

    # Coleta de Passivos
    i = 0
    while i < qp:
        exibir_titulo("Dados dos passivos")
        for item in passivos:
            print(f"Nome: {item['N']}\nValor(R$): {item['Valor']:.2f}\nTipo: {item['T']}\n")
            
        nome = input("Nome: ")
        try:
            valor = float(input("Valor(R$): "))
            if valor <= 0:
                print("\n*Por favor, insira um valor maior que 0*")
                input("Pressione Enter...")
                limpar_tela()
                continue
                
            tipo = int(input("Tipo (1 -> circulante / 2 -> não circulante): "))
            if tipo not in [1, 2]:
                print("*Esta opção não existe*")
                input("Pressione Enter...")
                limpar_tela()
                continue
            
            passivos.append({'N': nome, 'Valor': valor, 'T': tipo})
            i += 1
            limpar_tela()
        except ValueError:
            print("Valor inválido!")

    # Coleta de PL
    i = 0
    while i < qv:
        exibir_titulo("Dados do patrimônio líquido")
        for item in patrimonio_liquido:
            print(f"- {item['N']}: {item['Valor']:.2f}")
            
        nome = input("\nNome: ")
        try:
            valor = float(input("Valor(R$): "))
            if valor <= 0:
                print("\n*Por favor, insira um valor maior que 0*")
                input("Pressione Enter...")
                limpar_tela()
                continue
                
            patrimonio_liquido.append({'N': nome, 'Valor': valor})
            i += 1
            limpar_tela()
        except ValueError:
            print("Valor inválido!")

    # Cálculos Finais
    sa = sum(item['Valor'] for item in ativos)
    sp = sum(item['Valor'] for item in passivos)
    spl = sum(item['Valor'] for item in patrimonio_liquido)

    # Exibição dos Resultados
    exibir_titulo("Resultados")
    
    print("-" * 31)
    print("ATIVOS")
    print("-" * 31)
    print("Circulantes:")
    filtrar_por_tipo(ativos, 1)
    print("\nNão circulantes:")
    filtrar_por_tipo(ativos, 2)
    print(f"\nTotal: {sa:.2f}")
    
    print("-" * 31 + "\n")
    print("-" * 31)
    print("PASSIVOS + PL")
    print("-" * 31)
    print("Passivos circulantes:")
    filtrar_por_tipo(passivos, 1)
    print("\nPassivos não circulantes:")
    filtrar_por_tipo(passivos, 2)
    
    print("\nPatrimônio líquido:")
    for item in patrimonio_liquido:
        print(f"- {item['N']}: {item['Valor']:.2f}")

    print(f"\nTotal passivos: {sp:.2f}")
    print(f"Total PL: {spl:.2f}")
    print(f"Passivos + PL: {sp + spl:.2f}")
    print("-" * 31)
    print(f"\nBP = {sa - (sp + spl):.2f}\n")
    print("-" * 31)

if __name__ == "__main__":
    main()