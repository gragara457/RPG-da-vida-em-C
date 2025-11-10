#ifndef PERSONAGEM_H
#define PERSONAGEM_H

// --- Definição da Estrutura Principal ---
// Define a estrutura de dados central do jogo.
typedef struct {
    int saude;
    int felicidade;
    int dinheiro;
    int ano_atual;
} Personagem;

// --- Protótipos das Funções (O "Contrato" do Aluno 1) ---

/**
 * @brief Aloca memória e inicializa um novo personagem.
 * @req [Conceito: Alocação Dinâmica (malloc)]
 */
Personagem* criarPersonagem();

/**
 * @brief Libera a memória alocada para o personagem.
 * @req [Conceito: Alocação Dinâmica (free)]
 */
void liberarPersonagem(Personagem* p);

/**
 * @brief Exibe os atributos atuais do personagem na tela.
 * @req [Conceito: Ponteiros (acesso ->)]
 */
void exibirStatus(Personagem* p);

/**
 * @brief Modifica os atributos do personagem (passagem por referência).
 * @req [Conceito: Ponteiros (modificação de struct)]
 */
void aplicarEvento(Personagem* p, int mod_saude, int mod_felicidade, int mod_dinheiro);

/**
 * @brief Verifica se o jogo deve continuar.
 */
int jogoContinua(Personagem* p);

#endif // PERSONAGEM_H