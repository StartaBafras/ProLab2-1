#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loop.h"
#include "variable.h"

/**
 * @brief Döngüye ait verileri bağlı listede boş olduğu kabul edilen yere yazar.
 * @param data Verilerin kapsüllendiği veri paketinin adresi
 * @param loops İçi boş kabul edilen bağlı liste üyesinin adresi.
 */
int write_loop_data(loop_s *data, loop_s *loops)
{
    strcat(loops->condition, data->condition);
    loops->complexity = data->complexity;
    loops->dependent_variable = data->dependent_variable;
    loops->id = data->id;
    loops->kind = data->kind;
    loops->next = NULL;
    loops->start_end_line[0] = data->start_end_line[0];
    loops->start_end_line[1] = data->start_end_line[1];
    // printf("//%d //%d // %d //%d //%s \n", loops->id, loops->kind, loops->start_end_line[0], loops->start_end_line[1],loops->condition);

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
    if (loops->start_end_line[0] == NULL)
    {
        data->id = 0;
        write_loop_data(data, loops);
        return 0;
    }

    for (; loops->next != NULL; loops = loops->next)
        ;
    data->id = loops->id + 1;
    loops->next = malloc(sizeof(loop_s));
    loops = loops->next;
    write_loop_data(data, loops);

    return 0;
}

/**
 * @brief  dosyanın içindeki stringi alır.
 * for döngüsünü  bulur  ve struct'a ekler.
 * @param text string dizisi
 *
 *@retun 0:
 *
 */
int find_for(char text[][Size], loop_s *l_root)
{

    char name_loop[] = "for";
    char raise_loop[c_Size_s];     // artışı tutar
    char n_for_temp[c_Size_l];     // ismi geçiçi tutar
    char l_raise_temp[c_Size_l];   // artışı geçiçi tutar
    char loop_condition[c_Size_l]; // koşulu tutar
    int line_loop_start = NULL;    // başlama atırını tutar
    int line_loop_end = NULL;      // bitme satırını tutar

    char *p_loop;                  // türün yerini belli eden
    for (int i = 0; i < Size; i++) // satırları gezer
    {
        p_loop = text[i];
        if (NULL != strstr(p_loop, name_loop))
        {
            line_loop_start = i;
            p_loop = strstr(p_loop, name_loop);
            memset(n_for_temp, NULL, c_Size_l);
            strcat(n_for_temp, n_for_temp);
            p_loop += 1;
            p_loop = strstr(p_loop, ";");
            p_loop += 1;
            memset(l_raise_temp, NULL, c_Size_l);
            strcat(l_raise_temp, p_loop);
            memset(loop_condition, NULL, c_Size_l);
            int k = 0;

            for (int j = 0; j < strlen(l_raise_temp); j++) // satırın içini gezer

            {
                if ((l_raise_temp[j] == ';') || (l_raise_temp[j] == '<') || (l_raise_temp[j] == '>') || (l_raise_temp[j] == '=') || (l_raise_temp[j] == '!'))
                {
                    break;
                }
                if ('A' <= l_raise_temp[j])
                {
                    loop_condition[k] = l_raise_temp[j];
                    k++;
                }
            }

            p_loop = strstr(p_loop, ";");
            memset(l_raise_temp, NULL, c_Size_l);
            strcat(l_raise_temp, p_loop + 1);
            memset(raise_loop, NULL, c_Size_s);

            for (int j = 0; j < strlen(l_raise_temp); j++) // satırın içini gezer

            {
                if (l_raise_temp[j] == ')')
                {
                    break;
                }

                raise_loop[j] = l_raise_temp[j];
            }
            // fonk çağır
            line_loop_end = 0;
            line_loop_end = find_line_end(line_loop_start, text);
            // printf("--%s ---%s --%d  --%s--%d \n", name_loop, raise_loop, line_loop_start, loop_condition, line_loop_end);
            loop_s data;
            data.dependent_variable = malloc(sizeof(variable_s_pointer));
            data.dependent_variable->next = NULL;
            data.dependent_variable->variable = NULL;
            data.kind = v_FOR;
            memset(data.condition, NULL, c_Size_s);
            strcat(data.condition, loop_condition);
            data.start_end_line[0] = line_loop_start;
            data.start_end_line[1] = line_loop_end;
            data.id = 0;
            data.complexity = NULL;
            add_loop(&data, l_root);
        }
    }
}
/**
 *
 *@brief parantezin başladığı yeri alır ve bittiği yeri bulur böyle scope alanı belli olur.
 *@param line_start parantezin açıldığı satır.
 *
 */
int find_line_end(int line_start, char text[][Size])
{
    int count_brackets = 0; // parantez sayacı
    for (int i = line_start; i < Size; i++)
    {
        if (NULL != strstr(text[i], "{"))
        {
            count_brackets++;
        }
        if (NULL != strstr(text[i], "}"))
        {
            if (0 != count_brackets)
            {
                count_brackets--;
            }
            if (0 == count_brackets)
            {

                return i;
            }
        }
    }
    return -1;
}
/**
 * @brief while ve do while döngüsünü bulur
 * @param root rootu alır.
 */
