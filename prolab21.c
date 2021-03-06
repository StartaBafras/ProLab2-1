#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code_check.h"
#include "variable.h"
#include "loop.h"
#include "function.h"
#include "increase.h"


int main(void)
{

    int error = 0;
    
    error = move_and_compile();


    if (0 != error)
    {
        printf("Kod Hatalı Derlenemedi.");
        return 1;
    }

    printf("\n");

    system("time ./input");


    variable_s *v_root = malloc(sizeof(variable_s));
    loop_s *l_root = malloc(sizeof(loop_s));
    function_s *f_root = malloc(sizeof(function_s));

    char read_txt[Size][Size]; // dosya içeriği

    FILE *dosya = fopen("question.txt", "r");
    if (dosya == NULL)
    {
        printf("dosya açılamadı");
    }
    for (int k = 0; k < Size; k++) // dosyayı okur read_txt alır satır satır
    {

        for (int i = 0; i < Size; i++)
        {
            read_txt[k][i] = fgetc(dosya);
            if (read_txt[k][i] == '\n')
            {

                read_txt[k][i] = NULL;
                break;
            }
        }
    }

    find_variables(read_txt, v_root, f_root);
    find_for(read_txt, l_root);
    find_while(read_txt, l_root);
    connect_loop_and_variable(v_root, l_root);
    int result = find_recursive_in_struct(read_txt, f_root, v_root);
    if (result == 1)
    {
        find_size(v_root, Size, 0);
    }
    int recursive_amount = recursive_counter(f_root);
    if (recursive_amount == 0)
    {
        size_sum(v_root, f_root, 0);
    }
    else
    {

        size_sum(v_root, f_root, recursive_amount - 1);
    }
    int c = 0;
    for (int i = 0; i < 150; i++)
    {
        c = find_increase_case1(read_txt[i], strlen(read_txt[i]), i, v_root);
        c = find_increase_case2(read_txt[i], strlen(read_txt[i]), i, v_root);
    }

    

    loop_s *variable_loop_connect = l_root;

    while (1)
    {
        add_variable_in_loop(variable_loop_connect->condition, 150, v_root, variable_loop_connect);

        if (variable_loop_connect->next == NULL)
            break;
        else
            variable_loop_connect = variable_loop_connect->next;
    }

    find_max_complexity(f_root, l_root);

    add_loop_in_function(f_root,l_root);


    
}