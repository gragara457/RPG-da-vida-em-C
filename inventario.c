#include "inventario.h"
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
    printf("Item '%s' adicionado ao inventário!\n", item.nome);
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
        printf("Item '%s' removido do inventário.\n", nome_item);
        free(atual);
    } else {
        printf("Item '%s' não encontrado.\n", nome_item);
    }
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
        temp = temp->proximo;
    }
    printf("--------------------\n");
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
    printf("Inventário liberado da memória.\n");
}