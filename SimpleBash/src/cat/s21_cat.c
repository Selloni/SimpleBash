#include "s21_cat.h"

void init(flag *opt) {
    opt->fb = 0;
    opt->fn = 0;
    opt->fs = 0;
    opt->fe = 0;
    opt->ft = 0;
    opt->fv = 0;
}

int ckek_flag(int argc, char **argv, flag *opt) {
    size_t sym = 1;
    int stop_flag = 0;
    for (int mot = 1; argc > mot; mot++) {
        if (argv[mot][0] == '-' && argv[mot][1] != '-') {
            while (argv[mot][sym] != '\0') {
                if (argv[mot][sym] == 'b') {
                    opt->fb = 1;
                } else if (argv[mot][sym] == 'v') {
                    opt->fv = 1;
                } else if (argv[mot][sym] == 'n') {
                     opt->fn = 1;
                } else if (argv[mot][sym] == 's') {
                    opt->fs = 1;
                } else if (argv[mot][sym] == 'E') {
                    opt->fe = 1;
                } else if (argv[mot][sym] == 'T') {
                    opt->ft = 1;
                } else if (argv[mot][sym] == 'e') {
                    opt->fe = 1, opt->fv = 1;
                } else if (argv[mot][sym] == 't') {
                    opt->ft = 1;
                    opt->fv = 1;
                } else {
                    stop_flag++;
                    printf("cat: illegal option - %c\n usage: cat [-benstuv] [file ...]\n", argv[1][sym]);
                }
                if (opt->fb == 1 && opt->fn == 1) opt->fn = 0;
                sym++;
            }
        } else if (argv[mot][0] == '-' && argv[mot][1] == '-' && argv[mot][2] != '-') {
            if (strcmp(argv[mot], "--number-nonblank") == 0) {
                opt->fb = 1;
            } else if (strcmp(argv[mot], "--number") == 0) {
                opt->fn = 1;
            } else if (strcmp(argv[mot], "--squeeze-blank") == 0) {
                opt->fs = 1;
            } else {
                stop_flag = 1;
                printf("cat: illegal option -- -\nusage: cat [-benstuv] [file ...]\n");
            }
        }
    }
    return(stop_flag);
}

void read_text(char *file_name, flag *opt) {
    FILE *file;
    if ((file = fopen(file_name, "r")) == NULL) {
        printf("s21_cat: %s: No such file or directory\n", file_name);
    } else {
        int before = '\n', empty_str = 0, number = 1;
        int ch;
        while ((ch = getc(file)) != EOF) {
            if (opt->fs && ch == '\n' && before == '\n') {
                empty_str++;
            } else {
                empty_str = 0;
            }
            if (empty_str < 2) {
                if (before == '\n' && opt->fn) printf("%6d\t", number++);
                if (opt->fb && before =='\n' && ch != '\n') printf("%6d\t", number++);
                if (opt->fe && ch == '\n') putchar('$');
                if (opt->ft && ch == '\t') putchar('^'), ch = 'I';
                if (opt->fv || ch != '\n') {
                    if ((ch < 32 && ch > 10) || (ch < 9 && ch > 0)) putchar('^'), ch = ch + 64;
                    else if ( ch == 127) putchar('^'), ch = ch - 64;
                }
                putchar(ch);
            }
            before = ch;
        }
        fclose(file);
    }
}

int main(int argc, char **argv) {
    if (argc > 0) {
        flag opt;
        init(&opt);
        if (ckek_flag(argc, argv, &opt) == 0) {
            for (int i = 1; argc > i; i++) {
                if (argv[i][0] != '-') read_text(argv[i], &opt);
            }
        }
    }
    return(0);
}
