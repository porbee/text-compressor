/* word_index.h */

#define _WINDEX_H 1

#if !defined(_STRING_H) || !defined(_MISC_H)
    #ifndef _STRING_H
        #warning "Needed 'string.h' header file has not been included, including now"
        #include <string.h>
    #endif
    #ifndef _MISC_H
        #warning "Needed 'misc.h' header file has not been included, including now"
        #include "misc.h"
    #endif
#endif

int replace_null(int initial_null_position, int total_array_items, char replacing_array[256][32])
{
    for (int i = initial_null_position; i < total_array_items; i++)
    {
        for (int j = 0; j < strlen(replacing_array[i + 1]); j++)
        {
            char c = replacing_array[i + 1][j];
            replacing_array[i][j] = c;
            if (j + 1 == strlen(replacing_array[i + 1])) {replacing_array[i][j + 1] = '\0';}
        }
        replacing_array[i + 1][0] = '\0';
        total_array_items--;
    }
    return total_array_items;
}

int word_ocurrence(int total_word_num, char saved_words[256][32], char recurrent_words_array[128][32], int recurrency_quantity[128])
{
    char words_copy[256][32];
    int total_recurrent_words = 0, total_copied_word_num = total_word_num;
    bidimensional_array_copy(total_word_num, words_copy, saved_words);
    for (int i = 0, rep_num = 0; i < total_word_num; i++)
    {
        if (words_copy[i][0] == '\0') {break;}
        else
        {
            int ocurrences = 0;
            for (int j = 0; j < total_word_num; j++)
            {
                if (!(strcmp(words_copy[i], words_copy[j]))) {ocurrences++;}
            }
            if (ocurrences > 1)
            {
                for (int k = 0; k < strlen(words_copy[i]); k++)
                {
                    char c = words_copy[i][k];
                    recurrent_words_array[total_recurrent_words][k] = c;
                }
                recurrency_quantity[total_recurrent_words] = ocurrences; total_recurrent_words++;
                for (int a = 0; a < ocurrences; a++)
                {
                    for (int b = 0; b < total_copied_word_num; b++)
                    {
                        if (strcmp(words_copy[i], words_copy[b]) == 0 && i != b) 
                        {
                            words_copy[b][0] = '\0';
                            total_copied_word_num = replace_null(b, total_copied_word_num, words_copy);
                        }
                    }
                }
            }
        }
    }
    return total_recurrent_words;
}