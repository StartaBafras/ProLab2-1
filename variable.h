#ifndef __VARİABLE_H
#define __VARİABLE_H
#define Size 150// satır ve sutun sayısı
#define c_Size_s 10//small
#define c_Size_l 30//large

typedef struct variable_s
{
    int id;
    char name[10];
    char kind[30];
    int line;
    char size[20];
    int increase_rate;
    struct variable_s *next;

}variable_s;

typedef struct variable_s_pointer
{
    variable_s *variable; 
    struct variable_s_pointer *next;
}variable_s_pointer;

int write_variable_data(variable_s *data, variable_s *variable_p);

int add_variable_data(variable_s *data, variable_s *variable_p);

variable_s* search_variable(char *variable,int varibale_line ,variable_s *root);


int find_same_line_var(char name_var[50], int var_line, char var_kind[c_Size_s], variable_s *root); // aynı satırdaki değişenleri bulur


void find_size(variable_s *v_root,int start_line,int end_line);



#endif