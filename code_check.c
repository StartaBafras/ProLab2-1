#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "code_check.h"

int move_and_compile(void)
{
    FILE *original = fopen("question.txt","r");
    FILE *c_code = fopen("input.c","w");

    char temp[50];

    while (!feof(original))
    {
        memset(temp,0,50);

        for(int i=0; i<50; i++)
        {   
            temp[i] = fgetc(original);
            if(temp[i] == '\n' || temp[i] == -1)
            {
                if(temp[i] == -1) temp[i] = 0;
                break;
            }
        }
        
        fprintf(c_code,"%s",temp);
    }
    fclose(c_code);
    return system("make input");

}
