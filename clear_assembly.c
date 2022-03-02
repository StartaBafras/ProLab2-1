#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *original_assembly = fopen("assembly.s","r");
    FILE *new_assembly = fopen("clean_assembly.s","w");
    char temp[50];

    while (!feof(original_assembly))
    {
        memset(temp,0,50);

        for(int i=0; i<50; i++)
        {   
            temp[i] = fgetc(original_assembly);
            if(temp[i] == '\n') break;
        }

        for(int i=0; i<50;i++)
        {
            if(temp[i] == '.' && temp[i+1] > 96)
            {
                break;
            }

            else if(i == 49)
            {
                fprintf(new_assembly,"%s",temp);
            }
        }
    }
    
}