int find_while(char text[][Size], loop_s *l_root)
{
    char name_loop[c_Size_s] = "while";
    char *p_loop;
    char *token;
    char loop_condition[c_Size_l]; // koşulu tutar
    int line_loop_start = NULL;    // başlama atırını tutar
    int line_loop_end = NULL;      // bitme satırını tutar
    for (int i = 0; i < Size; i++)
    {
        p_loop = text[i];
        if (NULL != strstr(p_loop, name_loop))
        {
            line_loop_start = i;
            line_loop_end = 0;
            line_loop_end = find_line_end(line_loop_start, text);
            p_loop = strstr(p_loop, name_loop);
            p_loop += 6;
            p_loop = strtok(p_loop, "<");
            p_loop = strtok(p_loop, ">");
            p_loop = strtok(p_loop, "=");
            p_loop = strtok(p_loop, "!");
            memset(loop_condition, NULL, c_Size_l);
            strcat(loop_condition, p_loop);
            if (line_loop_end == line_loop_start)
            {
                line_loop_start = find_do(text, line_loop_end);
                strcat(name_loop, " do");
            }

            //  printf("--%s  --%d  --%s--%d \n", name_loop, line_loop_start, loop_condition, line_loop_end);
            loop_s data;
            data.dependent_variable = malloc(sizeof(variable_s_pointer));
            data.dependent_variable->next = NULL;
            data.dependent_variable->variable = NULL;
            if (NULL != strstr(name_loop, "do"))
            {
                data.kind = V_WHILE_DO;
            }
            else
            {
                data.kind = V_WHILE;
            }
            memset(data.condition, NULL, c_Size_s);
            strcat(data.condition, loop_condition);
            data.start_end_line[0] = line_loop_start;
            data.start_end_line[1] = line_loop_end;
            data.id = 0;
            data.complexity = NULL;

            add_loop(&data, l_root);
        }
    }
    return 0;
}
/**
 * @brief find_while while fonksiyonu tarafından
 * while'ın bittiği yer alır ve do'nun yerini bulur ve while atar
 * @param end_while_line while'ın bittiği yeri alır
 * */
int find_do(char text[][Size], int end_while_line)
{
    char name_loop[] = "do";
    char *p_loop;
    int line_loop_start = NULL; // başlama atırını tutar
    int line_loop_end = NULL;   // bitme satırını tutar
    for (int i = 0; i < Size; i++)
    {
        p_loop = text[i];
        if (NULL != strstr(p_loop, name_loop))
        {
            line_loop_start = i;
            line_loop_end = 0;
            line_loop_end = find_line_end(line_loop_start, text);
            if (line_loop_end == end_while_line)
            {

                return line_loop_start;
            }
        }
    }
    return -1;
}
/**
 *@brief döngü struct'ının içinde gezinir amacı döngüye ait değişkeni bulmak
 *
 *@param v_root variable struct'ın root'unu alır
 *
 *@param l_root  loop struct'ın root'unu alır
 */
void connect_loop_and_variable(variable_s *v_root, loop_s *l_root)
{
    int result = 0; // fonkisyonun geri dönüş parametresini tutar
    if (l_root != NULL)
    {
        result = research_variable_connect_loop_same_line(v_root, l_root->start_end_line[0]);

        if (-1 == result)
        {
            result = research_variable_connect_loop_different_line(v_root, l_root);
        }
        search_variable(l_root->condition, result, v_root);
        // printf("%d\n", l_root->id_var);
    }
    if (l_root->next != NULL)
    {
        connect_loop_and_variable(v_root, l_root->next);
    }
}
/**
 *@brief variable struct'ının içinde gezinir amacı döngüye ait değişkeni bulmak
 *döngünün başlangıç yerini alır, çünkü genelde değişken orda tanımlanır,
 * eğer tanımlanmamışsa and_variable_case_2 çağırılır
 *
 * @param v_root variable struct'ın root'unu alır
 *
 *@param loop_start_line döngünün başlangıç yerini alır.
 *
 *@return (int) -1: Bulunamadı
 */
int research_variable_connect_loop_same_line(variable_s *v_root, int loop_start_line)
{
    if (v_root != NULL)
    {
        if (loop_start_line == v_root->line)
        {
            return v_root->line;
        }
    }

    if (v_root->next != NULL)
    {
        return research_variable_connect_loop_same_line(v_root->next, loop_start_line);
    }
    return -1;
}
/**
 * @brief Variable struct'ının içinde gezinir amacı döngüye ait değişkeni bulmak
 *  for dongüsünün içinde tanımlanmamış ise çalışır .
 * bu durumda for döngüsünden önce tanımlanmıştır ve for tanımlamadan önceki yerlerde arar.
 *
 * @param v_root variable struct'ın root'unu alır
 *@param l_root  loop struct'ın root'unu alır
 *
 *
 */
