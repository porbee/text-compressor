/* misc.h */

#define _MISC_H 1

#ifndef _STRING_H
    #warning "Needed 'string.h' header file has not been included, including now"
    #include <string.h>
#endif

int eliminate_reps(int total_elements, int* array)
{
    int total_true_elements = total_elements, is_zero_included = 0;
    for (int n = 0; n < total_elements; n++)
    {
        if (array[n] == 0) {is_zero_included = 1; break;}
    }
    for (int i = 0; i < total_true_elements; i++)
    {
        int reference = array[i];
        for (int j = 0; j < total_true_elements; j++)
        {
            int eliminated = 0;
            if (reference == array[j] && j != i)
            {
                array[j] = 0;
                for (int k = j; k < total_true_elements; k++)
                {
                    array[k] = array[k + 1];
                    array[k + 1] = 0;
                }
                j = 0;
                eliminated++;
            }
            total_true_elements -= eliminated;
        }
    }
    return total_true_elements;
}

void bidimensional_array_copy(int total_word_num, char DEST[256][32], char SRC[256][32])
{
    for (int i = 0; i < total_word_num; i++)
    {
        for (int j = 0; j < strlen(SRC[i]); j++)
        {
            char c = SRC[i][j];
            DEST[i][j] = c;
        }
    }
}

void remove_present_symbols(char* AVAILABLE_SYMBOLS, int TOTAL_DIFFERENT_PRESENT_SYMBOLS, int REPEATED_SYMBOLS_POSITIONS[32])
{
    char *PRESENT_SYMBOLS;
    PRESENT_SYMBOLS = (char*) malloc(TOTAL_DIFFERENT_PRESENT_SYMBOLS);
    for (int n = 0; n < TOTAL_DIFFERENT_PRESENT_SYMBOLS; n++) {PRESENT_SYMBOLS[n] = AVAILABLE_SYMBOLS[REPEATED_SYMBOLS_POSITIONS[n]];}
    for (int p = 0; p < TOTAL_DIFFERENT_PRESENT_SYMBOLS; p++)
    {
        for (int q = 0; q < strlen(AVAILABLE_SYMBOLS); q++)
        {
            if (AVAILABLE_SYMBOLS[q] == PRESENT_SYMBOLS[p])
            {
                for (int r = q; r < strlen(AVAILABLE_SYMBOLS); r++)
                {
                    AVAILABLE_SYMBOLS[r] = AVAILABLE_SYMBOLS[r + 1];
                }
            }
        }
    }
    free(PRESENT_SYMBOLS);
}

int index_repeats(int recurrencies, int total_words, char arr_recurrent_words[128][32], int arr_repeated_pos[128], char saved_words[256][32])
{
    int rep_pos = 0;
    for (int r = 0; r < recurrencies; r++)
    {
        for (int s = 0; s < total_words; s++)
        {
            if (!(strcmp(saved_words[s], arr_recurrent_words[r])))
            {
                arr_repeated_pos[rep_pos] = s;
                rep_pos++;
            }
        }
    }
    return(rep_pos);
}
