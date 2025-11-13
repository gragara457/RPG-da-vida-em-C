#ifndef ARVORE_DECISAO_H
#define ARVORE_DECISAO_H

// Este módulo precisa saber o que é "Personagem" para modificá-lo
#include "personagem.h"
#include "inventario.h"

// --- Protótipos das Funções ---

/**
 * @brief Exibe um menu de decisão baseado na idade do personagem.
 * @param p O personagem que sofrerá as consequências.
 * @param id_nivel_decisao O ID do menu/nível atual da árvore (não usado na nova versão).
 * @req [Conceito: Recursão]
 */
void exibirMenuDecisao(Personagem* p, int id_nivel_decisao);

/**
 * @brief Submenu para escolher qual faculdade fazer (chamada recursiva).
 */
void decisaoCarreiraFaculdade(Personagem* p);

/**
 * @brief Submenu para escolher qual negócio abrir (chamada recursiva).
 */
void decisaoCarreiraNegocio(Personagem* p);

/**
 * @brief Decisões sobre relacionamento e casamento (21-40 anos).
 */
void decisaoCasamento(Personagem* p);

/**
 * @brief Decisões sobre ter filhos (para pessoas casadas).
 */
void decisaoFilhos(Personagem* p);

/**
 * @brief Gerencia o menu de inventário e uso de itens.
 */
void gerenciarInventario(Personagem* p, NoLista** inventario);

/**
 * @brief Exibe o menu principal unificado e processa a escolha do jogador.
 * @return 1 se uma decisão foi feita, 0 para continuar no menu.
 */
int exibirMenuPrincipal(Personagem* p, NoLista** inventario);

/**
 * @brief Processa a escolha do menu baseada na idade do personagem.
 */
void processarEscolhaMenu(Personagem* p, int escolha);

#endif // ARVORE_DECISAO_H