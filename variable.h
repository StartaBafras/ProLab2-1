#ifndef __VARİABLE_H
#define __VARİABLE_H

typedef struct variable_s
{
    int id;
    char name[10];
    int kind;
    int line;
    int increase_rate;
    struct variable_s *next;

}variable_s;

typedef struct veriable_s_pointer
{
    variable_s *variable; 
    variable_s *next;
}veriable_s_pointer;



#endif