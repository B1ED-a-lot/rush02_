# 🛡️ GUIA DE SOBREVIVÊNCIA - RUSH 02

## 📋 CHECKLIST DE ERROS (Para não esquecer nada!)

### Erros que devem retornar "Error\n":

```
┌────────────────────────────────────────────────────────────────────────────┐
│                        CHECKLIST DE VALIDAÇÃO                              │
├────────────────────────────────────────────────────────────────────────────┤
│ [ ] argc != 2 e argc != 3 (espera 1 ou 2 argumentos)                       │
│ [ ] String vazia ""                                                        │
│ [ ] Número com letras "42a", "abc"                                         │
│ [ ] Número negativo "-42"                                                  │
│ [ ] Número com sinal "+" → "+42"                                           │
│ [ ] Número decimal "42.5"                                                  │
│ [ ] Número com espaços " 42", "4 2"                                        │
└────────────────────────────────────────────────────────────────────────────┘
```

### Erros que devem retornar "Dict Error\n":

```
┌────────────────────────────────────────────────────────────────────────────┐
│                     CHECKLIST DE ERROS DO DICIONÁRIO                       │
├────────────────────────────────────────────────────────────────────────────┤
│ [ ] Arquivo não existe ou não pode ser aberto                              │
│ [ ] Linha sem ':' no dicionário                                            │
│ [ ] Chave (key) vazia ou só espaços                                        │
│ [ ] Chave com caracteres não-numéricos                                     │
│ [ ] Falta uma chave necessária para a conversão                            │
│     (ex: converter 50 mas não tem "50" nem "5" + "0")                      │
└────────────────────────────────────────────────────────────────────────────┘
```

---

## 🧪 TESTES PARA FAZER ANTES DE ENTREGAR

### Testes Básicos:

```bash
# Números simples (0-19)
./rush-02 0          # Esperado: zero
./rush-02 1          # Esperado: one
./rush-02 10         # Esperado: ten
./rush-02 15         # Esperado: fifteen
./rush-02 19         # Esperado: nineteen

# Dezenas (20-99)
./rush-02 20         # Esperado: twenty
./rush-02 42         # Esperado: forty two
./rush-02 99         # Esperado: ninety nine

# Centenas (100-999)
./rush-02 100        # Esperado: one hundred
./rush-02 101        # Esperado: one hundred one
./rush-02 234        # Esperado: two hundred thirty four
./rush-02 999        # Esperado: nine hundred ninety nine
```

### Testes de Milhares:

```bash
./rush-02 1000       # Esperado: one thousand
./rush-02 1001       # Esperado: one thousand one
./rush-02 1234       # Esperado: one thousand two hundred thirty four
./rush-02 10000      # Esperado: ten thousand
./rush-02 100000     # Esperado: one hundred thousand
./rush-02 999999     # Esperado: nine hundred ninety nine thousand nine hundred ninety nine
```

### Testes de Milhões e Além:

```bash
./rush-02 1000000    # Esperado: one million
./rush-02 1234567    # Esperado: one million two hundred thirty four thousand five hundred sixty seven
./rush-02 1000000000 # Esperado: one billion
```

### Testes de Erro:

```bash
./rush-02            # Esperado: Error (argc = 1)
./rush-02 ""         # Esperado: Error (string vazia)
./rush-02 "42a"      # Esperado: Error (letra no número)
./rush-02 "-42"      # Esperado: Error (número negativo)
./rush-02 "42.5"     # Esperado: Error (decimal)
./rush-02 " 42"      # Esperado: Error (espaço antes)
./rush-02 inexistente.txt 42  # Esperado: Dict Error (arquivo não existe)
```

### Testes com Dicionário Customizado:

```bash
# Crie um arquivo test.dict com:
# 20 : vinte
# 2 : dois

./rush-02 test.dict 22   # Esperado: vinte dois
```

### Teste de Formatação:

```bash
# Verificar se output termina corretamente
./rush-02 42 | cat -e
# Esperado: forty two$ ($ indica fim de linha)

# NÃO deve ter espaços extras:
./rush-02 42 | wc -c
# "forty two\n" = 10 caracteres
```

---

## 🎓 COMO EXPLICAR O CÓDIGO NA AVALIAÇÃO

### 1. Explique o FLUXO GERAL:

