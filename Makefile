CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -g
BUILD_DIR=./build
LIB=s21_matrix.a

CFILES=$(shell find lib -name '*.c')
HFILES=$(shell find lib -name '*.h')
OBJECTS=$(CFILES:%.c=$(BUILD_DIR)/%.o)

TEST_NAME=s21_tests
TEST_CFILES=$(shell find tests -name '*.c')
TEST_HFILES=$(shell find tests -name '*.h')
TEST_FLAGS=$(shell pkg-config --cflags --libs check)

export PATH:=${PATH}:$(shell realpath ~/.local/bin):$(shell pwd)/tests
GCOV_FLAG=--coverage -lgcov
GCOV_REPORT=./gcov_report/gcov_report.html

DEBUG_FLAG=-g
DEBUG_DIR=debug
DEBUG_NAME=debug.out

.PHONY: all test gcov_report clean 
.PHONY: gcov val check debug clean_gcovr clean_all style val gcovm gcovl testm testl test_build

all: $(LIB)

$(LIB): $(OBJECTS)
	@ar rc $(LIB) $(OBJECTS)
	@ranlib $(LIB)
	@echo;

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

#auto
test_build: clean_all $(LIB)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(TEST_CFILES) ./$(LIB) -o $(BUILD_DIR)/$(TEST_NAME) $(TEST_FLAGS)

test: test_build
	@$(BUILD_DIR)/$(TEST_NAME)

#linux
testl: clean_all $(LIB)
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) test TEST_FLAGS="-lcheck -lsubunit -lm" >/dev/null
	@$(BUILD_DIR)/$(TEST_NAME)

#mac
testm: clean_all $(LIB)
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) test TEST_FLAGS="-lpthread -lcheck" >/dev/null
	@$(BUILD_DIR)/$(TEST_NAME)

#auto
gcov_report:
	@$(MAKE) test CFLAGS="$(CFLAGS) $(GCOV_FLAG)" >/dev/null
	@mkdir -p gcov_report
	@rm -r $(BUILD_DIR)/*_t*.gc?? || true
	@gcovr --html-details $(GCOV_REPORT) 2>/dev/null || true
	@gcovr --xml build/cov.xml 2>/dev/null || true
	@ln -s $(GCOV_REPORT) ./gcov_report.html || true
	@$(MAKE) clean_gcovr >/dev/null
	@if [ ! -f $(GCOV_REPORT) ]; then echo;echo "Ошибка. Проверте доступность gcovr.";echo; fi
	@if [ -f $(GCOV_REPORT) ]; then echo;echo "Отчет сгенерирован в gcov_report.html";echo; fi

gcov: gcov_report
	@if [ -f $(GCOV_REPORT) ]; then xdg-open $(GCOV_REPORT); fi

#linux
gcovl:
	@$(MAKE) gcov TEST_FLAGS="-lcheck -lsubunit -lm"

#mac
gcovm:
	@$(MAKE) gcov TEST_FLAGS="-lpthread -lcheck"

debug: clean_all
	$(MAKE) $(LIB) CFLAGS="$(DEBUG_FLAG)" >/dev/null
	$(CC) $(DEBUG_FLAG) $(DEBUG_DIR)/*.c -L. -l:$(LIB) -o $(DEBUG_DIR)/$(DEBUG_NAME) -lm
	echo;$(DEBUG_DIR)/$(DEBUG_NAME);echo;

val: test_build
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(BUILD_DIR)/$(TEST_NAME)
	@$(MAKE) clean_all

check: val
	cppcheck --enable=all --suppress=missingIncludeSystem .
	cp ../materials/linters/.clang-format .
	find . -name '*.[ch]' | xargs clang-format -n || true
	rm .clang-format
	@echo;

style:
	cp ../materials/linters/.clang-format .
	find . -name '*.[ch]' | xargs clang-format -i || true
	rm .clang-format
	
clean_gcovr:
	@rm -f *.gcda *.gcno $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno $(BUILD_DIR)/$(TEST_NAME)

clean_all: clean_gcovr
	@rm -f $(OBJECTS)/*.o
	@rm -f $(LIB) $(TEST_NAME) $(DEBUG_DIR)/$(DEBUG_NAME)
	@rm -rf ./gcov_report *.html
	@rm -rf $(BUILD_DIR)

clean: clean_all
	@echo;echo "Clean complete";echo;
