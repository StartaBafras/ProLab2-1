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

int write_variable_data(variable_s *data, variable_s *variable_p);

int add_variable_data(variable_s *data, variable_s *variable_p);

variable_s* search_variable(char *variable, variable_s *variable_p);


#endif