CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=-lcheck -lm -lpthread 
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_*.c
HEAD=s21_math.h
LIB_O=s21_decimal.o
LIB_A=s21_decimal.a
TEST=test.out

CC_FLAGS = 
ASAN = -g -fsanitize=address
TESTFLAGS := -lcheck -coverage -lpthread -pthread 
GCOVFLAGS = -fprofile-arcs -ftest-coverage

C_FILES = s21_*.c 
O_FILES = s21_*.o

ifeq ($(shell uname -s),Linux)
	TESTFLAGS += -lrt -lm -lsubunit
endif

ifeq ($(shell uname -s),Linux)
	REPORT = gcov s21_*.gcno && gcovr --html > report.html
else ifeq ($(shell uname -s),Darwin)
	REPORT = gcov s21_*.gcno > report.html && cat report.html
endif

all: clean s21_decimal.a

rebuild: clean all

s21_decimal.a:clean  all_functions
	ar -rv s21_decimal.a $(O_FILES) s21_decimal.h
	ranlib s21_decimal.a

test: s21_decimal.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_decimal.a -o test
	./test

gcov_report: all_functions_gcov
	ar -rv s21_decimal.a $(O_FILES) s21_decimal.h
	ranlib s21_decimal.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_decimal.a -o test
	./test
	$(REPORT)
	make clean

style: clean
	cppcheck *.h *.c
	chmod 777 ../materials/linters/.clang-format
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -n *.c
	clang-format -n *.h

all_functions:
	gcc -c $(CC_FLAGS) s21_*.c 

all_functions_gcov:
	gcc -c $(CC_FLAGS) $(TESTFLAGS) s21_*.c 

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a
	rm -rf report/
	rm -rf temp/
	rm -rf atest.c
