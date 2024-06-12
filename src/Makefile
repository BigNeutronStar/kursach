CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=`pkg-config --cflags --libs check`
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=hse_*.c
HEAD=hse_math.h
LIB_O=hse_decimal.o
LIB_A=hse_decimal.a
TEST=test.out

CC_FLAGS =
ASAN = -g -fsanitize=address
TESTFLAGS := `pkg-config --cflags --libs check` -coverage -lpthread -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage

C_FILES = hse_*.c
O_FILES = hse_*.o

ifeq ($(shell uname -s),Linux)
	TESTFLAGS += -lrt -lm -lsubunit
endif

ifeq ($(shell uname -s),Linux)
	REPORT = gcovr --html --html-details -o coverage_report.html --exclude "test.c" && xdg-open coverage_report.html
else ifeq ($(shell uname -s),Darwin)
	REPORT = gcovr --html --html-details -o coverage_report.html --exclude "test.c" && open coverage_report.html
endif

all: clean hse_decimal.a

rebuild: clean all

hse_decimal.a: all_functions
	ar -rv hse_decimal.a $(O_FILES)
	ranlib hse_decimal.a

test: hse_decimal.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. hse_decimal.a -o test
	./test

gcov_report: all_functions_gcov
	ar -rv hse_decimal.a $(O_FILES)
	ranlib hse_decimal.a
	gcc test.c $(GCOVFLAGS) $(TESTFLAGS) -L. hse_decimal.a -o test
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
	gcc -c $(CC_FLAGS) $(SOURCES)

all_functions_gcov:
	gcc -c $(CC_FLAGS) $(GCOVFLAGS) $(SOURCES)

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a
	rm -rf report/
	rm -rf temp/
	rm -rf atest.c
