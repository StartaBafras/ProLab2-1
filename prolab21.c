#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code_check.h"
#include "variable.h"
#include "loop.h"
#include "function.h"
#include "increase.h"

int toplam(int dizi[], int n)
{
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        x = x + dizi[i];
    }
    return x;
}

int main(void)
{
    variable_s *v_root = malloc(sizeof(variable_s));
    loop_s *l_root = malloc(sizeof(loop_s));

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

    find_variables(read_txt, v_root);
    find_for(read_txt, l_root);
    find_while(read_txt, l_root);
    connect_loop_and_variable(v_root, l_root);
    find_size(v_root);
    int c = 0;
    for (int i = 0; i < 22; i++)
    {
        c = find_increase_case1(read_txt[i],30,i,v_root);
      
    }


    int error = 0;




    if (0 != error)
    {
        printf("Kod Hatalı Derlenemedi.");
        return 1;
    }
}