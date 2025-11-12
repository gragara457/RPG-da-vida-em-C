#include "personagem.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free

Personagem* criarPersonagem() {
    // REQUISITO: Alocação Dinâmica (malloc)
    Personagem* p = (Personagem*) malloc(sizeof(Personagem));
    if (p != NULL) {
        // Inicializa os atributos - começando aos 1 ano de idade
        p->saude = 100;
        p->felicidade = 100;
        p->dinheiro = 1000; // Começa com algum dinheiro
        p->ano_atual = 1;
        p->rodadas_sem_dinheiro = 0;
    }
    printf("\nBem-vindo a vida! Voce nasceu!\n");
    return p; // REQUISITO: Retornando um ponteiro
}

void liberarPersonagem(Personagem* p) {
    // REQUISITO: Alocação Dinâmica (free)
    if (p != NULL) {
        free(p);
    }
    printf("Memória do personagem liberada.\n");
}

void exibirStatus(Personagem* p) {
    if (p == NULL) return;
    // REQUISITO: Ponteiros (acesso com ->)
    printf("\n================================\n");
    printf("    STATUS - %d ANOS\n", p->ano_atual);
    printf("================================\n");
    printf(" Saude:       %d%%\n", p->saude);
    printf(" Felicidade:  %d%%\n", p->felicidade);
    printf(" Dinheiro:    R$ %d\n", p->dinheiro);
    printf("================================\n");
}

void aplicarEvento(Personagem* p, int mod_saude, int mod_felicidade, int mod_dinheiro) {
    if (p == NULL) return;
    // REQUISITO: Ponteiros (modificando a struct original)
    p->saude += mod_saude;
    p->felicidade += mod_felicidade;
    p->dinheiro += mod_dinheiro;

    // Limites dos atributos
    if (p->saude > 100) p->saude = 100;
    if (p->felicidade > 100) p->felicidade = 100;
    if (p->saude < 0) p->saude = 0;
    if (p->felicidade < 0) p->felicidade = 0;
}

int jogoContinua(Personagem* p) {
    if (p == NULL) return 0;
    
    // Verifica condições de game over
    if (p->saude <= 0) {
        printf("\nGAME OVER: Sua saude chegou a zero.\n");
        return 0;
    }
    
    if (p->felicidade <= 0) {
        printf("\nGAME OVER: Voce perdeu toda a felicidade e nao consegue mais continuar.\n");
        return 0;
    }
    
    if (p->ano_atual >= 80) {
        printf("\nFIM DE JOGO: Voce viveu uma vida longa e chegou aos 80 anos!\n");
        return 0;
    }
    
    // Verifica dinheiro negativo por 2+ rodadas consecutivas
    if (p->dinheiro <= 0) {
        p->rodadas_sem_dinheiro++;
        if (p->rodadas_sem_dinheiro >= 2) {
            printf("\nGAME OVER: Voce ficou sem dinheiro por tempo demais e faliu.\n");
            return 0;
        }
    } else {
        p->rodadas_sem_dinheiro = 0; // Reseta o contador se tiver dinheiro
    }
    
    return 1; // Jogo continua
}