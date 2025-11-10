#ifndef INVENTARIO_H
#define INVENTARIO_H

// --- Definição das Estruturas da Lista ---

// O que será guardado na lista
typedef struct {
    char nome[100];
    int valor;
} ItemVida;

// O nó da lista ligada
// @req [Conceito: Lista Ligada (Nó)]
// @req [Conceito: Ponteiros (para o próximo)]
typedef struct NoLista {
    ItemVida item;
    struct NoLista* proximo;
} NoLista;

// --- Protótipos das Funções (O "Contrato" do Aluno 2) ---

/**
 * @brief Adiciona um novo item ao inventário.
 * @param lista_head Ponteiro para o ponteiro do início da lista.
 * @req [Conceito: Lista Ligada (Inserção)]
 * @req [Conceito: Alocação Dinâmica (malloc para o nó)]
 */
void adicionarItem(NoLista** lista_head, ItemVida item);

/**
 * @brief Remove um item específico do inventário.
 * @req [Conceito: Lista Ligada (Remoção)]
 * @req [Conceito: Alocação Dinâmica (free no nó)]
 */
void removerItem(NoLista** lista_head, const char* nome_item);

/**
 * @brief Exibe todos os itens no inventário.
 * @req [Conceito: Lista Ligada (Percorrer)]
 */
void exibirInventARIO(NoLista* lista_head);

/**
 * @brief Libera toda a memória alocada para a lista.
 * @req [Conceito: Alocação Dinâmica (free em cada nó)]
 */
void liberarInventario(NoLista** lista_head);

#endif // INVENTARIO_H