/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_parsing.c                                 :+:      :+:    :+:   */
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
**                         FT_DICT_PARSING.C
** ============================================================================
**
** 📋 RESPONSABILIDADES DESTE ARQUIVO:
**    [1] Abrir e ler o arquivo do dicionário
**    [2] Processar linha por linha
**    [3] Construir a lista ligada de t_dict
**
** ============================================================================
**                    ANATOMIA DE UMA LINHA DO DICIONÁRIO
** ============================================================================
**
** Formato: [número][espaços]:[espaços][texto]\n
**
** Exemplos válidos:
**    "0: zero\n"
**    "42 : forty two\n"
**    "  100  :   hundred  \n"
**
** Processo de parsing:
**    "  42   :   forty two  \n"
**         │
**         ▼
**    ┌─────────────────────────────────────────┐
**    │ 1. Encontrar o ':'                      │
**    │ 2. Pegar tudo ANTES do ':' → "  42   "  │
**    │ 3. Pegar tudo DEPOIS do ':' → "forty.." │
**    │ 4. Remover espaços (trim) de ambos      │
**    │ 5. key = "42", value = "forty two"      │
**    └─────────────────────────────────────────┘
**
** ============================================================================
**                    🆕 FUNÇÕES NOVAS: open, read, close
** ============================================================================
**
** 📁 open(filename, flags):
**    - Abre um arquivo e retorna um "file descriptor" (fd)
**    - fd é um número inteiro que identifica o arquivo aberto
**    - flags: O_RDONLY = abrir apenas para leitura
**    - Retorna -1 se erro (arquivo não existe, sem permissão, etc)
**
** 📖 read(fd, buffer, count):
**    - Lê até 'count' bytes do arquivo para o 'buffer'
**    - Retorna quantos bytes foram lidos de verdade
**    - Retorna 0 quando chegou no fim do arquivo
**    - Retorna -1 se erro
**
** 🔒 close(fd):
**    - Fecha o arquivo
**    - SEMPRE feche arquivos que você abriu!
**
** ============================================================================
*/

/*
** read_file:
** Lê o conteúdo INTEIRO de um arquivo e retorna como string.
**
** Parâmetros:
**   filename - caminho do arquivo
**
** Retorno:
**   String com o conteúdo do arquivo (malloc!)
**   NULL se erro
**
** ⚠️  ATENÇÃO: Esta função usa malloc!
**    O chamador (caller) é responsável por fazer free!
*/

char	*read_file(char *filename)
{
	int		fd;
	char	*content;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	(void)content;
	(void)buffer;
	(void)bytes_read;
	/*
	** ========================================================================
	** TODO 1: Abrir o arquivo
	** ========================================================================
	** Use open(filename, O_RDONLY)
	** O_RDONLY significa "read only" (apenas leitura)
	**
	** Se open retornar -1, significa erro. Retorne NULL.
	**
	** 💡 EXEMPLO:
	**    fd = open(filename, O_RDONLY);
	**    if (fd == -1)
	**        return (NULL);
	** ========================================================================
	*/
	fd = -1;
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Ler o arquivo em partes
	** ========================================================================
	** Esta é a parte mais complexa! Você precisa:
	**
	** 1. Criar uma string 'content' inicialmente vazia (ou NULL)
	** 2. Ler BUFFER_SIZE bytes por vez em 'buffer'
	** 3. Concatenar 'buffer' no final de 'content'
	** 4. Repetir até read() retornar 0 (fim do arquivo)
	**
	** 💡 DICA SIMPLIFICADA PARA INICIANTES:
	**    Uma abordagem mais simples (menos eficiente mas funciona):
	**    - Primeiro, descubra o tamanho do arquivo lendo todo ele
	**    - Volte ao início com lseek() ou feche/reabra
	**    - Aloque memória suficiente
	**    - Leia tudo de uma vez
	**
	** 💡 DICA AVANÇADA (recomendada):
	**    Use uma função auxiliar para "juntar" strings (ft_strjoin)
	**    que aloca nova memória e concatena duas strings.
	**
	** 💡 PERGUNTA: Por que lemos em partes e não byte por byte?
	**    Resposta: read() faz uma "chamada de sistema" (syscall).
	**    Syscalls são lentas. Melhor fazer poucas leituras grandes
	**    do que muitas leituras pequenas.
	**
	** PSEUDOCÓDIGO:
	**    content = ft_strdup("");  // String vazia inicial
	**    while (1)
	**    {
	**        bytes_read = read(fd, buffer, BUFFER_SIZE);
	**        if (bytes_read <= 0)
	**            break;
	**        buffer[bytes_read] = '\0';  // Termina a string!
	**        temp = content;
	**        content = ft_strjoin(content, buffer);
	**        free(temp);  // Libera a string antiga!
	**    }
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Fechar o arquivo e retornar
	** ========================================================================
	** SEMPRE feche arquivos que você abriu!
	**
	** close(fd);
	** return (content);
	** ========================================================================
	*/
	/* Seu código aqui */

	return (NULL);
}

