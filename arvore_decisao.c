#include "arvore_decisao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funções auxiliares para cada fase da vida
void decisaoInfancia(Personagem* p);      // 5 anos
void decisaoEscolaPrimaria(Personagem* p); // 10 anos
void decisaoAdolescencia(Personagem* p);   // 15 anos
void decisaoCarreira(Personagem* p);       // 20 anos
void decisaoCarreiraMedia(Personagem* p);  // 25-40 anos
void decisaoMeiaIdadeInicial(Personagem* p); // 41-45 anos - Crise dos 40
void decisaoMeiaIdadeMedia(Personagem* p);   // 46-50 anos - Estabilização
void decisaoMeiaIdadeMadura(Personagem* p);  // 51-55 anos - Preparação
void decisaoMeiaIdadeFinal(Personagem* p);   // 56-60 anos - Transição
void decisaoTerceiraIdade(Personagem* p);  // 65+ anos

void exibirMenuDecisao(Personagem* p, int id_nivel_decisao) {
    if (p == NULL) return;
    
    int idade = p->ano_atual;
    
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
        // Entre 21-40: foca em carreira, casamento e filhos
        if (p->casado == 0 && idade >= 21 && idade <= 35) {
            decisaoCasamento(p);
        } else if (p->casado == 1 && p->filhos == 0 && idade >= 25 && idade <= 40) {
            decisaoFilhos(p);
        } else {
            decisaoCarreiraMedia(p);
        }
    } else if (idade <= 60) {
        // Diferentes situações conforme a idade na meia idade
        if (idade >= 41 && idade <= 45) {
            decisaoMeiaIdadeInicial(p);  // 41-45: Crise dos 40
        } else if (idade >= 46 && idade <= 50) {
            decisaoMeiaIdadeMedia(p);    // 46-50: Estabilização
        } else if (idade >= 51 && idade <= 55) {
            decisaoMeiaIdadeMadura(p);   // 51-55: Preparação
        } else {
            decisaoMeiaIdadeFinal(p);    // 56-60: Transição
        }
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
            printf("\nEscolha invalida! Seus pais ficaram confusos.\n");
            printf("   -5 Saude, -10 Felicidade\n");
            aplicarEvento(p, -5, -10, 0);
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
            printf("   +15 Felicidade, -10 Saude (estresse severo)\n");
            aplicarEvento(p, -10, 15, 0);
            break;
        case 2:
            printf("\nVoce teve um desenvolvimento equilibrado!\n");
            printf("   +15 Felicidade, +5 Saude\n");
            aplicarEvento(p, 5, 15, 0);
            break;
        case 3:
            printf("\nVoce fez muitos amigos, mas suas notas sofreram!\n");
            printf("   +20 Felicidade, -10 Saude, -R$ 200 (aulas particulares)\n");
            aplicarEvento(p, -10, 20, -200);
            break;
        case 4:
            printf("\nVoce foi expulso! Seus pais gastaram com escola particular cara!\n");
            printf("   -20 Felicidade, -15 Saude, -R$ 1000\n");
            aplicarEvento(p, -15, -20, -1000);
            break;
        default:
            printf("\nEscolha invalida! Voce ficou perdido e repetiu o ano!\n");
            printf("   -10 Saude, -15 Felicidade, -R$ 500\n");
            aplicarEvento(p, -10, -15, -500);
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
            printf("   +15 Felicidade, -15 Saude (estresse extremo), -R$ 800 (cursos)\n");
            aplicarEvento(p, -15, 15, -800);
            break;
        case 2:
            printf("\nVoce aprendeu uma profissao tecnica!\n");
            printf("   +10 Felicidade, +R$ 500, -R$ 1200 (curso)\n");
            aplicarEvento(p, 0, 10, -700);
            break;
        case 3:
            printf("\nVoce comecou a trabalhar cedo!\n");
            printf("   +5 Felicidade, +R$ 1000, -10 Saude (cansaco), -5 notas\n");
            aplicarEvento(p, -10, 5, 1000);
            break;
        case 4:
            printf("\nVoce aproveitou muito a adolescencia, mas suas notas despencaram!\n");
            printf("   +25 Felicidade, -R$ 500, -10 Saude (excessos)\n");
            aplicarEvento(p, -10, 25, -500);
            break;
        default:
            printf("\nEscolha invalida! Voce perdeu anos importantes e ficou para tras!\n");
            aplicarEvento(p, -10, -20, -1000);
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
        printf("   +5 Felicidade, +R$ 2000, -5 Saude (trabalho pesado)\n");
        aplicarEvento(p, -5, 5, 2000);
    } else if (escolha == 4) {
        printf("\nVoce viajou o mundo! Experiencia incrivel, mas sem estabilidade.\n");
        printf("   +30 Felicidade, -R$ 5000, +10 Saude\n");
        aplicarEvento(p, 10, 30, -5000);
    } else {
        printf("\nEscolha invalida! Voce perdeu tempo precioso e oportunidades!\n");
        aplicarEvento(p, -10, -15, -2000);
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

void decisaoMeiaIdadeInicial(Personagem* p) {
    int escolha;
    
    printf("CRISE DOS 40 - Questionando suas escolhas...\n\n");
    printf("1. Investir pesadamente para aposentadoria\n");
    printf("2. Comprar um carro esportivo (crise da meia idade)\n");
    printf("3. Voltar a estudar algo que sempre quis\n");
    printf("4. Mudar radicalmente de estilo de vida\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce comecou a se planejar para o futuro!\n");
            printf("   +10 Felicidade, +R$ 3000 (investimentos), -R$ 2000\n");
            aplicarEvento(p, 0, 10, 1000);
            break;
        case 2:
            printf("\nVoce comprou um carro dos sonhos!\n");
            printf("   +25 Felicidade, -R$ 4000, -5 Saude (estresse financeiro)\n");
            aplicarEvento(p, -5, 25, -4000);
            break;
        case 3:
            printf("\nVoce voltou a estudar sua paixao!\n");
            printf("   +30 Felicidade, -R$ 3000, +5 Saude (renovacao)\n");
            aplicarEvento(p, 5, 30, -3000);
            break;
        case 4:
            printf("\nVoce mudou completamente de vida!\n");
            printf("   +20 Felicidade, -R$ 2500, -10 Saude (estresse)\n");
            aplicarEvento(p, -10, 20, -2500);
            break;
        default:
            printf("\nVoce ficou paralisado pela indecisao!\n");
            printf("   -15 Felicidade, -5 Saude\n");
            aplicarEvento(p, -5, -15, 0);
    }
}

