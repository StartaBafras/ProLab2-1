#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"

int write_function_data(function_s *data, function_s *function_root)
{
    function_root->amount_call = data->amount_call;
    function_root->call_line = data->call_line;
    strcat(function_root->complexity, data->complexity);
    function_root->function_inside = data->function_inside;
    function_root->loops_inside = data->loops_inside;
    strcpy(function_root->name, data->name);
    function_root->start_end_line[0] = data->start_end_line[0];
    function_root->start_end_line[1] = data->start_end_line[1];
    function_root->next = NULL;
    memset(function_root->size, NULL, 20);
    memset(function_root->complexity, NULL, c_Size_s);

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
int add_loop_in_function(function_s *f_root, loop_s *l_root)
{
    loop_s *iter = l_root;
    loop_s_pointer *l_p = f_root->loops_inside;
    while(1)
    {
        while (1)
        {
            if(f_root->start_end_line[0] <= iter->start_end_line[0] && f_root->start_end_line[1] >= iter->start_end_line[1])
            {
                if(f_root->loops_inside->loop == NULL)
                {
                    f_root->loops_inside->loop = iter;
                }
                else
                {
                    while (l_p->next != NULL)
                    {
                        l_p = l_p->next;
                    }
                    
                    loop_s_pointer *new = malloc(sizeof(loop_s_pointer));
                    new->loop = iter;
                    new->next = NULL;
                    l_p->next = new;
                }
            }
            if(iter->next == NULL) break;
            iter = iter->next;
            
        }

        if(f_root->next == NULL) break;
        f_root = f_root->next;
    }
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
                        memset(data.complexity, NULL, c_Size_s);
                        memset(data.size, NULL, 20);
                        data.loops_inside = malloc(sizeof(loop_s_pointer));
                        data.loops_inside->next = NULL;
                        data.loops_inside->loop = NULL;
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
                        memset(data.size, NULL, 20);
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
int find_recursive_in_struct(char text[][Size], function_s *f_root, variable_s *v_root) // struct'ta fonksiyonları gezer
{

    int is_control_true = 1;
    int is_control_false = 1;

    if (f_root != NULL)
    {
        is_control_true = find_recursive_in_text(text, f_root, v_root); // fonkisyon için rekursif bulan fonksiyon çağırılır
    }

    if (f_root->next != NULL)
    {
        is_control_false = find_recursive_in_struct(text, f_root->next, v_root); // sonraki fonksiyon var mı bakılır
    }

    return is_control_true * is_control_false;
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
int find_recursive_in_text(char text[][Size], function_s *f_root, variable_s *v_root)
{
    char *p_text;
    int amount_call_func = 0;
    int call_line_func = 0;
    int is_call_same_line = 1;      // aynı satırda çağrılmış mı
    int is_call_find_size_func = 1; // fonkiyonu birden fazla çağrımamak için
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
    if (amount_call_func != 0) // eğer sıfırdan farklı ise rekürsiftir
    {

        find_size_function(f_root);
        find_size(v_root, f_root->start_end_line[0], f_root->start_end_line[1]);
        return 0;
    }
    return 1;
}

/**
 * @brief Fonksiyonunsize'na n kopyalar bu n yer karmaşıklığını temsil eder.
 *
 *
 * @param f_root Fonsiyon struct'ın kökünü alır.
 */
void find_size_function(function_s *f_root)
{
    memset(f_root->size, NULL, 20);
    for (int i = 0; i < 1; i++)
    {
        strcat(f_root->size, "n");
    }
}

/**
 * @brief Değişken ve rekursif  boyutlarını  toplar.
 *
 *  @param v_root Değişkene bağlı struct'ı işaret eden kök işaretçisi.
 *
 * @param f_root fonksiyona bağlı struct'ı işaret eden kök işaretçisi.
 */
void size_sum(variable_s *v_root, function_s *f_root, int number_index)
{
    int sum_int = 0; // toplam boyutu tutar
    char size_temp[c_Size_s];
    memset(size_temp, NULL, c_Size_s);
    char sum_char[c_Size_l];
    memset(sum_char, NULL, c_Size_l);
    while (v_root != NULL)
    {
        if (v_root->size[0] != '\0')
        {

            if (NULL != strstr(v_root->size, "n"))
            {

                strcat(sum_char, v_root->size);
                strcat(sum_char, " ");
            }
            else
            {
                size_temp[0] = v_root->size[number_index];

                sum_int += atoi(size_temp);
            }
        }
        if (v_root->next != NULL)
        {
            v_root = v_root->next;
        }
        else
        {
            break;
        }
    }

    strcat(sum_char, size_sum_function(f_root)); // fonksiyonların boyutunu hesaplayan fonksiyon çağırılır
    printf("\nYer Karmaşıklığı: %s %d\n", sum_char, sum_int);
    if (sum_char[0] != '\0')
    {
        big_O_calculator_for_size(sum_char); // eğer sabit yer karmaşıklığı değilse fonksiyon çağrılır.
    }
    else
    {
        printf("BİG-O Notasyonu: O(1)"); // sabit yer karmaşıklığı ise
    }
}

/**
 * @brief Rekürsif fonksiyonların boyutlarını  toplar.
 *
 *  @param f_root Fonksiyona bağlı struct'ı işaret eden kök işaretçisi.
 *
 *@return Rekursif fonksiyonun boyutunu dönderir.
 *
 */
char *size_sum_function(function_s *f_root)
{
    char sum_char_func[c_Size_l];
    memset(sum_char_func, NULL, c_Size_l);
    while (f_root != NULL)
    {
        if (f_root->size[0] != '\0')
        {

            if (NULL != strstr(f_root->size, "n"))
            {
                strcat(sum_char_func, f_root->size);
                strcat(sum_char_func, " ");
            }
        }
        if (f_root->next != NULL)
        {
            f_root = f_root->next;
        }
        else
        {
            break;
        }
    }
    char *p_char = sum_char_func;
    return p_char; // adresini döndürür
}
/**
 * @brief Yer karmaşıklığının Big-O'sunu hesaplar.
 *Strtok kullanarak boşluklardan böler.
 *Böldüğü stringlerin hangisi uzun ise onu seçer ve sadece harfleri bastırır.
 *  @param  big_O_text yer karmaşıklığının olduğu string'i alır.
 *
 */
void big_O_calculator_for_size(char *big_O_text)
{
    char big_o_temp[c_Size_s][c_Size_s];
    memset(big_o_temp, NULL, 100);
    char *token = strtok(big_O_text, " "); // boşluklara göre böler
    int i = 0;
    int max_lenght = 0;
    int big_O_index = 0;
    while (token != NULL)
    {

        strcat(big_o_temp[i], token);

        if (max_lenght < strlen(big_o_temp[i]))
        {
            max_lenght = strlen(big_o_temp[i]);
            big_O_index = i;
        }
        i++;

        // printf(" %s\n", token);
        token = strtok(NULL, " ");
    }
    printf("BİG-O Notasyonu: O(");
    for (int j = 0; j < strlen(big_o_temp[big_O_index]); j++)
    {
        if ('A' <= big_o_temp[big_O_index][j])
        {
            printf("%c", big_o_temp[big_O_index][j]);
        }
    }
    printf(")\n\n");
}

/**
 * @brief Fonksiyonun çağrılma miktarını alır ve fonsiyonun zaman karmaşıklığını hesaplar.
 *
 *
 * @param amount_call_func Fonksiyonun çağrılma miktarını alır.
 *
 * @param f_root Fonsiyon struct'ın kökünü alır.
 */
void find_complexity_function(int amount_call_func, function_s *f_root)
{
    memset(f_root->complexity, NULL, 20);
    if (1 != amount_call_func)
    {
        f_root->complexity[0] = amount_call_func + '0';
        strcat(f_root->complexity, "^n");
    }
    else
    {

        strcat(f_root->complexity, "n");
    }
    printf("Zaman Karmaşıklığı;\nBİG-O Notasyonu: O(%s)\n\n", f_root->complexity);
}
/**
 * @brief Döngülerin karmaşıklığı ile rekürsif fonksiyonların karmaşıklığını kıyas eder.
 *
 * @param f_root Fonsiyon struct'ın kökünü alır.
 * @param l_root Döngü struct'ın rootunu alır.
 *
 */
int find_max_complexity(function_s *f_root, loop_s *l_root)
{
    int max_complexity_lenght = 0;
    int result_find_loop_complexity = 0;
    while (f_root != NULL)
    {
        if (f_root->amount_call > max_complexity_lenght)
        {
            max_complexity_lenght = f_root->amount_call;
        }
        if (f_root->next != NULL)
        {
            f_root = f_root->next;
        }
        else
        {
            break;
        }
    }
    if (max_complexity_lenght == 0)

    {
        find_loop_complexity(l_root, 1);
    }
    else
    {

        result_find_loop_complexity = find_loop_complexity(l_root, 0);
        if (max_complexity_lenght > result_find_loop_complexity)
        {

            find_complexity_function(max_complexity_lenght, f_root);
        }
        else
        {

            find_loop_complexity(l_root, 1);
        }
    }
}
/**
 * @brief Kaç tane rekürsif fonksiyon var bulur ve döndürür.
 *
 * @param f_root Fonsiyon struct'ın kökünü alır.
 *
 */
int recursive_counter(function_s *f_root)
{
    int recursive_count = 0;
    while (f_root != NULL)
    {
        if (f_root->amount_call > 0)
        {
            recursive_count++;
        }
        if (f_root->next != NULL)
        {
            f_root = f_root->next;
        }
        else
        {
            break;
        }
    }

    return recursive_count;
}