```
"O programa funciona em 4 etapas principais:

1. VALIDAÇÃO: Verifica se os argumentos são válidos
   - argc deve ser 2 ou 3
   - O número deve conter apenas dígitos

2. PARSING: Lê o dicionário e cria uma lista ligada
   - Abre o arquivo com open()
   - Lê o conteúdo com read()
   - Para cada linha, separa key e value
   - Armazena em uma struct t_dict

3. CONVERSÃO: Transforma o número em texto
   - Usa decomposição: milhões, milhares, centenas, dezenas, unidades
   - Busca cada parte no dicionário

4. LIMPEZA: Libera toda a memória alocada
   - free_dict() percorre a lista e libera cada nó"
```

### 2. Se perguntarem sobre DECOMPOSIÇÃO:

```
"Para converter 1234:

1. Quantos dígitos? 4 → é milhares
2. 1234 / 1000 = 1 → 'one'
3. Busca 1000 no dict → 'thousand'
4. 1234 % 1000 = 234 → resto para processar
5. 234 / 100 = 2 → 'two'
6. Busca 100 no dict → 'hundred'
7. 234 % 100 = 34 → resto
8. 34 busca direto? Não tem
9. 34 / 10 = 3 → 30 → 'thirty'
10. 34 % 10 = 4 → 'four'

Resultado: 'one thousand two hundred thirty four'"
```

### 3. Se perguntarem sobre LISTA LIGADA:

```
"Usamos lista ligada porque:

1. Não sabemos quantas linhas tem o dicionário
2. Podemos adicionar entradas conforme lemos
3. Cada nó tem: key (número como string), value (texto), next (próximo)

Visualmente:
[0|zero|→] → [1|one|→] → [42|forty two|→] → NULL"
```

### 4. Se perguntarem sobre MEMÓRIA:

```
"Temos um rigoroso controle de memória:

ALOCAMOS em:
- read_file(): conteúdo do arquivo
- parse_line(): cada nó, key e value
- ft_strdup(), ft_strjoin(), etc.

LIBERAMOS em:
- parse_dict(): libera content após usar
- free_dict(): libera cada nó, key, value
- main(): chama free_dict() no final

Posso rodar valgrind/leaks para provar!"
```

### 5. Se perguntarem sobre CASOS ESPECIAIS:

```
"Tratamos vários casos:

1. Zero: busca direto '0' → 'zero'
2. Zeros à esquerda: '007' → pula zeros → '7' → 'seven'
3. Zeros no meio: '1001' → 'one thousand one' (sem 'zero' no meio)
4. Números muito grandes: trabalhamos com strings, não int
5. Espaços no dict: trim remove antes de usar"
```

---

## 📁 ESTRUTURA DO PROJETO

```
ex00/
├── Makefile
├── includes/
│   └── ft_rush02.h          # Header com structs e protótipos
├── srcs/
│   ├── main.c               # Ponto de entrada, validação
│   ├── ft_dict_parsing.c    # Leitura e parsing do dicionário
│   ├── ft_dict_utils.c      # Manipulação da lista ligada
│   ├── ft_number_converter.c # Lógica de conversão
│   └── ft_utils.c           # Funções auxiliares básicas
├── data/
│   └── numbers.dict         # Dicionário padrão
└── Guias_de_Estudo/
    ├── algoritmo_decomposicao.md
    ├── gerenciamento_memoria.md
    ├── funcoes_novas.md
    └── guia_de_sobrevivencia_rush02.md
```

---

## 📋 NORMA V4.1 - LEMBRETES

### Regras Críticas:

```
[ ] Funções com no máximo 25 linhas
[ ] No máximo 5 funções por arquivo .c
[ ] No máximo 5 variáveis por função
[ ] No máximo 4 parâmetros por função
[ ] Variáveis declaradas no início da função
[ ] Uma linha vazia entre declarações e código
[ ] Cabeçalho 42 em todos os arquivos
```

### Nomenclatura:

```
[ ] struct começa com s_  (ex: struct s_dict)
[ ] typedef começa com t_ (ex: t_dict)
[ ] Variáveis em snake_case (ex: bytes_read)
[ ] Funções em snake_case (ex: parse_dict)
```

### Proibições:

```
[ ] NÃO usar: for, do...while, switch, case, goto
[ ] NÃO usar: ternário (?:)
[ ] NÃO usar: VLAs (int arr[n])
[ ] NÃO usar: printf, atoi, ou funções não autorizadas
```