void decisaoMeiaIdadeMedia(Personagem* p) {
    int escolha;
    
    printf("ESTABILIZACAO - Encontrando equilibrio...\n\n");
    printf("1. Focar na carreira e crescimento profissional\n");
    printf("2. Dedicar mais tempo a familia\n");
    printf("3. Viajar e conhecer o mundo\n");
    printf("4. Cuidar da saude e fazer exercicios\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce impulsionou sua carreira!\n");
            printf("   +15 Felicidade, +R$ 4000, -10 Saude (trabalho intenso)\n");
            aplicarEvento(p, -10, 15, 4000);
            break;
        case 2:
            printf("\nVoce fortaleceu os lacos familiares!\n");
            printf("   +25 Felicidade, +10 Saude, -R$ 1500\n");
            aplicarEvento(p, 10, 25, -1500);
            break;
        case 3:
            printf("\nVoce explorou novos horizontes!\n");
            printf("   +30 Felicidade, +5 Saude, -R$ 3500\n");
            aplicarEvento(p, 5, 30, -3500);
            break;
        case 4:
            printf("\nVoce investiu na sua saude!\n");
            printf("   +20 Saude, +10 Felicidade, -R$ 2000\n");
            aplicarEvento(p, 20, 10, -2000);
            break;
        default:
            printf("\nVoce perdeu oportunidades por indecisao!\n");
            printf("   -10 Felicidade\n");
            aplicarEvento(p, 0, -10, 0);
    }
}

