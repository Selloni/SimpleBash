FLAG = -Wall -Werror -Wextra

all : s21_cat

rebuild :clean s21_cat test

s21_cat : s21_cat.c 
	gcc $(FLAG) s21_cat.c -o s21_cat

debug : s21_cat.c 
	gcc $(FLAG) s21_cat.c -g

test :
	sh run.sh

clean : 
	rm -rf *.o s21_cat *.out.* s21_cat.txt cat.txt

lo :
	for i in `seq 100 $(OP)`;	do ./s21_cat; done;

git :
	git add .
	git commit -m "cat done"
	git push

 style: s21_cat
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg

lik: s21_cat
	leaks --atExit -- ./s21_cat -benst test_file/all_flag_tests/*

cppcheck: s21_cat
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg	

checks: style cppcheck 
