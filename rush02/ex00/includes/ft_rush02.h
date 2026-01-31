/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rush02.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seu_login <seu_login@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:00:00 by seu_login         #+#    #+#             */
/*   Updated: 2026/01/30 00:00:00 by seu_login        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RUSH02_H
# define FT_RUSH02_H

/*
** ============================================================================
**                           RUSH-02: NUMBER TO WORDS
** ============================================================================
**
** 🎯 OBJETIVO:
** Converter um número em sua forma escrita por extenso, usando um dicionário.
**
** Exemplo: 42 → "forty two"
**          1234 → "one thousand two hundred thirty four"
**
** ============================================================================
**                         FUNÇÕES PERMITIDAS
** ============================================================================
**
** write  - Escreve bytes no terminal (você já conhece!)
** malloc - Aloca memória dinamicamente (NOVO!)
** free   - Libera memória alocada (NOVO!)
** open   - Abre um arquivo (NOVO!)
** read   - Lê bytes de um arquivo (NOVO!)
** close  - Fecha um arquivo (NOVO!)
**
** ⚠️  NENHUMA outra função é permitida! Nem printf, nem atoi, nem strlen da
**     biblioteca padrão. Vocês devem implementar tudo do zero.
**
** ============================================================================
**                        INCLUDES PERMITIDOS
** ============================================================================
*/

# include <unistd.h>    /* write, read, close */
# include <stdlib.h>    /* malloc, free */
# include <fcntl.h>     /* open (O_RDONLY) */

/*
** ============================================================================
**                              CONSTANTES
** ============================================================================
*/

/* Caminho padrão do dicionário (quando usuário não especifica) */
# define DEFAULT_DICT "data/numbers.dict"

/* Tamanho do buffer para leitura do arquivo */
/* TODO: Pergunta para o grupo: Por que 4096 e não 1? */
/*       Dica: Pense em quantas vezes read() é chamado... */
# define BUFFER_SIZE 4096

/*
** ============================================================================
**                              ESTRUTURAS
** ============================================================================
**
** 📚 REGRA DA NORMA:
**    - struct começa com s_  (ex: struct s_dict)
**    - typedef começa com t_ (ex: t_dict)
**
** ============================================================================
*/

/*
** s_dict: Armazena UMA entrada do dicionário
**
** ┌─────────────────────────────────────────────────────────────────────────┐
** │ IMPORTANTE: Por que key é char* e não int?                              │
** │                                                                         │
** │ O subject diz: "deve lidar com números ALÉM do unsigned int"            │
** │ unsigned int vai até ~4 bilhões (4.294.967.295)                         │
** │ O dicionário tem números até 10^36 (undecillion!)                       │
** │                                                                         │
** │ Então guardamos o número como STRING para comparar depois.              │
** └─────────────────────────────────────────────────────────────────────────┘
**
** Exemplo de entrada no dicionário: "42: forty two"
**   → key   = "42"
**   → value = "forty two"
*/

typedef struct s_dict
{
	char			*key;       /* O número como string (ex: "42", "1000") */
	char			*value;     /* O texto (ex: "forty two", "thousand") */
	struct s_dict	*next;      /* Ponteiro para próxima entrada (lista ligada) */
}	t_dict;

/*
** ============================================================================
**                    POR QUE LISTA LIGADA E NÃO ARRAY?
** ============================================================================
**
** 💡 Vantagem da Lista Ligada:
**    - Não precisa saber quantas entradas o dicionário tem antes de ler
**    - Pode adicionar entradas dinamicamente conforme lê o arquivo
**    - Cada entrada pode ter tamanho diferente
**
** 📊 Estrutura na memória:
**
**    head → [key:"0"|value:"zero"|next:─┐]
**                                       │
**           [key:"1"|value:"one"|next:──┼┐]
**                                       ││
**           [key:"2"|value:"two"|next:──┼┼┐]
**                                       │││
**                        ...            │││
**                                       ↓↓↓
**           [key:"1000"|value:"thousand"|next:NULL]
**
** ============================================================================
*/

/*
** ============================================================================
**                         FUNÇÕES UTILITÁRIAS
**                           (ft_utils.c)
** ============================================================================
** Estas são funções básicas que vocês já conhecem ou podem implementar
** facilmente. São os "blocos de construção" do projeto.
*/

