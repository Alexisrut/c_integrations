build: ## Build programm
	@gcc main.c -L. -lintegration -o main

help: ## Show help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_0-9-]+:.*?## / {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

.PHONY: build help clean test

libintegration.so: integration.c ## Compile shared library
	@gcc --shared -fPIC $< -o $@

clean: ## Remove temporary files
	@rm -f main
	@rm -f libintegration.so

test: ## Test integration
	@gcc test.c -L. -lintegration -o test
	@./test

.DEFAULT:
	@printf 'Error: target %s does not exist\n' "'$@'"