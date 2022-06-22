#include "s21_grep.h"

int main(int argc, char **argv) {
    parametr bufpar[BUFSIZ];
    flags opt = {0};
    if (pars_flag(argc, argv, &opt) == 0) {
        find_options(argc, argv, &opt, bufpar);
    }
}

void find_options(int argc, char **argv, flags *opt, parametr *bufpar) {
    int i = 1;
    if (argv[i][0] != '-') {
        strcpy(bufpar[0].name, argv[i]);
        if (argc > 3) opt->severalf = 1;
        while (i != argc - 1) {
            i++;
            // printf("not flag|%s--%s--%d--int %d|..\n", bufpar->name, argv[i], argc, i);////
            read_file(argv[i], opt, bufpar);
        }
    }
    if (argv[i][0] == '-') {
        i = i + 1;
        flag_f(argv[i], opt, bufpar);
        strcpy(bufpar[0].name, argv[i]);
        if (argc > 4) {
            opt->severalf = 1;
        }
        while (i != argc - 1) {
            i++;
            // printf("have flag|%s--%s--%d--int %d|..\n", bufpar->name, argv[i], argc, i);////
            read_file(argv[i], opt, bufpar);
        }
    }
}

// void flag_0 (char *str, flags *opt, parametr *bufpar) {
    //     if (opt->fo) {
    //         regex_t regex;
    //         regmatch_t math[1];
    //         for (int l = 0; l < fl._count; l++) {
    //             regcomp(&regex, bufpar[0].name, (opt->fi) ? REG_ICASE : 0);
    //             while ((regexec(&regex, str, 1, math, 0)) == 0) {
    //             for (int x = (int)math[0].rm_so; x < (int)math[0].rm_eo; x++) {
    //                 printf("%c", str[x]);
    //             }
    //             str += (int)math[0].rm_eo;  ////////
    //             printf("\n");
    //             regfree(&regex);
    //             }
    //         }
    // }
// }

void read_file(char *name_file, flags *opt, parametr *bufpar) {
    FILE *file;
    if ((file = (fopen(name_file, "r"))) == NULL) {
        if (!opt->fs) printf("s21_grep: %s No such file or directory", name_file);
    }
    if (opt->ff != 2) {
        int ns = 1;
        char str[BUFSIZ] = {'\0'};
        while (fgets(str, BUFSIZ - 1, file) != NULL) {
            int success, regflag = 0;
            regex_t regex;  //  регулярные выражение
            if (opt->fi) regflag = REG_ICASE;
            if (opt->ff == 0) {
                regcomp(&regex, bufpar[0].name, regflag);  //  компилируем рег выражения
                success = regexec(&regex, str, 0, NULL, 0);  // return0нашел
            } else if (opt->ff == 1) {
                for (int i = 1; i < opt->line_in_f; i++) {
                    regcomp(&regex, bufpar[i].name, regflag);
                    // printf("%s",str);///////
                    success = regexec(&regex, str, 0, NULL, 0);
                    // printf("%d.", ns);
                    if (!success) break;
                    // printf("%s\n", bufpar[i].name);//////
                }
                // printf("%d.", ns);//////////
            }
            regfree(&regex);
            if (!success) {
                opt->count_tru++;
                if (!opt->fl && !opt->fv && !opt->fc) {
                    // if(opt->flag_0 == 0) {//  ограничение на вход в  if когда есть флаги
                    print_file(name_file, opt);
                    flag_n(ns, opt);
                    printf("%s", str);
                    // }
                }
            }
            if (success) {
                opt->count_false++;
                if ((opt->fv) && (!opt->fc)) {
                    print_file(name_file, opt);
                    flag_n(ns, opt);
                    if (!opt->fl) {
                        printf("%s", str);
                    } else if (opt->fv) {
                        printf("%s\n", name_file);
                        break;
                    }
                }
            }
            ns++;  // count lines
        }
        if (opt->fc) {
            if (opt->fv) {
                print_file(name_file, opt);
                printf("%d\n", opt->count_false);
            } else {
                print_file(name_file, opt);
                printf("%d\n", opt->count_tru);
            }
        }
        if (opt->fl) {
            if (!opt->fv && opt->count_tru != 0) {
                printf("%s\n", name_file);
            } else if (opt->fv && opt->count_false != 0) {
                printf("%s\n", name_file);
            }
        }
        opt->count_tru = 0;
        opt->count_false = 0;
    }
    fclose(file);
}

void flag_f(char *name_file, flags *opt, parametr *bufpar) {
    if (opt->ff) {
        opt->line_in_f = 1;
        FILE *file;
        if ((file = fopen(name_file, "r")) == NULL) {
            printf("s21_grep: %s No such file or directory", name_file);
            opt->ff = 2;
        } else {
            char str[BUFSIZ] = {'\0'};
            while ((fgets(str, BUFSIZ - 1, file)) != NULL) {
                int len;
                // printf("%s::%d\n", "строки", opt->line_in_f); ///
                len = strlen(str) - 1;
                if (len == 0) len++;
                strncpy(bufpar[opt->line_in_f].name, str, len);
                // printf("%s", bufpar[opt->line_in_f].name);//////
                opt->line_in_f++;
            }
            fclose(file);
        }
    }
}

void print_file(char *name_file, flags *opt) {
    if (opt->severalf == 1 && !opt->fh && !opt->fl) {
        printf("%s:", name_file);
    }
}

void flag_n(int ns, flags *opt) {
    if (opt->fn) {
        printf("%d:", ns);
    }
}

int pars_flag(int argc, char **argv, flags *opt) {
    int stop_flag = 0;
    int wor = 1;
    while (wor < argc) {
        if (argv[wor][0] == '-') {
            for (int sym = 1; argv[wor][sym] != '\0'; sym++) {
                if (stop_flag == 0) {
                    if (argv[wor][sym] == 'e') {
                        opt->fe = 1;
                    } else if (argv[wor][sym] == 'i') {
                        opt->fi = 1;
                    } else if (argv[wor][sym] == 'v') {
                        opt->fv = 1;
                    } else if (argv[wor][sym] == 'c') {
                        opt->fc = 1;
                    } else if (argv[wor][sym] == 'l') {
                        opt->fl = 1;
                    } else if (argv[wor][sym] == 'n') {
                        opt->fn = 1;
                    } else if (argv[wor][sym] == 'h') {
                        opt->fh = 1;
                    } else if (argv[wor][sym] == 's') {
                        opt->fs = 1;
                    } else if (argv[wor][sym] == 'f') {
                        opt->ff = 1;
                    } else if (argv[wor][sym] == 'o') {
                        opt->fo = 1;
                    } else {
                        stop_flag = 1;
                        printf("error");
                    }
                }
            }
            // opt->flag_0 = opt->fe+opt->fi+opt->fv+opt->fc+opt->fl+opt->fh+
            // opt->fn+opt->fs+opt->ff+opt->fo;  //  нкжно придумать что то по лучше
        }
        wor++;
    }
    return stop_flag;
}
