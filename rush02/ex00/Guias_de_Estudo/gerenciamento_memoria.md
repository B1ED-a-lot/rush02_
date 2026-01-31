# 🧠 Gerenciamento de Memória no Rush 02

## Por que isso é importante?

Na avaliação do Rush, o avaliador **VAI** verificar se há memory leaks usando ferramentas como `valgrind` ou `leaks`. Se houver vazamento de memória, você **perde pontos**!

---

## 1. Conceitos Básicos

### O que é a Heap?

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        MEMÓRIA DO PROGRAMA                              │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────┐                                                   │
│  │      STACK      │  ← Variáveis locais (int x, char c, etc.)         │
│  │  (pilha)        │    Liberadas automaticamente quando função sai    │
│  └─────────────────┘                                                   │
│                                                                         │
│  ┌─────────────────┐                                                   │
│  │      HEAP       │  ← Memória alocada com malloc()                   │
│  │  (monte)        │    NÃO é liberada automaticamente!                │
│  │                 │    Você DEVE chamar free()!                        │
│  └─────────────────┘                                                   │
│                                                                         │
│  ┌─────────────────┐                                                   │
│  │      DATA       │  ← Variáveis globais, strings literais            │
│  └─────────────────┘                                                   │
│                                                                         │
│  ┌─────────────────┐                                                   │
│  │      CODE       │  ← O código do programa em si                     │
│  └─────────────────┘                                                   │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

### A Regra de Ouro

```
╔═══════════════════════════════════════════════════════════════════════╗
║                                                                       ║
║   🎯 CADA malloc() DEVE TER UM free() CORRESPONDENTE                  ║
║                                                                       ║
║   malloc() → aloca memória                                            ║
║   free()   → libera memória                                           ║
║                                                                       ║
║   Se você não fizer free(), a memória fica "presa" até o programa     ║
║   terminar. Isso é um MEMORY LEAK (vazamento de memória).             ║
║                                                                       ║
╚═══════════════════════════════════════════════════════════════════════╝
```

---

## 2. Funções que Alocam Memória no Rush 02

### Tabela de Rastreamento

```
┌─────────────────────────────────────────────────────────────────────────┐
│ FUNÇÃO               │ O QUE ALOCA              │ QUEM LIBERA           │
├─────────────────────────────────────────────────────────────────────────┤
│ read_file()          │ Conteúdo do arquivo      │ parse_dict()          │
│ ft_strdup()          │ Cópia de string          │ Varia (ver abaixo)    │
│ ft_strtrim_spaces()  │ String trimada           │ parse_line() ou       │
│                      │                          │ caller                │
│ parse_line()         │ t_dict node              │ free_dict()           │
│ parse_line()         │ node->key                │ free_dict()           │
│ parse_line()         │ node->value              │ free_dict()           │
│ ft_strjoin()         │ String concatenada       │ Caller (quem chamou)  │
│ ft_substr()          │ Substring                │ Caller                │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 3. Anatomia do free_dict()

Esta é a função mais importante para evitar leaks!

```c
void free_dict(t_dict *dict)
{
    t_dict *next;
    
    while (dict != NULL)
    {
        next = dict->next;   // 1. Guarda próximo ANTES de liberar!
        free(dict->key);     // 2. Libera a key
        free(dict->value);   // 3. Libera o value
        free(dict);          // 4. Libera o nó em si
        dict = next;         // 5. Avança para o próximo
    }
}
```

### Visualização

```
ANTES do free_dict():

    head → [key1|value1|next:─┐]    [key2|value2|next:─┐]    [key3|value3|next:NULL]
           ↑                  │     ↑                  │     ↑
           malloc'd           └────>malloc'd           └────>malloc'd


DURANTE o free_dict() (iteração 1):

    dict → [key1|value1|next:─┐]    [key2|value2|next:─┐]    [key3|value3|next:NULL]
                              │     ↑
    next ─────────────────────┼────>│
                              │
    1. next = dict->next      │
    2. free(dict->key)        │
    3. free(dict->value)      │
    4. free(dict)  ───────────┘
    5. dict = next


DEPOIS do free_dict():

    Toda memória liberada! ✅
```

---

## 4. Padrões Comuns de Memory Leak

### Leak 1: Esquecer de liberar antes de retornar erro

```c
// ❌ ERRADO - Leak se malloc2 falhar!
char *funcao(void)
{
    char *str1;
    char *str2;
    
    str1 = malloc(10);
    if (!str1)
        return (NULL);
    
    str2 = malloc(20);
    if (!str2)
        return (NULL);  // LEAK! str1 não foi liberado!
    
    // ...
}

// ✅ CORRETO
char *funcao(void)
{
    char *str1;
    char *str2;
    
    str1 = malloc(10);
    if (!str1)
        return (NULL);
    
    str2 = malloc(20);
    if (!str2)
    {
        free(str1);      // Libera str1 antes de sair!
        return (NULL);
    }
    
    // ...
}
```

### Leak 2: Perder a referência

```c
// ❌ ERRADO - Perdeu a referência para a memória original!
char *str;

str = ft_strdup("hello");
str = ft_strdup("world");  // LEAK! O "hello" está perdido!

// ✅ CORRETO
char *str;
char *temp;

