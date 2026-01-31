# 📚 Guia das Funções Novas

## Introdução

No Rush 02, vocês vão usar funções que talvez nunca usaram antes:
- `malloc` - Alocar memória
- `free` - Liberar memória
- `open` - Abrir arquivo
- `read` - Ler arquivo
- `close` - Fechar arquivo

Este guia explica cada uma com exemplos práticos!

---

## 1. malloc() - Alocação de Memória

### O que faz?
Reserva um bloco de memória do tamanho que você pedir.

### Sintaxe
```c
void *malloc(size_t size);
```

### Parâmetros
- `size`: Quantos bytes você quer (use `sizeof` para calcular!)

### Retorno
- Sucesso: Ponteiro para a memória alocada
- Erro: `NULL` (sem memória disponível)

### Exemplos

```c
// Exemplo 1: Alocar espaço para uma string
char *str;

str = malloc(6);  // 5 caracteres + '\0'
if (str == NULL)  // SEMPRE verifique!
    return (NULL);

str[0] = 'h';
str[1] = 'e';
str[2] = 'l';
str[3] = 'l';
str[4] = 'o';
str[5] = '\0';

// Agora str contém "hello"
// NÃO ESQUEÇA: free(str) quando terminar!
```

```c
// Exemplo 2: Alocar espaço para uma struct
t_dict *node;

node = malloc(sizeof(t_dict));  // sizeof calcula o tamanho!
if (node == NULL)
    return (NULL);

node->key = NULL;
node->value = NULL;
node->next = NULL;

// NÃO ESQUEÇA: free(node) quando terminar!
```

```c
// Exemplo 3: Alocar array de inteiros
int *numeros;
int i;

numeros = malloc(10 * sizeof(int));  // 10 inteiros
if (numeros == NULL)
    return (NULL);

i = 0;
while (i < 10)
{
    numeros[i] = i * 2;
    i++;
}
// numeros = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}

// NÃO ESQUEÇA: free(numeros) quando terminar!
```

### ⚠️ Erros Comuns

```c
// ERRADO: Não verificar retorno
char *str = malloc(100);
str[0] = 'a';  // Se malloc falhou, CRASH!

// CORRETO: Sempre verificar
char *str = malloc(100);
if (!str)
    return (NULL);
str[0] = 'a';
```

```c
// ERRADO: Esquecer o '\0'
char *str = malloc(5);  // Para "hello"
// "hello" tem 5 caracteres + '\0' = 6 bytes!

// CORRETO:
char *str = malloc(6);  // ou malloc(5 + 1)
```

---

## 2. free() - Liberação de Memória

### O que faz?
Devolve a memória que foi alocada com `malloc`.

### Sintaxe
```c
void free(void *ptr);
```

### Parâmetros
- `ptr`: Ponteiro retornado por `malloc`

### Retorno
- Nenhum (`void`)

### Exemplos

```c
// Exemplo básico
char *str;

str = malloc(10);
if (!str)
    return ;

// ... usa str ...

free(str);  // Libera a memória
str = NULL; // Boa prática: anula o ponteiro
```

```c
// Exemplo com struct
t_dict *node;

node = malloc(sizeof(t_dict));
node->key = malloc(10);
node->value = malloc(20);

// Para liberar, libere na ordem inversa ou de dentro pra fora:
free(node->key);
free(node->value);
free(node);
```

### ⚠️ Erros Comuns

```c
// ERRADO: Double free
char *str = malloc(10);
free(str);
free(str);  // ERRO! Já foi liberado!

// CORRETO:
char *str = malloc(10);
free(str);
str = NULL;  // Agora free(NULL) é seguro (não faz nada)
```

```c
// ERRADO: Use after free
char *str = malloc(10);
str[0] = 'a';
free(str);
printf("%c", str[0]);  // ERRO! Memória já liberada!

// CORRETO:
char *str = malloc(10);
str[0] = 'a';
printf("%c", str[0]);  // Usa ANTES de liberar
free(str);
```

