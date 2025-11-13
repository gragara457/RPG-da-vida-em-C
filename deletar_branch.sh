#!/bin/bash

# Script para deletar a branch Teste-Simplificado
# Script to delete the Teste-Simplificado branch

echo "========================================="
echo "Script de Deleção de Branch"
echo "Branch Deletion Script"
echo "========================================="
echo ""

BRANCH_NAME="Teste-Simplificado"

# Verificar se a branch existe remotamente
echo "Verificando se a branch '$BRANCH_NAME' existe remotamente..."
echo "Checking if branch '$BRANCH_NAME' exists remotely..."

if git ls-remote --heads origin | grep -q "refs/heads/$BRANCH_NAME"; then
    echo "✓ Branch '$BRANCH_NAME' encontrada no remoto."
    echo "✓ Branch '$BRANCH_NAME' found on remote."
    echo ""
    
    # Mostrar informações da branch
    echo "Informações da branch / Branch information:"
    git ls-remote --heads origin | grep "$BRANCH_NAME"
    echo ""
    
    # Perguntar confirmação
    read -p "Deseja deletar a branch remota '$BRANCH_NAME'? (s/N): " -n 1 -r
    echo ""
    
    if [[ $REPLY =~ ^[SsYy]$ ]]; then
        echo "Deletando branch remota / Deleting remote branch..."
        
        if git push origin --delete "$BRANCH_NAME"; then
            echo "✓ Branch remota '$BRANCH_NAME' deletada com sucesso!"
            echo "✓ Remote branch '$BRANCH_NAME' deleted successfully!"
            
            # Limpar referências locais
            echo ""
            echo "Limpando referências locais / Cleaning local references..."
            git fetch --prune
            echo "✓ Referências limpas!"
            echo "✓ References cleaned!"
        else
            echo "✗ Erro ao deletar a branch remota."
            echo "✗ Error deleting remote branch."
            exit 1
        fi
    else
        echo "Operação cancelada / Operation cancelled."
        exit 0
    fi
else
    echo "✗ Branch '$BRANCH_NAME' não encontrada no remoto."
    echo "✗ Branch '$BRANCH_NAME' not found on remote."
    echo ""
    echo "Branches disponíveis / Available branches:"
    git ls-remote --heads origin
    exit 1
fi

echo ""
echo "========================================="
echo "Branches restantes / Remaining branches:"
echo "========================================="
git ls-remote --heads origin
