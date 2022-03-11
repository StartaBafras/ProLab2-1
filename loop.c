#include <stdio.h>
#include <stdlib.h>
#include "loop.h"
#include "variable.h"



/**
 * @brief Döngüye ait verileri bağlı listede boş olduğu kabul edilen yere yazar.
 * @param data Verilerin kapsüllendiği veri paketinin adresi
 * @param loops İçi boş kabul edilen bağlı liste üyesinin adresi.
 */ 
int write_loop_data(loop_s *data,loop_s *loops)
{
    loops->complexity = data->complexity;
    loops->dependent_variable = data->dependent_variable;
    loops->id = data->id;
    loops->kind = data->kind;
    loops->next = NULL;
    loops->start_end_line[0] = data->start_end_line[0];
    loops->start_end_line[1] = data->start_end_line[1];

    return 0;

}

/**
 * @brief Tespit edilen döngüyü döngülerin toplandığı bağlı listeye ekler.
 * @param data Verilerin kapsüllendiği veri paketinin adresi.
 * @param loops Döngüleri işaret eden kök işaretçisi.
 * 
 */
int add_loop(loop_s *data, loop_s *loops)
{
    if(loops->id == NULL)
    {
        data->id = 0;
        write_loop_data(data,loops);
        return 0;
    }


    for(;loops->next != NULL; loops = loops->next);
    data->id = loops->id+1;
    loops->next = malloc(sizeof(loop_s));
    loops = loops->next;
    write_loop_data(data,loops);

    return 0;

}