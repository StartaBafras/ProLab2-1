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


#endif