void decisaoMeiaIdadeMadura(Personagem* p) {
    int escolha;
    
    printf("PREPARACAO - Pensando no legado...\n\n");
    printf("1. Preparar aposentadoria e investimentos\n");
    printf("2. Ajudar filhos com estudos e carreira\n");
    printf("3. Dedicar-se a causas sociais\n");
    printf("4. Renovar o casamento ou relacionamentos\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce garantiu um futuro financeiro estavel!\n");
            printf("   +20 Felicidade, +R$ 5000 (investimentos)\n");
            aplicarEvento(p, 0, 20, 5000);
            break;
        case 2:
            printf("\nVoce investiu no futuro dos seus filhos!\n");
            printf("   +25 Felicidade, -R$ 3000, +5 Saude (satisfacao)\n");
            aplicarEvento(p, 5, 25, -3000);
            break;
        case 3:
            printf("\nVoce encontrou proposito ajudando outros!\n");
            printf("   +30 Felicidade, +10 Saude, -R$ 1000\n");
            aplicarEvento(p, 10, 30, -1000);
            break;
        case 4:
            if (p->casado == 1) {
                printf("\nVoce e seu conjuge renovaram o relacionamento!\n");
                printf("   +35 Felicidade, +5 Saude, -R$ 2000\n");
                aplicarEvento(p, 5, 35, -2000);
            } else {
                printf("\nVoce encontrou um novo amor!\n");
                printf("   +25 Felicidade, -R$ 1500\n");
                aplicarEvento(p, 0, 25, -1500);
            }
            break;
        default:
            printf("\nVoce perdeu tempo com incertezas!\n");
            printf("   -10 Felicidade\n");
            aplicarEvento(p, 0, -10, 0);
    }
}

void decisaoMeiaIdadeFinal(Personagem* p) {
    int escolha;
    
    printf("TRANSICAO - Preparando para a terceira idade...\n\n");
    printf("1. Finalizar planos de aposentadoria\n");
    printf("2. Passar conhecimento para as proximas geracoes\n");
    printf("3. Realizar sonhos adiados\n");
    printf("4. Simplificar a vida e reduzir estresse\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce esta pronto para se aposentar!\n");
            printf("   +25 Felicidade, +R$ 3000, +5 Saude (alivio)\n");
            aplicarEvento(p, 5, 25, 3000);
            break;
        case 2:
            printf("\nVoce se tornou um mentor valioso!\n");
            printf("   +30 Felicidade, +10 Saude, -R$ 500\n");
            aplicarEvento(p, 10, 30, -500);
            break;
        case 3:
            printf("\nVoce realizou seus sonhos pendentes!\n");
            printf("   +35 Felicidade, -R$ 4000, +5 Saude\n");
            aplicarEvento(p, 5, 35, -4000);
            break;
        case 4:
            printf("\nVoce encontrou paz e simplicidade!\n");
            printf("   +20 Felicidade, +15 Saude, +R$ 1000 (economia)\n");
            aplicarEvento(p, 15, 20, 1000);
            break;
        default:
            printf("\nVoce se sentiu perdido na transicao!\n");
            printf("   -15 Felicidade, -5 Saude\n");
            aplicarEvento(p, -5, -15, 0);
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

void decisaoCasamento(Personagem* p) {
    int escolha;
    
    printf("RELACIONAMENTOS - Voce conheceu alguem especial!\n\n");
    printf("1. Casar por amor verdadeiro\n");
    printf("2. Casar por conveniencia financeira\n");
    printf("3. Ficar solteiro e focar na carreira\n");
    printf("4. Ter relacionamentos casuais\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce se casou por amor! Uma cerimonia linda mas cara.\n");
            printf("   +25 Felicidade, +10 Saude, -R$ 5000 (casamento)\n");
            aplicarEvento(p, 10, 25, -5000);
            p->casado = 1;
            break;
        case 2:
            printf("\nVoce se casou por interesse. Ganhos financeiros, mas sem amor.\n");
            printf("   -10 Felicidade, +R$ 8000, -5 Saude (estresse)\n");
            aplicarEvento(p, -5, -10, 8000);
            p->casado = 1;
            break;
        case 3:
            printf("\nVoce focou na carreira. Sucesso profissional, mas solidao.\n");
            printf("   +R$ 3000, -15 Felicidade, -5 Saude\n");
            aplicarEvento(p, -5, -15, 3000);
            break;
        case 4:
            printf("\nVoce teve varios relacionamentos. Diversao, mas instabilidade emocional.\n");
            printf("   +10 Felicidade, -R$ 2000, -10 Saude (DSTs e estresse)\n");
            aplicarEvento(p, -10, 10, -2000);
            break;
        default:
            printf("\nEscolha invalida! Voce perdeu a oportunidade e ficou sozinho.\n");
            aplicarEvento(p, -5, -20, 0);
    }
}

