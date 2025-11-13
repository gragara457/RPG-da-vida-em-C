/*
 * =====================================
 * RPG DA VIDA EM C - ARQUIVO PRINCIPAL
 * =====================================
 * 
 * Este arquivo contém a função principal do jogo e o loop principal.
 * 
 * CONCEITOS UTILIZADOS:
 * - Funções: main(), criarPersonagem(), exibirStatus(), aplicarEvento(), etc.
 * - Structs: Personagem, ItemVida, NoLista
 * - Ponteiros: Personagem*, NoLista*, passagem por referência (&)
 * 
 * ARQUITETURA:
 * - main.c: Loop principal e controle do jogo
 * - personagem.c/h: Estrutura e funções do personagem 
 * - inventario.c/h: Sistema de itens e lista ligada
 * - arvore_decisao.c/h: Árvore de decisões por idade
 */

// Arquivo: main.c
#include <stdio.h>    // Funções de entrada/saída (printf, scanf)
#include <stdlib.h>   // Funções de alocação dinâmica (malloc, free)

// Nossos arquivos de cabeçalho
#include "personagem.h"      // Struct Personagem e funções relacionadas
#include "inventario.h"      // Struct ItemVida, NoLista e funções de lista ligada
#include "arvore_decisao.h"  // Funções da árvore de decisões

/**
 * =====================================
 * FUNÇÃO PRINCIPAL (MAIN)
 * =====================================
 * 
 * Controla o fluxo principal do jogo:
 * 1. Cria personagem (PONTEIRO + ALOCAÇÃO DINÂMICA)
 * 2. Inicializa inventário (LISTA LIGADA)
 * 3. Loop principal do jogo
 * 4. Libera memória (PONTEIROS)
 * 
 * CONCEITOS DEMONSTRADOS:
 * - STRUCT: Personagem (definida em personagem.h)
 * - PONTEIROS: Personagem* jogador, NoLista* inventario
 * - FUNÇÕES: criarPersonagem(), exibirStatus(), aplicarEvento()
 */
