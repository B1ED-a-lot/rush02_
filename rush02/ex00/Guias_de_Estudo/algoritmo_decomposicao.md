# 🧮 Algoritmo de Decomposição Numérica

## Introdução

Este guia explica como transformar um número grande em suas partes para converter em texto.

A ideia central é: **dividir para conquistar**.

---

## 1. O Básico: Divisão e Módulo (%)

### O que são?

```
DIVISÃO (/)                      MÓDULO (%)
"Quantas vezes cabe?"            "Qual o resto?"

42 / 10 = 4                      42 % 10 = 2
(10 cabe 4 vezes em 42)          (sobram 2)

1234 / 100 = 12                  1234 % 100 = 34
(100 cabe 12 vezes em 1234)      (sobram 34)
```

### Por que são úteis?

```
O número 1234 pode ser "fatiado":

1234 / 1000 = 1    → "one"        (milhares)
1234 % 1000 = 234  → resto para processar

234 / 100 = 2      → "two"        (centenas)
234 % 100 = 34     → resto para processar

34 / 10 = 3        → "thirty"     (dezenas)
34 % 10 = 4        → "four"       (unidades)

Resultado: "one thousand two hundred thirty four"
```

---

## 2. A Tabela de Grandezas

Cada "grandeza" corresponde a uma potência de 10:

```
┌─────────────────────────────────────────────────────────────────────────┐
│ GRANDEZA       │ VALOR              │ ZEROS │ DIVISOR                   │
├─────────────────────────────────────────────────────────────────────────┤
│ unidade        │ 1                  │ 0     │ 1                         │
│ dezena         │ 10                 │ 1     │ 10                        │
│ centena        │ 100                │ 2     │ 100                       │
│ milhar         │ 1,000              │ 3     │ 1000                      │
│ milhão         │ 1,000,000          │ 6     │ 1000000                   │
│ bilhão         │ 1,000,000,000      │ 9     │ 1000000000                │
│ trilhão        │ 1,000,000,000,000  │ 12    │ 1000000000000             │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 3. O Algoritmo Passo a Passo

### Exemplo: Converter 1234567 para texto

```
PASSO 1: Identificar a grandeza
─────────────────────────────────
Número: 1234567
Quantos dígitos? 7
7 dígitos = milhões (10^6 tem 7 dígitos: 1,000,000)

PASSO 2: Separar a parte dessa grandeza
─────────────────────────────────────────
1234567 / 1000000 = 1    → "one"
1234567 % 1000000 = 234567 → resto

Imprime: "one" + " " + "million"

PASSO 3: Processar o resto (234567)
─────────────────────────────────────
234567 tem 6 dígitos = milhares

234567 / 1000 = 234      → processar recursivamente
234567 % 1000 = 567      → resto

PASSO 4: Processar 234 (centenas)
──────────────────────────────────
234 / 100 = 2            → "two"
234 % 100 = 34           → resto

Imprime: "two" + " " + "hundred"

PASSO 5: Processar 34 (dezenas)
─────────────────────────────────
34 não está no dicionário
34 / 10 = 3 → 30 → "thirty"
34 % 10 = 4 → "four"

Imprime: "thirty" + " " + "four"

... e assim por diante para 567

RESULTADO FINAL:
"one million two hundred thirty four thousand five hundred sixty seven"
```

---

## 4. Fluxograma do Algoritmo

```
                    ┌─────────────────────┐
                    │ convert_number(num) │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ num está no dict?   │
                    └──────────┬──────────┘
                               │
              ┌────────────────┴────────────────┐
              │ SIM                             │ NÃO
              ▼                                 ▼
    ┌─────────────────┐              ┌─────────────────────┐
    │ Imprime e       │              │ Encontra maior      │
    │ retorna         │              │ grandeza (G)        │
    └─────────────────┘              └──────────┬──────────┘
                                               │
                                               ▼
                                    ┌─────────────────────┐
                                    │ parte = num / G     │
                                    │ resto = num % G     │
                                    └──────────┬──────────┘
                                               │
                                               ▼
                                    ┌─────────────────────┐
                                    │ convert_number(parte)│
                                    │ imprime nome de G   │
                                    │ convert_number(resto)│
                                    └─────────────────────┘
```

---

## 5. Trabalhando com Strings (Números Grandes!)

### O Problema

O Rush 02 exige lidar com números MUITO grandes:
- `unsigned int` vai até ~4 bilhões (10 dígitos)
- `unsigned long long` vai até ~18 quintilhões (19 dígitos)
- O dicionário tem até undecillion (37 dígitos!)

### A Solução: Número como String

Em vez de fazer divisão matemática, "fatiamos" a string:

```
Número como string: "1234567890123"
Comprimento: 13 dígitos

