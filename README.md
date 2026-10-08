# Lex & Yacc Expression Parser & Parse Tree Generator

[![Language](https://img.shields.io/badge/Language-Lex%20%2F%20Yacc%20%2F%20C99-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Parser](https://img.shields.io/badge/Parser-Flex%20%26%20Bison%20%2F%20GCC-green.svg)](https://www.gnu.org/software/bison/)
[![Course](https://img.shields.io/badge/Course-BCSE306L%20Compiler%20Design-red.svg)](https://vit.ac.in)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Author Information
- **Author:** Shrri Dharshan D R
- **GitHub:** [@shrridharshan27](https://github.com/shrridharshan27)
- **Registration Number:** `23BPS1090`
- **Course:** Compiler Design Laboratory (`BCSE306L`)
- **Lab Slot:** `L23+L24`

---

## Overview
This repository contains a syntax analyzer and parse tree generator for arithmetic and assignment expressions. It features:
- **Lex/Flex Lexical Specification** (`src/lexer.l`) for tokenization.
- **Yacc/Bison Grammar Rules** (`src/parser.y`) enforcing operator precedence and balanced parentheses.
- **Parse Tree Node Construction**: Dynamic creation of hierarchical syntax tree structures with in-order and visual 90-degree rendering.
- **Standalone Pure C Implementation** (`src/standalone_parser.c`): Fully runnable with standard GCC on Windows/Linux without requiring external Flex/Bison binaries.

---

## Grammar Productions
```
statement -> ID '=' expr ';'
           | expr ';'

expr      -> expr '+' expr
           | expr '-' expr
           | expr '*' expr
           | expr '/' expr
           | '(' expr ')'
           | ID
           | NUM
```
- Precedence: `*`, `/` has higher precedence than `+`, `-`.
- Associativity: Left-associative for all arithmetic operators.

---

## Build & Execution

### 1. Standalone Pure C Runner (Immediate execution on Windows MinGW)
```bash
gcc -std=c99 -Wall -Wextra src/standalone_parser.c -o build/standalone_parser
./build/standalone_parser
```

### 2. Using Flex & Bison (Linux / WSL / MinGW with MSYS2)
```bash
flex src/lexer.l
bison -d src/parser.y
gcc lex.yy.c parser.tab.c -o build/parser
./build/parser
```

---

## License
MIT License - see [LICENSE](LICENSE) for details.
