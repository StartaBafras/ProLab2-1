#ifndef __LOOP_H
#define __LOOP_H


#include "variable.h"

typedef struct loop_s
{
    int id;
    int kind;
    int start_end_line[2];
    veriable_s_pointer dependent_variable;
    int complexity;
    struct loop_s *next;

}loop_s;

typedef struct loop_s_pointer
{
    loop_s *loop; 
    loop_s *next;
}loop_s_pointer;




int add_loop(loop_s *data, loop_s *loops);


int write_loop_data(loop_s *data,loop_s *loops);

#endif