int main() {
    // === APRESENTAÇÃO DO JOGO ===
    printf("\n");
    printf("========================================\n");
    printf("                                        \n");
    printf("       RPG DA VIDA EM C                 \n");
    printf("                                        \n");
    printf("   Viva uma vida completa e tome        \n");
    printf("   decisoes que moldarao seu destino!   \n");
    printf("                                        \n");
    printf("========================================\n\n");

    // === CRIAÇÃO DOS DADOS PRINCIPAIS ===
    
    // 1. Criação do Personagem (CONCEITO: ALOCAÇÃO DINÂMICA)
    // - Usa malloc() internamente em criarPersonagem()
    // - Retorna um PONTEIRO para a struct Personagem
    Personagem* jogador = criarPersonagem();  // PONTEIRO para struct
    
    // 2. Inicialização do Inventário (CONCEITO: LISTA LIGADA)
    // - NoLista é uma struct que contém ItemVida e ponteiro para próximo
    // - Começa como NULL (lista vazia)
    NoLista* inventario = NULL; // PONTEIRO para lista ligada

    // Verificação de erro na alocação de memória

    if (jogador == NULL) {
        printf("Erro fatal: Não foi possível alocar memória para o jogador.\n");
        return 1;
    }
    
    // Adiciona itens iniciais ao inventário (CONCEITO: PASSAGEM POR REFERÊNCIA)
    // - Passa &inventario (endereço do ponteiro) para modificar a lista
    adicionarItensIniciais(&inventario);  // PONTEIRO por referência

    // === LOOP PRINCIPAL DO JOGO ===
    // 
    // Continua enquanto jogoContinua() retornar verdadeiro
    // - jogoContinua() é uma FUNÇÃO que verifica condições de game over
    // - Recebe PONTEIRO para acessar os campos da struct Personagem
    while (jogoContinua(jogador)) {  // FUNÇÃO + PONTEIRO
        
        // === MENU PRINCIPAL ===
        // Loop interno para o menu de opções
        int decisao_feita = 0;
        while (!decisao_feita) {
            // === EXIBIÇÃO DO STATUS ===
            // - exibirStatus() é uma FUNÇÃO que recebe PONTEIRO
            // - Acessa campos da STRUCT usando ponteiro: jogador->nome, jogador->saude, etc.
            exibirStatus(jogador);  // FUNÇÃO + PONTEIRO para STRUCT
            
            // === MENU DE OPÇÕES ===
            printf("\n===========================================\n");
            // - Usa jogador->nome (PONTEIRO acessando campo da STRUCT)
            printf("         MENU PRINCIPAL - %s\n", jogador->nome);  // PONTEIRO->campo
            printf("===========================================\n");
            printf("\n[0] Encerrar o jogo\n");
            printf("[5] Acessar inventario\n");
            printf("[C] Continuar para decisao da vida\n");
            printf("\nEscolha uma opcao: ");
            
            char opcao;
            scanf(" %c", &opcao);  // Passagem por referência (&opcao)
            
            // === PROCESSAMENTO DAS OPÇÕES ===
            
            if (opcao == '0') {
                printf("\nVoce decidiu encerrar sua vida aqui...\n");
                // Modifica campo da STRUCT usando PONTEIRO
                jogador->saude = 0;  // PONTEIRO->campo = valor
                decisao_feita = 1;
            } else if (opcao == '5') {
                // === GERENCIAMENTO DO INVENTÁRIO ===
                // - gerenciarInventario() é uma FUNÇÃO
                // - Recebe PONTEIRO para personagem e PONTEIRO por referência para lista
                gerenciarInventario(jogador, &inventario);  // FUNÇÃO + PONTEIROS
                printf("\nPressione ENTER para voltar ao menu...");
                while (getchar() != '\n');
                getchar();
            } else if (opcao == 'C' || opcao == 'c') {
                // Vai para as decisoes da vida
                printf("\n");
                exibirMenuDecisao(jogador, 0);
                decisao_feita = 1;
            } else {
                printf("\nOpcao invalida! Use [0], [5] ou [C]\n");
                printf("Pressione ENTER para tentar novamente...");
                while (getchar() != '\n');
                getchar();
            }
        }
        if (jogador->saude == 0) {
            break;
        }
        
        // === SISTEMA DE ENVELHECIMENTO ===
        // Avança 5 anos no tempo de jogo
        printf("\nPassaram-se 5 anos...\n");
        
        // Modifica campo da STRUCT usando PONTEIRO
        jogador->ano_atual += 5;  // PONTEIRO->campo += valor
        
        // === CÁLCULO DAS PERDAS POR ENVELHECIMENTO ===
        // Variáveis locais para cálculos
        int perda_saude = 5; // Voltou para 5 (era 3)
        int perda_felicidade = 1; // Perda gradual de felicidade
        int custo_vida = 200; // Reduzido de 300 para 200
        
        // Envelhecimento se torna mais severo com a idade (menos agressivo)
        if (jogador->ano_atual >= 45) { // Aumentado de 40 para 45
            perda_saude += 3; // Voltou para 3 (era 2)
            perda_felicidade += 1; // Felicidade começa a declinar
            custo_vida += 200; // Reduzido de 300 para 200
        }
        if (jogador->ano_atual >= 65) { // Aumentado de 60 para 65
            perda_saude += 4; // Ajustado para 4 (era 3)
            perda_felicidade += 2; // Total 4 de felicidade (era 3)
            custo_vida += 200; // Reduzido de 300 para 200
        }
        
        // === CUSTOS DE FAMÍLIA ===
        // - Acessa campo da STRUCT usando PONTEIRO (jogador->filhos)
        if (jogador->filhos > 0) {  // PONTEIRO->campo
            int custo_filhos = jogador->filhos * 300;  // Cálculo baseado na STRUCT
            custo_vida += custo_filhos;
            printf("Gastos com %d filho(s): -R$ %d\n", jogador->filhos, custo_filhos);
        }
        
        // === EXIBIÇÃO DAS PERDAS ===
        printf("O tempo cobra seu preco: -%d Saude", perda_saude);
        if (perda_felicidade > 0) {
            printf(" -%d Felicidade", perda_felicidade);
        }
        printf(" -R$ %d (custos de vida)\n", custo_vida);
        
        // === APLICAÇÃO DOS EVENTOS ===
        // - aplicarEvento() é uma FUNÇÃO que modifica a STRUCT
        // - Recebe PONTEIRO e valores para modificar os campos
        aplicarEvento(jogador, -perda_saude, -perda_felicidade, -custo_vida);  // FUNÇÃO + PONTEIRO
        
        // === PAUSA PARA O JOGADOR ===
        // Permite ao jogador acompanhar as mudanças
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n'); // Limpa buffer do teclado
        getchar(); // Espera o usuário pressionar ENTER
    } // Fim do while principal - jogo continua enquanto jogoContinua() = verdadeiro

    // === FIM DO JOGO ===
    
    printf("\n");
    printf("========================================\n");
    printf("                                        \n");
    printf("           FIM DE JOGO                  \n");
    printf("                                        \n");
    printf("========================================\n");
    
    // === EXIBIÇÃO FINAL ===
    // - Chamadas de FUNÇÕES usando PONTEIROS
    exibirStatus(jogador);      // FUNÇÃO + PONTEIRO para STRUCT
    exibirInventario(inventario); // FUNÇÃO + PONTEIRO para lista ligada

    // === LIMPEZA DE MEMÓRIA (CONCEITO: LIBERAÇÃO DINÂMICA) ===
    // 
    // MUITO IMPORTANTE: Libera toda memória alocada dinamicamente
    // - Evita vazamentos de memória (memory leaks)
    // - Usa PONTEIROS por referência para modificar/limpar
    
    liberarInventario(&inventario);  // FUNÇÃO + PONTEIRO por referência
    liberarPersonagem(jogador);      // FUNÇÃO + PONTEIRO (chama free() internamente)

    printf("\nObrigado por jogar!\n");
    return 0;
} // Fim da função main

/*
 * =====================================
 * RESUMO DOS CONCEITOS UTILIZADOS:
 * =====================================
 * 
 * ✅ STRUCTS (3+):
 *    - Personagem (nome, saude, felicidade, dinheiro, etc.)
 *    - ItemVida (nome, valor, tipo, efeitos)
 *    - NoLista (item + ponteiro para proximo)
 * 
 * ✅ FUNÇÕES (3+):
 *    - criarPersonagem()     - cria e aloca personagem
 *    - exibirStatus()        - exibe dados do personagem  
 *    - aplicarEvento()       - modifica atributos
 *    - jogoContinua()        - verifica condições de game over
 *    - gerenciarInventario() - interface do inventário
 *    - liberarPersonagem()   - libera memória
 *    - E MUITAS outras...
 * 
 * ✅ PONTEIROS (3+ usos):
 *    - Personagem* jogador          - ponteiro para struct
 *    - NoLista* inventario          - ponteiro para lista ligada
 *    - &inventario                  - passagem por referência
 *    - jogador->nome                - acesso via ponteiro
 *    - jogador->saude = 0           - modificação via ponteiro
 *    - E MUITOS outros usos...
 */