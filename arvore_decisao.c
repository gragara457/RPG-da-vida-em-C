#include "arvore_decisao.h"
#include <stdio.h>

// Funções auxiliares para cada fase da vida
void decisaoInfancia(Personagem* p);      // 5 anos
void decisaoEscolaPrimaria(Personagem* p); // 10 anos
void decisaoAdolescencia(Personagem* p);   // 15 anos
void decisaoCarreira(Personagem* p);       // 20 anos
void decisaoCarreiraMedia(Personagem* p);  // 25-40 anos
void decisaoMeiaIdade(Personagem* p);      // 45-60 anos
void decisaoTerceiraIdade(Personagem* p);  // 65+ anos

void exibirMenuDecisao(Personagem* p, int id_nivel_decisao) {
    if (p == NULL) return;
    
    int idade = p->ano_atual;
    
    printf("\n===========================================\n");
    printf("  MOMENTO DE DECISAO - %d ANOS\n", idade);
    printf("===========================================\n\n");
    
    // Decisões baseadas na idade
    if (idade <= 5) {
        decisaoInfancia(p);
    } else if (idade <= 10) {
        decisaoEscolaPrimaria(p);
    } else if (idade <= 15) {
        decisaoAdolescencia(p);
    } else if (idade <= 20) {
        decisaoCarreira(p);
    } else if (idade <= 40) {
        decisaoCarreiraMedia(p);
    } else if (idade <= 60) {
        decisaoMeiaIdade(p);
    } else {
        decisaoTerceiraIdade(p);
    }
}

