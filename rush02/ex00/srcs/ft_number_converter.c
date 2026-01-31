/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_converter.c                             :+:      :+:    :+:   */
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
**                      FT_NUMBER_CONVERTER.C
** ============================================================================
**
** 🎯 O CORAÇÃO DO RUSH-02!
**
** Este arquivo contém a lógica para converter um número em texto.
** É a parte mais desafiadora e também a mais divertida!
**
** ============================================================================
**                    ESTRATÉGIA DE DECOMPOSIÇÃO
** ============================================================================
**
** 📊 ANALOGIA: "Fatiar o Bolo"
**
** Imagine que o número é um bolo de várias camadas:
**
**    1.234.567 (um milhão, duzentos e trinta e quatro mil, quinhentos...)
**
**    ┌─────────────────────────────────────────────────────────────────────┐
**    │         1              234             567                          │
**    │    ┌─────────┐    ┌─────────┐    ┌─────────┐                       │
**    │    │ milhões │    │ milhares│    │ unidades│                       │
**    │    └─────────┘    └─────────┘    └─────────┘                       │
**    │                                                                     │
**    │  "one million"  "two hundred thirty four thousand"  "five..."      │
**    └─────────────────────────────────────────────────────────────────────┘
**
** PROCESSO:
** 1. Encontre a maior "camada" (milhões, milhares, centenas...)
** 2. Processe essa camada
** 3. Remova essa camada e repita com o resto
**
** ============================================================================
**                        CASOS ESPECIAIS
** ============================================================================
**
** 📌 CASO 1: Número direto no dicionário
**    - "42" → busca "42" → encontra "forty two" → imprime!
**    - "0" → busca "0" → encontra "zero" → imprime!
**
** 📌 CASO 2: Dezenas compostas (21-99, exceto 20,30,40...)
**    - "42" não está no dict, mas "40" e "2" estão
**    - Imprime "forty" + " " + "two"
**
** 📌 CASO 3: Centenas (100-999)
**    - "234" → "2" + "hundred" + "thirty four"
**    - Ou seja: (234 / 100) + "hundred" + (234 % 100)
**
** 📌 CASO 4: Milhares, milhões, etc.
**    - "1234567" → processa recursivamente
**    - milhões: 1234567 / 1000000 = 1 → "one million"
**    - resto: 1234567 % 1000000 = 234567 → processa recursivamente
**
** ============================================================================
**                       NÚMEROS COMO STRING
** ============================================================================
**
** ⚠️  IMPORTANTE: O subject diz que devemos lidar com números MUITO grandes!
**    Números maiores que unsigned long long (18 quintilhões).
**
** Por isso, trabalhamos com o número como STRING, não como int!
**
** Para "fatiar" strings numéricas:
**    "1234567"
**         │
**         ▼
**    ┌─────────────────────────────────────────────────────────────────────┐
**    │ Comprimento = 7 dígitos                                             │
**    │                                                                     │
**    │ Se len >= 7 (milhões): pega primeiros (len-6) dígitos               │
**    │    "1" é a parte dos milhões                                        │
**    │    "234567" é o resto                                               │
**    │                                                                     │
**    │ Se len >= 4 (milhares): pega primeiros (len-3) dígitos              │
**    │    E assim por diante...                                            │
**    └─────────────────────────────────────────────────────────────────────┘
**
** ============================================================================
*/

/*
** is_valid_number:
** Verifica se uma string representa um número válido.
**
** Regras:
** - Apenas dígitos (0-9)
** - Não pode estar vazio
** - Não pode ter sinais (-, +)
** - Não pode ter ponto decimal
**
** 💡 DICA SOBRE ZEROS À ESQUERDA:
**    O subject não é 100% claro sobre "007".
**    Recomendação: aceite, mas trate como "7".
**    Ou seja, pule os zeros iniciais (exceto se o número for "0").
*/

