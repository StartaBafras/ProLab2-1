#ifndef __FUNCTİON_H
#define __FUNCTİON_H

#include "loop.h"
#include "variable.h"

typedef struct function_s
{
    char name[20];
    int start_end_line[2];
    loop_s_pointer *loops_inside;
    struct function_s_pointer *function_inside;
    int complexity;
    int amount_call;
    int call_line;
    struct function_s *next;

}function_s;

typedef struct function_s_pointer
{
    function_s *function; 
    function_s *next;

}function_s_pointer;

loop_s* search_loop(int begin_line, loop_s *root);

int add_loop_in_function(function_s *function_struct, int loop_begin_line, loop_s *root);

int add_function(function_s *data, function_s *function_root);
int write_function_data(function_s *data, function_s *function_root);

int find_variables(char text[][Size], variable_s *root,function_s *f_root); // değişken türünü ismini yerini bulur
#endif