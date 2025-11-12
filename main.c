// Arquivo: main.c
#include <stdio.h>
#include <stdlib.h>

// Nossos arquivos de cabeçalho
#include "personagem.h"
#include "inventario.h"
#include "arvore_decisao.h"

// --- Função Principal (main) ---
int main() {
    printf("\n");
    printf("========================================\n");
    printf("                                        \n");
    printf("       RPG DA VIDA EM C                 \n");
    printf("                                        \n");
    printf("   Viva uma vida completa e tome        \n");
    printf("   decisoes que moldarao seu destino!   \n");
    printf("                                        \n");
    printf("========================================\n\n");

    // 1. Criação do Personagem (Alocação Dinâmica)
    Personagem* jogador = criarPersonagem();
    NoLista* inventario = NULL; // Lista Ligada começa vazia

    if (jogador == NULL) {
        printf("Erro fatal: Não foi possível alocar memória para o jogador.\n");
        return 1;
    }

    // 2. Loop Principal do Jogo - Avança de 5 em 5 anos
    while (jogoContinua(jogador)) {
        
        // Exibe o status atual
        exibirStatus(jogador);
        
        // A cada ciclo, apresenta uma decisão baseada na idade
        exibirMenuDecisao(jogador, 0);
        
        // Avança 5 anos
        printf("\nPassaram-se 5 anos...\n");
        jogador->ano_atual += 5;
        
        // Aplica a perda de saúde pelo envelhecimento
        printf("O tempo cobra seu preco: -5 Saude\n");
        aplicarEvento(jogador, -5, 0, 0);
        
        // Pequena pausa para o jogador acompanhar
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n'); // Limpa buffer
        getchar(); // Espera o ENTER
    }

    // 3. Fim do Jogo - Exibe status final
    printf("\n");
    printf("========================================\n");
    printf("                                        \n");
    printf("           FIM DE JOGO                  \n");
    printf("                                        \n");
    printf("========================================\n");
    
    exibirStatus(jogador);
    exibirInventario(inventario);

    // 4. Limpeza (Liberação de Memória)
    liberarInventario(&inventario);
    liberarPersonagem(jogador);

    printf("\nObrigado por jogar!\n");
    return 0;
}