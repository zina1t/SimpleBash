FLAGS=gcc -Wall -Werror -Wextra
CAT = src/cat/
GREP = src/

default: all

all: s21_grep

s21_grep:s21_grep.c grep_funcs.c grep_funcs.h
	$(FLAGS) s21_grep.c grep_funcs.c -o s21_grep 

clean:
	rm -rf s21_grep second first result 

rebuild: clean all