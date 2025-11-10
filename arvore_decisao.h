#ifndef ARVORE_DECISAO_H
#define ARVORE_DECISAO_H

// Este módulo precisa saber o que é "Personagem" para modificá-lo
#include "personagem.h"

// --- Protótipos das Funções (O "Contrato" do Aluno 3) ---

/**
 * @brief Exibe um menu de decisão que pode levar a outros submenus.
 * @param p O personagem que sofrerá as consequências.
 * @param id_nivel_decisao O ID do menu/nível atual da árvore.
 * @req [Conceito: Recursão]
 */
void exibirMenuDecisao(Personagem* p, int id_nivel_decisao);

#endif // ARVORE_DECISAO_H