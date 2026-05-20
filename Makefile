#ASM_INT = integration.S
#ASM_O = integration.S
#C_O = integration.c
#C_INT = integration.c

#build: ## Build programm
#	@gcc main.c -L. -lintegration -o main

#help: ## Show help
#	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_0-9-]+:.*?## / {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

#.PHONY: build help clean test

#libintegration.so: $(ASM_INT) $(C_INT) ## Compile shared library
#	@nasm -f elf32 $< -o $(ASM_O)
#	@gcc $(C_INT) -o $(C_O)
#	@gcc -shared $(C_O) $(ASM_O) -o $@

#clean: ## Remove temporary files
#	@rm -f main
#	@rm -f libintegration.so
#	@rm -f $(ASM_O)
#	@rm -f $(C_O)

#test: ## Test integration
#	@gcc test.c -L. -lintegration -o test
#	@./test

#.DEFAULT:
#	@printf 'Error: target %s does not exist\n' "'$@'"

CC = gcc

CFLAGS = -Wall -Wextra -fPIC

all: libintegration.so

libintegration.so: integration.o asm_integration.o
	$(CC) -m32 -shared integration.o asm_integration.o -o libintegration.so

integration.o: integration.c
	@gcc -m32 -std=c99 -c integration.c -o integration.o

asm_integration.o: asm_integration.S
	@nasm -f elf32  asm_integration.S -o asm_integration.o

clean:
	rm -f *.o *.so