int	is_valid_number(char *str)
{
	int	i;

	(void)i;
	/*
	** ========================================================================
	** TODO 1: Verificar se string é NULL ou vazia
	** ========================================================================
	** if (!str || str[0] == '\0')
	**     return (0);
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Verificar se cada caractere é dígito
	** ========================================================================
	** i = 0;
	** while (str[i])
	** {
	**     if (!ft_isdigit(str[i]))
	**         return (0);
	**     i++;
	** }
	** return (1);
	**
	** 💡 PERGUNTA: E se o número for "-42" (negativo)?
	**    Resposta: O subject diz "inteiro válido e POSITIVO"
	**    Então "-42" deve retornar Error (is_valid_number retorna 0)
	** ========================================================================
	*/
	/* Seu código aqui */

	return (0);
}

/*
** skip_leading_zeros:
** Retorna ponteiro para o primeiro dígito não-zero.
** Se o número for todo zeros, retorna ponteiro para o último zero.
**
** Exemplos:
**   "00042" → retorna ponteiro para '4'
**   "000"   → retorna ponteiro para o último '0'
**   "42"    → retorna ponteiro para '4' (sem mudança)
*/

static char	*skip_leading_zeros(char *str)
{
	/*
	** ========================================================================
	** TODO: Pular zeros à esquerda
	** ========================================================================
	** while (*str == '0' && *(str + 1) != '\0')
	**     str++;
	** return (str);
	**
	** 💡 NOTA: Mantemos pelo menos um caractere!
	**    "000" → "0" (não string vazia)
	** ========================================================================
	*/
	/* Seu código aqui */

	return (str);
}

/*
** print_small_number:
** Imprime números de 0 a 99.
** Estes são os casos "base" da nossa decomposição.
**
** Retorno:
**   1 se sucesso
**   0 se chave não encontrada no dicionário
*/

static int	print_small_number(t_dict *dict, char *num)
{
	char	*value;
	char	tens[3];
	char	units[2];

	(void)value;
	(void)tens;
	(void)units;
	/*
	** ========================================================================
	** TODO 1: Tentar buscar o número diretamente
	** ========================================================================
	** Primeiro, tente encontrar o número exato no dicionário.
	** Ex: "42" pode estar como "42: quarenta e dois"
	**     "15" está como "15: fifteen"
	**
	** value = dict_search(dict, num);
	** if (value)
	** {
	**     ft_putstr(value);
	**     return (1);
	** }
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Se não encontrou, decompor em dezena + unidade
	** ========================================================================
	** Se o número tem 2 dígitos e não foi encontrado diretamente,
	** decomponha em dezena (40) + unidade (2).
	**
	** Exemplo: "42"
	**   - tens = "40" (primeiro dígito + '0')
	**   - units = "2" (segundo dígito)
	**
	** tens[0] = num[0];
	** tens[1] = '0';
	** tens[2] = '\0';
	** units[0] = num[1];
	** units[1] = '\0';
	**
	** 💡 CUIDADO: Se units for "0", não imprima!
	**    "40" → "forty", não "forty zero"
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Imprimir dezena + espaço + unidade
	** ========================================================================
	** value = dict_search(dict, tens);
	** if (!value)
	**     return (0);  // Dict Error!
	** ft_putstr(value);
	**
	** if (units[0] != '0')
	** {
	**     ft_putchar(' ');
	**     value = dict_search(dict, units);
	**     if (!value)
	**         return (0);
	**     ft_putstr(value);
	** }
	** return (1);
	** ========================================================================
	*/
	/* Seu código aqui */

	return (0);
}

/*
** convert_number:
** Função principal que converte um número para texto.
**
** Parâmetros:
**   dict   - dicionário com as traduções
**   number - número como string (ex: "1234")
**
** Retorno:
**   1 se sucesso
**   0 se erro (chave não encontrada no dicionário)
**
** ============================================================================
**                    ALGORITMO DE DECOMPOSIÇÃO
** ============================================================================
**
** 1. Pular zeros à esquerda ("007" → "7")
** 2. Se número está diretamente no dict, imprimir e retornar
** 3. Senão, encontrar a maior grandeza (milhão, mil, cem...)
** 4. Imprimir a parte dessa grandeza
** 5. Recursivamente processar o resto
**
** ============================================================================
*/