---

## 🔧 COMPILAÇÃO E DEBUG

### Compilar:

```bash
make          # Compila o projeto
make clean    # Remove .o
make fclean   # Remove .o e executável
make re       # Recompila tudo
```

### Debug com prints (REMOVER antes de entregar!):

```c
// Use write para stderr (fd=2) para não misturar com output
write(2, "DEBUG: aqui\n", 12);

// Para ver valores numéricos, crie uma função temporária:
void debug_num(int n)
{
    char c;
    if (n >= 10)
        debug_num(n / 10);
    c = '0' + (n % 10);
    write(2, &c, 1);
}
```

### Verificar Memory Leaks:

```bash
# Linux
valgrind --leak-check=full ./rush-02 42

# macOS
leaks -atExit -- ./rush-02 42
```

---

## 🚀 DIVISÃO DE TAREFAS NO GRUPO

### Sugestão para 3 pessoas:

```
PESSOA 1: Parsing (ft_dict_parsing.c + ft_dict_utils.c)
- Implementar read_file()
- Implementar parse_line()
- Implementar parse_dict()
- Implementar dict_add_back(), dict_search()
- Implementar free_dict()

PESSOA 2: Conversão (ft_number_converter.c)
- Implementar is_valid_number()
- Implementar print_small_number()
- Implementar convert_number()
- Lógica de decomposição

PESSOA 3: Base (main.c + ft_utils.c)
- Implementar main() com validações
- Implementar ft_putchar(), ft_putstr()
- Implementar ft_strlen(), ft_strcmp()
- Implementar ft_strdup(), ft_isdigit()
- Implementar ft_strtrim_spaces()
- Ajudar com funções auxiliares extras (ft_substr, ft_strjoin)
```

### Dica de Integração:

```
1. Primeiro: funções básicas (ft_utils.c)
2. Depois: parsing do dicionário
3. Por último: conversão

Testem cada parte ANTES de juntar!
```

---

## ⏰ CRONOGRAMA SUGERIDO (48h)

### Dia 1 (Sábado):

```
Manhã (4h):
- Ler e entender o subject completamente
- Planejar a divisão de tarefas
- Configurar o repositório git

Tarde (4h):
- Implementar ft_utils.c (todos juntos para entender)
- Testar cada função isoladamente

Noite (4h):
- Começar o parsing (read_file, parse_line)
- Começar a validação do número
```

### Dia 2 (Domingo):

```
Manhã (4h):
- Terminar parsing
- Terminar is_valid_number
- Testar parsing com dicionário simples

Tarde (4h):
- Implementar lógica de conversão
- Começar com casos simples (0-99)

Noite (4h):
- Implementar casos maiores (100+, 1000+)
- Integrar tudo no main
- Testes extensivos
```

### Segunda (Última hora):

```
- Remover TODOS os prints de debug
- Verificar Norma
- Testar todos os casos
- Verificar memory leaks
- REVISAR o código em grupo (todos devem entender tudo!)
```

---

## 🆘 PROBLEMAS COMUNS E SOLUÇÕES

### Problema: Segmentation Fault
```
Causas comuns:
- Acesso a ponteiro NULL
- Acesso fora dos limites do array
- Uso de memória após free

Solução:
- Sempre verifique if (!ptr) antes de usar
- Use prints de debug para encontrar onde crashou
```

### Problema: Output com formato errado
```
Sintoma: "forty  two" (dois espaços)
Causa: Imprimindo espaço quando não deveria

Solução: Verifique condições antes de ft_putchar(' ')
```

### Problema: Memory Leak
```
Sintoma: valgrind mostra bytes não liberados

Solução:
- Verifique se free_dict está correto
- Verifique se libera temp em loops de strjoin
- Verifique se libera content após parse_dict
```

### Problema: Dict Error quando não deveria
```
Causa: parse_line rejeitando linhas válidas

Solução:
- Verifique se está fazendo trim correto
- Verifique se encontra ':' corretamente
- Print debug do que está parseando
```

---

**BOA SORTE NA AVALIAÇÃO! 🚀**

*"O grupo que treina junto, vence junto!"*

---

## 📌 CONTATOS ÚTEIS

- Slack/Discord do grupo: _____________
- Horário da avaliação: _____________
- Local da avaliação: _____________

**Não deixem ninguém para trás. Se um não sabe, ensinem!**
