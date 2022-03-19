#include <stdio.h>
#include <string.h>
#include "increase.h"
#include "variable.h"


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

    }
    return -1;


}

/**
 * @brief "i++" gibi arttırımları tespit etmeye çalışır
 * @param message İgili satır
 * @param size İlgili satırın boyutu
 * @return -1: Bulunamadı 
 * 
 */
int find_increase_case1(char *message, int size, int line,variable_s *v_root)
{
    int error= 0;
    message = clear_special_character(message,sizeof(message),'+',' ');
    message = clear_special_character(message,sizeof(message),'-',' ');
    error = find_char(message, '+', size);
    if(error != -1)
    {
        if(message[error+1] == '+')
        {
            char *v = detect_variable(message,error,size);
            search_variable(v,line,v_root)->increase_rate = LINEER_POSITIVE;
            return LINEER_POSITIVE; // Lineer artış
        }
    }

    error = find_char(message, '-', size);
    if(error != -1)
    {
        if(message[error+1] == '-')
        {
            search_variable(detect_variable(message,error,size),line,v_root)->increase_rate = LINEER_NEGATIVE;
            return LINEER_NEGATIVE; // Lineer azalış
        }
    }


    return -1;
}

/**
 * @brief Verilen satırdaki değişkenleri bitişik olan karakterler mantığını kullanarak ayırt etmeyi sağlar.
 * 
 * @param message Karakter dizisi.
 * @param location Karakter dizisinde başlanacak yer.
 * @param Karakter dizisinin boyutu.
 * 
 * @return Değişkenin ismi
 */
char* detect_variable(char *message, int location, int size)
{
    int begin = location+1;
    int end = location-1 ;

    for(int i=location; i<size; i++)
    {
        if( message[i] != ';' && message[i] != ' ' && message[i] != ',' && message[i] != '\0' && message[i] != ')' && message[i] != '('  )
        {
            end++;
        }
        else break;
    }

    for(int i=location;i >=0; i--)
    {
        if( message[i] != ';' && message[i] != ' ' && message[i] != ',')
        {
            begin--;
        }
        else break;
    } 

    char *variable = malloc(sizeof(char) * (end-begin+1));

    for(int i=begin, j=0; i<=end;i++,j++)
    {   
        if(message[i] != '+' && message[i] != '-' && message[i] != ')' && message[i] != '(')
        {
            variable[j] = message[i];
        }
        else j--;
    }

    return variable;
}
/**
 * @brief Arttırımlarda +=, *= gibi durumları tespit etmeye çalışır.
 * 
 * @param message Satırın kendisi.
 * @param size Satırın genişliği.
 * 
 * @return Artış değeri.
 */
int find_increase_case2(char *message, int size,int line,variable_s *v_root)
{
    int error = 0;
    int location = 0;
    char *var;
    

    while(1)
    {

        error = find_char((message),'=',50);
        if(error != -1)
        {
            if(message[error-1] == '+')
            {
                location = error-2;

                while(1)
                {
                    if(message[location] != ' ')
                    {
                    var = detect_variable(message,location,size);
                    break;
                    }
                    else location--;
                }

                search_variable(var,line,v_root)->increase_rate = LINEER_POSITIVE;

                return LINEER_POSITIVE;
            }
            else if(message[error-1] == '-')
            {
                location = error-2;

                while(1)
                {
                    if(message[location] != ' ')
                    {
                    var = detect_variable(message,location,size);
                    break;
                    }
                    else location--;
                }

                search_variable(var,line,v_root)->increase_rate = LINEER_NEGATIVE;
                return LINEER_NEGATIVE;
            }
            else if(message[error-1] == '*')
            {
                location = error-2;

                while(1)
                {
                    if(message[location] != ' ')
                    {
                    var = detect_variable(message,location,size);
                    break;
                    }
                    else location--;
                }

                search_variable(var,line,v_root)->increase_rate = EXPONENTIAL_POSITIVE;

                return EXPONENTIAL_POSITIVE;
            }
            else if(message[error-1] == '/')
            {
                location = error-2;

                while(1)
                {
                    if(message[location] != ' ')
                    {
                    var = detect_variable(message,location,size);
                    break;
                    }
                    else location--;
                }

                search_variable(var,line,v_root)->increase_rate = EXPONENTIAL_NEGATIVE;

                return EXPONENTIAL_NEGATIVE;
            }
            for(int i=0; i<=error;i++)
            {
                message[i] = '0';
            }
            if(error == MAX_SENTENCE_LENGTH) break;
        }
        else break;
    }
    return -1;
}

/**
 * @brief Başka değişkene bağlı olarak artan veya azalan değişkenleri analiz eder.
 * 
 * @param root Değişkenler bağlı listesini işaret eden kök işaretçisi.
 * @param message Hesaplanacak satır.
 * @param size Satırı içeren dizinin uzunluğu.
 * @param line_number Satır numarası.
 * 
 */
int find_complex_increase(char *message, int size, int line_number, variable_s *root)
{
    int error = 0;
    int word = 2; // Boşluk saydığımız için 1 ile başlıyor, +1 de noktalı virgülden gelmekte

    error = find_char(message,'=',size); // Eşittir olup olmadığının kontrolü

    if(error == -1) return -1;
    
    for(int i=0; i<size; i++) if(message[i] == ' ') word++;

    char *m_p[word];


    sentence_divider(m_p,message,word);
    m_p[word-1] = ";";
    
    error = find_char(message,'(',size);

    if(error != -1) return -1; // Çıkış yapıyor ancak paranteze göre durum eklenmeli

    for(int i=0; i<word; i++)
    {
        if(0 == strcmp(m_p[i],"="))
        {
            for(int j=i; j<word;j++)
            {
                if(0 == strcmp(m_p[j],";") || 0 == strcmp(m_p[j],"," ))
                {
                    search_variable(m_p[i-1],line_number,root)->increase_rate = calculate_compexity(m_p,i,j,root);
                    i = j;
                }
            }
        }
    }

}

int calculate_compexity(char *d_m[],int begin_index, int end_index, variable_s *root)
{

}


/**
 * @brief Alınan mesajın içindeki istenen karakteri başak bir karakter ile değiştirmeye yarar.
 * 
 * @param message Karakterleri içeren dizi.
 * @param size Dizinin boyutu.
 * @param old_character Değiştirilmesi istenen karakter.
 * @param new_character Eski karakterle değiştirilecek karakter.
 */
char *clear_special_character(char *message,int size, char old_character, char new_character)
{
    for(int i=0; i<size; i++)
    {
        if(message[i] == old_character && (message[i+1] != old_character &&  message[i-1] != old_character))
        {
            message[i] = new_character;
        }
    }
    return message;
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

