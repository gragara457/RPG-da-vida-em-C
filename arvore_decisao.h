#ifndef ARVORE_DECISAO_H
#define ARVORE_DECISAO_H

// Este módulo precisa saber o que é "Personagem" para modificá-lo
#include "personagem.h"

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

#endif // ARVORE_DECISAO_H