void decisaoInfancia(Personagem* p) {
    int escolha;
    
    printf("INFANCIA - Seus pais perguntam:\n\n");
    printf("1. Colocar voce em aulas de musica\n");
    printf("2. Colocar voce em aulas de esportes\n");
    printf("3. Deixar voce brincar livremente\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce comecou aulas de musica!\n");
            printf("   +10 Felicidade, +5 Saude\n");
            aplicarEvento(p, 5, 10, 0);
            break;
        case 2:
            printf("\nVoce comecou a praticar esportes!\n");
            printf("   +15 Saude, +5 Felicidade\n");
            aplicarEvento(p, 15, 5, 0);
            break;
        case 3:
            printf("\nVoce teve uma infancia livre e feliz!\n");
            printf("   +20 Felicidade\n");
            aplicarEvento(p, 0, 20, 0);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoEscolaPrimaria(Personagem* p) {
    int escolha;
    
    printf("ESCOLA PRIMARIA - Como voce se comporta?\n\n");
    printf("1. Estudar muito e ser o melhor da turma\n");
    printf("2. Equilibrar estudos e amizades\n");
    printf("3. Focar em fazer amigos e brincar\n");
    printf("4. Ser rebelde e bagunceiro\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce se tornou o aluno destaque!\n");
            printf("   +10 Felicidade, -5 Saude (estresse)\n");
            aplicarEvento(p, -5, 10, 0);
            break;
        case 2:
            printf("\nVoce teve um desenvolvimento equilibrado!\n");
            printf("   +15 Felicidade, +5 Saude\n");
            aplicarEvento(p, 5, 15, 0);
            break;
        case 3:
            printf("\nVoce fez muitos amigos!\n");
            printf("   +20 Felicidade, -5 Saude\n");
            aplicarEvento(p, -5, 20, 0);
            break;
        case 4:
            printf("\nVoce foi expulso e seus pais ficaram bravos!\n");
            printf("   -15 Felicidade, -10 Saude\n");
            aplicarEvento(p, -10, -15, 0);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoAdolescencia(Personagem* p) {
    int escolha;
    
    printf("ADOLESCENCIA - O que fazer no ensino medio?\n\n");
    printf("1. Focar nos estudos para passar no vestibular\n");
    printf("2. Fazer um curso tecnico\n");
    printf("3. Arrumar um emprego de meio periodo\n");
    printf("4. Aproveitar a vida e curtir com os amigos\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce estudou muito para o vestibular!\n");
            printf("   +15 Felicidade, -10 Saude (estresse)\n");
            aplicarEvento(p, -10, 15, 0);
            break;
        case 2:
            printf("\nVoce aprendeu uma profissao tecnica!\n");
            printf("   +10 Felicidade, +R$ 500\n");
            aplicarEvento(p, 0, 10, 500);
            break;
        case 3:
            printf("\nVoce comecou a trabalhar cedo!\n");
            printf("   +5 Felicidade, +R$ 1000, -5 Saude\n");
            aplicarEvento(p, -5, 5, 1000);
            break;
        case 4:
            printf("\nVoce aproveitou muito a adolescencia!\n");
            printf("   +25 Felicidade, -R$ 300\n");
            aplicarEvento(p, 0, 25, -300);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoCarreira(Personagem* p) {
    int escolha;
    
    printf("INICIO DA VIDA ADULTA - Que caminho seguir?\n\n");
    printf("1. Fazer Faculdade\n");
    printf("2. Abrir um negocio\n");
    printf("3. Entrar direto no mercado de trabalho\n");
    printf("4. Viajar o mundo\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    if (escolha == 1) {
        // CHAMADA RECURSIVA - submenu de faculdade
        decisaoCarreiraFaculdade(p);
    } else if (escolha == 2) {
        // CHAMADA RECURSIVA - submenu de negócio
        decisaoCarreiraNegocio(p);
    } else if (escolha == 3) {
        printf("\nVoce comecou a trabalhar imediatamente!\n");
        printf("   +5 Felicidade, +R$ 2000\n");
        aplicarEvento(p, 0, 5, 2000);
    } else if (escolha == 4) {
        printf("\nVoce viajou o mundo!\n");
        printf("   +30 Felicidade, -R$ 3000, +10 Saude\n");
        aplicarEvento(p, 10, 30, -3000);
    } else {
        printf("\nEscolha invalida!\n");
        aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoCarreiraFaculdade(Personagem* p) {
    int escolha;
    
    printf("\nQUAL FACULDADE FAZER?\n\n");
    printf("1. Ciencia da Computacao\n");
    printf("2. Medicina\n");
    printf("3. Direito\n");
    printf("4. Engenharia\n");
    printf("5. Administracao\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce se formou em Ciencia da Computacao!\n");
            printf("   +15 Felicidade, +R$ 3000, -R$ 800 (mensalidades)\n");
            aplicarEvento(p, 0, 15, 2200);
            break;
        case 2:
            printf("\nVoce se formou em Medicina!\n");
            printf("   +20 Felicidade, +R$ 5000, -R$ 2000 (mensalidades), -10 Saude\n");
            aplicarEvento(p, -10, 20, 3000);
            break;
        case 3:
            printf("\nVoce se formou em Direito!\n");
            printf("   +10 Felicidade, +R$ 2500, -R$ 1200 (mensalidades)\n");
            aplicarEvento(p, 0, 10, 1300);
            break;
        case 4:
            printf("\nVoce se formou em Engenharia!\n");
            printf("   +12 Felicidade, +R$ 3500, -R$ 1000 (mensalidades)\n");
            aplicarEvento(p, 0, 12, 2500);
            break;
        case 5:
            printf("\nVoce se formou em Administracao!\n");
            printf("   +8 Felicidade, +R$ 2000, -R$ 600 (mensalidades)\n");
            aplicarEvento(p, 0, 8, 1400);
            break;
        default:
            printf("\nVoce desistiu da faculdade!\n");
            aplicarEvento(p, 0, -10, 0);
    }
}

void decisaoCarreiraNegocio(Personagem* p) {
    int escolha;
    
    printf("\nQUE TIPO DE NEGOCIO ABRIR?\n\n");
    printf("1. Restaurante\n");
    printf("2. Loja Online\n");
    printf("3. Startup de Tecnologia\n");
    printf("4. Consultoria\n");
    printf("5. Franquia\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce abriu um Restaurante!\n");
            printf("   +10 Felicidade, +R$ 1000, -R$ 1500 (investimento), -5 Saude\n");
            aplicarEvento(p, -5, 10, -500);
            break;
        case 2:
            printf("\nVoce abriu uma Loja Online!\n");
            printf("   +15 Felicidade, +R$ 1500, -R$ 500 (investimento)\n");
            aplicarEvento(p, 0, 15, 1000);
            break;
        case 3:
            printf("\nVoce criou uma Startup de Tecnologia!\n");
            printf("   +25 Felicidade, +R$ 5000, -R$ 2000 (investimento), -10 Saude\n");
            aplicarEvento(p, -10, 25, 3000);
            break;
        case 4:
            printf("\nVoce abriu uma Consultoria!\n");
            printf("   +12 Felicidade, +R$ 2000, -R$ 800 (investimento)\n");
            aplicarEvento(p, 0, 12, 1200);
            break;
        case 5:
            printf("\nVoce comprou uma Franquia!\n");
            printf("   +8 Felicidade, +R$ 2500, -R$ 3000 (investimento)\n");
            aplicarEvento(p, 0, 8, -500);
            break;
        default:
            printf("\nVoce desistiu de abrir o negocio!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoCarreiraMedia(Personagem* p) {
    int escolha;
    
    printf("CARREIRA EM DESENVOLVIMENTO - O que fazer?\n\n");
    printf("1. Buscar uma promocao trabalhando mais horas\n");
    printf("2. Fazer uma pos-graduacao/MBA\n");
    printf("3. Mudar de carreira completamente\n");
    printf("4. Manter o equilibrio vida-trabalho\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce foi promovido!\n");
            printf("   +10 Felicidade, +R$ 3000, -10 Saude (horas extras)\n");
            aplicarEvento(p, -10, 10, 3000);
            break;
        case 2:
            printf("\nVoce fez uma especializacao!\n");
            printf("   +15 Felicidade, +R$ 2000, -R$ 1500 (curso)\n");
            aplicarEvento(p, 0, 15, 500);
            break;
        case 3:
            printf("\nVoce mudou de carreira!\n");
            printf("   +20 Felicidade, -R$ 1000, -5 Saude (incerteza)\n");
            aplicarEvento(p, -5, 20, -1000);
            break;
        case 4:
            printf("\nVoce manteve o equilibrio!\n");
            printf("   +15 Felicidade, +R$ 1500, +10 Saude\n");
            aplicarEvento(p, 10, 15, 1500);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoMeiaIdade(Personagem* p) {
    int escolha;
    
    printf("MEIA-IDADE - Pensando no futuro...\n\n");
    printf("1. Investir pesadamente para aposentadoria\n");
    printf("2. Comprar a casa dos sonhos\n");
    printf("3. Viajar enquanto tem saude\n");
    printf("4. Ajudar os filhos financeiramente\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce investiu para o futuro!\n");
            printf("   +5 Felicidade, +R$ 5000 (retornos futuros), -R$ 2000\n");
            aplicarEvento(p, 0, 5, 3000);
            break;
        case 2:
            printf("\nVoce comprou a casa dos sonhos!\n");
            printf("   +25 Felicidade, -R$ 5000\n");
            aplicarEvento(p, 0, 25, -5000);
            break;
        case 3:
            printf("\nVoce viajou pelo mundo!\n");
            printf("   +30 Felicidade, -R$ 3000, +5 Saude\n");
            aplicarEvento(p, 5, 30, -3000);
            break;
        case 4:
            printf("\nVoce ajudou sua familia!\n");
            printf("   +20 Felicidade, -R$ 2000\n");
            aplicarEvento(p, 0, 20, -2000);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}

void decisaoTerceiraIdade(Personagem* p) {
    int escolha;
    
    printf("TERCEIRA IDADE - Aproveitando a vida...\n\n");
    printf("1. Dedicar-se a hobbies e voluntariado\n");
    printf("2. Passar tempo com familia\n");
    printf("3. Viajar e conhecer novos lugares\n");
    printf("4. Cuidar da saude e fazer exercicios\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce encontrou novos propositos!\n");
            printf("   +20 Felicidade, -R$ 500\n");
            aplicarEvento(p, 0, 20, -500);
            break;
        case 2:
            printf("\nVoce fortaleceu lacos familiares!\n");
            printf("   +25 Felicidade, +5 Saude\n");
            aplicarEvento(p, 5, 25, 0);
            break;
        case 3:
            printf("\nVoce explorou o mundo!\n");
            printf("   +30 Felicidade, -R$ 2000\n");
            aplicarEvento(p, 0, 30, -2000);
            break;
        case 4:
            printf("\nVoce priorizou sua saude!\n");
            printf("   +15 Felicidade, +15 Saude, -R$ 1000\n");
            aplicarEvento(p, 15, 15, -1000);
            break;
        default:
            printf("\nEscolha invalida!\n");
            aplicarEvento(p, 0, -5, 0);
    }
}