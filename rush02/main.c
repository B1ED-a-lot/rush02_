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

/*
** RUSH-02 em um único arquivo (experimento com 10 funções)
** Funções permitidas: write, malloc, free, open, read, close
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096
#define DEFAULT_DICT "numbers.dict"

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

/*
** FUNÇÃO 1: ft_strlen
** Retorna comprimento da string
*/
int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*
** FUNÇÃO 2: ft_strcmp
** Compara duas strings, retorna 0 se iguais
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
** FUNÇÃO 3: ft_strdup_trim
** Duplica string removendo espaços do início e fim
** Combina strdup + strtrim em uma função
*/
char	*ft_strdup_trim(char *src, int start, int end)
{
	char	*dest;
	int		i;
	int		len;

	if (!src)
		return (NULL);
	while (start <= end && (src[start] == ' ' || src[start] == '\t'))
		start++;
	while (end > start && (src[end] == ' ' || src[end] == '\t'
			|| src[end] == '\n' || src[end] == '\r'))
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (NULL);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** FUNÇÃO 4: parse_dict
** Lê o arquivo e cria a lista ligada do dicionário
** Combina: open + read + parsing + criação de lista
*/
t_dict	*parse_dict(char *filename)
{
	int		fd;
	char	buf[BUFFER_SIZE];
	char	*content;
	char	*temp;
	int		bytes;
	int		total;
	t_dict	*head;
	t_dict	*node;
	int		i;
	int		line_start;
	int		colon;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	total = 0;
	while ((bytes = read(fd, buf, BUFFER_SIZE - 1)) > 0)
	{
		buf[bytes] = '\0';
		temp = malloc(total + bytes + 1);
		if (!temp)
		{
			free(content);
			close(fd);
			return (NULL);
		}
		i = 0;
		while (i < total)
		{
			temp[i] = content[i];
			i++;
		}
		i = 0;
		while (i < bytes)
		{
			temp[total + i] = buf[i];
			i++;
		}
		temp[total + bytes] = '\0';
		free(content);
		content = temp;
		total = total + bytes;
	}
	close(fd);
	if (bytes == -1 || total == 0)
	{
		free(content);
		return (NULL);
	}
	head = NULL;
	i = 0;
	line_start = 0;
	while (i <= total)
	{
		if (content[i] == '\n' || content[i] == '\0')
		{
			colon = line_start;
			while (colon < i && content[colon] != ':')
				colon++;
			if (colon > line_start && colon < i)
			{
				node = malloc(sizeof(t_dict));
				if (node)
				{
					node->key = ft_strdup_trim(content, line_start, colon - 1);
					node->value = ft_strdup_trim(content, colon + 1, i - 1);
					node->next = NULL;
					if (node->key && node->value)
					{
						if (!head)
							head = node;
						else
						{
							temp = (char *)head;
							while (((t_dict *)temp)->next)
								temp = (char *)((t_dict *)temp)->next;
							((t_dict *)temp)->next = node;
						}
					}
					else
					{
						free(node->key);
						free(node->value);
						free(node);
					}
				}
			}
			line_start = i + 1;
		}
		i++;
	}
	free(content);
	return (head);
}

/*
** FUNÇÃO 5: dict_search
** Busca uma chave no dicionário e retorna o valor
*/
char	*dict_search(t_dict *dict, char *key)
{
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}

/*
** FUNÇÃO 6: free_dict
** Libera toda a memória do dicionário
*/
void	free_dict(t_dict *dict)
{
	t_dict	*next;

	while (dict)
	{
		next = dict->next;
		free(dict->key);
		free(dict->value);
		free(dict);
		dict = next;
	}
}

/*
** FUNÇÃO 7: is_valid_number
** Verifica se string é número válido (apenas dígitos)
** Retorna ponteiro para primeiro dígito não-zero (ou último se tudo zero)
*/
char	*is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (NULL);
		i++;
	}
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	return (str);
}

