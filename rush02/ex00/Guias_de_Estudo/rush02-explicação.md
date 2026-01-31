# 🎯 RUSH 02 - Explicação Completa para o Grupo

## Primeiro: O que é o problema?

Vocês precisam transformar um número em texto. Parece simples, mas tem várias camadas:

```
Entrada: ./rush-02 42
Saída:   forty two

Entrada: ./rush-02 1234
Saída:   one thousand two hundred thirty four
```

O programa lê um **dicionário** (arquivo de texto) que contém as "traduções":
```
0: zero
1: one
...
20: twenty
30: thirty
...
100: hundred
1000: thousand
```

E usa essas peças para montar qualquer número.

---

## As 6 Funções Permitidas

Vocês só podem usar: `write`, `malloc`, `free`, `open`, `read`, `close`

Vou explicar cada uma:

### 1. `write` (vocês já conhecem!)

```c
write(1, "hello", 5);  // Escreve "hello" no terminal
```

- `1` = saída padrão (terminal)
- `"hello"` = o que escrever
- `5` = quantos bytes

### 2. `open` - Abrir arquivo

Imagina que o arquivo é uma caixa trancada. `open` te dá a chave (um número).

```c
int fd;

fd = open("arquivo.txt", O_RDONLY);
// fd agora é um número (3, 4, 5...)
// Se der erro, fd = -1
```

**Por que um número?** O sistema operacional gerencia vários arquivos abertos. Ele te dá um "ticket" (file descriptor) para identificar qual arquivo você quer usar.

### 3. `read` - Ler arquivo

Com o ticket em mãos, você pede para ler:

```c
char buffer[100];
int  quantos_leu;

quantos_leu = read(fd, buffer, 99);
// Lê ATÉ 99 bytes do arquivo para o buffer
// Retorna quantos bytes REALMENTE leu
// Retorna 0 se chegou no fim
// Retorna -1 se deu erro
```

**Pegadinha importante:** `read` NÃO coloca `\0` no final! Você precisa fazer:
```c
buffer[quantos_leu] = '\0';
```

### 4. `close` - Fechar arquivo

Devolveu o ticket:
```c
close(fd);
```

Sempre feche o que abriu!

### 5. `malloc` - Pedir memória emprestada

Aqui é onde a coisa fica interessante. Até agora vocês usaram variáveis assim:

```c
char str[100];  // 100 bytes na STACK (pilha)
```

O problema: você precisa saber o tamanho ANTES de compilar. E se você não souber?

**malloc** pede memória da **HEAP** (monte):

```c
char *str;

str = malloc(100);  // Pede 100 bytes emprestados
if (str == NULL)    // SEMPRE verifique!
    return (NULL);  // Sem memória disponível

// Agora str aponta para 100 bytes que são SEUS
str[0] = 'H';
str[1] = 'i';
str[2] = '\0';
```

**A diferença crucial:**

| STACK (pilha) | HEAP (monte) |
|---------------|--------------|
| `char str[100];` | `char *str = malloc(100);` |
| Tamanho fixo em tempo de compilação | Tamanho decidido em tempo de execução |
| Liberado automaticamente quando a função termina | Você DEVE liberar manualmente |
| Rápido | Um pouco mais lento |

### 6. `free` - Devolver memória emprestada

Se `malloc` é pedir emprestado, `free` é devolver:

```c
char *str = malloc(100);
// ... usa str ...
free(str);  // Devolve os 100 bytes
str = NULL; // Boa prática: anula o ponteiro
```

**A regra de ouro:**
> Cada `malloc` precisa de um `free` correspondente. Sem exceção.

Se você não devolver (esquecer o `free`), é **memory leak** - vazamento de memória. O avaliador VAI verificar isso.

---

## A Arquitetura do Projeto

Agora que vocês entendem as ferramentas, vou explicar POR QUE organizamos assim:

### Por que uma struct `t_dict`?

O dicionário tem linhas assim:
```
42: forty two
100: hundred
```

Precisamos guardar isso em algum lugar. Uma struct organiza:

```c
typedef struct s_dict
{
    char            *key;    // "42"
    char            *value;  // "forty two"
    struct s_dict   *next;   // Próxima entrada
}   t_dict;
```

### Por que lista ligada?

Não sabemos quantas linhas o dicionário tem. Poderia ser 10, 50, 100...

