/* ************************************************************************** */
/*                                                                            */
/*   main.c (TESTS)                                                           */
/*   Testando funções isoladas do Rush 02                                     */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> /* Para printf (apenas nos testes) */

/* --- ESTRUTURAS E DEFINIÇÕES --- */

typedef struct s_dict
{
	char			*key;
	char			*valueue;
	struct s_dict	*next;
}	t_dict;

/* --- HELPERS NECESSÁRIOS --- */

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

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(src);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* --- FUNÇÕES ALVO DO TESTE (COPIADAS) --- */

/* FUNÇÃO 5: dict_search */
char	*dict_search(t_dict *dict, char *key)
{
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
			return (dict->valueue);
		dict = dict->next;
	}
	return (NULL);
}

/* FUNÇÃO 6: free_dict */
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

/* FUNÇÃO 7: is_valueid_number */
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
** FUNÇÃO: print_small
** Missão: Imprimir números de 0 a 99.
** Recebe: O dicionário (livro de referência) e o número em texto (ex: "42").
*/
int print_small(t_dict *dict, char *num, int len)
{
    char *val;       // Variável para guardar a tradução encontrada (ex: "forty")
    char tens[3];    // Espaço para montar a dezena (ex: "40" + \0)
    char units[2];   // Espaço para montar a unidade (ex: "2" + \0)

    // PASSO 1: TENTATIVA DIRETA
    // O número exato existe no dicionário? (ex: "11" -> eleven, "42" -> forty two)
    val = dict_search(dict, num);
    if (val) 
    {
        // Se achou, ótimo! Imprime e vai embora feliz.
        write(1, val, ft_strlen(val));
        return (1); // Sucesso
    }

    // PASSO 2: SEPARAÇÃO (Só para números de 2 dígitos)
    // Se não achou direto e não tem 2 dígitos (len != 2), então deu ruim.
    // Ex: Se veio "5" e não achou no passo 1, é erro no dicionário.
    if (len != 2)
        return (0); // Erro

    // PASSO 3: MONTAR A DEZENA
    // Vamos pegar o "4" de "42" e transformar em "40".
    tens[0] = num[0]; // Pega o '4'
    tens[1] = '0';    // Coloca o '0' do lado -> vira "40"
    tens[2] = '\0';   // Fecha a string

    // Busca "40" no dicionário
    val = dict_search(dict, tens);
    if (!val)
        return (0); // Se não tiver "40" no dicionário, impossível continuar. Erro.
    
    // Imprime a dezena ("forty")
    write(1, val, ft_strlen(val));

    // PASSO 4: MONTAR A UNIDADE
    // Se o segundo número não for 0 (ex: 40 não precisa imprimir "zero")
    if (num[1] != '0')
    {
        units[0] = num[1]; // Pega o '2'
        units[1] = '\0';   // Fecha a string -> vira "2"

        // Busca "2" no dicionário
        val = dict_search(dict, units);
        if (!val)
            return (0); // Se não tiver "2", erro.

        // Imprime um espacinho para separar "forty" de "two"
        write(1, " ", 1);
        
        // Imprime a unidade ("two")
        write(1, val, ft_strlen(val));
    }

    // Trabalho concluído com sucesso!
    return (1);
}

/* --- HELPERS DE TESTE --- */

/* Adiciona um item ao dicionário manualmente */
void	add_mock_item(t_dict **head, char *key, char *value)
{
	t_dict *node = malloc(sizeof(t_dict));
	node->key = ft_strdup(key);
	node->valueue = ft_strdup(value);
	node->next = *head;
	*head = node;
}

/* Cria um dicionário básico para testes */
t_dict	*create_mock_dict(void)
{
	t_dict *dict = NULL;
	add_mock_item(&dict, "0", "zero");
	add_mock_item(&dict, "1", "one");
	add_mock_item(&dict, "2", "two");
	add_mock_item(&dict, "3", "three");
	add_mock_item(&dict, "4", "four");
	add_mock_item(&dict, "5", "five");
	add_mock_item(&dict, "6", "six");
	add_mock_item(&dict, "7", "seven");
	add_mock_item(&dict, "8", "eight");
	add_mock_item(&dict, "9", "nine");
	add_mock_item(&dict, "10", "ten");
	add_mock_item(&dict, "11", "eleven");
	add_mock_item(&dict, "12", "twelve");
	add_mock_item(&dict, "20", "twenty");
	add_mock_item(&dict, "30", "thirty");
	add_mock_item(&dict, "40", "forty");
	add_mock_item(&dict, "42", "forty two"); // Exemplo composto direto
	add_mock_item(&dict, "50", "fifty");
	return dict;
}

/* --- MAIN DE TESTE --- */

int	main(int argc, char **argv)
{
	t_dict	*dict;
	char	*result;
	int		ret;

	if (argc < 2)
	{
		printf("Uso: %s [valueid|search|print|free] [args...]\n", argv[0]);
		return (1);
	}

	/* Teste is_valueid_number */
	if (ft_strcmp(argv[1], "valueid") == 0)
	{
		if (argc != 3)
		{
			printf("Uso: %s valueid <numero>\n", argv[0]);
			return (1);
		}
		printf("Testando is_valueid_number('%s')...\n", argv[2]);
		result = is_valueid_number(argv[2]);
		if (result)
			printf("SUCESSO: valueido. Retorno: '%s'\n", result);
		else
			printf("FALHA: Invalueido (NULL)\n");
	}
	/* Teste dict_search */
	else if (ft_strcmp(argv[1], "search") == 0)
	{
		if (argc != 3)
		{
			printf("Uso: %s search <chave>\n", argv[0]);
			return (1);
		}
		dict = create_mock_dict();
		printf("Buscando chave '%s' no dicionario mock...\n", argv[2]);
		result = dict_search(dict, argv[2]);
		if (result)
			printf("ENCONTRADO: valueor = '%s'\n", result);
		else
			printf("NAO ENCONTRADO.\n");
		free_dict(dict);
	}
	/* Teste print_small */
	else if (ft_strcmp(argv[1], "print") == 0)
	{
		if (argc != 3)
		{
			printf("Uso: %s print <numero_pequeno>\n", argv[0]);
			return (1);
		}
		dict = create_mock_dict();
		printf("Testando print_small('%s'):\nOutput: [", argv[2]);
		fflush(stdout); // Garante que o printf saia antes do write
		ret = print_small(dict, argv[2], ft_strlen(argv[2]));
		write(1, "]\n", 2);
		
		if (ret)
			printf("Retorno: 1 (Sucesso)\n");
		else
			printf("Retorno: 0 (Erro)\n");
		free_dict(dict);
	}
	/* Teste free_dict */
	else if (ft_strcmp(argv[1], "free") == 0)
	{
		dict = create_mock_dict();
		printf("Criado dicionario mock. Chamando free_dict...\n");
		free_dict(dict);
		printf("Memoria liberada (verificar com valuegrind/leaks se possivel).\n");
	}
	else
	{
		printf("Comando desconhecido: %s\n", argv[1]);
	}

	return (0);
}
