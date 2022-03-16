#ifndef __LOOP_H
#define __LOOP_H


#include "variable.h"
#define v_FOR 0x10
#define V_WHILE 0x11
#define V_WHILE_DO 0x16
#define Size 150// satır ve sutun sayısı
#define c_Size_s 10//small
#define c_Size_l 30//large
typedef struct loop_s
{
    int id;
    int kind;
    int start_end_line[2];
    variable_s_pointer *dependent_variable;
    int complexity;
    char condition[10];
    struct loop_s *next;

}loop_s;

typedef struct loop_s_pointer
{
    loop_s *loop; 
    loop_s *next;
}loop_s_pointer;




int add_loop(loop_s *data, loop_s *loops);


int write_loop_data(loop_s *data,loop_s *loops);


int find_for(char text[][Size], loop_s *l_root); // for yerini ve artış oranını bulur


int find_line_end(int line_start, char text[][Size]); // iç içe for bulur

int find_while(char text[][Size], loop_s *l_root);

int find_do(char text[][Size], int end_while_line);

void connect_loop_and_variable(variable_s *v_root, loop_s *l_root);

int research_variable_connect_loop_same_line(variable_s *v_root, int loop_start_line);

int research_variable_connect_loop_different_line(variable_s *v_root, loop_s *l_root);

int find_line_end(int line_start, char text[][Size]); // iç içe for bulur


#endif