/*
** parse_line:
** Faz o parsing de UMA linha do dicionário.
**
** Parâmetros:
**   line - uma linha do dicionário (ex: "42 : forty two")
**
** Retorno:
**   Ponteiro para novo t_dict com key e value (malloc!)
**   NULL se linha inválida ou erro
**
** ⚠️  ATENÇÃO: Aloca memória para t_dict, key e value!
*/

t_dict	*parse_line(char *line)
{
	t_dict	*entry;
	int		colon_pos;
	char	*raw_key;
	char	*raw_value;

	(void)entry;
	(void)colon_pos;
	(void)raw_key;
	(void)raw_value;
	/*
	** ========================================================================
	** TODO 1: Verificar se linha é válida
	** ========================================================================
	** - Linha NULL ou vazia → retorna NULL
	** - Linha sem ':' → retorna NULL
	** - Linha que é só espaços → retorna NULL
	**
	** 💡 PERGUNTA: Como encontrar o ':' na string?
	**    Resposta: Percorra a string com um while procurando ':'
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Encontrar a posição do ':'
	** ========================================================================
	** Percorra a linha caractere por caractere até encontrar ':'
	** Guarde a posição em colon_pos
	**
	** 💡 CUIDADO: E se a linha não tiver ':'?
	**    Você precisa verificar isso! Retorne NULL.
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Extrair a parte ANTES do ':' (raw_key)
	** ========================================================================
	** Crie uma substring de line[0] até line[colon_pos - 1]
	**
	** 💡 DICA: Você vai precisar de uma função auxiliar ft_substr
	**    que extrai uma parte da string.
	**
	** Exemplo: "  42   :  forty two"
	**          colon_pos = 7
	**          raw_key = "  42   " (índices 0 a 6)
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 4: Extrair a parte DEPOIS do ':' (raw_value)
	** ========================================================================
	** Crie uma substring de line[colon_pos + 1] até o final
	** (mas sem incluir '\n' se existir!)
	**
	** Exemplo: "  42   :  forty two\n"
	**          colon_pos = 7
	**          raw_value = "  forty two" (índices 8 até fim, sem \n)
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 5: Remover espaços (trim) de raw_key e raw_value
	** ========================================================================
	** Use ft_strtrim_spaces para remover espaços do início e fim
	**
	** raw_key   "  42   " → "42"
	** raw_value "  forty two  " → "forty two"
	**
	** ⚠️  CUIDADO: ft_strtrim_spaces aloca nova memória!
	**    Você precisa fazer free de raw_key e raw_value depois!
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 6: Validar key e value
	** ========================================================================
	** - key não pode ser vazio ou só espaços
	** - key deve conter apenas dígitos
	** - value não pode ser vazio
	**
	** Se qualquer validação falhar, libere memória e retorne NULL
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 7: Criar o nó t_dict
	** ========================================================================
	** - Aloque memória para entry (sizeof(t_dict))
	** - entry->key = chave trimada (já alocada)
	** - entry->value = valor trimado (já alocado)
	** - entry->next = NULL
	**
	** Retorne entry
	** ========================================================================
	*/
	/* Seu código aqui */

	return (NULL);
}