Com **array**, precisaríamos saber o tamanho antes. Com **lista ligada**, adicionamos conforme lemos:

```
head → [0|zero|→] → [1|one|→] → [42|forty two|→] → NULL
```

Cada "caixa" aponta para a próxima. A última aponta para NULL (fim).

### Por que key é `char*` e não `int`?

Essa decisão é **crítica**. O subject diz:

> "Seu programa deve lidar com números além do intervalo de um unsigned int."

`unsigned int` vai até ~4 bilhões. Mas o dicionário tem:

```
1000000000000: trillion           (1 trilhão)
1000000000000000: quadrillion
...até undecillion (10^36)!
```

Nenhum tipo inteiro do C guarda isso. Então tratamos o número como **string** e comparamos caractere por caractere.

---

## O Fluxo do Programa (Passo a Passo)

```
1. VALIDAR ARGUMENTOS
   └─ argc == 2 ou 3?
   └─ Número só tem dígitos?

2. CARREGAR DICIONÁRIO
   └─ Abrir arquivo (open)
   └─ Ler conteúdo (read)
   └─ Para cada linha:
      └─ Separar key e value pelo ':'
      └─ Remover espaços (trim)
      └─ Adicionar na lista ligada

3. CONVERTER NÚMERO
   └─ Decompor em partes (milhões, milhares, centenas...)
   └─ Buscar cada parte no dicionário
   └─ Imprimir com espaços entre

4. LIBERAR MEMÓRIA
   └─ free() de tudo que foi malloc()
```

---

## A Lógica de Decomposição (O Coração do Projeto)

Esta é a parte mais desafiadora. Vou explicar com um exemplo:

### Convertendo 1234

```
1234 tem 4 dígitos → é da casa dos MILHARES

Passo 1: Quantos milhares?
  1234 / 1000 = 1
  Busca "1" no dict → "one"
  Busca "1000" no dict → "thousand"
  Imprime: "one thousand"

Passo 2: Qual o resto?
  1234 % 1000 = 234
  Agora converte 234...

234 tem 3 dígitos → é da casa das CENTENAS

Passo 3: Quantas centenas?
  234 / 100 = 2
  Busca "2" → "two"
  Busca "100" → "hundred"
  Imprime: " two hundred"

Passo 4: Qual o resto?
  234 % 100 = 34
  Agora converte 34...

34 tem 2 dígitos → é DEZENA

Passo 5: 34 está no dict?
  Não! Então decompõe:
  34 / 10 = 3 → "30" → "thirty"
  34 % 10 = 4 → "4" → "four"
  Imprime: " thirty four"

RESULTADO: "one thousand two hundred thirty four"
```

### A tabela de grandezas

| Dígitos | Grandeza | Divisor | Chave no dict |
|---------|----------|---------|---------------|
| 1 | unidade | 1 | o próprio número |
| 2 | dezena | 10 | "20", "30"... ou decomposição |
| 3 | centena | 100 | "100" |
| 4-6 | milhar | 1000 | "1000" |
| 7-9 | milhão | 1000000 | "1000000" |
| 10-12 | bilhão | 1000000000 | "1000000000" |

### Mas espera... números são strings!

Como fazemos divisão com strings? Não fazemos! Usamos o **comprimento** da string:

```c
char *num = "1234567";
int len = 7;  // 7 dígitos = milhões

// Milhões: pega os primeiros (7 - 6) = 1 dígito
// parte = "1"
// resto = "234567"
```

É como "fatiar" a string em vez de fazer conta matemática.

---

## Ordem de Implementação (Cronograma Prático)

### Dia 1 - Sábado

**Manhã (todos juntos):**
1. Leiam o subject juntos
2. Implementem `ft_utils.c` juntos:
   - `ft_putchar`, `ft_putstr` (vocês já sabem!)
   - `ft_strlen`, `ft_strcmp` (também já sabem!)
   - `ft_strdup` (primeiro contato com malloc)

**Teste o ft_strdup:**
```c
// Em um main temporário de teste:
char *copia = ft_strdup("hello");
ft_putstr(copia);
free(copia);
```

**Tarde:**
1. **Pessoa 1**: Começa `read_file()` - ler arquivo inteiro
2. **Pessoa 2**: Começa `is_valid_number()` - validar entrada
3. **Pessoa 3**: Começa `main.c` - estrutura básica

