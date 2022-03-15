#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include <string.h>


int write_function_data(function_s *data, function_s *function_root)
{
    function_root->amount_call = data->amount_call;
    function_root->call_line = data->call_line;
    function_root->complexity = data->complexity;
    function_root->function_inside = data->function_inside;
    function_root->loops_inside = data->loops_inside;
    strcpy(function_root->name,data->name);
    function_root->start_end_line[0] = data->start_end_line[0];
    function_root->start_end_line[1] = data->start_end_line[1];
}   


int add_function(function_s *data, function_s *function_root)
{
    if(function_root->start_end_line[0] == NULL)
    {
        write_variable_data(data,function_root);
        return 0;
    }


     while (function_root->next != NULL)
        function_root = function_root->next;

    
    function_s *function_p_new = malloc(sizeof(function_s));

    function_root->next = function_p_new;
    write_variable_data(data, function_root->next);
}


/**
 * @brief Fonksiyonun içindeki döngüyü fonksiyona bağlamaya yarar.
 * 
 * @param function_struct Döngünün ekleneceği fonksiyonu işaret eden işaretçi.
 * @param loop_begin_line Eklenecek döngünün başlangıç satırı.
 * @param root Döngü bağlı listesini işaret eden kök işaretçisi.
 */
int add_loop_in_function(function_s *function_struct, int loop_begin_line, loop_s *root)
{

    if(function_struct->loops_inside->loop == NULL)
    {
        function_struct->loops_inside->loop = search_loop(loop_begin_line,root);
        function_struct->loops_inside->next = NULL;
        return 0;
    }
    
    loop_s_pointer *p = function_struct->loops_inside;

    while (p->next != NULL) p = p->next;

    loop_s_pointer* new = malloc(sizeof(loop_s_pointer));
    new->loop = search_loop(loop_begin_line,root);
    new->next = NULL;
    p->next = new;

    return 0;

}

/**
 * @brief Döngü bağlı listesinde aranan döngüyü bulup adresini döndürür.
 * 
 * @param begin_line Aranan döngünün başladığı satır.
 * @param root Döngü bağlı listesini işaret eden kök işaretçisi.
 * 
 * @return Döngü strtuct türünden adres.
 */
loop_s* search_loop(int begin_line, loop_s *root)
{
    while(1)
    {
        if( root->start_end_line[0] == begin_line)
        {
            return root;
        }

        if(root->next != NULL) root = root->next;
        else break;
    }

    return NULL;
}