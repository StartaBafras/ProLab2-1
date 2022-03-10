#include <stdio.h>

#define Lineer 1
#define Exponential 2
#define Logaritmic 3

/**
* @brief Bir dizinin içinde isenen karakteri bulup 
* bulunduğu ilk yerin indeksini döndürür.
* 
* @param message String dizisi
* @param c Aranan karakter
* @param size String dizisinin boyutu
* 
* @return (int) -1: Bulunamadı
*
*/
int find_char(char *message, char c,int size)
{
    for(int i=0; i < size; i++)
    {
        if(message[i] == c) return i;
    }

    return -1;
}



int find_increase(char *message,int size)
{
    int error= 0;

    error = find_char(message, '+', size);
    if(error != -1)
    {
        if(message[error+1] == '+')
        {
            return Lineer; // Lineer artış
        }
    }

    error = find_char(message, '-', size);
    if(error != -1)
    {
        if(message[error+1] == '-')
        {
            return Lineer; // Lineer artış
        }
    }

    return -1;
}

/*
int main(void)
{
    char q[8] = "a = i++";

    int error = 0;

    error = find_char(q,'=',sizeof(q));

    if(error != -1)
    {
        error = find_increase(&q[error],sizeof(q)-error-1);
    }
    
}*/