#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"

int write_function_data(function_s *data, function_s *function_root)
{
    function_root->amount_call = data->amount_call;
    function_root->call_line = data->call_line;
    function_root->complexity = data->complexity;
    function_root->function_inside = data->function_inside;
    function_root->loops_inside = data->loops_inside;
    strcpy(function_root->name, data->name);
    function_root->start_end_line[0] = data->start_end_line[0];
    function_root->start_end_line[1] = data->start_end_line[1];
    function_root->next=NULL;
    memset( function_root->size,NULL,20);
    // printf("%s--%d--%d\n",data->name,data->start_end_line[0],data->start_end_line[1]);
}

int add_function(function_s *data, function_s *function_root)
{
    if (function_root->start_end_line[0] == NULL)
    {
        write_function_data(data, function_root);
        return 0;
    }

    while (function_root->next != NULL)
        function_root = function_root->next;

    function_s *function_p_new = malloc(sizeof(function_s));

    function_root->next = function_p_new;
    write_function_data(data, function_root->next);
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

    if (function_struct->loops_inside->loop == NULL)
    {
        function_struct->loops_inside->loop = search_loop(loop_begin_line, root);
        function_struct->loops_inside->next = NULL;
        return 0;
    }

    loop_s_pointer *p = function_struct->loops_inside;

    while (p->next != NULL)
        p = p->next;

    loop_s_pointer *new = malloc(sizeof(loop_s_pointer));
    new->loop = search_loop(loop_begin_line, root);
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
loop_s *search_loop(int begin_line, loop_s *root)
{
    while (1)
    {
        if (root->start_end_line[0] == begin_line)
        {
            return root;
        }

        if (root->next != NULL)
            root = root->next;
        else
            break;
    }

    return NULL;
}

int find_variables(char text[][Size], variable_s *root, function_s *f_root)

{

    char variables[7][c_Size_s] = {"int ", "double ", "char ", "float ", "void ", "long ", "short "}; // türler
    int func_line_end = NULL;                                                                         // fonsiyon bitiş
    char *p_kind;                                                                                     // türün yerini belli eden p_kind
    char *p_name;                                                                                     // ismin yerini belli eder
    char name_temp[Size];                                                                             // isimi geçiçi olarak tutar
    // char name_temp2[c_Size_l];                                                                        // ismi geçiçi olarak tutuar
    char var_name[c_Size_l];       // ismi tutar
    char var_kind[c_Size_l];       // türü tutar
    int var_line = -1;             // türün satırını tutar
    for (int i = 0; i < Size; i++) // satırları gezer
    {
        p_kind = text[i];
        for (int j = 0; j < 7; j++) // türleri gezer
        {
            if (NULL != strstr(p_kind, variables[j]))
            {
                p_kind = strstr(p_kind, variables[j]); // yerini bulur pointera atar
                var_line = i;
                memset(var_kind, NULL, c_Size_l);               // içini siler
                memset(var_name, NULL, c_Size_l);               // içini temizler
                memcpy(var_kind, p_kind, strlen(variables[j])); // türü atar
                p_kind += strlen(variables[j]);                 // türünün sonunu işaret eder
                memset(name_temp, NULL, Size);                  // içini boşaltır
                strcat(name_temp, p_kind);                      // geçiçi değişkene atar
                int l = 0;
                for (int k = 0; k < strlen(name_temp); k++) // satırın içini gezer

                {
                    if ((')' == name_temp[k]) || (';' == name_temp[k])) // eğer bunlardan biri varsa isim almayı bırakır
                    {
                        break;
                    }
                    if (('A' <= name_temp[k]) || ('[' == name_temp[k]) || ('_' == name_temp[k]) || ('(' == name_temp[k]) || ('*' == name_temp[k]) || (',' == name_temp[k])) // isme dahil eder
                    {

                        var_name[l] = name_temp[k];
                        l++;
                    }
                    /* else
                     {
                         var_name[k] = ' ';
                     }*/
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
                        function_s data;
                        data.start_end_line[0] = var_line;
                        data.start_end_line[1] = func_line_end;
                        memset(data.name, NULL, 20);
                        strcat(data.name, var_name);
                        data.amount_call = NULL;
                        data.call_line = NULL;
                        data.complexity = NULL;
                        add_function(&data, f_root);

                        //   printf("func;%s --%s--%d--%d\n", var_kind, var_name, var_line, func_line_end);
                        memset(var_name, NULL, c_Size_l);
                        memset(var_kind, NULL, c_Size_l);
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
                        memset(data.name, NULL, strlen(data.name));
                        strcat(data.name, var_name);
                        add_variable_data(&data, root);
                        //  printf("%s --%s--%d\n", var_kind, var_name, var_line);
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

/**
 *@brief fonksiyon struct'ını alır ve içinde gezinir.
 * amaç rekursif olan fonksiyonları tespit etmek.
 *
 *@param text Dosyadan okunan read_txt'i alır.
 *
 * @param f_root fonksiyon struct'ın rootunu alır
 * */

void find_recursive_in_struct(char text[][Size], function_s *f_root) // struct'ta fonksiyonları gezer
{

    if (f_root != NULL)
    {
        find_recursive_in_text(text, f_root); // fonkisyon için rekursif bulan fonksiyon çağırılır
    }

    if (f_root->next != NULL)
    {
        find_recursive_in_struct(text, f_root->next); // sonraki fonksiyon var mı bakılır
    }
}

/**
 *@brief Fonksiyonun başlangıç ve bitiş satırını alır ve  text içinde gezinir.
 * Amaç rekursif olan fonksiyonları tespit etmek.
 * Fonsiyonun başlangıç ve bitiş yerleri arasında gezer.
 * Aynı satırda birden fazla varsa amount değişkenini artırır
 *
 *
 *@param text Dosyadan okunan read_txt'i alır.
 *
 * @param f_root Fonksiyon struct'ın rootunu alır
 *
 */
int find_recursive_in_text(char text[][Size], function_s *f_root)
{
    char *p_text;
    int amount_call_func = 0;
    int call_line_func = 0;
    int is_call_same_line = 1; // aynı satırda çağrılmış mı
    for (int i = f_root->start_end_line[0] + 1; i < f_root->start_end_line[1]; i++)
    {
        if (is_call_same_line == 1) // aynı satırda çarğılmışsa satırı kaybetmemek için
        {
            p_text = text[i];
        }
        if (NULL != strstr(p_text, f_root->name))
        {
            call_line_func = i;
            if (is_call_same_line == 1)
            {
                amount_call_func = 1;
            }
            p_text = strstr(p_text, f_root->name);
            p_text += strlen(f_root->name);
            if (NULL != strstr(p_text, f_root->name)) // aynı satırda tekrar çağrılmış  mı
            {
                amount_call_func++;     //çağrılma miktarı artar
                i--;                    // döngü tekrarlanır
                is_call_same_line = -1; // aynı satırda tekrar çağrılmıştır
            }
            else // aynı satırda yoksa
            {
                is_call_same_line = 1;
            }
        }
    }

    f_root->amount_call = amount_call_func; // strucağa verileri aktarır
    f_root->call_line = call_line_func;
    if (amount_call_func != 0)//eğer sıfırdan farklı ise rekürsiftir
    {
        find_size_function(amount_call_func, f_root);
    }
}


/**
 * @brief Fonksiyonun çağrılma miktarını alır ve fonsiyonun size'na
 *  çağrılma miktarı kadar n kopyalar bu n yer karmaşıklığını temsil eder.
 * 
 * @param amount_call_func Fonksiyonun çağrılma miktarını alır.
 * 
 * @param f_root Fonsiyon struct'ın kökünü alır.
 */
void find_size_function(int amount_call_func, function_s *f_root)
{
    memset(f_root->size, NULL, 20);
    for (int i = 0; i < amount_call_func; i++)
    {
        strcat(f_root->size, "n");
    }
}