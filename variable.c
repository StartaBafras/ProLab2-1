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
        data->id = 1;
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
 * @brief Değişken bağlı listesinde istenen değişkeni isminden bulur ve tutulduğu adresi döndürür.
 * @param variable Değişkenin ismi
 * @param variable_p Değişen bağlı listesini işaret eden kök işaretçisi.
 * 
 * @return  Değişkenin bağlı listedeki adresi
 */
variable_s* search_variable(char *variable, variable_s *variable_p)
{
    while(1)
    {
        if(strcmp(variable_p->name,variable))
        {
            return variable_p;
        }
        else
        {
            if(variable_p->next != NULL)
            {
                variable_p = variable_p->next;
            }
            else
            {
                return NULL;
            }
        }
    }

}

/**
 *@brief variable struct'ında türlere bakıp boyutunu ekler
 *@param v_root variable struct'ın root'unu alır
 */
void find_size(variable_s *v_root)
{
    char variables[c_Size_s][c_Size_s] = {"pointer", "int", "double", "char", "float", "long", "short", "matrix", "dizi"}; // türler
    char sizes[c_Size_s][c_Size_s] = {" +8", " +4", " +8", " +1", " +4", " +4", " +2", "n2", "n"};

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
 * @brief Değişkenler bağlı listesine kayıtlı olan bir değişkeni 
 * bağlı listede arar ve adresini gönderir.
 * 
 * @param variable Değişkenin ismi.
 * @param root Değişkenleri tutan bağlı listenin kök adresi.
 * 
 * @return variable_s türünden adres.
 */
variable_s* find_variables_by_name(char *variable ,variable_s *root)
{
    
    while(1)
    {
        if( 0 == strcmp(variable,root->name))
        {
            return root;
        }

        if(root->next != NULL) root = root->next;
        else break;
    }

    return NULL;

}


/**
 * @brief  dosyanın içindeki stringi alır.
 * değişken ve fonksiyonları bulur ve struct'a ekler.
 * @param text string dizisi
 *
 *
 *
 */
int find_variables(char text[][Size], variable_s *root)

{
    

    char variables[7][c_Size_s] = {"int ", "double ", "char ", "float ", "void ", "long ", "short "}; // türler
    int func_line_end = NULL;                                                                   // fonsiyon bitiş
    char *p_kind;                                                                               // türün yerini belli eden p_kind
    char *p_name;                                                                               // ismin yerini belli eder
    char name_temp[Size];                                                                        // isimi geçiçi olarak tutar
    //char name_temp2[c_Size_l];                                                                        // ismi geçiçi olarak tutuar
    char var_name[c_Size_l];                                                                          // ismi tutar
    char var_kind[c_Size_l];                                                                          // türü tutar
    int var_line = -1;                                                                          // türün satırını tutar
    for (int i = 0; i < Size; i++)                                                               // satırları gezer
    {
        p_kind = text[i];
        for (int j = 0; j < 7; j++) // türleri gezer
        {
            if (NULL != strstr(p_kind, variables[j]))
            {
                p_kind = strstr(p_kind, variables[j]); // yerini bulur pointera atar
                var_line = i;
                memset(var_kind, NULL, c_Size_l);                     // içini siler
                memset(var_name, NULL, c_Size_l);                     // içini temizler
                memcpy(var_kind, p_kind, strlen(variables[j])); // türü atar
                p_kind += strlen(variables[j]);                 // türünün sonunu işaret eder
                memset(name_temp, NULL,Size);     // içini boşaltır
                strcat(name_temp, p_kind);                      // geçiçi değişkene atar

                for (int k = 0; k < strlen(name_temp); k++) // satırın içini gezer

                {
                    if ((')' == name_temp[k]) || (';' == name_temp[k])) // eğer bunlardan biri varsa isim almayı bırakır
                    {
                        break;
                    }
                    if (('A' <= name_temp[k]) || ('[' == name_temp[k]) || ('_' == name_temp[k]) || ('(' == name_temp[k]) || ('*' == name_temp[k]) || (',' == name_temp[k])) // isme dahil eder
                    {

                        var_name[k] = name_temp[k];
                    }
                    else
                    {
                        var_name[k] = ' ';
                    }
                }
                for (int k = 0; k < strlen(var_name); k++) // ismin içinde gezer
                {
                    if ((('[' == var_name[k]) && ('[' == var_name[k + 3])) || (('[' == var_name[k]) && ('[' == var_name[k + 2])))
                    {
                        strcat(var_kind, "matrix");
                        var_name[k] = NULL;
                        break;
                    }
                    else if (('[' == var_name[k]) && ('[' != var_name[k + 3]))
                    {
                        strcat(var_kind, "dizi");
                        var_name[k] = NULL;
                        break;
                    }

                    if (('(' == var_name[k])) // eğer isimde ()varsa fonksiyon olduğu için değişken değildir siler ve fonksiyon  olarak ekler
                    {
                        var_name[k] = NULL; // son elemaı siler
                        func_line_end = 0;
                        func_line_end = find_line_end(var_line, text);
                        strcat(var_kind, "func");
                     //   printf("func;%s --%s--%d--%d\n", var_kind, var_name, var_line, func_line_end);
                        memset(var_name, NULL, c_Size_l);
                        memset(var_kind, NULL,c_Size_l);
                        var_line = -1;
                    }
                }
                if (NULL != strstr(var_name, "*"))
                {
                    var_name[0] = ' ';
                    strcat(var_kind, "pointer");
                }
                if ((var_line != -1) && (NULL != var_name[0])) // bulduysa struct'a ekle
                {

                    if (NULL != strstr(var_name, ","))
                    {
                        find_same_line_var(var_name, var_line, var_kind, root);

                        memset(var_name, NULL, c_Size_l);

                        /* var_name[strlen(var_name)] = ',';
                         for (int l = 0; l < strlen(var_name); l++) // bir değişkende türüne birden fazla tanımlama var mı diye bakar
                         {
                             if (',' == var_name[l])
                             {
                                 memset(name_temp2, NULL, strlen(name_temp2));

                                 strncat(name_temp2, var_name, l);
                                 printf("%s --%s--%d\n", var_kind, name_temp2, var_line);
                                 strcat(data.name, name_temp2);
                                 add_variable_data(&data, root);
                                 p_name = strchr(var_name, ',');
                                 memset(var_name, NULL, l);
                                 strcat(var_name, p_name + 1);
                                 l = -1;
                                 memset(data.name, NULL, strlen(data.name));
                             }
                         }*/
                    }
                    else
                    {
                        variable_s data; // struct'a eklenir
                        memset(data.kind, NULL, strlen(data.kind));
                        strcat(data.kind, var_kind);
                        data.line = var_line;
                        // data.id = 0;
                        strcat(data.name, var_name);
                        add_variable_data(&data, root);
                      //  printf("%s --%s--%d\n", var_kind, var_name, var_line);
                        memset(data.name, NULL, strlen(data.name));
                        data.line = NULL;
                    }
                }
            }

            if (NULL != strstr(p_kind, variables[j])) // aynı değişken türünden  yine  var mı bakılır
            {
                j = j - 1;
            }
        }
    }

    return 0;
}