**Noite:**
1. Integrem o que fizeram
2. Testem: conseguem ler o dicionário e mostrar no terminal?

### Dia 2 - Domingo

**Manhã:**
1. Terminem `parse_line()` - separar key:value
2. Terminem `parse_dict()` - montar a lista
3. Implementem `dict_search()` - buscar uma chave

**Teste:**
```c
// Após carregar o dict:
char *value = dict_search(dict, "42");
ft_putstr(value);  // Deve imprimir "forty two"
```

**Tarde:**
1. Implementem `convert_number()` para casos simples (0-99)
2. Depois expandam para centenas (100-999)
3. Depois milhares (1000+)

**Noite:**
1. Testes extensivos
2. Verifiquem memory leaks
3. **TODOS revisam TODO o código**

---

## Memory Management - O Mapa das Alocações

Este é o ponto onde a maioria reprova. Criei um mapa:

```
┌─────────────────────────────────────────────────────────────────┐
│ QUEM ALOCA                     │ QUEM LIBERA                    │
├─────────────────────────────────────────────────────────────────┤
│ read_file() → conteúdo         │ parse_dict() libera após usar  │
│ ft_strdup() → string           │ quem chamou, ou free_dict()    │
│ parse_line() → nó t_dict       │ free_dict()                    │
│ parse_line() → node->key       │ free_dict()                    │
│ parse_line() → node->value     │ free_dict()                    │
│ ft_strtrim_spaces() → string   │ quem chamou                    │
└─────────────────────────────────────────────────────────────────┘
```

A função `free_dict()` é crucial:

```c
void free_dict(t_dict *dict)
{
    t_dict *next;

    while (dict != NULL)
    {
        next = dict->next;  // Guarda o próximo ANTES de liberar!
        free(dict->key);
        free(dict->value);
        free(dict);
        dict = next;
    }
}
```

**Por que guardar `next` antes?** Porque depois do `free(dict)`, a memória de `dict` é inválida. Se tentasse acessar `dict->next` depois, seria erro.

---

## Erros Comuns a Evitar

### 1. Não verificar retorno de malloc
```c
// ERRADO
char *str = malloc(100);
str[0] = 'a';  // Se malloc falhou, CRASH!

// CORRETO
char *str = malloc(100);
if (!str)
    return (NULL);
str[0] = 'a';
```

### 2. Esquecer o '\0' em strings
```c
// ERRADO
char *str = malloc(5);
// Para "hello" (5 letras)... mas e o '\0'?

// CORRETO
char *str = malloc(6);  // 5 + 1 para o '\0'
```

### 3. Perder a referência
```c
// ERRADO - memory leak!
char *str = ft_strdup("hello");
str = ft_strdup("world");  // "hello" está perdido para sempre!

// CORRETO
char *str = ft_strdup("hello");
char *temp = str;
str = ft_strdup("world");
free(temp);
```

### 4. read() sem '\0'
```c
// ERRADO
char buffer[100];
read(fd, buffer, 99);
ft_putstr(buffer);  // buffer pode ter lixo!

// CORRETO
char buffer[100];
int bytes = read(fd, buffer, 99);
buffer[bytes] = '\0';  // Agora é uma string válida
ft_putstr(buffer);
```

---

## Como Explicar na Avaliação

O avaliador vai perguntar coisas como:

**"Por que usaram lista ligada?"**
> "Porque não sabemos quantas entradas o dicionário tem antes de ler. Com lista ligada, adicionamos conforme lemos, sem precisar de tamanho fixo."

**"Como funciona a decomposição?"**
> "Identificamos a grandeza pelo número de dígitos. Se tem 4 dígitos, é milhares. Separamos a parte dos milhares, imprimimos, e processamos o resto recursivamente."

**"Como garantem que não tem memory leak?"**
> "Temos um mapa de quem aloca e quem libera. A função `free_dict()` percorre toda a lista liberando cada nó, sua key e seu value. Testamos com valgrind."

**"Por que a key é string e não int?"**
> "O subject exige números maiores que unsigned int. O dicionário tem até undecillion (10^36), que não cabe em nenhum tipo inteiro do C. Tratando como string, comparamos caractere por caractere."

---

## Última Dica

Não tentem fazer tudo de uma vez. Construam em camadas:

