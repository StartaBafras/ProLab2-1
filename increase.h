#ifndef __INCREASE_H
#define __INCREASE_H

#include "variable.h"

#define LINEER_POSITIVE 1
#define LINEER_NEGATIVE 2
#define EXPONENTIAL_POSITIVE 3
#define EXPONENTIAL_NEGATIVE 4
#define LOGARITMIC_POSİTİVE 5
#define LOGARITMIC_NEGATIVE 6

#define MAX_SENTENCE_LENGTH 30

int find_char(char *message, char c,int size);

int find_increase_case1(char *message, int size, int line,variable_s *v_root);

int find_increase_case2(char *message, int size,int line,variable_s *v_root);

int sentence_divider(char *message_p[],char *message, int word);

int find_complex_increase(char *message, int size, int line_number, variable_s *root);

int clear_comma(char *message,int size);

char* detect_variable(char *message, int location, int size);


#endif
