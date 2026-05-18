# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -Werror

# Папки
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Исходные файлы
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/math.c

# Файлы тестов
TEST_SRC = $(TEST_DIR)/test_math.c $(SRC_DIR)/math.c

# Итоговые исполняемые файлы
TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/test_app

# Главная цель
all: $(TARGET)

# Сборка программы
$(TARGET):
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Сборка тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)
	@echo "All tests passed!"

# Компиляция тестов
$(TEST_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Пересборка
rebuild: clean all

# Чтобы make не путал команды с файлами
.PHONY: all run test clean rebuild