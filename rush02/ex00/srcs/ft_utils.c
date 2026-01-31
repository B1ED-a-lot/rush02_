/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                        :+:      :+:    :+:   */
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
**                            FT_UTILS.C
** ============================================================================
**
** 📋 FUNÇÕES BÁSICAS (vocês já conhecem a maioria!)
**
** Estas são as ferramentas fundamentais que usaremos em todo o projeto.
** São como os "tijolos" com que construímos a "casa".
**
** ============================================================================
*/

/*
** ft_putchar:
** Escreve UM caractere no terminal.
**
** 📖 write(fd, buffer, count):
**   - fd = 1 significa "saída padrão" (o terminal)
**   - buffer = endereço do dado a escrever
**   - count = quantos bytes escrever
**
** &c significa "endereço de c" (onde c está na memória)
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
** ft_putstr:
** Escreve uma string inteira no terminal.
**
** 💡 PERGUNTA: Por que não usamos um loop com ft_putchar?
**    Resposta: Podemos! Mas é MUITO mais lento.
**    Cada write() faz uma "chamada de sistema" (syscall).
**    Melhor fazer 1 syscall grande do que muitas pequenas.
*/

void	ft_putstr(char *str)
{
	/*
	** ========================================================================
	** TODO: Verificar NULL e escrever a string
	** ========================================================================
	** if (!str)
	**     return;
	** write(1, str, ft_strlen(str));
	** ========================================================================
	*/
	/* Seu código aqui */
}

/*
** ft_strlen:
** Conta quantos caracteres tem uma string (sem contar o '\0').
**
** Exemplo: "hello" → 5
*/

int	ft_strlen(char *str)
{
	int	len;

	/*
	** ========================================================================
	** TODO: Contar caracteres até encontrar '\0'
	** ========================================================================
	** len = 0;
	** while (str[len])
	**     len++;
	** return (len);
	** ========================================================================
	*/
	(void)len;
	/* Seu código aqui */

	return (0);
}

/*
** ft_strcmp:
** Compara duas strings caractere por caractere.
**
** Retorno:
**   0 se forem iguais
**   Diferença (s1[i] - s2[i]) no primeiro caractere diferente
**
** 💡 DICA: Retornar 0 significa IGUAIS (pode parecer contra-intuitivo!)
*/

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	/*
	** ========================================================================
	** TODO: Comparar caractere por caractere
	** ========================================================================
	** i = 0;
	** while (s1[i] && s2[i] && s1[i] == s2[i])
	**     i++;
	** return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	**
	** 💡 PERGUNTA: Por que (unsigned char)?
	**    Resposta: Para lidar corretamente com caracteres > 127
	**    (caracteres acentuados, símbolos especiais, etc.)
	** ========================================================================
	*/
	(void)i;
	/* Seu código aqui */

	return (0);
}

/*
** ft_isdigit:
** Verifica se um caractere é um dígito (0-9).
**
** Retorno:
**   1 se for dígito
**   0 se não for
**
** 💡 LEMBRETE: Caracteres em C são números!
**    '0' = 48, '1' = 49, ... '9' = 57 (tabela ASCII)
**    Então verificar se é dígito é checar se está entre '0' e '9'
*/

int	ft_isdigit(char c)
{
	/*
	** ========================================================================
	** TODO: Verificar se c está entre '0' e '9'
	** ========================================================================
	** return (c >= '0' && c <= '9');
	** ========================================================================
	*/
	/* Seu código aqui */

	(void)c;
	return (0);
}

/*
** ============================================================================
**                    🆕 FUNÇÕES COM MALLOC
** ============================================================================
**
** ⚠️  ATENÇÃO: As funções abaixo usam malloc!
**    Isso significa que ALOCAM MEMÓRIA DINAMICAMENTE.
**    O chamador (quem chama a função) é RESPONSÁVEL por fazer FREE!
**
** ============================================================================
*/

/*
** ft_strdup:
** Cria uma CÓPIA de uma string (alocando nova memória).
**
** ⚠️  MALLOC: Esta função aloca memória!
**    O chamador DEVE fazer free() da string retornada!
**
** Exemplo:
**    char *original = "hello";
**    char *copia = ft_strdup(original);
**    // copia é uma nova string em outro lugar da memória
**    // modificar copia NÃO afeta original
**    free(copia);  // NÃO ESQUEÇA!
*/

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;
	int		i;

	/*
	** ========================================================================
	** TODO 1: Verificar NULL e calcular tamanho
	** ========================================================================
	** if (!src)
	**     return (NULL);
	** len = ft_strlen(src);
	** ========================================================================
	*/
	(void)dest;
	(void)len;
	(void)i;
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Alocar memória
	** ========================================================================
	** dest = malloc(len + 1);  // +1 para o '\0'!
	** if (!dest)
	**     return (NULL);  // malloc falhou (sem memória)
	**
	** 💡 PERGUNTA: Por que malloc pode falhar?
	**    Resposta: Se o sistema não tiver memória disponível.
	**    É raro, mas devemos sempre verificar!
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Copiar caractere por caractere
	** ========================================================================
	** i = 0;
	** while (src[i])
	** {
	**     dest[i] = src[i];
	**     i++;
	** }
	** dest[i] = '\0';  // Não esqueça do terminador!
	** return (dest);
	** ========================================================================
	*/
	/* Seu código aqui */

	return (NULL);
}

/*
** ============================================================================
**                    📋 RESUMO DAS FUNÇÕES
** ============================================================================
**
** ┌────────────────────────────────────────────────────────────────────────┐
** │ FUNÇÃO       │ USA MALLOC? │ PRECISA FREE? │ RETORNO                   │
** ├────────────────────────────────────────────────────────────────────────┤
** │ ft_putchar   │ Não         │ Não           │ void                      │
** │ ft_putstr    │ Não         │ Não           │ void                      │
** │ ft_strlen    │ Não         │ Não           │ int (comprimento)         │
** │ ft_strcmp    │ Não         │ Não           │ int (0 = igual)           │
** │ ft_isdigit   │ Não         │ Não           │ int (1 = é dígito)        │
** │ ft_strdup    │ SIM!        │ SIM!          │ char* (cópia ou NULL)     │
** └────────────────────────────────────────────────────────────────────────┘
**
** ============================================================================
*/
