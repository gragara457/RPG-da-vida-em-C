#include "personagem.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free

// Aluno 1: Implementar estas funções

Personagem* criarPersonagem() {
    // TODO: Alocar memória para o Personagem (malloc)
    // TODO: Inicializar os atributos (saude, felicidade, etc.)
    // TODO: Retornar o ponteiro para o personagem alocado
    printf("Função 'criarPersonagem' ainda não implementada.\n");
    return NULL; // Retorno temporário
}

void liberarPersonagem(Personagem* p) {
    // TODO: Verificar se p não é NULL
    // TODO: Liberar a memória (free)
    printf("Função 'liberarPersonagem' ainda não implementada.\n");
}

void exibirStatus(Personagem* p) {
    // TODO: Verificar se p não é NULL
    // TODO: Usar printf para mostrar os atributos (p->saude, etc.)
    printf("Função 'exibirStatus' ainda não implementada.\n");
}

void aplicarEvento(Personagem* p, int mod_saude, int mod_felicidade, int mod_dinheiro) {
    // TODO: Verificar se p não é NULL
    // TODO: Somar os modificadores aos atributos do personagem (p->dinheiro += ...)
    printf("Função 'aplicarEvento' ainda não implementada.\n");
}

int jogoContinua(Personagem* p) {
    // TODO: Verificar se p não é NULL
    // TODO: Checar condições de fim de jogo (ex: p->saude <= 0)
    // TODO: Retornar 0 se o jogo acabou, 1 se continua
    printf("Função 'jogoContinua' ainda não implementada.\n");
    return 0; // Retorno temporário (para o loop não ser infinito)
}