```c
// ERRADO: Liberar memória não alocada com malloc
char str[] = "hello";
free(str);  // ERRO! str está na stack, não na heap!

char *str2 = "hello";
free(str2);  // ERRO! String literal está na seção DATA!
```

---

## 3. open() - Abrir Arquivo

### O que faz?
Abre um arquivo e retorna um "file descriptor" (número que identifica o arquivo).

### Sintaxe
```c
int open(const char *pathname, int flags);
```

### Parâmetros
- `pathname`: Caminho do arquivo (ex: "data/dict.txt")
- `flags`: Como abrir (O_RDONLY = apenas leitura)

### Retorno
- Sucesso: Número positivo (file descriptor)
- Erro: -1 (arquivo não existe, sem permissão, etc.)

### Exemplos

```c
#include <fcntl.h>  // Para O_RDONLY

// Exemplo básico
int fd;

fd = open("meu_arquivo.txt", O_RDONLY);
if (fd == -1)
{
    // Erro! Arquivo não existe ou sem permissão
    return (NULL);
}

// Agora fd é um número que identifica o arquivo
// Use read(fd, ...) para ler
// Use close(fd) quando terminar!
```

### Flags Comuns

```c
O_RDONLY    // Apenas leitura (o que usamos no Rush!)
O_WRONLY    // Apenas escrita
O_RDWR      // Leitura e escrita
O_CREAT     // Criar arquivo se não existir
O_TRUNC     // Truncar (apagar conteúdo) se existir
```

### File Descriptors Especiais

```c
0 = stdin   (entrada padrão - teclado)
1 = stdout  (saída padrão - terminal)
2 = stderr  (saída de erros)

// Arquivos que você abrir terão fd = 3, 4, 5, ...
```

---

## 4. read() - Ler Arquivo

### O que faz?
Lê bytes de um arquivo para um buffer (array).

### Sintaxe
```c
ssize_t read(int fd, void *buf, size_t count);
```

### Parâmetros
- `fd`: File descriptor (retornado por open)
- `buf`: Onde guardar os bytes lidos
- `count`: Quantos bytes ler (no máximo)

### Retorno
- Positivo: Quantos bytes foram lidos DE VERDADE
- Zero: Chegou no fim do arquivo (EOF)
- -1: Erro

### Exemplos

```c
// Exemplo 1: Ler arquivo inteiro em partes
int     fd;
char    buffer[1024];
int     bytes_read;

fd = open("arquivo.txt", O_RDONLY);
if (fd == -1)
    return (NULL);

// Loop de leitura
while (1)
{
    bytes_read = read(fd, buffer, 1023);  // Deixa espaço pro '\0'
    
    if (bytes_read == -1)  // Erro
    {
        close(fd);
        return (NULL);
    }
    
    if (bytes_read == 0)  // Fim do arquivo
        break;
    
    buffer[bytes_read] = '\0';  // Transforma em string
    
    // Processa buffer...
}

close(fd);
```

```c
// Exemplo 2: Ler byte por byte (LENTO, mas simples)
int     fd;
char    c;
int     bytes_read;

fd = open("arquivo.txt", O_RDONLY);

while ((bytes_read = read(fd, &c, 1)) > 0)
{
    // c contém o próximo caractere
    write(1, &c, 1);  // Imprime no terminal
}

close(fd);
```

### ⚠️ Importante sobre read()

```c
// read() NÃO adiciona '\0' automaticamente!
char buffer[100];
int bytes = read(fd, buffer, 99);

// ERRADO:
printf("%s", buffer);  // buffer pode não ter '\0'!

// CORRETO:
buffer[bytes] = '\0';  // Adicione manualmente!
printf("%s", buffer);
```

```c
// read() pode ler MENOS do que você pediu
int bytes = read(fd, buffer, 1000);
// bytes pode ser 500 se o arquivo tiver só 500 bytes!
```

---

## 5. close() - Fechar Arquivo

