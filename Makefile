ASM_INT = asm_integration.S
ASM_O = asm_integration.o
C_O = integration.o
C_INT = integration.c
CC = gcc
CFLAGS = -Wall -Wextra -fPIC

help: ## Show help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_0-9-]+:.*?## / {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

.PHONY: build help clean test

build: ## Build programm
	@$(CC) -m32 main.c -L. -lintegration -o main

run: ## Run programm(!build before run!)
	@LD_LIBRARY_PATH=. ./main

libintegration.so: $(C_O) $(ASM_O) ## Compile shared library
	$(CC) -m32 -shared $< $(ASM_O) -o $@

$(C_O): $(C_INT) ## Compile C-part
	@$(CC) -m32 -std=c99 -c $< -o $@

$(ASM_O): $(ASM_INT) ## Compile ASM-part
	@nasm -f elf32  $< -o $@

clean: ## Remove temporary files
	@rm -f main
	@rm -f libintegration.so
	@rm -f $(ASM_O)
	@rm -f $(C_O)

test: ## Test integration
	@@$(CC) -m32 test.c -L. -lintegration -o test
	@LD_LIBRARY_PATH=. ./test

.DEFAULT:
	@printf 'Error: target %s does not exist\n' "'$@'"