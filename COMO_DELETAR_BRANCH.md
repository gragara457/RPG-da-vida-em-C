# Como Deletar uma Branch

## Branch Identificada para Deleção

Foi identificada a branch `Teste-Simplificado` que está no mesmo commit que a branch `main` e parece ser redundante.

**Informações da branch:**
- Nome: `Teste-Simplificado`
- Commit: `4c011438c97ab8f033d0b260592ddc0953897dae`
- Status: Mesmo commit que a branch `main`

## Como Deletar a Branch

### Deletar Branch Local

Se você tem a branch localmente, delete com:

```bash
git branch -d Teste-Simplificado
```

Se a branch não foi mergeada e você tem certeza que quer deletá-la, use:

```bash
git branch -D Teste-Simplificado
```

### Deletar Branch Remota (no GitHub)

Para deletar a branch remota, use um dos seguintes métodos:

#### Método 1: Via Linha de Comando (Git)

```bash
git push origin --delete Teste-Simplificado
```

ou

```bash
git push origin :Teste-Simplificado
```

#### Método 2: Via GitHub CLI

```bash
gh api -X DELETE repos/gragara457/RPG-da-vida-em-C/git/refs/heads/Teste-Simplificado
```

#### Método 3: Via Interface Web do GitHub

1. Acesse: https://github.com/gragara457/RPG-da-vida-em-C/branches
2. Encontre a branch `Teste-Simplificado`
3. Clique no ícone de lixeira ao lado da branch
4. Confirme a deleção

## Verificar Branches Existentes

Para ver todas as branches locais:
```bash
git branch
```

Para ver todas as branches remotas:
```bash
git branch -r
```

Para ver todas as branches (locais e remotas):
```bash
git branch -a
```

## Limpar Referências de Branches Deletadas

Depois de deletar uma branch remota, limpe as referências locais:

```bash
git fetch --prune
```

ou

```bash
git remote prune origin
```
