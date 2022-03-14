#include <stdio.h>
#include <stdlib.h>
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
        data->id = 1;
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
    char raise_loop[c_Size_s];        // artışı tutar
    char n_for_temp[c_Size_l];        // ismi geçiçi tutar
    char l_raise_temp[c_Size_l];      // artışı geçiçi tutar
    char loop_condition[c_Size_l];    // koşulu tutar
    int line_loop_start = NULL; // başlama atırını tutar
    int line_loop_end = NULL;   // bitme satırını tutar

    char *p_loop;                          // türün yerini belli eden
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

            for (int j = 0; j < strlen(l_raise_temp); j++) // satırın içini gezer

            {
                if (l_raise_temp[j] == ';')
                {
                    break;
                }
                if ('A' <= l_raise_temp[j])
                {
                    loop_condition[j] = l_raise_temp[j];
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
            //printf("--%s ---%s --%d  --%s--%d \n", name_loop, raise_loop, line_loop_start, loop_condition, line_loop_end);
            loop_s data;
            data.kind = v_FOR;
            memset(data.condition, NULL, c_Size_s);
            strcat(data.condition, loop_condition);
            data.start_end_line[0] = line_loop_start;
            data.start_end_line[1] = line_loop_end;
            data.id = 0;
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
    char name_loop[] = "while";
    char *p_loop;
    char *token;
    char loop_condition[c_Size_l];    // koşulu tutar
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
            p_loop = strstr(p_loop, name_loop);
            p_loop += 6;
            token = strtok(p_loop, ")");
            memset(loop_condition, NULL, c_Size_l);
            strcat(loop_condition, token);
            if (line_loop_end == line_loop_start)
            {
                line_loop_start = find_do(text, line_loop_end);
                strcat(name_loop, " do");
            }

          //  printf("--%s  --%d  --%s--%d \n", name_loop, line_loop_start, loop_condition, line_loop_end);
            loop_s data;
            if (NULL != strstr(name_loop, "do"))
            {
                data.kind = V_WHILE_DO;
            }
            else
            {
                data.kind = V_WHILE;
            }

            data.start_end_line[0] = line_loop_start;
            data.start_end_line[1] = line_loop_end;
            data.id = 0;
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
 *@param v_root variable struct'ın root'unu alır
 *@param l_root  loop struct'ın root'unu alır
 */
void loop_and_variable(variable_s *v_root, loop_s *l_root)
{

    if (l_root != NULL)
    {
        l_root->id_var = and_variable(v_root, l_root->start_end_line[0]);
        if (-1 == l_root->id_var)
        {
            l_root->id_var = and_variable_case_2(v_root, l_root);
        }
        //printf("%d\n", l_root->id_var);
    }
    if (l_root->next != NULL)
    {
        loop_and_variable(v_root, l_root->next);
    }
}
/**
 *@brief variable struct'ının içinde gezinir amacı döngüye ait değişkeni bulmak
 *döngünün başlangıç yerini alır, çünkü genelde değişken orda tanımlanır,
 * eğer tanımlanmamışsa and_variable_case_2 çağırılır
 * @param v_root variable struct'ın root'unu alır
 *@param loop_start_line döngünün başlangıç yerini alır.
 * 
 *
 */
int and_variable(variable_s *v_root, int loop_start_line)
{
    if (v_root != NULL)
    {
        if (loop_start_line == v_root->line)
        {
            return v_root->id;
        }
    }

    if (v_root->next != NULL)
    {
        return and_variable(v_root->next, loop_start_line);
    }
    return -1;
}
/**
 * @brief case 2 durumunda çalışır bu durum for döngüsünden önce tanımlanmış ise
 * @param v_root variable struct'ın root'unu alır
 *@param l_root  loop struct'ın root'unu alır
 * 
 * 
*/
int and_variable_case_2(variable_s *v_root, loop_s *l_root)
{

    if ((0 == strcmp(l_root->condition, v_root->name)) && (l_root->start_end_line[0] >= v_root->line))
    {
        return v_root->id;
    }
    if (v_root->next != NULL)
    {
        and_variable_case_2(v_root = v_root->next, l_root);
    }
}