#!/bin/bash

#colors

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
LIGHT_GRAY='\033[0;37m'
YELLOW='\033[0;33m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'       # Cyan
LIGHT_GRAY='\033[0;37m' # Gris clair
ORANGE='\033[38;5;214m' # Orange (approximatif)
PINK='\033[38;5;205m'   # Rose
TEAL='\033[38;5;44m'    # Bleu sarcelle (teal)
NC='\033[0m' # No Color

MINISHELL=./minishell

tests=(
	#$>
	"Test1:Retour a la ligne \n:echo '\n':$>"
	"Test2:Espaces :echo ' ':$>"
	"Test3:Tabulations :echo '	':$>"
	"Test4:Deux points :echo ':':$>"
	"Test5:Point d'exlamation !:echo '!':$>"
	#bash: syntax error near unexpected token `newline'$>
	"Test6:>:echo '>':bash: syntax error near unexpected token `newline'$>"
	"Test7:<:echo '<':bash: syntax error near unexpected token `newline'$>"
	"Test8:>>:echo '>>':bash: syntax error near unexpected token `newline'$>"
	"Test8:<<:echo '<<':bash: syntax error near unexpected token `newline'$>"
	"Test8:<>:echo '<>':bash: syntax error near unexpected token `newline'$>"
	"Test8:>>>>>:echo '>>>>>':bash: syntax error near unexpected token `newline'$>"
)