void decisaoFilhos(Personagem* p) {
    int escolha;
    
    printf("FAMILIA - Voce e seu parceiro estao pensando em ter filhos...\n\n");
    printf("1. Ter 1 filho - familia pequena\n");
    printf("2. Ter 2-3 filhos - familia tradicional\n");
    printf("3. Ter muitos filhos (4+) - familia grande\n");
    printf("4. Nao ter filhos - focar no casal\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            printf("\nVoce teve 1 filho! Alegria e responsabilidade equilibradas.\n");
            printf("   +20 Felicidade, -R$ 2000, -5 Saude (parto/cuidados)\n");
            aplicarEvento(p, -5, 20, -2000);
            p->filhos = 1;
            break;
        case 2:
            printf("\nVoce teve 2-3 filhos! Uma familia alegre mas cara.\n");
            printf("   +30 Felicidade, -R$ 5000, -10 Saude (multiplos partos)\n");
            aplicarEvento(p, -10, 30, -5000);
            p->filhos = 3;
            break;
        case 3:
            printf("\nVoce teve uma familia grande! Muito amor, mas estresse financeiro extremo.\n");
            printf("   +40 Felicidade, -R$ 10000, -20 Saude (exaustao)\n");
            aplicarEvento(p, -20, 40, -10000);
            p->filhos = 5;
            break;
        case 4:
            printf("\nVoces decidiram nao ter filhos. Mais liberdade, mas podem se arrepender.\n");
            printf("   +10 Felicidade, +R$ 3000, +5 Saude\n");
            aplicarEvento(p, 5, 10, 3000);
            // Chance de arrependimento futuro
            if (p->ano_atual >= 35) {
                printf("   Mas voces comecam a sentir um vazio...\n");
                aplicarEvento(p, 0, -15, 0);
            }
            break;
        default:
            printf("\nEscolha invalida! A indecisao causou problemas no relacionamento.\n");
            aplicarEvento(p, -10, -25, -1000);
    }
}

void gerenciarInventario(Personagem* p, NoLista** inventario) {
    int opcao;
    char nome_item[100];
    
    while (1) {
        printf("\n");
        exibirInventario(*inventario);
        printf("\n===========================================\n");
        printf("         MENU DO INVENTARIO\n");
        printf("===========================================\n");
        printf("\n[1] Usar item\n");
        printf("[2] Voltar ao menu principal\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            if (*inventario == NULL) {
                printf("\nInventario vazio! Nao ha itens para usar.\n");
                printf("Pressione ENTER para continuar...");
                while (getchar() != '\n');
                getchar();
                continue;
            }
            
            printf("\nDigite o nome EXATO do item para usar: ");
            scanf(" %[^\n]", nome_item); // Le string com espacos
            
            if (usarItem(inventario, nome_item, (struct Personagem*)p)) {
                printf("\nItem usado com sucesso!\n");
                printf("\nSeu status atualizado:\n");
                printf("Saude: %d%%, Felicidade: %d%%, Dinheiro: R$ %d\n", 
                       p->saude, p->felicidade, p->dinheiro);
            }
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
        } else if (opcao == 2) {
            printf("\nVoltando ao menu principal...\n");
            break;
        } else {
            printf("\nOpcao invalida! Use [1] ou [2]\n");
            printf("Pressione ENTER para tentar novamente...");
            while (getchar() != '\n');
            getchar();
        }
    }
}

