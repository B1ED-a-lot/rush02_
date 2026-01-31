/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_utils.c                                   :+:      :+:    :+:   */
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
**                         FT_DICT_UTILS.C
** ============================================================================
**
** 📋 RESPONSABILIDADES DESTE ARQUIVO:
**    [1] Manipulação da lista ligada (adicionar, buscar)
**    [2] Liberação de memória do dicionário
**    [3] Funções auxiliares de string (trim, substr)
**
** ============================================================================
**                         LISTA LIGADA 101
** ============================================================================
**
** Uma lista ligada é como uma corrente:
**
**    head → [dado1|next:─┐]    [dado2|next:─┐]    [dado3|next:NULL]
**                        │                  │             ↑
**                        └─────────────────>└────────────>┘
**
** Cada "elo" (nó) tem:
**    - Os dados que queremos guardar (key, value)
**    - Um ponteiro para o próximo nó (next)
**
** O último nó aponta para NULL (fim da lista).
**
** ============================================================================
*/

/*
** dict_add_back:
** Adiciona uma entrada no FINAL da lista ligada.
**
** Parâmetros:
**   head  - ponteiro para ponteiro do início da lista
**   new   - nova entrada a ser adicionada
**
** 💡 Por que head é **head (ponteiro para ponteiro)?
**    Porque se a lista estiver vazia, precisamos MODIFICAR head!
**    Se fosse *head, modificaríamos apenas uma cópia local.
*/

void	dict_add_back(t_dict **head, t_dict *new_entry)
{
	t_dict	*current;

	(void)current;
	/*
	** ========================================================================
	** TODO 1: Verificar parâmetros
	** ========================================================================
	** Se head for NULL ou new_entry for NULL, apenas retorne.
	** Não há nada para fazer.
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Caso especial - lista vazia
	** ========================================================================
	** Se *head for NULL, a lista está vazia!
	** Nesse caso, o novo nó se torna o primeiro (head).
	**
	** *head = new_entry;
	** return;
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Encontrar o último nó
	** ========================================================================
	** Comece do head e percorra até encontrar um nó onde next == NULL
	**
	** current = *head;
	** while (current->next != NULL)
	**     current = current->next;
	**
	** 💡 VISUALIZAÇÃO:
	**    [A] → [B] → [C] → NULL
	**     ↑     ↑     ↑
	**   head   ...  current (parou aqui pois C->next == NULL)
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 4: Conectar o novo nó
	** ========================================================================
	** current->next = new_entry;
	**
	** Resultado:
	**    [A] → [B] → [C] → [NEW] → NULL
	** ========================================================================
	*/
	/* Seu código aqui */
}

/*
** dict_search:
** Busca uma chave no dicionário e retorna o valor correspondente.
**
** Parâmetros:
**   dict - ponteiro para o início da lista
**   key  - chave a ser buscada (ex: "42")
**
** Retorno:
**   O valor correspondente (ex: "forty two")
**   NULL se a chave não foi encontrada
**
** 💡 NOTA: Não aloca memória! Retorna ponteiro para dentro do dict.
*/

char	*dict_search(t_dict *dict, char *key)
{
	/*
	** ========================================================================
	** TODO: Percorrer a lista procurando a chave
	** ========================================================================
	** 
	** while (dict != NULL)
	** {
	**     if (ft_strcmp(dict->key, key) == 0)  // Chaves iguais!
	**         return (dict->value);
	**     dict = dict->next;
	** }
	** return (NULL);  // Não encontrou
	**
	** 💡 PERGUNTA: Por que usamos ft_strcmp e não dict->key == key?
	**    Resposta: Porque são PONTEIROS! Comparar ponteiros verifica
	**    se apontam pro MESMO lugar na memória, não se os conteúdos
	**    são iguais. ft_strcmp compara caractere por caractere.
	** ========================================================================
	*/
	/* Seu código aqui */

	(void)dict;
	(void)key;
	return (NULL);
}

