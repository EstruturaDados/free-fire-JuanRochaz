#include <stdio.h>   // Biblioteca para entrada e saída de dados (printf, scanf, fgets)
#include <string.h>  // Biblioteca para manipulação de strings (strcmp, strlen)
#include <stdlib.h>  // Biblioteca para funções gerais (exit, se necessário, mas não usado aqui)

// Definição da struct Item
// Esta estrutura representa um item no inventário do jogador, com nome (até 29 chars + null),
// tipo (até 19 chars + null, ex: "arma", "munição", "cura") e quantidade (inteiro positivo).
typedef struct {
    char nome[30];     // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];     // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;    // Quantidade disponível (ex: 1 para arma, 30 para munição)
} Item;

// Protótipos das funções obrigatórias
// Essas funções manipulam o vetor de itens, garantindo usabilidade e eficiência.
// O parâmetro numItens é passado por referência em inserir/remover para atualizar o contador.
void inserirItem(Item itens[], int *numItens);
void removerItem(Item itens[], int *numItens);
void listarItens(Item itens[], int numItens);
void buscarItem(Item itens[], int numItens);

int main() {
    // Declaração do vetor de structs com capacidade para 10 itens
    // Isso permite armazenar até 10 itens de forma sequencial e eficiente em memória.
    Item itens[10];
    int numItens = 0;  // Contador de itens atuais (inicia em 0, máximo 10)
    int opcao;         // Variável para capturar a escolha do menu

    // Mensagem inicial para orientar o usuário (usabilidade)
    printf("=== Sistema de Inventario - Mochila de Loot (Free Fire Simulado) ===\n");
    printf("Voce pode cadastrar ate 10 itens. Use o menu abaixo para interagir.\n\n");

    // Laço principal do menu: while para manter o programa rodando até a saída
    // Usa switch para opções claras, facilitando a manutenção e leitura.
    while (1) {
        printf("Menu:\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item (por nome)\n");
        printf("3 - Listar Todos os Itens\n");
        printf("4 - Buscar Item (por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        // Leitura da opção com scanf (inteiro)
        if (scanf("%d", &opcao) != 1) {
            // Tratamento de erro simples para input inválido (limpa buffer)
            while (getchar() != '\n');
            printf("Opcao invalida! Tente novamente.\n\n");
            continue;
        }
        
        // Limpa o buffer após scanf para evitar problemas com fgets subsequentes
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                if (numItens < 10) {
                    inserirItem(itens, &numItens);
                    listarItens(itens, numItens);  // Listagem após operação (requisito)
                } else {
                    printf("Mochila cheia! Maximo de 10 itens.\n\n");
                }
                break;
            case 2:
                if (numItens > 0) {
                    removerItem(itens, &numItens);
                    listarItens(itens, numItens);  // Listagem após operação
                } else {
                    printf("Nenhum item na mochila!\n\n");
                }
                break;
            case 3:
                listarItens(itens, numItens);
                break;
            case 4:
                if (numItens > 0) {
                    buscarItem(itens, numItens);
                    // Opcional: listar após busca para contexto, mas foco na exibição do item
                    printf("\nInventario completo:\n");
                    listarItens(itens, numItens);
                } else {
                    printf("Nenhum item na mochila!\n\n");
                }
                break;
            case 0:
                printf("Saindo do sistema. Boa sorte no battle royale!\n");
                return 0;  // Sai do programa com sucesso
            default:
                printf("Opcao invalida! Escolha de 0 a 4.\n\n");
        }
        printf("\n");  // Separação para melhor usabilidade
    }

    return 0;  // Indica término bem-sucedido (não alcançado devido ao return no case 0)
}

// Função para inserir um novo item no vetor
// Verifica se há espaço (numItens < 10), lê dados com fgets para permitir espaços em nomes/tipos,
// e atualiza o contador. Mensagens orientativas para usabilidade.
void inserirItem(Item itens[], int *numItens) {
    printf("=== Inserir Novo Item ===\n");
    printf("Digite o nome do item: ");
    fgets(itens[*numItens].nome, 30, stdin);  // fgets permite espaços e é seguro (limite 30)
    // Remove newline do fgets (boa prática)
    itens[*numItens].nome[strcspn(itens[*numItens].nome, "\n")] = 0;
    
    printf("Digite o tipo (ex: arma, munição, cura): ");
    fgets(itens[*numItens].tipo, 20, stdin);
    itens[*numItens].tipo[strcspn(itens[*numItens].tipo, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &itens[*numItens].quantidade);
    // Limpa buffer após scanf
    while (getchar() != '\n');
    
    (*numItens)++;  // Incrementa o contador
    printf("Item inserido com sucesso!\n");
}

// Função para remover um item por nome (busca sequencial e deslocamento)
// Percorre o vetor com for, compara nomes com strcmp (case-sensitive),
// remove deslocando elementos e atualiza numItens. Tempo O(n), eficiente para n=10.
void removerItem(Item itens[], int *numItens) {
    char nomeBusca[30];
    printf("=== Remover Item ===\n");
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    int encontrado = 0;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(itens[i].nome, nomeBusca) == 0) {
            // Encontrado: desloca elementos à direita para "apagar" o item i
            for (int j = i; j < *numItens - 1; j++) {
                itens[j] = itens[j + 1];
            }
            (*numItens)--;
            encontrado = 1;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            break;  // Remove apenas o primeiro encontrado
        }
    }
    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila!\n", nomeBusca);
    }
    // Limpa buffer se necessário, mas fgets já lido
}

// Função para listar todos os itens (percorre com for)
// Exibe de forma formatada e clara, com verificação se vazio. Desempenho O(n).
void listarItens(Item itens[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Colete itens para comecar.\n");
        return;
    }
    
    printf("\n=== Lista de Itens na Mochila (%d itens) ===\n", numItens);
    for (int i = 0; i < numItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", itens[i].nome);
        printf("  Tipo: %s\n", itens[i].tipo);
        printf("  Quantidade: %d\n", itens[i].quantidade);
        printf("  ----------------\n");
    }
}

// Função para buscar um item por nome (busca sequencial com for e strcmp)
// Localiza o item e exibe seus dados. Se não encontrar, avisa. Tempo O(n), <2s trivial.
void buscarItem(Item itens[], int numItens) {
    char nomeBusca[30];
    printf("=== Buscar Item ===\n");
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    int encontrado = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(itens[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", itens[i].nome);
            printf("Tipo: %s\n", itens[i].tipo);
            printf("Quantidade: %d\n", itens[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila!\n", nomeBusca);
    }
}
