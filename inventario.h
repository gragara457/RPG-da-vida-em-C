#ifndef INVENTARIO_H
#define INVENTARIO_H

// Forward declaration para evitar dependências circulares
struct Personagem;

// --- Definição das Estruturas da Lista ---

// O que será guardado na lista
typedef struct {
    char nome[100];
    int valor;
    char tipo[50]; // "consumivel", "permanente", "equipamento"
    int efeito_saude;
    int efeito_felicidade;
    int efeito_dinheiro;
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
void exibirInventario(NoLista* lista_head);

/**
 * @brief Libera toda a memória alocada para a lista.
 * @req [Conceito: Alocação Dinâmica (free em cada nó)]
 */
void liberarInventario(NoLista** lista_head);

/**
 * @brief Usa um item do inventário (se for consumível, remove da lista).
 * @param lista_head Ponteiro para o ponteiro do início da lista.
 * @param nome_item Nome do item a ser usado.
 * @param personagem Ponteiro para o personagem que receberá os efeitos.
 * @return 1 se o item foi usado com sucesso, 0 caso contrário.
 */
int usarItem(NoLista** lista_head, const char* nome_item, struct Personagem* personagem);

/**
 * @brief Cria um item com os parâmetros especificados.
 */
ItemVida criarItem(const char* nome, int valor, const char* tipo, int efeito_saude, int efeito_felicidade, int efeito_dinheiro);

/**
 * @brief Adiciona itens iniciais ao inventário.
 */
void adicionarItensIniciais(NoLista** lista_head);

#endif // INVENTARIO_H