int	convert_number(t_dict *dict, char *number)
{
	int		len;
	char	*num;
	char	*value;

	(void)len;
	(void)num;
	(void)value;
	/*
	** ========================================================================
	** TODO 1: Pular zeros à esquerda e calcular comprimento
	** ========================================================================
	** num = skip_leading_zeros(number);
	** len = ft_strlen(num);
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Caso base - número pequeno (0-99)
	** ========================================================================
	** if (len <= 2)
	**     return (print_small_number(dict, num));
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Centenas (100-999)
	** ========================================================================
	** Se len == 3:
	**   - Primeiro dígito é quantas centenas
	**   - Resto são dezenas e unidades
	**
	** Exemplo: "234"
	**   - "2" + "hundred" + " " + "34"
	**
	** PSEUDOCÓDIGO:
	**   if (len == 3)
	**   {
	**       // Imprime quantas centenas (primeiro dígito)
	**       digit[0] = num[0];
	**       digit[1] = '\0';
	**       if (!print_small_number(dict, digit))
	**           return (0);
	**       
	**       // Imprime " hundred"
	**       ft_putchar(' ');
	**       value = dict_search(dict, "100");
	**       if (!value)
	**           return (0);
	**       ft_putstr(value);
	**       
	**       // Se resto não é zero, imprime espaço e processa resto
	**       if (num[1] != '0' || num[2] != '0')
	**       {
	**           ft_putchar(' ');
	**           return (convert_number(dict, num + 1));  // Recursão!
	**       }
	**       return (1);
	**   }
	**
	** 💡 PERGUNTA: Por que usamos recursão aqui?
	**    Resposta: Para reutilizar a lógica! O "resto" é tratado
	**    da mesma forma que qualquer outro número.
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 4: Milhares, milhões, bilhões, etc.
	** ========================================================================
	** Esta é a parte mais complexa! Você precisa:
	**
	** 1. Determinar qual é a maior grandeza:
	**    - len 4-6: milhares (1000)
	**    - len 7-9: milhões (1000000)
	**    - len 10-12: bilhões (1000000000)
	**    - etc.
	**
	** 2. Separar o número em duas partes:
	**    - A parte ANTES da grandeza
	**    - A parte DEPOIS (resto)
	**
	** 3. Imprimir: [parte antes] + [nome da grandeza] + [resto]
	**
	** EXEMPLO DETALHADO para "1234567":
	**    len = 7 → grandeza é milhão (1000000)
	**    
	**    Parte antes: "1" (índices 0 até len-7 = 0)
	**    Parte depois: "234567" (índices 1 até fim)
	**    
	**    Imprime: "one" + " " + "million" + " " + convert("234567")
	**
	** 💡 DICA: Use uma tabela para mapear comprimentos para grandezas:
	**    len 4-6  → divide em (len-3) e 3 dígitos → "thousand"
	**    len 7-9  → divide em (len-6) e 6 dígitos → "million"
	**    len 10-12 → divide em (len-9) e 9 dígitos → "billion"
	**
	** 💡 DICA 2: Vocês podem criar funções auxiliares:
	**    - get_scale_key(): retorna "1000", "1000000", etc.
	**    - get_scale_len(): retorna quantos dígitos pular
	** ========================================================================
	*/
	/* Seu código aqui */

	return (0);
}

/*
** ============================================================================
**                    📊 EXEMPLO PASSO A PASSO
** ============================================================================
**
** Entrada: "1234567"
**
** Chamada 1: convert_number(dict, "1234567")
**   len = 7 (milhões)
**   Parte milhões: "1"
**   Imprime: "one"
**   Imprime: " "
**   Imprime: "million" (busca "1000000")
**   Imprime: " "
**   Chama: convert_number(dict, "234567")
**
** Chamada 2: convert_number(dict, "234567")
**   len = 6 (milhares, pois 234 mil)
**   Parte milhares: "234"
**   Chama: convert_number(dict, "234") para imprimir "two hundred thirty four"
**   Imprime: " "
**   Imprime: "thousand"
**   Imprime: " "
**   Chama: convert_number(dict, "567")
**
** Chamada 3: convert_number(dict, "234")
**   len = 3 (centenas)
**   Imprime: "two"
**   Imprime: " hundred"
**   Imprime: " "
**   Chama: convert_number(dict, "34")
**
** ... e assim por diante.
**
** Resultado: "one million two hundred thirty four thousand five hundred..."
**
** ============================================================================
*/
