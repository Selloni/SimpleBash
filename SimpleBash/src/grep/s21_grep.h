#ifndef SIMPLEBASH_SRC_GREP_S21_GREP_H_
#define SIMPLEBASH_SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>

typedef struct {
    int fe;
    int fi;
    int fv;
    int fc;
    int fl;
    int fn;
    int fh;
    int fs;
    int ff;
    int fo;
    // int flag_0;  // костыль
    int line_in_f;
    int count_tru;
    int count_false;
    int severalf;  // контроль количества файлов
} flags;

typedef struct {
    char name[BUFSIZ];
} parametr;

// typedef struct  {
//     regoff_t rm_so;
//     regoff_t rm_eo;
// } regmatch_t;

void find_options(int argc, char **argv, flags *opt, parametr *bufpar);
void read_file(char *name_file, flags *opt, parametr *bufpar);
int pars_flag(int argc, char **argv, flags *opt);
void print_file(char *name_file, flags *opt);
void flag_n(int ns, flags *opt);
void flag_f(char *name_file, flags *opt, parametr *bufpar);
void flag_o(char *str, flags *opt, parametr *bufpar);

#endif  //  SIMPLEBASH_SRC_GREP_S21_GREP_H_
