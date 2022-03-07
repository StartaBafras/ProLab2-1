#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variable.h"

/**
 * @brief Değişkenlere ait verileri bağlı listede boş olduğu kabul edilen yere yazar.
 * @param data Verilerin kapsüllendiği veri paketinin adresi
 * @param variable_p İçi boş kabul edilen bağlı liste üyesinin adresi.
 */ 
int write_variable_data(variable_s *data, variable_s *variable_p)
{
    variable_p->kind = data->kind;
    variable_p->line = data->line;
    strcpy(variable_p->name,data->name);
    variable_p->increase_rate = NULL;
    
}

/**
 * @brief Tespit edilen değişkeni değişkenlerin toplandığı bağlı listeye ekler.
 * @param data Verilerin kapsüllendiği veri paketinin adresi.
 * @param variable_p Verileri işaret eden kök işaretçisi.
 * 
 */
int add_variable_data(variable_s *data, variable_s *variable_p)
{
    if(variable_p->id == NULL)
    {
        data->id = 0;
        write_variable_data(data,variable_p);
        return 0;
    }

    for(;variable_p->next != NULL; variable_p = variable_p->next);
    data->id = variable_p->id+1;
    write_variable_data(data,variable_p);

}