13 dígitos = trilhões (10^12 tem 13 dígitos)

"Fatiar":
  - Pegar primeiros (13 - 12) = 1 dígito: "1"
  - Pegar resto: "234567890123"

Imprime: "one" + " " + "trillion"
Chama: convert_number("234567890123")
```

### Tabela de Fatiamento por Comprimento

```
┌─────────────────────────────────────────────────────────────────────────┐
│ COMPRIMENTO │ GRANDEZA        │ PEGAR PRIMEIROS │ CHAVE DO DICT         │
├─────────────────────────────────────────────────────────────────────────┤
│ 4-6         │ thousand        │ len - 3         │ "1000"                │
│ 7-9         │ million         │ len - 6         │ "1000000"             │
│ 10-12       │ billion         │ len - 9         │ "1000000000"          │
│ 13-15       │ trillion        │ len - 12        │ "1000000000000"       │
│ 16-18       │ quadrillion     │ len - 15        │ "1000000000000000"    │
│ 19-21       │ quintillion     │ len - 18        │ ...                   │
│ ...         │ ...             │ ...             │ ...                   │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 6. Casos Especiais

### Caso 1: Zeros no Meio

```
Número: 1001
          │
          ▼
1001 / 1000 = 1     → "one thousand"
1001 % 1000 = 1     → "one"

Cuidado: não imprimir "zero" para o "00" do meio!
Resultado: "one thousand one" (não "one thousand zero zero one")
```

### Caso 2: Números de 11 a 19

```
Estes são especiais! Não seguem o padrão dezena + unidade.
11 = "eleven" (não "ten one")
15 = "fifteen" (não "ten five")

O dicionário já tem esses valores, então basta buscar diretamente!
```

### Caso 3: Dezenas Exatas

```
20 = "twenty" (não "twenty zero")
30 = "thirty"
...

Se a unidade for 0, não imprima nada depois da dezena!
```

---

## 7. Pseudocódigo Final

```
função convert_number(dict, num):
    // Pular zeros à esquerda
    num = skip_leading_zeros(num)
    
    // Tentar buscar diretamente
    se dict_search(num) existe:
        imprimir(dict_search(num))
        retornar sucesso
    
    len = comprimento(num)
    
    // Caso: centenas (3 dígitos)
    se len == 3:
        imprimir convert_number(num[0])      // primeiro dígito
        imprimir " "
        imprimir dict_search("100")          // "hundred"
        se num[1..2] != "00":
            imprimir " "
            retornar convert_number(num[1..2])
        retornar sucesso
    
    // Caso: dezenas compostas (2 dígitos)
    se len == 2:
        imprimir dict_search(num[0] + "0")   // "forty"
        se num[1] != '0':
            imprimir " "
            imprimir dict_search(num[1])     // "two"
        retornar sucesso
    
    // Caso: milhares e acima
    grandeza = encontrar_grandeza(len)
    tamanho_parte = len - grandeza.zeros
    
    parte = num[0..tamanho_parte-1]
    resto = num[tamanho_parte..]
    
    convert_number(parte)
    imprimir " "
    imprimir dict_search(grandeza.chave)
    
    se resto != todos_zeros:
        imprimir " "
        retornar convert_number(resto)
    
    retornar sucesso
```

---

## 8. Exercícios Práticos

Antes de codar, pratique no papel!

### Exercício 1: Decomponha manualmente
```
42 = ?
234 = ?
1001 = ?
10500 = ?
```

### Exercício 2: Qual é a grandeza?
```
Número com 5 dígitos = ?
Número com 8 dígitos = ?
Número com 11 dígitos = ?
```

### Exercício 3: Casos especiais
```
O que acontece com:
- "0" (zero)?
- "000" (zeros à esquerda)?
- "1000000" (milhão exato)?
```

---

## 9. Dicas de Implementação

1. **Comece simples**: Primeiro faça funcionar para 0-99, depois 100-999, depois milhares...

2. **Teste muito**: Cada vez que adicionar uma grandeza, teste exaustivamente.

3. **Use prints de debug**: Coloque `write(2, "DEBUG: ...", ...)` para ver o fluxo (use fd=2 para stderr).

4. **Confie na recursão**: Se a parte pequena funciona, a recursão vai fazer o resto funcionar!

---

**Boa sorte! 🚀**

*"Um número de cada vez, uma grandeza de cada vez!"*
