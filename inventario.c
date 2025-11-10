#include "inventario.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strcmp (comparar strings)

// Aluno 2: Implementar estas funções

void adicionarItem(NoLista** lista_head, ItemVida item) {
    // TODO: Alocar memória para um novo NoLista (malloc)
    // TODO: Preencher o novo nó com o 'item'
    // TODO: Ligar o novo nó ao início da lista (*lista_head)
    printf("Função 'adicionarItem' ainda não implementada.\n");
}

void removerItem(NoLista** lista_head, const char* nome_item) {
    // TODO: Percorrer a lista procurando pelo 'nome_item' (usar strcmp)
    // TODO: Se achar, remover o nó da lista (cuidado com os ponteiros anterior/proximo)
    // TODO: Liberar a memória do nó removido (free)
    printf("Função 'removerItem' ainda não implementada.\n");
}

void exibirInventARIO(NoLista* lista_head) {
    // TODO: Criar um ponteiro 'temp'
    // TODO: Fazer um loop (while temp != NULL)
    // TODO: Dentro do loop, imprimir o item (temp->item.nome) e avançar (temp = temp->proximo)
    printf("Função 'exibirInventARIO' ainda não implementada.\n");
}

void liberarInventario(NoLista** lista_head) {
    // TODO: Fazer um loop while que percorre a lista
    // TODO: Em cada iteração, guardar o 'proximo', dar 'free' no nó atual, e avançar
    // TODO: No final, setar *lista_head = NULL
    printf("Função 'liberarInventario' ainda não implementada.\n");
}