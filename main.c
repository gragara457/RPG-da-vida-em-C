// Arquivo: main.c
#include <stdio.h>
#include <stdlib.h> // Para malloc, free, NULL

// Nossos arquivos de cabeçalho
#include "personagem.h"
#include "inventario.h"
#include "arvore_decisao.h"

// --- STUBS/ESQUELETOS DAS FUNÇÕES (Implementação) ---
// (Idealmente, isso estaria em arquivos .c separados, mas para um
//  exemplo inicial simples, podemos colocar aqui ou em um 'utils.c')

// --- Funções de Personagem (personagem.c) ---
Personagem* criarPersonagem() {
    // REQUISITO: Alocação Dinâmica (malloc)
    Personagem* p = (Personagem*) malloc(sizeof(Personagem));
    if (p != NULL) {
        // Inicializa os atributos
        p->saude = 100;
        p->felicidade = 80;
        p->dinheiro = 500;
        p->ano_atual = 18;
    }
    printf("Personagem criado com sucesso!\n");
    return p; // REQUISITO: Retornando um ponteiro
}

void liberarPersonagem(Personagem* p) {
    // REQUISITO: Alocação Dinâmica (free)
    if (p != NULL) {
        free(p);
    }
    printf("Personagem liberado da memória.\n");
}

void exibirStatus(Personagem* p) {
    if (p == NULL) return;
    // REQUISITO: Ponteiros (acesso com ->)
    printf("\n--- STATUS (Ano: %d) ---\n", p->ano_atual);
    printf("Saude: %d\n", p->saude);
    printf("Felicidade: %d\n", p->felicidade);
    printf("Dinheiro: R$ %d\n", p->dinheiro);
    printf("-------------------------\n");
}

void aplicarEvento(Personagem* p, int mod_saude, int mod_felicidade, int mod_dinheiro) {
    if (p == NULL) return;
    // REQUISITO: Ponteiros (modificando a struct original)
    p->saude += mod_saude;
    p->felicidade += mod_felicidade;
    p->dinheiro += mod_dinheiro;

    // Garante que os status não fiquem abaixo de 0 (exceto dinheiro)
    if (p->saude > 100) p->saude = 100;
    if (p->felicidade > 100) p->felicidade = 100;
    if (p->saude < 0) p->saude = 0;
}

int jogoContinua(Personagem* p) {
    p->ano_atual++; // Avança o tempo
    if (p->saude <= 0) {
        printf("Game Over: Sua saúde chegou a zero.\n");
        return 0;
    }
    if (p->ano_atual > 80) {
        printf("Fim de jogo: Você viveu uma vida longa!\n");
        return 0;
    }
    return 1;
}

// --- Funções de Inventário (inventario.c) ---
void adicionarItem(NoLista** lista_head, ItemVida item) {
    // REQUISITO: Alocação Dinâmica (malloc para o nó)
    NoLista* novo_no = (NoLista*) malloc(sizeof(NoLista));
    if (novo_no == NULL) {
        printf("Erro: Falha ao alocar memória para novo item!\n");
        return;
    }

    novo_no->item = item;
    novo_no->proximo = NULL;

    // REQUISITO: Lista Ligada (Inserção no início)
    // (Usamos *lista_head para acessar o ponteiro 'head' original)
    if (*lista_head == NULL) {
        *lista_head = novo_no;
    } else {
        // (Ou insere no fim, mas no início é mais fácil)
        novo_no->proximo = *lista_head;
        *lista_head = novo_no;
    }
    printf("Item '%s' adicionado ao inventário!\n", item.nome);
}

void exibirInventario(NoLista* lista_head) {
    printf("\n--- INVENTÁRIO ---\n");
    if (lista_head == NULL) {
        printf("Vazio.\n");
        return;
    }
    
    // REQUISITO: Lista Ligada (Percorrendo com ponteiro)
    NoLista* temp = lista_head;
    while (temp != NULL) {
        printf("- %s (Valor: %d)\n", temp->item.nome, temp->item.valor);
        temp = temp->proximo; // Avança para o próximo nó
    }
    printf("--------------------\n");
}

void liberarInventario(NoLista** lista_head) {
    NoLista* atual = *lista_head;
    NoLista* proximo;

    while (atual != NULL) {
        proximo = atual->proximo; // Guarda o próximo
        // REQUISITO: Alocação Dinâmica (free em cada nó)
        free(atual);              // Libera o atual
        atual = proximo;            // Move para o próximo
    }
    *lista_head = NULL; // Garante que a lista está vazia
    printf("Inventário liberado da memória.\n");
}