str = ft_strdup("hello");
temp = str;                // Guarda referência
str = ft_strdup("world");
free(temp);                // Libera o antigo
```

### Leak 3: Esquecer de liberar em funções intermediárias

```c
// ❌ ERRADO - ft_strjoin aloca, mas nunca liberamos!
char *read_file(char *filename)
{
    char *content;
    char buffer[100];
    
    content = ft_strdup("");
    while (read(...))
    {
        content = ft_strjoin(content, buffer);  // LEAK a cada iteração!
    }
    return (content);
}

// ✅ CORRETO
char *read_file(char *filename)
{
    char *content;
    char *temp;
    char buffer[100];
    
    content = ft_strdup("");
    while (read(...))
    {
        temp = content;                         // Guarda o antigo
        content = ft_strjoin(content, buffer);
        free(temp);                             // Libera o antigo
    }
    return (content);
}
```

---

## 5. Checklist de Memória do Rush 02

Use este checklist antes de entregar!

### No main.c:
```
[ ] Se parse_dict() falhar após alocar memória, libero tudo?
[ ] Se convert_number() falhar, chamo free_dict()?
[ ] No final, SEMPRE chamo free_dict()?
```

### No ft_dict_parsing.c:
```
[ ] read_file(): retorno é liberado após parse_dict usar?
[ ] parse_line(): se malloc do node falhar, libero key e value já alocados?
[ ] parse_dict(): se uma linha falhar, continuo sem leak?
```

### No ft_dict_utils.c:
```
[ ] ft_strtrim_spaces(): o caller sabe que precisa liberar?
[ ] free_dict(): libero key, value E o node?
```

### No ft_number_converter.c:
```
[ ] Se alocar memória temporária, libero antes de retornar?
[ ] Não guardo ponteiros para dentro do dict (esses não devem ser liberados!)
```

### No ft_utils.c:
```
[ ] ft_strdup(): caller sabe que precisa liberar?
```

---

## 6. Testando Memory Leaks

### No Linux (com valgrind):

```bash
# Compilar com -g para debug info
cc -Wall -Wextra -Werror -g -o rush-02 srcs/*.c -I includes

# Rodar com valgrind
valgrind --leak-check=full ./rush-02 42

# Saída esperada (sem leaks):
# ==12345== All heap blocks were freed -- no leaks are possible
```

### No macOS (com leaks):

```bash
# Rodar com leaks
leaks -atExit -- ./rush-02 42

# Ou durante execução
./rush-02 42 &
leaks rush-02
```

### Interpretando a saída do valgrind:

```
# BOM ✅
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 50 allocs, 50 frees, 10,000 bytes allocated
==12345== 
==12345== All heap blocks were freed -- no leaks are possible

# RUIM ❌
==12345== HEAP SUMMARY:
==12345==     in use at exit: 1,024 bytes in 10 blocks  ← LEAK!
==12345==   total heap usage: 50 allocs, 40 frees       ← 10 frees faltando!
==12345== 
==12345== LEAK SUMMARY:
==12345==    definitely lost: 1,024 bytes in 10 blocks  ← Memória perdida!
```

---

## 7. Diagrama de Fluxo de Memória

```
                                      PROGRAMA INICIA
                                            │
                                            ▼
                              ┌─────────────────────────────┐
                              │    parse_dict(filename)     │
                              │                             │
                              │  ┌───────────────────────┐  │
                              │  │ read_file() → malloc  │  │
                              │  └───────────┬───────────┘  │
                              │              │              │
                              │  ┌───────────▼───────────┐  │
                              │  │ parse_line() (loop)   │  │
                              │  │ → malloc node         │  │
                              │  │ → malloc key          │  │
                              │  │ → malloc value        │  │
                              │  └───────────┬───────────┘  │
                              │              │              │
                              │  ┌───────────▼───────────┐  │
                              │  │ free(content)         │  │ ← Libera read_file
                              │  └───────────────────────┘  │
                              └─────────────┬───────────────┘
                                            │
                                            │ Retorna dict (lista ligada)
                                            ▼
                              ┌─────────────────────────────┐
                              │    convert_number(dict)     │
                              │                             │
                              │  (Não aloca, só usa dict)   │
                              └─────────────┬───────────────┘
                                            │
                                            ▼
                              ┌─────────────────────────────┐
                              │       free_dict(dict)       │
                              │                             │
                              │  ┌───────────────────────┐  │
                              │  │ Para cada node:       │  │
                              │  │   free(node->key)     │  │
                              │  │   free(node->value)   │  │
                              │  │   free(node)          │  │
                              │  └───────────────────────┘  │
                              └─────────────────────────────┘
                                            │
                                            ▼
                                    PROGRAMA TERMINA
                                    (0 bytes em uso ✅)
```

---

## 8. Dicas Finais

1. **Sempre inicialize ponteiros com NULL**
   ```c
   char *str = NULL;  // Se não usar, free(NULL) é seguro!
   ```

2. **Depois de free, coloque NULL**
   ```c
   free(ptr);
   ptr = NULL;  // Evita "double free" e "use after free"
   ```

3. **Teste cada função isoladamente**
   ```c
   // Teste read_file sozinho
   char *content = read_file("dict.txt");
   // ... verifica se está correto ...
   free(content);
   // Roda valgrind aqui antes de continuar!
   ```

4. **Use um padrão consistente**
   - Quem aloca documenta quem libera
   - Funções que alocam têm "WARNING: malloc" nos comentários

---

**Lembre-se: Um programa sem leaks é um programa profissional! 🎯**

*"Cada byte alocado é uma responsabilidade assumida."*
