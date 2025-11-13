#include "inventario.h"
#include "personagem.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strcmp (comparar strings)

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
    if (*lista_head == NULL) {
        *lista_head = novo_no;
    } else {
        novo_no->proximo = *lista_head;
        *lista_head = novo_no;
    }
    printf("Item '%s' adicionado ao inventario!\n", item.nome);
}

void removerItem(NoLista** lista_head, const char* nome_item) {
    if (*lista_head == NULL) return;
    
    NoLista* atual = *lista_head;
    NoLista* anterior = NULL;
    
    // Procura o item
    while (atual != NULL && strcmp(atual->item.nome, nome_item) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Se encontrou o item
    if (atual != NULL) {
        if (anterior == NULL) {
            // Item está no início
            *lista_head = atual->proximo;
        } else {
            // Item está no meio ou fim
            anterior->proximo = atual->proximo;
        }
        printf("Item '%s' removido do inventario.\n", nome_item);
        free(atual);
    } else {
        printf("Item '%s' não encontrado.\n", nome_item);
    }
}

void exibirInventario(NoLista* lista_head) {
    printf("\n=== INVENTARIO ===\n");
    if (lista_head == NULL) {
        printf("Vazio.\n");
        return;
    }
    
    // REQUISITO: Lista Ligada (Percorrendo com ponteiro)
    NoLista* temp = lista_head;
    int contador = 1;
    while (temp != NULL) {
        printf("%d. %s (%s)\n", contador, temp->item.nome, temp->item.tipo);
        printf("   Valor: R$ %d\n", temp->item.valor);
        if (temp->item.efeito_saude != 0 || temp->item.efeito_felicidade != 0 || temp->item.efeito_dinheiro != 0) {
            printf("   Efeitos ao usar: ");
            if (temp->item.efeito_saude != 0) printf("Saude %+d ", temp->item.efeito_saude);
            if (temp->item.efeito_felicidade != 0) printf("Felicidade %+d ", temp->item.efeito_felicidade);
            if (temp->item.efeito_dinheiro != 0) printf("Dinheiro %+d", temp->item.efeito_dinheiro);
            printf("\n");
        }
        printf("\n");
        temp = temp->proximo;
        contador++;
    }
    printf("==================\n");
}

void liberarInventario(NoLista** lista_head) {
    NoLista* atual = *lista_head;
    NoLista* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista_head = NULL;
    printf("Inventario liberado da memoria.\n");
}

ItemVida criarItem(const char* nome, int valor, const char* tipo, int efeito_saude, int efeito_felicidade, int efeito_dinheiro) {
    ItemVida item;
    strcpy(item.nome, nome);
    strcpy(item.tipo, tipo);
    item.valor = valor;
    item.efeito_saude = efeito_saude;
    item.efeito_felicidade = efeito_felicidade;
    item.efeito_dinheiro = efeito_dinheiro;
    return item;
}

int usarItem(NoLista** lista_head, const char* nome_item, struct Personagem* personagem) {
    if (*lista_head == NULL || personagem == NULL) return 0;
    
    NoLista* atual = *lista_head;
    NoLista* anterior = NULL;
    
    // Procura o item
    while (atual != NULL && strcmp(atual->item.nome, nome_item) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Se encontrou o item
    if (atual != NULL) {
        ItemVida item = atual->item;
        
        // Aplica os efeitos ao personagem usando a função externa
        printf("\nUsando %s...\n", item.nome);
        aplicarEvento((Personagem*)personagem, item.efeito_saude, item.efeito_felicidade, item.efeito_dinheiro);
        
        if (item.efeito_saude != 0) printf("Saúde %+d\n", item.efeito_saude);
        if (item.efeito_felicidade != 0) printf("Felicidade %+d\n", item.efeito_felicidade);
        if (item.efeito_dinheiro != 0) printf("Dinheiro %+d\n", item.efeito_dinheiro);
        
        // Remove o item se for consumível
        if (strcmp(item.tipo, "consumivel") == 0) {
            if (anterior == NULL) {
                *lista_head = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item %s foi consumido e removido do inventario.\n", item.nome);
        }
        
        return 1;
    } else {
        printf("Item '%s' nao encontrado no inventario.\n", nome_item);
        return 0;
    }
}

void adicionarItensIniciais(NoLista** lista_head) {
    // Itens consumiveis basicos - valor representa o preco do item, nao custo de uso
    ItemVida item1 = criarItem("Remedio Barato", 50, "consumivel", 15, 0, 0);
    ItemVida item2 = criarItem("Chocolate", 10, "consumivel", 0, 10, 0);
    ItemVida item3 = criarItem("Dinheiro Guardado", 1000, "consumivel", 0, 0, 1000);
    
    adicionarItem(lista_head, item1);
    adicionarItem(lista_head, item2);
    adicionarItem(lista_head, item3);
    
    printf("\nItens iniciais adicionados ao seu inventario!\n");
}