1. Primeiro: funções que vocês já conhecem (`ft_strlen`, `ft_putstr`)
2. Depois: funções com malloc simples (`ft_strdup`)
3. Depois: leitura de arquivo
4. Depois: parsing
5. Por último: conversão

Testem CADA camada antes de ir para a próxima. Se a base estiver sólida, o resto fica mais fácil.

**Vocês conseguem! 🚀**

# Continuação 

Excelentes perguntas! São exatamente essas dúvidas que mostram que você está pensando como programador. Vou responder cada uma com calma.

---

## 1. Por que `buffer[100]` mas `read(fd, buffer, 99)`?

```c
char buffer[100];
int bytes = read(fd, buffer, 99);
buffer[bytes] = '\0';
```

O buffer tem 100 posições: índices 0 a 99.

Quando pedimos para `read` ler **99 bytes**, estamos reservando a **posição 99** (a centésima e última) para colocar o `\0` manualmente depois.

```
Índices:  [0] [1] [2] ... [97] [98] [99]
           h   e   l        l    o   \0
           └─────── read leu ──────┘  └── nós colocamos
```

**E se alocássemos 101?**

```c
char buffer[101];
read(fd, buffer, 100);
buffer[100] = '\0';
```

Funcionaria perfeitamente! Teríamos:
- 100 posições para dados (índices 0-99)
- 1 posição para o `\0` (índice 100)

**A regra é:** sempre reserve espaço para o `\0` se quiser tratar como string.

Se você fizer `buffer[100]` e `read(fd, buffer, 100)`, não sobra espaço para o `\0`. Você teria que:
- Ou não tratar como string (só como bytes brutos)
- Ou arriscar escrever fora do array (BUG!)

---

## 2. Por que `malloc` aloca na HEAP e `char str[100]` vai para STACK?

Essa é uma pergunta sobre como o computador organiza a memória. Vou usar uma analogia:

### A Memória é como um Prédio

```
┌─────────────────────────────────────────────────┐
│                    TOPO                         │
│  ┌───────────────────────────────────────────┐  │
│  │              STACK (Pilha)                │  │  ← Cresce para BAIXO ↓
│  │  - Variáveis locais                       │  │
│  │  - Parâmetros de função                   │  │
│  │  - Endereços de retorno                   │  │
│  │  - Automático: entra e sai sozinho        │  │
│  └───────────────────────────────────────────┘  │
│                      │                          │
│                      ↓ (cresce)                 │
│                      .                          │
│                      .                          │
│                      ↑ (cresce)                 │
│                      │                          │
│  ┌───────────────────────────────────────────┐  │
│  │              HEAP (Monte)                 │  │  ← Cresce para CIMA ↑
│  │  - Memória alocada com malloc             │  │
│  │  - Você controla: malloc/free             │  │
│  │  - Persiste até você liberar              │  │
│  └───────────────────────────────────────────┘  │
│                                                 │
│  ┌───────────────────────────────────────────┐  │
│  │         DATA (Dados globais)              │  │
│  │  - Variáveis globais                      │  │
│  │  - Strings literais ("hello")             │  │
│  └───────────────────────────────────────────┘  │
│                                                 │
│  ┌───────────────────────────────────────────┐  │
│  │         CODE (Código)                     │  │
│  │  - Suas funções compiladas                │  │
│  └───────────────────────────────────────────┘  │
│                    BASE                         │
└─────────────────────────────────────────────────┘
```

### STACK - A Pilha de Pratos

Imagina uma pilha de pratos na pia. Você coloca um prato em cima (push), tira o de cima (pop).

Quando você chama uma função:
```c
void foo(void)
{
    char str[100];  // ← Colocado na pilha
    int x;          // ← Colocado na pilha
    // ...
}                   // ← Função termina, TUDO é removido automaticamente
```

O sistema **automaticamente** reserva espaço quando a função começa e **automaticamente** libera quando termina.

**Vantagens:**
- Muito rápido (só move um ponteiro)
- Sem risco de memory leak
- Não precisa se preocupar

**Desvantagens:**
- Tamanho deve ser conhecido em tempo de compilação
- Espaço limitado (geralmente 1-8 MB)
- Morre quando a função termina

### HEAP - O Depósito

A heap é como um depósito onde você aluga espaço. Você pede (malloc) e devolve (free).

