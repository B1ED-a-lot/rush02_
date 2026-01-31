/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seu_login <seu_login@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:00:00 by seu_login         #+#    #+#             */
/*   Updated: 2026/01/30 00:00:00 by seu_login        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush02.h"

/*
** ============================================================================
**                              MAIN.C
** ============================================================================
**
** 📋 RESPONSABILIDADES DESTE ARQUIVO:
**    [1] Validar número de argumentos (argc pode ser 2 ou 3)
**    [2] Determinar qual é o dicionário e qual é o número
**    [3] Fazer o parsing do dicionário
**    [4] Validar se o número é válido
**    [5] Chamar a conversão
**    [6] Liberar memória e sair
**
** ============================================================================
**                         FLUXO DO PROGRAMA
** ============================================================================
**
**   ./rush-02 42                    (argc = 2)
**   ./rush-02 meu_dict.txt 42       (argc = 3)
**
**         │
**         ▼
**   ┌──────────────────┐
**   │ argc == 2 ou 3?  │───Não──→ print_error() → return 1
**   └────────┬─────────┘
**            │Sim
**            ▼
**   ┌──────────────────────────────────────────┐
**   │ Se argc == 2:                            │
**   │   dict_path = DEFAULT_DICT               │
**   │   number    = argv[1]                    │
**   │                                          │
**   │ Se argc == 3:                            │
**   │   dict_path = argv[1]                    │
**   │   number    = argv[2]                    │
**   └────────┬─────────────────────────────────┘
**            │
**            ▼
**   ┌──────────────────┐
**   │ is_valid_number? │───Não──→ print_error() → return 1
**   └────────┬─────────┘
**            │Sim
**            ▼
**   ┌──────────────────┐
**   │ parse_dict()     │───NULL──→ print_dict_error() → return 1
**   └────────┬─────────┘
**            │OK
**            ▼
**   ┌──────────────────┐
**   │ convert_number() │───0──→ print_dict_error() → free_dict() → return 1
**   └────────┬─────────┘
**            │1 (sucesso)
**            ▼
**   ┌──────────────────┐
**   │ free_dict()      │
**   │ return 0         │
**   └──────────────────┘
**
** ============================================================================
*/

/*
** print_error:
** Imprime "Error\n" quando o número é inválido.
**
** Casos de uso:
** - argc diferente de 2 ou 3
** - Número com caracteres não-numéricos (ex: "42a", "-5", "10.5")
** - String vazia
*/

void	print_error(void)
{
	write(1, "Error\n", 6);
}

/*
** print_dict_error:
** Imprime "Dict Error\n" quando há problema no dicionário.
**
** Casos de uso:
** - Arquivo não existe ou não pode ser aberto
** - Linha mal formatada (sem ':')
** - Falta uma chave necessária para a conversão
** - Espaços onde deveria ter número
*/

void	print_dict_error(void)
{
	write(1, "Dict Error\n", 11);
}

/*
** main:
** Ponto de entrada do programa.
**
** Parâmetros:
**   argc - número de argumentos (programa + args)
**   argv - array de strings com os argumentos
**
** Retorno:
**   0 - sucesso
**   1 - erro (opcional, subject não especifica)
*/

int	main(int argc, char **argv)
{
	char	*dict_path;
	char	*number;
	t_dict	*dict;

	/*
	** ========================================================================
	** TODO 1: Validar argc
	** ========================================================================
	** argc deve ser 2 ou 3:
	**   - argc == 2: ./rush-02 <número>
	**   - argc == 3: ./rush-02 <dicionário> <número>
	**
	** Se argc for diferente de 2 e de 3, imprima erro e retorne.
	**
	** 💡 DICA: Use um if simples
	**    if (argc != 2 && argc != 3)
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Determinar dict_path e number baseado em argc
	** ========================================================================
	** 
	** Se argc == 2:
	**   - dict_path recebe DEFAULT_DICT (constante definida no header)
	**   - number recebe argv[1]
	**
	** Se argc == 3:
	**   - dict_path recebe argv[1]
	**   - number recebe argv[2]
	**
	** 💡 PERGUNTA: Por que usamos uma constante DEFAULT_DICT?
	**    Resposta: Para facilitar mudanças futuras e deixar claro o valor
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Validar se o número é válido
	** ========================================================================
	** Chame is_valid_number(number)
	** Se retornar 0 (falso/inválido), imprima error e retorne.
	**
	** 💡 PERGUNTA: O que torna um número inválido?
	**    - Letras: "42a"
	**    - Sinais: "-5", "+3"  
	**    - Decimais: "10.5"
	**    - Espaços: " 42", "4 2"
	**    - String vazia: ""
	**    - Zeros à esquerda: "007" (ATENÇÃO: verifique se o subject permite!)
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 4: Fazer parsing do dicionário
	** ========================================================================
	** Chame parse_dict(dict_path)
	** Se retornar NULL (erro), imprima dict error e retorne.
	**
	** ⚠️  IMPORTANTE: parse_dict aloca memória!
	**    Você DEVE chamar free_dict() antes de sair do programa.
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 5: Converter o número para texto
	** ========================================================================
	** Chame convert_number(dict, number)
	** Se retornar 0 (erro), imprima dict error, libere memória e retorne.
	**
	** 💡 PERGUNTA: Quando convert_number pode falhar?
	**    - Quando o dicionário não tem uma chave necessária
	**    - Ex: Converter 50 mas dicionário não tem "50: fifty"
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 6: Imprimir newline e liberar memória
	** ========================================================================
	** - Imprima '\n' após o resultado (subject mostra output com $)
	** - Chame free_dict(dict) para liberar TODA memória alocada
	** - Retorne 0 (sucesso)
	**
	** ⚠️  MEMORY LEAK: Se esquecer free_dict, o avaliador VAI descontar!
	** ========================================================================
	*/
	/* Seu código aqui */

	(void)dict_path;
	(void)number;
	(void)dict;
	return (0);
}

/*
** ============================================================================
**                    💡 ESQUELETO DA SOLUÇÃO
** ============================================================================
**
** Quando terminar seus TODOs, o código deve ficar parecido com:
**
** int main(int argc, char **argv)
** {
**     char   *dict_path;
**     char   *number;
**     t_dict *dict;
**
**     if (argc != 2 && argc != 3)
**     {
**         print_error();
**         return (1);
**     }
**     if (argc == 2)
**     {
**         dict_path = DEFAULT_DICT;
**         number = argv[1];
**     }
**     else
**     {
**         dict_path = argv[1];
**         number = argv[2];
**     }
**     if (!is_valid_number(number))
**     {
**         print_error();
**         return (1);
**     }
**     dict = parse_dict(dict_path);
**     if (!dict)
**     {
**         print_dict_error();
**         return (1);
**     }
**     if (!convert_number(dict, number))
**     {
**         print_dict_error();
**         free_dict(dict);
**         return (1);
**     }
**     write(1, "\n", 1);
**     free_dict(dict);
**     return (0);
** }
**
** ============================================================================
*/
