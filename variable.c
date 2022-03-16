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
    variable_p->id = data->id;
    strcpy(variable_p->kind, data->kind);
    variable_p->line = data->line;
    strcpy(variable_p->name,data->name);
    variable_p->increase_rate = NULL;
    variable_p->next = NULL;
    
}

/**
 * @brief Tespit edilen değişkeni değişkenlerin toplandığı bağlı listeye ekler.
 * @param data Verilerin kapsüllendiği veri paketinin adresi.
 * @param variable_p Verileri işaret eden kök işaretçisi.
 * 
 */
int add_variable_data(variable_s *data, variable_s *variable_p)
{
    if(variable_p->line == NULL)
    {
        data->id = 0;
        write_variable_data(data,variable_p);
        return 0;
    }
     while (variable_p->next != NULL)
        variable_p = variable_p->next;
    data->id = variable_p->id + 1;
    variable_s *variable_p_new = malloc(sizeof(variable_s));
    variable_p->next = variable_p_new;
    write_variable_data(data, variable_p->next);

}

/**
 * @brief Değişkenler bağlı listesine kayıtlı olan bir değişkeni 
 * bağlı listede arar ve adresini gönderir.
 * 
 * @param variable Değişkenin ismi.
 * @param variable_line Değişkenin bulunduğu satırç
 * @param root Değişkenleri tutan bağlı listenin kök adresi.
 * 
 * @return variable_s türünden adres.
 */
variable_s* search_variable(char *variable,int varibale_line ,variable_s *root)
{
    
    while(1)
    {
        if( 0 == strcmp(variable,root->name) && varibale_line >= root->line)
        {
            printf("%d\n",root->line);
            return root;
        }

        if(root->next != NULL) root = root->next;
        else break;
    }

    return NULL;

}

/**
 *@brief variable struct'ında türlere bakıp boyutunu ekler
 *@param v_root variable struct'ın root'unu alır
 */
void find_size(variable_s *v_root)
{
    char variables[c_Size_s][c_Size_s] = {"pointer", "int", "double", "char", "float", "long", "short", "matrix", "dizi"}; // türler
    char sizes[c_Size_s][c_Size_s] = {" +8", " +4", " +8", " +1", " +4", " +4", " +2", "nn", "n"};

    // memset(v_root->size, NULL, c_Size_l);
    if (v_root != NULL)
    {
        for (int i = 0; i < 9; i++)
        {
            if (i == 2)
            {
                continue;
            }
            if (NULL != strstr(v_root->kind, variables[2])) // pointer
            {
                strcpy(v_root->size, sizes[2]);
            }
            else if (NULL != strstr(v_root->kind, variables[i]))
            {
                strcat(v_root->size, sizes[i]);
            }
        }
    }
    //printf("%s --%s\n", v_root->size, v_root->kind);
    if (v_root->next != NULL)
    {
        find_size(v_root->next);
    }
}
/**
 * @brief aynı satırdaki değişkenleri bulur ve ekler.
 * @param name_var değişken isimlerini alır.
 * @param var_line satırlarını alır.
 * @param var_kind türlerini alır.
 * @param root rootu alır.
 */
int find_same_line_var(char name_var[50], int var_line, char var_kind[c_Size_s], variable_s *root)
{

    char *token = strtok(name_var, ",");
    while (token != NULL)
    {
        variable_s data;
        // printf(" %s %s %d\n", token, var_kind, var_line);
        memset(data.kind, NULL, strlen(data.kind));
        strcat(data.kind, var_kind);
        data.line = var_line;
        // data.id = 0;
        memset(data.name, NULL, strlen(data.name));
        strcat(data.name, token);
        add_variable_data(&data, root);
        data.line = NULL;
        token = strtok(NULL, ",");
    }
    return 0;
}





/**
 * @brief  dosyanın içindeki stringi alır.
 * değişken ve fonksiyonları bulur ve struct'a ekler.
 * @param text string dizisi
 *
 *
 *
 */
