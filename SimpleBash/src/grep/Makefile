FLAG = -Wall -Werror -Wextra

all : s21_grep

rebuild :clean s21_grep sh

s21_grep : s21_grep.c 
	gcc $(FLAG) s21_grep.c -o s21_grep

debug : s21_grep.c 
	gcc $(FLAG) s21_grep.c -g

test : checks
	sh run.sh
	

clean : 
	rm -rf *.o s21_grep *.out s21_grep.txt grep.txt

# lo :
# 	for i in `seq 100 $(OP)`;	do ./s21_grep; done;

git :
	git add .
	git commit -m "Make grep"
	git push

vg:
	CK_FORK=no valgrind --tool=memcheck ./s21_grep -n void s21_grep.c

style: s21_grep
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h разобрбраться 
	rm -f CPPLINT.cfg 

lik: s21_grep
	leaks --atExit -- ./s21_grep -e int s21_grep.c -benst test_file/all_flag_tests/*

cppcheck: s21_grep
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg	

checks: style cppcheck 