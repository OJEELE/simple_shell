#include "main.h"

/* _strtok - function that tokenizes string
 * @str: pointer to string to be separated
 * @delim: delimiter to separate the string
 * Return: returns null
 */
void _strtok(const char *str,  char delim)
{
    int len = strlen(str);
    char word[len + 1];
    int j = 0;

    for (int i = 0; i <= len; i++)
    {
        if (str[i] == delim || str[i] == '\0')
        {
            word[j] = '\0';
            if (j > 0)
            {
                printf("%s\n", word);
                j = 0;
            }
        }
        else
        {
            word[j++] = str[i];
        }
    }
}
int main()
{
    const char *input = "This is a sample string";
    char delim = ' ';
    _strtok(input, delim);

    return 0;
}