int research_variable_connect_loop_different_line(variable_s *v_root, loop_s *l_root)
{

    if ((0 == strcmp(l_root->condition, v_root->name)) && (l_root->start_end_line[0] >= v_root->line))
    {
        return v_root->line;
    }
    if (v_root->next != NULL)
    {
        research_variable_connect_loop_different_line(v_root = v_root->next, l_root);
    }
}

/**
 * @brief Verilen döngünün koşulunun bağlı olduğu değişkeni değişkenler bağlı listesinde bulur
 * ve döngünün yapısına bağlar.
 *
 * @param variable Döngünün bağlı olduğu değişkenin ismi.
 * @param variable_line Değişkenin bulunduğu satır.
 * @param v_root Değişken bağlı listesini işaret eden kök işaretçisi.
 * @param loop_struct İşlem yapılacak döngüyü işaret eden işaretçi.
 *
 * @return 0: İşlem Tamamlandı
 */
int add_variable_in_loop(char *variable, int variable_line, variable_s *v_root, loop_s *loop_struct)
{
    variable_s *new_v = search_variable(variable, variable_line, v_root);

    if (new_v == NULL)
        return -1;

    if (loop_struct->dependent_variable->variable == NULL)
    {
        loop_struct->dependent_variable->variable = new_v;
        return 0;
    }

    variable_s_pointer *new_p;

    new_p = loop_struct->dependent_variable;

    while (new_p->next != NULL)
        new_p = new_p->next;

    new_p->next = malloc(sizeof(variable_s_pointer));

    new_p->next->variable = new_v;
    new_p->next->next = NULL;

    return 0;
}

/**
 *@brief döngü struct'ını alır ve içinde gezinir.
 * Amaç iç içe döngüleri tespit etmek.
 *
 * @param l_root Döngü struct'ın rootunu alır
 * */
void find_loop_complexity(loop_s *l_root)
{
    int lines_and_increase_arr[c_Size_l][3];
    int complexity_arr[c_Size_l][c_Size_s];
    memset(complexity_arr, NULL, c_Size_l * c_Size_s);

    int complexity_index = 0;
    int i = 0;

    while ((l_root != NULL) && (l_root->start_end_line != 0))
    {

        lines_and_increase_arr[i][0] = l_root->start_end_line[0];
        lines_and_increase_arr[i][1] = l_root->start_end_line[1];
        lines_and_increase_arr[i][2] = l_root->dependent_variable->variable->increase_rate;

        if (l_root->next != NULL)
        {
            l_root = l_root->next;
            i++;
        }
        else
        {
            break;
        }
    }
    int m = 0;
    for (int j = 0; j < i + 1; j++, m++)
    {
        int l = 0;
        for (int k = 0; k < i + 1; k++)
        {

            if ((lines_and_increase_arr[k][0] > lines_and_increase_arr[j][0]) && (lines_and_increase_arr[k][1] < lines_and_increase_arr[j][1]))
            {
                if ((lines_and_increase_arr[k][0] > lines_and_increase_arr[k - 1][0]) && (lines_and_increase_arr[k][1] < lines_and_increase_arr[k - 1][1]))
                {
                    complexity_arr[m][0] = lines_and_increase_arr[j][2];
                    complexity_arr[m][l + 1] = lines_and_increase_arr[k][2];
                    l++;
                }
                else
                {
                    m++;
                    l = 0;
                    complexity_arr[m][0] = lines_and_increase_arr[j][2];
                    complexity_arr[m][l + 1] = lines_and_increase_arr[k][2];
                    l++;
                }
            }
        }
    }
    int max_lenght_N = 0;
    int max_lenght_logN = 0;
    for (int k = 0; k < 10; k++)
    {
        int N_count = 0;
        int lonG_count = 0;
        for (int j = 0; j < i; j++)
        {
            if ((1 == complexity_arr[k][j]) || (2 == complexity_arr[k][j]))
            {
                N_count++;
            }
            else if ((2 < complexity_arr[k][j]) && (7 > complexity_arr[k][j]))
            {
                lonG_count++;
            }

            if (max_lenght_N < N_count)
            {
                max_lenght_logN = lonG_count;
                max_lenght_N = N_count;
                complexity_index = k;
            }
            if (max_lenght_N == N_count)
            {

                if (lonG_count > max_lenght_logN)
                {
                    max_lenght_logN = lonG_count;
                    complexity_index = k;
                    max_lenght_N = N_count;
                }
            }
        }
    }
    char complexity_string[6][c_Size_s] = {"n", "n", "logN", "logN", "logN", "logN"};
    printf("\n");
    for (int j = 0; j < c_Size_s; j++)
    {
        for (int k = 1; k <= 6; k++)
        {
            if (complexity_arr[complexity_index][j] == k)
            {
                printf("%s", complexity_string[k - 1]);
            }
        }
    }

    printf("\n");
}