int exibirMenuPrincipal(Personagem* p, NoLista** inventario) {
    if (p == NULL) return 1;
    
    printf("\n===========================================\n");
    printf("  %s - %d ANOS\n", p->nome, p->ano_atual);
    printf("===========================================\n");
    printf("  [0] Encerrar o jogo\n");
    printf("  [I] Acessar Inventário\n");
    printf("===========================================\n\n");
    
    // Mostra as opções da idade atual
    int idade = p->ano_atual;
    if (idade <= 5) {
        printf("INFÂNCIA - Seus pais perguntam:\n\n");
        printf("  [1] Colocar você em aulas de música\n");
        printf("  [2] Colocar você em aulas de esportes\n");
        printf("  [3] Deixar você brincar livremente\n");
    } else if (idade <= 10) {
        printf("ESCOLA PRIMÁRIA - Como você se comporta?\n\n");
        printf("  [1] Estudar muito e ser o melhor da turma\n");
        printf("  [2] Equilibrar estudos e amizades\n");
        printf("  [3] Focar em fazer amigos e brincar\n");
        printf("  [4] Ser rebelde e bagunceiro\n");
    } else if (idade <= 15) {
        printf("ADOLESCÊNCIA - O que fazer no ensino médio?\n\n");
        printf("  [1] Focar nos estudos para passar no vestibular\n");
        printf("  [2] Fazer um curso técnico\n");
        printf("  [3] Arrumar um emprego de meio período\n");
        printf("  [4] Aproveitar a vida e curtir com os amigos\n");
    } else if (idade <= 20) {
        printf("INÍCIO DA VIDA ADULTA - Que caminho seguir?\n\n");
        printf("  [1] Fazer Faculdade\n");
        printf("  [2] Abrir um negócio\n");
        printf("  [3] Entrar direto no mercado de trabalho\n");
        printf("  [4] Viajar o mundo\n");
    } else if (idade <= 40) {
        if (p->casado == 0 && idade >= 21 && idade <= 35) {
            printf("RELACIONAMENTOS - Você conheceu alguém especial!\n\n");
            printf("  [1] Casar por amor verdadeiro\n");
            printf("  [2] Casar por conveniência financeira\n");
            printf("  [3] Ficar solteiro e focar na carreira\n");
            printf("  [4] Ter relacionamentos casuais\n");
        } else if (p->casado == 1 && p->filhos == 0 && idade >= 25 && idade <= 40) {
            printf("FAMÍLIA - Você e seu parceiro estão pensando em ter filhos...\n\n");
            printf("  [1] Ter 1 filho - família pequena\n");
            printf("  [2] Ter 2-3 filhos - família tradicional\n");
            printf("  [3] Ter muitos filhos (4+) - família grande\n");
            printf("  [4] Não ter filhos - focar no casal\n");
        } else {
            printf("CARREIRA EM DESENVOLVIMENTO - O que fazer?\n\n");
            printf("  [1] Buscar uma promoção trabalhando mais horas\n");
            printf("  [2] Fazer uma pós-graduação/MBA\n");
            printf("  [3] Mudar de carreira completamente\n");
            printf("  [4] Manter o equilíbrio vida-trabalho\n");
        }
    } else if (idade <= 60) {
        printf("MEIA-IDADE - Pensando no futuro...\n\n");
        printf("  [1] Investir pesadamente para aposentadoria\n");
        printf("  [2] Comprar a casa dos sonhos\n");
        printf("  [3] Viajar enquanto tem saúde\n");
        printf("  [4] Ajudar os filhos financeiramente\n");
    } else {
        printf("TERCEIRA IDADE - Aproveitando a vida...\n\n");
        printf("  [1] Dedicar-se a hobbies e voluntariado\n");
        printf("  [2] Passar tempo com família\n");
        printf("  [3] Viajar e conhecer novos lugares\n");
        printf("  [4] Cuidar da saúde e fazer exercícios\n");
    }
    
    printf("\n===========================================\n");
    printf("Sua escolha: ");
    
    char entrada[10];
    scanf("%s", entrada);
    
    // Processa a entrada
    if (strcmp(entrada, "0") == 0) {
        printf("\nVocê decidiu encerrar sua vida aqui...\n");
        p->saude = 0;
        return 1;
    } else if (strcmp(entrada, "I") == 0 || strcmp(entrada, "i") == 0) {
        gerenciarInventario(p, inventario);
        return 0; // Volta ao menu
    } else {
        int escolha = atoi(entrada);
        if (escolha >= 1 && escolha <= 4) {
            // Chama a função de decisão apropriada baseada na escolha do usuário
            processarEscolhaMenu(p, escolha);
            return 1;
        } else {
            printf("\nEscolha inválida! Tente novamente.\n");
            return 0; // Volta ao menu
        }
    }
}

