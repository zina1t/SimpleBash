FLAGS=gcc -Wall -Werror -Wextra
default: all

all: s21_cat

s21_cat:s21_cat.c funcs.c funcs.h
	$(FLAGS) s21_cat.c funcs.c -o s21_cat 

clean:
	rm -rf s21_cat second first result 

rebuild: clean all