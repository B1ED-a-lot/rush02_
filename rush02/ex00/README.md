# 🚀 RUSH 02 - Number to Words

## 📋 Visão Geral

Este projeto converte números em sua forma escrita por extenso (ex: `42` → `forty two`).

**Prazo:** 48 horas
**Avaliação:** Por pares (humano)
**Funções permitidas:** `write`, `malloc`, `free`, `open`, `read`, `close`

---

## 📁 Estrutura do Projeto

```
ex00/
├── Makefile                    # Compilação
├── README.md                   # Este arquivo
├── includes/
│   └── ft_rush02.h            # Header com structs e protótipos
├── srcs/
│   ├── main.c                 # Validação e fluxo principal
│   ├── ft_dict_parsing.c      # Leitura do dicionário
│   ├── ft_dict_utils.c        # Lista ligada e utilidades
│   ├── ft_number_converter.c  # Conversão número → texto
│   └── ft_utils.c             # Funções auxiliares básicas
├── data/
│   └── numbers.dict           # Dicionário padrão
└── Guias_de_Estudo/
    ├── algoritmo_decomposicao.md   # Como fatiar números
    ├── gerenciamento_memoria.md    # Evitar memory leaks
    ├── funcoes_novas.md            # malloc, free, open, read, close
    └── guia_de_sobrevivencia_rush02.md  # Tudo para a avaliação
```

---

## 🛠️ Como Usar

### Compilar
```bash
make        # Compila o projeto
make clean  # Remove arquivos objeto
make fclean # Remove objetos e executável
make re     # Recompila tudo
```

### Executar
```bash
# Com dicionário padrão
./rush-02 42

# Com dicionário customizado
./rush-02 meu_dicionario.txt 42
```

### Exemplos de Saída Esperada
```bash
./rush-02 0         # zero
./rush-02 42        # forty two
./rush-02 100       # one hundred
./rush-02 1234      # one thousand two hundred thirty four
./rush-02 1000000   # one million
```

---

## 📚 Guias de Estudo (LEIAM!)

1. **funcoes_novas.md** - Começem por aqui! Explica `malloc`, `free`, `open`, `read`, `close`
2. **algoritmo_decomposicao.md** - Como transformar 1234 em "one thousand..."
3. **gerenciamento_memoria.md** - Checklist para evitar memory leaks
4. **guia_de_sobrevivencia_rush02.md** - Tudo que precisam para a avaliação

---

## 👥 Divisão de Tarefas Sugerida

### Pessoa 1: Parsing
- `ft_dict_parsing.c`: `read_file()`, `parse_line()`, `parse_dict()`
- `ft_dict_utils.c`: `dict_add_back()`, `dict_search()`, `free_dict()`

### Pessoa 2: Conversão  
- `ft_number_converter.c`: `is_valid_number()`, `convert_number()`, `print_small_number()`

### Pessoa 3: Base
- `main.c`: Validação de argumentos, fluxo principal
- `ft_utils.c`: `ft_putstr()`, `ft_strlen()`, `ft_strcmp()`, `ft_strdup()`, `ft_isdigit()`
- `ft_dict_utils.c`: `ft_strtrim_spaces()` + funções auxiliares extras

---

## ⚠️ Checklist Antes de Entregar

- [ ] `make fclean && make` compila sem erros
- [ ] `norminette *.c includes/*.h` sem erros
- [ ] Testou números: 0, 1-19, 20-99, 100-999, 1000+, 1000000+
- [ ] Testou erros: argc errado, número inválido, arquivo inexistente
- [ ] Memory leaks: `valgrind ./rush-02 42` mostra 0 leaks
- [ ] TODOS do grupo entendem 100% do código
- [ ] Removeu TODOS os prints de debug

---

## 🎯 Objetivos de Aprendizado

- Manipulação de arquivos (`open`, `read`, `close`)
- Alocação dinâmica de memória (`malloc`, `free`)
- Estruturas de dados (lista ligada)
- Decomposição numérica
- Trabalho em equipe

---

**Boa sorte! 🍀**

*"Se você não consegue explicar, você não entendeu."*