/*
** free_dict:
** Libera TODA a memória alocada para o dicionário.
**
** ⚠️  CRÍTICO: Esta função DEVE liberar:
**    - Cada node->key
**    - Cada node->value
**    - Cada node (a estrutura t_dict em si)
**
** 💡 DICA: Sempre que fizer malloc, pergunte: "Onde está o free?"
*/

void	free_dict(t_dict *dict)
{
	t_dict	*next;

	(void)next;
	/*
	** ========================================================================
	** TODO: Percorrer e liberar cada nó
	** ========================================================================
	**
	** while (dict != NULL)
	** {
	**     next = dict->next;  // Guarda o próximo ANTES de liberar!
	**     free(dict->key);
	**     free(dict->value);
	**     free(dict);
	**     dict = next;
	** }
	**
	** 💡 PERGUNTA CRÍTICA: Por que salvamos dict->next antes de free?
	**    Resposta: Depois do free(dict), a memória de dict é inválida!
	**    Acessar dict->next depois do free seria um BUG grave.
	**
	** 📊 VISUALIZAÇÃO:
	**    [A] → [B] → [C] → NULL
	**
	**    Iteração 1: dict=[A], next=[B], free([A])
	**    Iteração 2: dict=[B], next=[C], free([B])
	**    Iteração 3: dict=[C], next=NULL, free([C])
	**    Iteração 4: dict=NULL, sai do while
	** ========================================================================
	*/
	/* Seu código aqui */
}

/*
** ft_strtrim_spaces:
** Remove espaços do INÍCIO e FIM de uma string.
**
** Parâmetros:
**   str - string original
**
** Retorno:
**   Nova string trimada (malloc!)
**   NULL se erro
**
** Exemplo:
**   "  hello world  " → "hello world"
**   "   42   " → "42"
**
** ⚠️  ATENÇÃO: Usa malloc! Caller deve fazer free!
*/

char	*ft_strtrim_spaces(char *str)
{
	int		start;
	int		end;
	int		len;
	char	*result;
	int		i;

	(void)start;
	(void)end;
	(void)len;
	(void)result;
	(void)i;
	/*
	** ========================================================================
	** TODO 1: Verificar parâmetro
	** ========================================================================
	** Se str for NULL, retorne NULL
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Encontrar o início (primeiro caractere não-espaço)
	** ========================================================================
	** start = 0;
	** while (str[start] == ' ' || str[start] == '\t')
	**     start++;
	**
	** 💡 NOTA: '\t' é TAB. O dicionário pode ter tabs como espaços.
	**
	** Exemplo: "   hello" → start = 3
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Encontrar o fim (último caractere não-espaço)
	** ========================================================================
	** end = ft_strlen(str) - 1;
	** while (end > start && (str[end] == ' ' || str[end] == '\t'
	**        || str[end] == '\n' || str[end] == '\r'))
	**     end--;
	**
	** 💡 NOTA: Também removemos \n e \r (fim de linha)
	**
	** Exemplo: "hello   \n" → end = 4 (posição do 'o')
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 4: Calcular tamanho e alocar
	** ========================================================================
	** len = end - start + 1;
	** if (len <= 0)   // String era só espaços!
	**     return (ft_strdup(""));  // Retorna string vazia
	** result = malloc(len + 1);  // +1 para o '\0'
	** if (!result)
	**     return (NULL);
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 5: Copiar a parte trimada
	** ========================================================================
	** i = 0;
	** while (i < len)
	** {
	**     result[i] = str[start + i];
	**     i++;
	** }
	** result[i] = '\0';
	** return (result);
	** ========================================================================
	*/
	/* Seu código aqui */

	return (NULL);
}

/*
** ============================================================================
**                    📋 FUNÇÕES AUXILIARES EXTRAS
** ============================================================================
**
** Se precisar, adicione aqui:
**   - ft_substr: extrai parte de uma string
**   - ft_strjoin: concatena duas strings
**
** ⚠️  LEMBRE: Máximo 5 funções por arquivo!
**    Se precisar de mais, crie ft_string_utils.c
**
** ============================================================================
*/