/*
** FUNÇÃO 8: print_small
** Imprime números de 0 a 99
** Retorna 1 se sucesso, 0 se erro
*/
int	print_small(t_dict *dict, char *num, int len)
{
	char	*val;
	char	tens[3];
	char	units[2];

	val = dict_search(dict, num);
	if (val)
	{
		write(1, val, ft_strlen(val));
		return (1);
	}
	if (len != 2)
		return (0);
	tens[0] = num[0];
	tens[1] = '0';
	tens[2] = '\0';
	val = dict_search(dict, tens);
	if (!val)
		return (0);
	write(1, val, ft_strlen(val));
	if (num[1] != '0')
	{
		units[0] = num[1];
		units[1] = '\0';
		val = dict_search(dict, units);
		if (!val)
			return (0);
		write(1, " ", 1);
		write(1, val, ft_strlen(val));
	}
	return (1);
}

/*
** FUNÇÃO 9: convert_number
** Converte número para texto recursivamente
** Lida com todas as grandezas (hundred, thousand, million, etc)
*/
int	convert_number(t_dict *dict, char *num, int space)
{
	int		len;
	char	*scale_key;
	char	*val;
	int		scale_len;
	char	part[40];
	int		i;
	int		all_zero;

	while (*num == '0' && *(num + 1) != '\0')
		num++;
	len = ft_strlen(num);
	if (len == 0)
		return (1);
	if (space)
		write(1, " ", 1);
	if (len <= 2)
		return (print_small(dict, num, len));
	if (len == 3)
	{
		part[0] = num[0];
		part[1] = '\0';
		if (!print_small(dict, part, 1))
			return (0);
		val = dict_search(dict, "100");
		if (!val)
			return (0);
		write(1, " ", 1);
		write(1, val, ft_strlen(val));
		if (num[1] != '0' || num[2] != '0')
			return (convert_number(dict, num + 1, 1));
		return (1);
	}
	if (len <= 6)
	{
		scale_key = "1000";
		scale_len = 3;
	}
	else if (len <= 9)
	{
		scale_key = "1000000";
		scale_len = 6;
	}
	else if (len <= 12)
	{
		scale_key = "1000000000";
		scale_len = 9;
	}
	else if (len <= 15)
	{
		scale_key = "1000000000000";
		scale_len = 12;
	}
	else if (len <= 18)
	{
		scale_key = "1000000000000000";
		scale_len = 15;
	}
	else if (len <= 21)
	{
		scale_key = "1000000000000000000";
		scale_len = 18;
	}
	else if (len <= 24)
	{
		scale_key = "1000000000000000000000";
		scale_len = 21;
	}
	else if (len <= 27)
	{
		scale_key = "1000000000000000000000000";
		scale_len = 24;
	}
	else if (len <= 30)
	{
		scale_key = "1000000000000000000000000000";
		scale_len = 27;
	}
	else if (len <= 33)
	{
		scale_key = "1000000000000000000000000000000";
		scale_len = 30;
	}
	else if (len <= 36)
	{
		scale_key = "1000000000000000000000000000000000";
		scale_len = 33;
	}
	else
	{
		scale_key = "1000000000000000000000000000000000000";
		scale_len = 36;
	}
	i = 0;
	while (i < len - scale_len)
	{
		part[i] = num[i];
		i++;
	}
	part[i] = '\0';
	if (!convert_number(dict, part, 0))
		return (0);
	val = dict_search(dict, scale_key);
	if (!val)
		return (0);
	write(1, " ", 1);
	write(1, val, ft_strlen(val));
	all_zero = 1;
	i = len - scale_len;
	while (num[i])
	{
		if (num[i] != '0')
			all_zero = 0;
		i++;
	}
	if (!all_zero)
		return (convert_number(dict, num + (len - scale_len), 1));
	return (1);
}

/*
** FUNÇÃO 10: main
** Ponto de entrada - valida args, carrega dict, converte, limpa
*/
int	main(int argc, char **argv)
{
	char	*dict_path;
	char	*number;
	t_dict	*dict;

	if (argc != 2 && argc != 3)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (argc == 2)
	{
		dict_path = DEFAULT_DICT;
		number = argv[1];
	}
	else
	{
		dict_path = argv[1];
		number = argv[2];
	}
	number = is_valid_number(number);
	if (!number)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	dict = parse_dict(dict_path);
	if (!dict)
	{
		write(1, "Dict Error\n", 11);
		return (1);
	}
	if (!convert_number(dict, number, 0))
	{
		write(1, "Dict Error\n", 11);
		free_dict(dict);
		return (1);
	}
	write(1, "\n", 1);
	free_dict(dict);
	return (0);
}