/* Escreve uma string no terminal */
void	ft_putstr(char *str);

/* Escreve um caractere no terminal */
void	ft_putchar(char c);

/* Retorna o comprimento de uma string */
int		ft_strlen(char *str);

/* Compara duas strings (retorna 0 se iguais) */
int		ft_strcmp(char *s1, char *s2);

/* Duplica uma string (aloca memória nova!) */
/* ⚠️  ATENÇÃO: Usa malloc! Precisa de free depois! */
char	*ft_strdup(char *src);

/* Verifica se caractere é um dígito (0-9) */
int		ft_isdigit(char c);

/*
** ============================================================================
**                         PARSING DO DICIONÁRIO
**                      (ft_dict_parsing.c e ft_dict_utils.c)
** ============================================================================
** Responsável por:
** - Abrir e ler o arquivo do dicionário
** - Separar cada linha em key (número) e value (texto)
** - Construir a lista ligada de t_dict
*/

/* Lê o arquivo inteiro e retorna como uma única string */
/* ⚠️  ATENÇÃO: Usa malloc! Precisa de free depois! */
char	*read_file(char *filename);

/* Faz o parsing completo: arquivo → lista ligada */
/* ⚠️  ATENÇÃO: Usa malloc! Precisa de free depois! */
t_dict	*parse_dict(char *filename);

/* Faz o parsing de uma única linha do dicionário */
/* ⚠️  ATENÇÃO: Usa malloc! Precisa de free depois! */
t_dict	*parse_line(char *line);

/* Adiciona uma entrada no final da lista */
void	dict_add_back(t_dict **head, t_dict *new_entry);

/* Busca uma chave no dicionário (retorna o value ou NULL) */
char	*dict_search(t_dict *dict, char *key);

/* Libera TODA a memória do dicionário */
/* 📋 ESSENCIAL: Deve ser chamado antes do programa terminar! */
void	free_dict(t_dict *dict);

/*
** ============================================================================
**                         FUNÇÕES DE TRIMMING
**                         (ft_dict_utils.c)
** ============================================================================
** O dicionário pode ter espaços extras:
**   "  42   :   forty two  "
** Precisamos remover esses espaços para obter:
**   key = "42"
**   value = "forty two"
*/

/* Remove espaços do início e fim de uma string */
/* ⚠️  ATENÇÃO: Usa malloc! Precisa de free depois! */
char	*ft_strtrim_spaces(char *str);

/*
** ============================================================================
**                       CONVERSÃO DE NÚMEROS
**                      (ft_number_converter.c)
** ============================================================================
** O CORAÇÃO DO PROJETO! Aqui acontece a mágica de transformar
** "1234" em "one thousand two hundred thirty four"
*/

/* Valida se a string é um número válido (apenas dígitos, sem sinais) */
int		is_valid_number(char *str);

/* Função principal de conversão: número → texto */
/* Retorna 1 se sucesso, 0 se erro */
int		convert_number(t_dict *dict, char *number);

/*
** ============================================================================
**                         FUNÇÕES DE ERRO
**                           (main.c)
** ============================================================================
*/

/* Imprime "Error\n" - para número inválido */
void	print_error(void);

/* Imprime "Dict Error\n" - para problemas no dicionário */
void	print_dict_error(void);

#endif

/*
** ============================================================================
**                    📋 CHECKLIST DE MEMÓRIA
** ============================================================================
**
** Toda vez que usar malloc, anote aqui para não esquecer o free:
**
** ┌─────────────────────────────────────────────────────────────────────────┐
** │ FUNÇÃO               │ MALLOC EM           │ FREE EM                    │
** ├─────────────────────────────────────────────────────────────────────────┤
** │ read_file()          │ conteúdo do arquivo │ após parse_dict()          │
** │ ft_strdup()          │ cópia da string     │ em free_dict() ou caller   │
** │ ft_strtrim_spaces()  │ string trimada      │ caller da função           │
** │ parse_line()         │ t_dict node         │ em free_dict()             │
** │ parse_line()         │ node->key           │ em free_dict()             │
** │ parse_line()         │ node->value         │ em free_dict()             │
** └─────────────────────────────────────────────────────────────────────────┘
**
** 🎯 REGRA DE OURO: Quem aloca, libera (ou documenta quem vai liberar)
**
** ============================================================================
*/
