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

typedef struct veriable_s_pointer
{
    variable_s *variable; 
    variable_s *next;
}veriable_s_pointer;

int write_variable_data(variable_s *data, variable_s *variable_p);

int add_variable_data(variable_s *data, variable_s *variable_p);

variable_s* search_variable(char *variable, variable_s *variable_p);


int find_same_line_var(char name_var[50], int var_line, char var_kind[c_Size_s], variable_s *root); // aynı satırdaki değişenleri bulur

int find_variables(char text[][Size], variable_s *root); // değişken türünü ismini yerini bulur

void find_size(variable_s *v_root);

variable_s* find_variables_by_name(char *variable ,variable_s *root);


#endif