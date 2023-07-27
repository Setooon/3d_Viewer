.PHONY: all a clean gcov_report s21_string remove_s21_string linter cppcheck leaks
CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_LIB = off
TEST_LIB2 = core
TESTFILE = test
GCOV_FLAG = -fprofile-arcs -ftest-coverage
LIBS_FOR_CHECK_PCKG =
D_OS =
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_FOR_CHECK_PCKG = -lcheck -lsubunit -lm -lpthread -lrt
	D_OS = -D __My_Linux__
else
	LIBS_FOR_CHECK_PCKG = -lcheck -lm -lpthread
	D_OS = -D __My_APPLE__
endif

all: clean install tests gcov_report

3d_Viewer_1.a: remove_3d_Viewer_1.a
	$(CC) $(D_OS) -c $(FLAGS) $(TEST_LIB).c -o $(TEST_LIB).a 
	$(CC) $(D_OS) -c $(FLAGS) $(TEST_LIB2).c -o $(TEST_LIB2).a

remove_3d_Viewer_1.a:
	rm -f *$(TEST_LIB)*.a *$(TEST_LIB)*.o *$(TEST_LIB2)*.o

test: 3d_Viewer_1.a
	$(CC) $(FLAGS) -o a.out test.c $(TEST_LIB).a $(TEST_LIB2).a $(LIBS_FOR_CHECK_PCKG) $(GCOV_FLAG)
	./a.out

gcov_report:
	$(CC) $(D_OS) -c $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).c -o $(TEST_LIB).a
	$(CC) $(D_OS) -c $(FLAGS) $(GCOV_FLAG) $(TEST_LIB2).c -o $(TEST_LIB2).a
	$(CC) $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).a $(TEST_LIB2).a $(TESTFILE).c $(LIBS_FOR_CHECK_PCKG) -o a2.out
	./a2.out
	@echo "=== gcov start ==="
	gcov a2.out
	lcov -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
clean:
	rm -rf  *.gc* report test test.info build 3d_Viewer_1 doxygen
	rm -f *.a *.o *.so *.out $(TESTFILE) *.info *.gcno *.gcda

check: tests
	clang-format -n *.c *.h
	CK_FORK=no leaks --atExit -- ./a2.out

uninstall:
	rm -rf $(HOME)/3d_Viewer_1/

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	rm -rf $(HOME)/3d_Viewer_1
	mkdir $(HOME)/3d_Viewer_1/
	cp -rf build/3d_Viewer_1.app $(HOME)/3d_Viewer_1/
	# make clean

dvi_install:
	brew install doxygen

dvi:
	rm -rf doxygen
	doxygen
	open doxygen/html/index.html

dist: 
	rm -rf build
	mkdir 3d_Viewer_1
	mkdir 3d_Viewer_1/src
	cp Makefile *.c *.h *.cpp *.ui *.pro 3d_Viewer_1/src/
	tar -cvzf 3d_Viewer_1.tar.gz 3d_Viewer_1
	mv 3d_Viewer_1.tar.gz $(HOME)/
	rm -rf 3d_Viewer_1/
