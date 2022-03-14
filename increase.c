#include <stdio.h>
#include <string.h>
#include "increase.h"



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
int find_char(char *message, char c, int size)
{
    if(message != NULL)
    {
            for(int i=0; i < size; i++)
        {
        if(message[i] == c) return i;
        }

    return -1;
    }

}

/**
 * @brief "i++" gibi arttırımları tespit etmeye çalışır
 * @param message İgili satır
 * @param size İlgili satırın boyutu
 * @return -1: Bulunamadı 
 * 
 */
int find_increase_case1(char *message, int size)
{
    int error= 0;

    error = find_char(message, '+', size);
    if(error != -1)
    {
        if(message[error+1] == '+')
        {
            return LINEER_POSITIVE; // Lineer artış
        }
    }

    error = find_char(message, '-', size);
    if(error != -1)
    {
        if(message[error+1] == '-')
        {
            return LINEER_NEGATIVE; // Lineer azalış
        }
    }

    return -1;
}


int find_increase_case2(char *message, int size)
{
    int error = 0;
    error = find_char(message,'=',size);
    if(error != -1)
    {
        if(message[error-1] == '+')
        {
            return LINEER_POSITIVE;
        }
        else if(message[error-1] == '-')
        {
            return LINEER_NEGATIVE;
        }
        else if(message[error-1] == '*')
        {
            return EXPONENTIAL_POSITIVE;
        }
        else if(message[error-1] == '/')
        {
            return EXPONENTIAL_NEGATIVE;
        }
    }
    
    return -1;
}

/**
 * @brief Başka değişkene bağlı olarak artan veya azalan değişkenleri analiz eder.
 * @param message İlgili satırın tamamı
 * @param size Satırı içeren dizinin uzunluğu
 * 
 */
int find_complex_increase(char *message, int size)
{
    int error = 0;
    int word = 1;

    error = find_char(message,'=',size); // Eşittir olup olmadığının kontrolü

    if(error == -1) return -1;
    
    for(int i=0; i<size; i++) if(message[i] == ' ') word++;

    char *m_p[word];
    sentence_divider(m_p,message,word);
    
    error = find_char(message,'(',size);

    if(error == -1) return -1;





}

int calculata_compexity(char *d_m[],int word)
{
    int i=0;
    for(;d_m[i] != '=';i++);



}

/**
 * @brief Alınan mesajın içindeki virül karekterlerini boşluk olarak değiştirir.
 * @param message Karakterleri içeren dizi.
 * @param size Dizinin boyutu.
 */
int clear_line(char *message,int size)
{
    for(int i=0; i<size; i++)
    {
        if(message[i] == ',')
        {
            message[i] = ' ';
        }
    }
}
int find_variables_by_name(char *message, int size)
{
    int word = 1;

    for(int i=0; i<size; i++) if(message[i] == ' ') word++;


}

/**
 * @brief Verilen diziyi boşluklara göre parçalayarak bir işaretçiye kayıt eder.
 * @param message_p Verilerin tutulacağı char işaretçisi dizisi.
 * @param message Parçalanacak cümle.
 * @param word Cümledeki kelime sayısı.
 */
int sentence_divider(char *message_p[],char *message, int word)
{
    int error = 0;

    message_p[0] = strtok(message," ");

    for(int i=1; i<word;i++)
    {
        message_p[i] = strtok(NULL," ");
        
    }

    //Dizileri temizleme işlemi
    for(int i=0; i < word; i++)
    {
        error = find_char(message_p[i],'[',MAX_SENTENCE_LENGTH);
        if(error != -1)
        {
            message_p[i][error] = '\0';
        }
    }

    return 0;
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