// --- Função da Árvore de Decisão (arvore_decisao.c) ---
void exibirMenuDecisao(Personagem* p, int id_nivel_decisao) {
    // REQUISITO: Recursão
    
    int escolha;

    // Nível 0 = Menu Principal de Carreira
    if (id_nivel_decisao == 0) {
        printf("\nDecisão de Carreira (Nível 0):\n");
        printf("1. Fazer Faculdade\n");
        printf("2. Abrir um negócio\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            // REQUISITO: Chamada Recursiva (indo para o Nível 1)
            exibirMenuDecisao(p, 1); 
        } else {
            printf("Você decidiu empreender! (Isso custou R$ 500)\n");
            aplicarEvento(p, 0, 5, -500);
            // REQUISITO: Caso Base (não chama mais a si mesmo)
        }
    }
    // Nível 1 = Menu de Cursos (só chega aqui se escolheu 1 no Nível 0)
    else if (id_nivel_decisao == 1) {
        printf("\nQual curso? (Nível 1):\n");
        printf("1. Ciência da Computação\n");
        printf("2. Medicina\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            printf("Você se formou em C. da Computação!\n");
            aplicarEvento(p, 0, 10, -200); // Custa menos
            // Adiciona o diploma (ItemVida)
            ItemVida diploma = {"Diploma CC", 10};
            // (Passamos o endereço da lista_head, mas não temos ela aqui...
            // ...isso mostra a necessidade de ligar o inventário ao personagem!)
            // Por enquanto, vamos pular a adição do item.
        } else {
            printf("Você se formou em Medicina!\n");
            aplicarEvento(p, 0, 15, -1000); // Custa mais
        }
        // REQUISITO: Caso Base (não chama mais a si mesmo)
    }
}


// --- Função Principal (main) ---
int main() {
    printf("Bem-vindo ao RPG da Vida em C!\n");

    // 1. Criação (Alocação Dinâmica)
    Personagem* jogador = criarPersonagem();
    NoLista* inventario = NULL; // Lista Ligada começa vazia

    if (jogador == NULL) {
        printf("Erro fatal: Não foi possível alocar memória para o jogador.\n");
        return 1;
    }

    int escolha_menu;
    
    // 2. Loop Principal do Jogo
    while (jogoContinua(jogador)) {
        exibirStatus(jogador); // Usa Ponteiro

        printf("\nO que fazer este ano? (Ano %d)\n", jogador->ano_atual);
        printf("1. Trabalhar (Ganha R$ 100, -5 Felicidade)\n");
        printf("2. Fazer uma grande decisão de carreira (Recursão)\n");
        printf("3. Ver Inventário (Lista Ligada)\n");
        printf("4. (TESTE) Ganhar um item\n");
        printf("0. Desistir da vida (Sair)\n");
        printf("Escolha: ");
        
        // Validação simples de entrada
        if (scanf("%d", &escolha_menu) != 1) {
            // Limpa o buffer de entrada se o usuário digitou lixo
            while (getchar() != '\n');
            escolha_menu = -1; // Força "opção inválida"
        }

        switch (escolha_menu) {
            case 1:
                // REQUISITO: Passando ponteiro para modificar
                aplicarEvento(jogador, 0, -5, 100);
                break;
            case 2:
                // REQUISITO: Chamando a função Recursiva
                exibirMenuDecisao(jogador, 0); // Começa do nível 0
                break;
            case 3:
                // REQUISITO: Passando ponteiro da lista para ler
                exibirInventario(inventario);
                break;
            case 4:
                { // (Usamos chaves para criar um escopo local para 'item_teste')
                    ItemVida item_teste = {"Relógio de Ouro", 50};
                    // REQUISITO: Passando ponteiro-para-ponteiro para modificar a lista
                    adicionarItem(&inventario, item_teste);
                }
                break;
            case 0:
                jogador->saude = 0; // Força o fim do jogo
                printf("Você decidiu encerrar o jogo.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    // 3. Limpeza (Liberação de Memória)
    printf("\n--- FIM DE JOGO ---\n");
    exibirStatus(jogador);
    exibirInventario(inventario);

    // REQUISITO: Limpando a Alocação Dinâmica
    liberarInventario(&inventario);
    liberarPersonagem(jogador);

    return 0;
}