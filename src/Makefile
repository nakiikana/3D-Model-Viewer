CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c11
APP = s21_3DViewer_v1.0/*

GCOVFLAGS = -L. --coverage
TEST_FLAGS = -lm -lcheck

ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lpthread -lrt -lsubunit -lm
endif

all: install

build:
	mkdir s21_3DViewer_v1.0
	cd s21_3DViewer_v1.0 && cmake -B build "../" && make -C build 3DViewer_v1

install: build
	cp   -rf s21_3DViewer_v1.0/build/3DViewer_v1.app $(HOME)/Desktop/3DViewer_v1.app
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/3DViewer_v1.app

launch:
	open $(HOME)/Desktop/3DViewer_v1.app

dvi:
	doxygen Doxyfile
	open html/index.html

dist: dvi
	rm -rf ../Archive_s21_3DViewer_v1.0/
	mkdir ../Archive_s21_3DViewer_v1.0/
	cp -r ../src/ ../Archive_s21_3DViewer_v1.0/
	tar -C ../ -czvf Archive_s21_3DViewer_v1.0.tgz Archive_s21_3DViewer_v1.0/
	mv Archive_s21_3DViewer_v1.0.tgz $(HOME)/Desktop/
	rm -rf ../Archive_s21_3DViewer_v1.0/

test: clean
	$(CC) $(CFLAGS) -g test.c parser.c transform.c $(TEST_FLAGS) -o test
	./test

check:
	clang-format -style=Google -n *.c mainwindow.cpp main.cpp glview.cpp
	clang-format -style=Google -i *.c mainwindow.cpp main.cpp glview.cpp
	clang-format -style=Google -n *.c mainwindow.cpp main.cpp glview.cpp
	make test
	CK_FORK=no leaks --atExit -- ./test

style:
	clang-format -n -style=Google *.c mainwindow.cpp main.cpp glview.cpp

fix-style:
	clang-format -i -style=Google *.c mainwindow.cpp main.cpp glview.cpp

gcov_report: clean
	$(CC) $(CFLAGS) test.c parser.c transform.c -coverage $(TEST_FLAGS) -o gcovreport
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open ./report/index.html
	rm -rf *.a *.info *.gcda *.gcno gcovreport

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf gcovreport
	rm -rf s21_3DViewer_v1.0
	rm -rf test