void processarEscolhaMenu(Personagem* p, int escolha) {
    if (p == NULL) return;
    
    int idade = p->ano_atual;
    
    // Redireciona para a função apropriada baseada na idade
    if (idade <= 5) {
        switch (escolha) {
            case 1:
                printf("\nVocê começou aulas de música!\n");
                printf("   +10 Felicidade, +5 Saúde\n");
                aplicarEvento(p, 5, 10, 0);
                break;
            case 2:
                printf("\nVocê começou a praticar esportes!\n");
                printf("   +15 Saúde, +5 Felicidade\n");
                aplicarEvento(p, 15, 5, 0);
                break;
            case 3:
                printf("\nVocê teve uma infância livre e feliz!\n");
                printf("   +20 Felicidade\n");
                aplicarEvento(p, 0, 20, 0);
                break;
            default:
                printf("\nEscolha inválida! Seus pais ficaram confusos.\n");
                aplicarEvento(p, -5, -10, 0);
        }
    } else if (idade <= 10) {
        switch (escolha) {
            case 1:
                printf("\nVocê se tornou o aluno destaque!\n");
                printf("   +15 Felicidade, -10 Saúde (estresse severo)\n");
                aplicarEvento(p, -10, 15, 0);
                break;
            case 2:
                printf("\nVocê teve um desenvolvimento equilibrado!\n");
                printf("   +15 Felicidade, +5 Saúde\n");
                aplicarEvento(p, 5, 15, 0);
                break;
            case 3:
                printf("\nVocê fez muitos amigos, mas suas notas sofreram!\n");
                printf("   +20 Felicidade, -10 Saúde, -R$ 200 (aulas particulares)\n");
                aplicarEvento(p, -10, 20, -200);
                break;
            case 4:
                printf("\nVocê foi expulso! Seus pais gastaram com escola particular cara!\n");
                printf("   -20 Felicidade, -15 Saúde, -R$ 1000\n");
                aplicarEvento(p, -15, -20, -1000);
                break;
        }
    } else if (idade <= 15) {
        switch (escolha) {
            case 1:
                printf("\nVocê estudou muito para o vestibular!\n");
                printf("   +15 Felicidade, -15 Saúde (estresse extremo), -R$ 800 (cursos)\n");
                aplicarEvento(p, -15, 15, -800);
                break;
            case 2:
                printf("\nVocê aprendeu uma profissão técnica!\n");
                printf("   +10 Felicidade, +R$ 500, -R$ 1200 (curso)\n");
                aplicarEvento(p, 0, 10, -700);
                break;
            case 3:
                printf("\nVocê começou a trabalhar cedo!\n");
                printf("   +5 Felicidade, +R$ 1000, -10 Saúde (cansaço)\n");
                aplicarEvento(p, -10, 5, 1000);
                break;
            case 4:
                printf("\nVocê aproveitou muito a adolescência, mas suas notas despencaram!\n");
                printf("   +25 Felicidade, -R$ 500, -10 Saúde (excessos)\n");
                aplicarEvento(p, -10, 25, -500);
                break;
        }
    } else if (idade <= 20) {
        switch (escolha) {
            case 1:
                // Faculdade - vai para submenu
                decisaoCarreiraFaculdade(p);
                break;
            case 2:
                // Negócio - vai para submenu
                decisaoCarreiraNegocio(p);
                break;
            case 3:
                printf("\nVocê começou a trabalhar imediatamente!\n");
                printf("   +5 Felicidade, +R$ 2000, -5 Saúde (trabalho pesado)\n");
                aplicarEvento(p, -5, 5, 2000);
                break;
            case 4:
                printf("\nVocê viajou o mundo! Experiência incrível, mas sem estabilidade.\n");
                printf("   +30 Felicidade, -R$ 5000, +10 Saúde\n");
                aplicarEvento(p, 10, 30, -5000);
                break;
        }
    } else {
        // Para outras idades, chama a função de decisão original
        exibirMenuDecisao(p, escolha);
    }
}