/*
** parse_dict:
** Faz o parsing completo do arquivo do dicionário.
**
** Parâmetros:
**   filename - caminho do arquivo do dicionário
**
** Retorno:
**   Ponteiro para o início da lista ligada (head)
**   NULL se erro
**
** ⚠️  ATENÇÃO: Esta função aloca MUITA memória!
**    O chamador DEVE chamar free_dict() para liberar!
*/

t_dict	*parse_dict(char *filename)
{
	char	*content;
	t_dict	*head;
	t_dict	*entry;
	int		i;
	int		line_start;

	(void)content;
	(void)head;
	(void)entry;
	(void)i;
	(void)line_start;
	/*
	** ========================================================================
	** TODO 1: Ler o arquivo inteiro
	** ========================================================================
	** Chame read_file(filename)
	** Se retornar NULL, retorne NULL
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 2: Processar linha por linha
	** ========================================================================
	** Percorra 'content' caractere por caractere.
	** Quando encontrar '\n', você tem uma linha completa!
	**
	** PSEUDOCÓDIGO:
	**    head = NULL;
	**    i = 0;
	**    line_start = 0;
	**    while (content[i])
	**    {
	**        if (content[i] == '\n')
	**        {
	**            line = extrair_substring(content, line_start, i);
	**            entry = parse_line(line);
	**            if (entry)
	**                dict_add_back(&head, entry);
	**            free(line);
	**            line_start = i + 1;
	**        }
	**        i++;
	**    }
	**
	** 💡 PERGUNTA: E se a última linha não terminar com '\n'?
	**    Você precisa processar ela também!
	** ========================================================================
	*/
	/* Seu código aqui */

	/*
	** ========================================================================
	** TODO 3: Liberar content e retornar head
	** ========================================================================
	** free(content);
	** return (head);
	**
	** 💡 PERGUNTA: Por que não precisamos fazer free do head aqui?
	**    Resposta: O chamador (main) precisa usar o head!
	**    Ele vai chamar free_dict() quando terminar.
	** ========================================================================
	*/
	/* Seu código aqui */

	return (NULL);
}

/*
** ============================================================================
**                    📊 VISUALIZAÇÃO DO PROCESSO
** ============================================================================
**
** Arquivo numbers.dict:
**    ┌────────────────────────┐
**    │ 0: zero                │
**    │ 1: one                 │
**    │ 42 : forty two         │
**    │ 100: hundred           │
**    └────────────────────────┘
**
** Após read_file():
**    content = "0: zero\n1: one\n42 : forty two\n100: hundred\n"
**
** Após processar cada linha:
**    ┌───────────────────────────────────────────────────────────────┐
**    │ Linha: "0: zero\n"                                            │
**    │   → parse_line() → {key:"0", value:"zero", next:NULL}         │
**    │                                                               │
**    │ Linha: "1: one\n"                                             │
**    │   → parse_line() → {key:"1", value:"one", next:NULL}          │
**    │                                                               │
**    │ Linha: "42 : forty two\n"                                     │
**    │   → parse_line() → {key:"42", value:"forty two", next:NULL}   │
**    │                                                               │
**    │ Linha: "100: hundred\n"                                       │
**    │   → parse_line() → {key:"100", value:"hundred", next:NULL}    │
**    └───────────────────────────────────────────────────────────────┘
**
** Lista ligada final:
**    head → [0|zero] → [1|one] → [42|forty two] → [100|hundred] → NULL
**
** ============================================================================
*/