### O que faz?
Fecha um arquivo aberto, liberando o file descriptor.

### Sintaxe
```c
int close(int fd);
```

### Parâmetros
- `fd`: File descriptor a fechar

### Retorno
- Sucesso: 0
- Erro: -1

### Exemplo

```c
int fd;

fd = open("arquivo.txt", O_RDONLY);
if (fd == -1)
    return (NULL);

// ... usa o arquivo ...

close(fd);  // SEMPRE feche!
```

### ⚠️ Por que fechar é importante?

1. **Limite de file descriptors**: O sistema tem um limite de arquivos abertos
2. **Recursos do sistema**: Cada arquivo aberto usa recursos
3. **Flush de dados**: Em escrita, close garante que tudo foi salvo

---

## 6. Exemplo Completo: Lendo um Arquivo

```c
#include <fcntl.h>   // open, O_RDONLY
#include <unistd.h>  // read, close, write
#include <stdlib.h>  // malloc, free

#define BUFFER_SIZE 1024

/*
** Lê um arquivo inteiro e retorna como string.
** Retorna NULL em caso de erro.
** IMPORTANTE: O caller deve fazer free() do retorno!
*/
char *read_entire_file(char *filename)
{
    int     fd;
    char    buffer[BUFFER_SIZE + 1];
    char    *content;
    char    *temp;
    int     bytes_read;

    // 1. Abrir o arquivo
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (NULL);

    // 2. Começar com string vazia
    content = ft_strdup("");
    if (!content)
    {
        close(fd);
        return (NULL);
    }

    // 3. Ler em partes e concatenar
    while (1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        if (bytes_read == -1)  // Erro de leitura
        {
            free(content);
            close(fd);
            return (NULL);
        }
        
        if (bytes_read == 0)  // Fim do arquivo
            break;
        
        buffer[bytes_read] = '\0';  // Termina a string
        
        // Concatena (cuidado com leaks!)
        temp = content;
        content = ft_strjoin(content, buffer);
        free(temp);
        
        if (!content)
        {
            close(fd);
            return (NULL);
        }
    }

    // 4. Fechar e retornar
    close(fd);
    return (content);
}
```

---

## 7. Resumo Visual

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        FLUXO DE USO DE ARQUIVO                          │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│   ┌──────────┐        ┌──────────┐        ┌──────────┐                 │
│   │  open()  │───────>│  read()  │───────>│  close() │                 │
│   └──────────┘        └──────────┘        └──────────┘                 │
│        │                   │                    │                       │
│        │                   │                    │                       │
│   Retorna fd          Retorna bytes        Retorna 0                   │
│   ou -1 (erro)        lidos, 0 (EOF),      ou -1 (erro)                │
│                       ou -1 (erro)                                      │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────┐
│                        FLUXO DE USO DE MEMÓRIA                          │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│   ┌──────────┐        ┌──────────┐        ┌──────────┐                 │
│   │ malloc() │───────>│  usar    │───────>│  free()  │                 │
│   └──────────┘        └──────────┘        └──────────┘                 │
│        │                   │                    │                       │
│        │                   │                    │                       │
│   Retorna ptr         Lê/escreve           Libera ptr                  │
│   ou NULL (erro)      na memória           (sem retorno)               │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 8. Checklist de Uso

### Para malloc/free:
```
[ ] Verificou se malloc retornou NULL?
[ ] Usou sizeof() para calcular o tamanho?
[ ] Lembrou do +1 para strings (para o '\0')?
[ ] Fez free() de tudo que alocou?
[ ] Anulou o ponteiro depois do free?
```

### Para open/read/close:
```
[ ] Verificou se open retornou -1?
[ ] Está lendo em um buffer adequado?
[ ] Adicionou '\0' depois de read?
[ ] Tratou read retornando 0 (EOF)?
[ ] Fechou o arquivo com close?
```

---

**Pratique essas funções isoladamente antes de usar no Rush! 🎯**

*"Domine as ferramentas antes de construir a casa."*