```c
void foo(void)
{
    char *str = malloc(100);  // Pede 100 bytes do depósito
    // ...
    free(str);                 // Devolve ao depósito
}
```

**Por que existe?**

1. **Tamanho dinâmico:** Você não sabe quantos bytes precisa até rodar o programa
2. **Sobrevive à função:** A memória continua existindo mesmo depois que a função termina
3. **Tamanho grande:** A heap é muito maior que a stack

**No Rush 02:** Não sabemos o tamanho do dicionário antes de ler. Pode ter 10 linhas ou 1000. Por isso usamos malloc.

### Por que o C funciona assim?

É uma decisão de design da linguagem. A stack é gerenciada pelo **processador** (hardware), é extremamente eficiente. A heap é gerenciada pelo **sistema operacional**, mais flexível mas mais lenta.

Quando você escreve `char str[100]`, o compilador sabe exatamente quanto espaço reservar e coloca na stack. Quando você escreve `malloc(n)`, `n` pode ser qualquer valor - só sabemos em tempo de execução, então vai para a heap.

---

## 3. Poderia fazer o projeto SEM malloc, free e struct?

**Tecnicamente sim, mas seria muito difícil e limitado.**

### Sem malloc/free:

Você precisaria de arrays estáticos com tamanho fixo:

```c
// Em vez de lista ligada dinâmica:
char keys[1000][50];      // 1000 chaves, cada uma até 50 chars
char values[1000][100];   // 1000 valores, cada um até 100 chars
int count;                // Quantas entradas existem
```

**Problemas:**
- E se o dicionário tiver 1001 linhas? Falha.
- E se uma chave tiver 51 caracteres? Falha.
- Desperdiça memória: reserva 1000 mesmo se usar 40.
- Tamanho da stack é limitado! 1000 * 150 = 150KB só nisso.

### Sem struct:

```c
// Em vez de:
t_dict node;
node.key = "42";
node.value = "forty two";

// Precisaria de arrays paralelos:
char keys[1000][50];
char values[1000][100];
// keys[0] corresponde a values[0], etc.
```

**Problemas:**
- Menos organizado
- Mais fácil de cometer erros
- Impossível fazer lista ligada (que precisa de ponteiro para próximo)

### Resumo dos prós e contras

| Abordagem | Prós | Contras |
|-----------|------|---------|
| **Com malloc/struct** | Flexível, usa só a memória necessária, lista ligada possível | Precisa gerenciar memória, mais complexo |
| **Sem malloc/struct** | Mais simples, sem memory leaks | Limites fixos, desperdício de memória, pode estourar stack |

**Para o Rush 02**, a abordagem com malloc é praticamente obrigatória porque:
1. Não sabemos o tamanho do arquivo
2. Não sabemos o tamanho de cada linha
3. Lista ligada é a forma natural de representar o dicionário

---

## 4. Lista Ligada vs Array

### Array

```
┌─────┬─────┬─────┬─────┬─────┐
│  0  │  1  │  2  │  3  │  4  │
└─────┴─────┴─────┴─────┴─────┘
   ↑
Memória CONTÍGUA (uma do lado da outra)
Acesso direto: arr[3] → vai direto no índice 3
```

**Características:**
- Tamanho fixo (em C puro)
- Acesso O(1): `arr[500]` é instantâneo
- Inserir no meio é caro: precisa mover tudo
- Memória contígua

### Lista Ligada

```
┌───────────┐     ┌───────────┐     ┌───────────┐
│ dado | ●──┼────>│ dado | ●──┼────>│ dado | NULL│
└───────────┘     └───────────┘     └───────────┘
    Nó 1              Nó 2              Nó 3

Memória ESPALHADA (cada nó pode estar em qualquer lugar)
Acesso sequencial: para chegar no 3º, passa pelo 1º e 2º
```

**Características:**
- Tamanho dinâmico
- Acesso O(n): para achar o elemento 500, percorre 500 nós
- Inserir/remover é barato: só muda ponteiros
- Memória não-contígua

### Quando usar cada um?

| Situação | Melhor escolha |
|----------|---------------|
| Tamanho conhecido, acesso por índice | Array |
| Tamanho desconhecido, inserções frequentes | Lista ligada |
| Busca frequente por posição | Array |
| Leitura sequencial | Ambos servem |

