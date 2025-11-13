#include "personagem.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strlen

Personagem* criarPersonagem() {
    // REQUISITO: Alocação Dinâmica (malloc)
    Personagem* p = (Personagem*) malloc(sizeof(Personagem));
    if (p != NULL) {
        printf("\nBem-vindo a vida! Voce nasceu!\n");
        printf("Qual eh o seu nome? ");
        fgets(p->nome, sizeof(p->nome), stdin);
        
        // Remove a quebra de linha do nome
        int len = strlen(p->nome);
        if (len > 0 && p->nome[len-1] == '\n') {
            p->nome[len-1] = '\0';
        }
        
        // Inicializa os atributos - começando aos 1 ano de idade
        p->saude = 100;
        p->felicidade = 100;
        p->dinheiro = 1000; // Começa com algum dinheiro
        p->ano_atual = 1;
        p->rodadas_sem_dinheiro = 0;
        p->casado = 0; // Começa solteiro
        p->filhos = 0; // Sem filhos
        
        printf("\nOla, %s! Sua jornada pela vida comeca agora!\n", p->nome);
    }
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
    printf("    %s - %d ANOS\n", p->nome, p->ano_atual);
    printf("================================\n");
    printf(" Saude:       %d%%\n", p->saude);
    printf(" Felicidade:  %d%%\n", p->felicidade);
    printf(" Dinheiro:    R$ %d\n", p->dinheiro);
    printf(" Estado civil: %s\n", p->casado ? "Casado(a)" : "Solteiro(a)");
    if (p->filhos > 0) {
        printf(" Filhos:      %d\n", p->filhos);
    }
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
    
    // Verifica condições de game over - VERSÃO EQUILIBRADA
    if (p->saude <= 0) {
        printf("\n========================================\n");
        printf("           GAME OVER - MORTE            \n");
        printf("========================================\n");
        printf("\n%s, sua saude chegou a zero...\n", p->nome);
        printf("Voce lutou bravamente, mas o corpo nao aguentou mais.\n");
        printf("Que sua jornada sirva de aprendizado para outros.\n");
        return 0;
    }
    
    if (p->felicidade <= 5) {
        printf("\n========================================\n");
        printf("         GAME OVER - DEPRESSAO          \n");
        printf("========================================\n");
        printf("\n%s, a tristeza tomou conta de sua vida...\n", p->nome);
        printf("A escuridao foi mais forte que sua vontade de viver.\n");
        printf("As vezes, buscar ajuda eh o maior ato de coragem.\n");
        return 0;
    }
    
    if (p->ano_atual >= 80) {
        printf("\n========================================\n");
        printf("         FIM DE JOGO - LONGEVIDADE      \n");
        printf("========================================\n");
        printf("\n%s, voce viveu uma vida longa e chegou aos 80 anos!\n", p->nome);
        printf("Parabens por uma jornada tao longa!\n");
        return 0;
    }
    
    // Verifica dinheiro negativo - MENOS RIGIDO
    if (p->dinheiro < -5000) {
        printf("\n========================================\n");
        printf("        GAME OVER - FALENCIA            \n");
        printf("========================================\n");
        printf("\n%s, as dividas se acumularam demais (R$ %d)...\n", p->nome, p->dinheiro);
        printf("Voce perdeu tudo e nao conseguiu se reerguer.\n");
        printf("O dinheiro nao eh tudo, mas eh necessario para sobreviver.\n");
        return 0;
    }
    
    if (p->dinheiro <= 0) {
        p->rodadas_sem_dinheiro++;
        if (p->rodadas_sem_dinheiro >= 5) { // Aumentado de 3 para 5
            printf("\n========================================\n");
            printf("        GAME OVER - SEM RECURSOS       \n");
            printf("========================================\n");
            printf("\n%s, voce ficou sem dinheiro por muito tempo...\n", p->nome);
            printf("A pobreza extrema acabou levando voce a situacao de rua.\n");
            printf("Infelizmente, nao conseguiu encontrar uma forma de se recuperar.\n");
            return 0;
        }
    } else {
        p->rodadas_sem_dinheiro = 0; // Reseta o contador se tiver dinheiro
    }
    
    // Condições punitivas reduzidas
    if (p->saude <= 15 && p->ano_atual >= 65) { // Idade aumentada de 50 para 65
        printf("\n========================================\n");
        printf("     GAME OVER - SAUDE DETERIORADA      \n");
        printf("========================================\n");
        printf("\n%s, sua saude se deteriorou muito com a idade avancada...\n", p->nome);
        printf("O corpo ja nao tinha mais forcas para continuar.\n");
        printf("Voce viveu uma vida plena ate onde foi possivel.\n");
        return 0;
    }
    
    if (p->felicidade <= 15 && p->casado == 0 && p->ano_atual >= 50) { // Idade reduzida de 40 para 50
        printf("\n========================================\n");
        printf("       GAME OVER - SOLIDAO EXTREMA      \n");
        printf("========================================\n");
        printf("\n%s, a solidao se tornou insuportavel...\n", p->nome);
        printf("Voce passou anos sozinho e a tristeza tomou conta de tudo.\n");
        printf("As vezes, os relacionamentos sao essenciais para a felicidade.\n");
        return 0;
    }
    
    return 1; // Jogo continua
}