/*
 * RPG DA VIDA EM C - VERSÃO SIMPLIFICADA
 * ======================================
 * 
 * CONCEITOS UTILIZADOS (APENAS 3 DE CADA):
 * 
 * STRUCTS (3):
 * 1. Personagem - dados do jogador
 * 2. Item - item do inventário  
 * 3. Jogo - controle geral
 * 
 * FUNÇÕES (3):
 * 1. criarJogo() - inicializa o jogo
 * 2. jogarRodada() - executa uma rodada
 * 3. finalizarJogo() - termina o jogo
 * 
 * PONTEIROS (3):
 * 1. Jogo* jogo - ponteiro para struct do jogo
 * 2. jogo->personagem - acesso via ponteiro
 * 3. &jogo->item - endereço para modificação
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================
// STRUCT 1: PERSONAGEM
// =============================
typedef struct {
    char nome[50];
    int saude;
    int felicidade;
    int idade;
} Personagem;

// =============================
// STRUCT 2: ITEM
// =============================
typedef struct {
    char nome[30];
    int efeito_saude;
    int efeito_felicidade;
} Item;

// =============================
// STRUCT 3: JOGO
// =============================
typedef struct {
    Personagem personagem;  // Struct dentro de struct
    Item item;              // Item único no inventário
    int rodadas;
    int ativo;
} Jogo;

// =============================
// FUNÇÃO 1: CRIAR JOGO
// =============================
Jogo* criarJogo() {
    // PONTEIRO 1: Alocação dinâmica retorna ponteiro
    Jogo* jogo = (Jogo*) malloc(sizeof(Jogo));
    
    if (jogo != NULL) {
        printf("=== RPG DA VIDA EM C ===\\n");
        printf("Digite seu nome: ");
        fgets(jogo->personagem.nome, sizeof(jogo->personagem.nome), stdin);
        
        // Remove a quebra de linha do nome
        int len = strlen(jogo->personagem.nome);
        if (len > 0 && jogo->personagem.nome[len-1] == '\n') {
            jogo->personagem.nome[len-1] = '\0';
        }
        
        // Inicialização
        jogo->personagem.saude = 100;
        jogo->personagem.felicidade = 100;
        jogo->personagem.idade = 20;
        
        // Item inicial
        strcpy(jogo->item.nome, "Pocao de Vida");
        jogo->item.efeito_saude = 20;
        jogo->item.efeito_felicidade = 10;
        
        jogo->rodadas = 0;
        jogo->ativo = 1;
        
        printf("\nOla %s! Sua vida comeca aos 20 anos!\n", jogo->personagem.nome);
    }
    
    return jogo;  // Retorna ponteiro
}

// =============================
// FUNÇÃO 2: JOGAR RODADA  
// =============================
void jogarRodada(Jogo* jogo) {
    if (jogo == NULL) return;
    
    // Exibe status
    printf("\n=== %s - %d anos ===\n", jogo->personagem.nome, jogo->personagem.idade);
    printf("Saude: %d | Felicidade: %d\n", jogo->personagem.saude, jogo->personagem.felicidade);
    printf("Item: %s (+%d saude, +%d felicidade)\n", 
           jogo->item.nome, jogo->item.efeito_saude, jogo->item.efeito_felicidade);
    
    // Menu simples
    printf("\n1. Trabalhar (perder saude, ganhar dinheiro)\n");
    printf("2. Descansar (ganhar saude, perder tempo)\n");  
    printf("3. Usar item do inventario\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    
    int escolha;
    scanf("%d", &escolha);
    
    switch(escolha) {
        case 1:
            jogo->personagem.saude -= 10;
            jogo->personagem.felicidade -= 5;
            printf("Voce trabalhou duro! Perdeu saude mas ganhou experiencia.\n");
            break;
        case 2:
            jogo->personagem.saude += 15;
            jogo->personagem.felicidade += 10;
            printf("Voce descansou! Recuperou saude e se sentiu melhor.\n");
            break;
        case 3:
            // PONTEIRO 3: Passagem por referência
            printf("Usando %s...\n", jogo->item.nome);
            jogo->personagem.saude += jogo->item.efeito_saude;
            jogo->personagem.felicidade += jogo->item.efeito_felicidade;
            
            // Limita valores
            if (jogo->personagem.saude > 100) jogo->personagem.saude = 100;
            if (jogo->personagem.felicidade > 100) jogo->personagem.felicidade = 100;
            
            printf("Item usado! Efeitos aplicados.\n");
            break;
        case 0:
            jogo->ativo = 0;
            printf("Voce decidiu encerrar sua vida aqui...\n");
            return;
        default:
            printf("Escolha invalida!\n");
            return;
    }
    
    // Envelhecimento
    jogo->personagem.idade += 5;
    jogo->personagem.saude -= 5;  // Perde saúde com a idade
    jogo->rodadas++;
    
    // Verifica game over
    if (jogo->personagem.saude <= 0) {
        printf("\n=== GAME OVER ===\n");
        printf("Sua saude chegou a zero!\n");
        jogo->ativo = 0;
    } else if (jogo->personagem.idade >= 80) {
        printf("\n=== PARABENS ===\n");
        printf("Voce viveu 80 anos!\n");
        jogo->ativo = 0;
    }
}

// =============================
// FUNÇÃO 3: FINALIZAR JOGO
// =============================
void finalizarJogo(Jogo* jogo) {
    if (jogo != NULL) {
        printf("\n=== ESTATISTICAS FINAIS ===\n");
        printf("Nome: %s\n", jogo->personagem.nome);
        printf("Idade final: %d anos\n", jogo->personagem.idade);
        printf("Saude final: %d\n", jogo->personagem.saude);
        printf("Felicidade final: %d\n", jogo->personagem.felicidade);
        printf("Rodadas jogadas: %d\n", jogo->rodadas);
        
        // Libera memória
        free(jogo);  // Libera o ponteiro
        printf("\nMemoria liberada. Obrigado por jogar!\n");
    }
}

// =============================
// MAIN - CONTROLE DO JOGO
// =============================
int main() {
    // Cria o jogo (retorna ponteiro)
    Jogo* meuJogo = criarJogo();
    
    if (meuJogo == NULL) {
        printf("Erro ao criar o jogo!\n");
        return 1;
    }
    
    // Loop principal
    while (meuJogo->ativo) {
        jogarRodada(meuJogo);
        
        if (meuJogo->ativo) {
            printf("\nPressione Enter para continuar...");
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
        }
    }
    
    // Finaliza o jogo
    finalizarJogo(meuJogo);
    
    return 0;
}

/*
 * =============================
 * RESUMO DOS CONCEITOS:
 * =============================
 * 
 * ✅ STRUCTS (exatamente 3):
 *    1. Personagem - dados do jogador
 *    2. Item - item do inventário
 *    3. Jogo - controle geral
 * 
 * ✅ FUNÇÕES (exatamente 3):
 *    1. criarJogo() - inicializa
 *    2. jogarRodada() - executa rodada  
 *    3. finalizarJogo() - finaliza
 * 
 * ✅ PONTEIROS (exatamente 3 usos):
 *    1. Jogo* jogo - ponteiro para struct
 *    2. jogo->personagem.nome - acesso via ->
 *    3. &jogo->item - endereço para modificação
 * 
 * TOTAL: 3 structs, 3 funções, 3 ponteiros ✅
 */