**No Rush 02:** Lemos o dicionário linha por linha e depois buscamos sequencialmente. Lista ligada é ideal porque:
- Não sabemos quantas linhas
- Adicionamos uma por uma conforme lemos
- Buscamos percorrendo do início

---

## 5. É necessário usar TODAS as funções permitidas?

**Sim, todas são necessárias para este projeto:**

| Função | Por que é necessária |
|--------|---------------------|
| `write` | Imprimir o resultado |
| `open` | Abrir o arquivo do dicionário |
| `read` | Ler o conteúdo do arquivo |
| `close` | Fechar o arquivo (boa prática + evita problemas) |
| `malloc` | Alocar memória para strings e nós da lista |
| `free` | Liberar memória (obrigatório, avaliador verifica!) |

Se você não usar `open/read/close`, não consegue ler o dicionário.
Se você não usar `malloc/free`, não consegue lidar com tamanhos dinâmicos.
Se você não usar `write`, não consegue mostrar o resultado.

---

## 6. E se usasse `unsigned long long` em vez de strings?

Boa pergunta! `unsigned long long` é 64 bits e vai até aproximadamente **18.4 quintilhões** (18,446,744,073,709,551,615).

### O que mudaria:

```c
// Em vez de:
typedef struct s_dict
{
    char            *key;    // "1000000000000"
    char            *value;
    struct s_dict   *next;
}   t_dict;

// Seria:
typedef struct s_dict
{
    unsigned long long  key;    // 1000000000000
    char                *value;
    struct s_dict       *next;
}   t_dict;
```

### Vantagens:

1. **Comparação mais rápida:** Comparar dois números é uma instrução. Comparar strings precisa de loop.
2. **Menos memória:** `unsigned long long` = 8 bytes fixos. String "1000000000000" = 14 bytes.
3. **Parsing mais simples:** Não precisa implementar comparação de strings numéricas.

### Desvantagens (e por que NÃO usamos):

1. **Limite:** O dicionário do Rush 02 tem:
   ```
   1000000000000000000000: sextillion     (10^21)
   1000000000000000000000000: septillion  (10^24)
   ...até...
   1000000000000000000000000000000000000: undecillion (10^36)
   ```
   
   `unsigned long long` vai até ~1.8 × 10^19. **Não cabe!**

2. **O subject diz explicitamente:**
   > "Seu programa deve lidar com números além do intervalo de um unsigned int."
   
   E o dicionário fornecido vai até 10^36. A intenção é que vocês tratem como string.

3. **Conversão de string para número:** Você precisaria implementar `ft_atoull` (atoi para unsigned long long), e ainda assim não funcionaria para números grandes.

### Como funcionaria a comparação com strings:

```c
// Com unsigned long long:
if (node->key == 42)
    return (node->value);

// Com strings:
if (ft_strcmp(node->key, "42") == 0)
    return (node->value);
```

A versão com strings é mais lenta, mas é a única que funciona para todos os casos.

### Curiosidade: como comparar strings numéricas corretamente?

Se você comparar "9" e "10" com `strcmp`, "9" vem DEPOIS de "10" (porque '9' > '1' no ASCII).

Para comparar numericamente:
1. Compare o comprimento primeiro (mais dígitos = maior)
2. Se mesmo comprimento, compare caractere por caractere

```c
// "9" vs "10"
// strlen("9") = 1, strlen("10") = 2
// 1 < 2, então "9" < "10" ✓

// "42" vs "43"
// strlen iguais, compara char por char
// '4' == '4', '2' < '3', então "42" < "43" ✓
```

No Rush 02, você só precisa de **igualdade** (buscar chave exata), então `ft_strcmp` normal funciona.

---

## Resumindo

| Pergunta | Resposta curta |
|----------|----------------|
| Buffer 100, read 99? | Reservar espaço para o `\0` |
| Por que heap vs stack? | Stack é automática/fixa, heap é manual/dinâmica |
| Sem malloc/struct? | Possível mas muito limitado e difícil |
| Lista vs array? | Lista é dinâmica, array é fixo/rápido |
| Precisa de todas as funções? | Sim, cada uma tem papel essencial |
| E se fosse unsigned long long? | Não funcionaria, números do dict são maiores |

Quer que eu aprofunde mais algum ponto?