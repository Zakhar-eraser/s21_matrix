MODULES+=create_matrix
MODULES+=remove_matrix
MODULES+=eq_matrix
MODULES+=sum_matrix
MODULES+=sub_matrix
MODULES+=mult_number
MODULES+=mult_matrix
MODULES+=transpose
MODULES+=determinant
MODULES+=calc_complements
MODULES+=inverse_matrix
#################  DO NOT CHANGE BELOW  #################
STYLE_CHECK_MODE=
BUILD_DIR=build/
UNIT_TESTS_DIR=unit_tests/
CFLAGS=-Wall -Wextra -Werror -std=c11
LFLAGS=
COMPILER=gcc
MODULES_OBJ=$(addsuffix .o, $(MODULES))
COMMON_OBJ=common.o
TEST_OBJ=$(addprefix $(UNIT_TESTS_DIR), $(addsuffix _test.o, $(MODULES)))
TEST_OBJ+=$(UNIT_TESTS_DIR)tests_common.o $(UNIT_TESTS_DIR)tests_runner.o

all: s21_matrix.a

s21_matrix.a: $(MODULES_OBJ) $(COMMON_OBJ)
	ar rc $@ $(addprefix $(BUILD_DIR), $(COMMON_OBJ)) $(addprefix $(BUILD_DIR), $(MODULES_OBJ))
	ranlib $@

test: s21_matrix.a $(TEST_OBJ)
	$(COMPILER) $(LFLAGS) -o s21_matrix_test.out $(addprefix $(BUILD_DIR), $(TEST_OBJ)) s21_matrix.a `pkg-config --cflags --libs check` -lm

test_debug: CFLAGS+=-g
test_debug: test

test_san: CFLAGS+= -fsanitize=address
test_san: LFLAGS+= -fsanitize=address
test_san: test_debug

style:
	mv ../materials/linters/.clang-format .
	clang-format $(STYLE_CHECK_MODE) *.c */*.c */*.c *.h */*.h */*.h
	mv .clang-format ../materials/linters/

style_correct: STYLE_CHECK_MODE=-i
style_correct: style

style_check: STYLE_CHECK_MODE=-n
style_check: style

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: LFLAGS += -fprofile-arcs
gcov_report: test
	CK_FORK=no ./s21_matrix_test.out
	lcov -t "report" -o report.info -c -d .
	genhtml -o "html_report" report.info

clean:
	-rm -rf $(BUILD_DIR)
	-rm s21_matrix.a
	-rm *.gcda
	-rm *.gcno
	-rm -rf html_report
	-rm report.info
	-rm s21_matrix_test.out

%.o: %.c
	mkdir -p $(BUILD_DIR)$(@D)
	$(COMPILER) $(CFLAGS) -c $< -o $(BUILD_DIR)$@
