#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/base.h"
#include "headers/filemanipule.h"
#include "headers/misc.h"
#include "headers/word_index.h"

#if !defined(WORD_MAX) || !defined(LETTER_MAX)
    #ifndef WORD_MAX
        #define WORD_MAX 1024
    #endif
    #ifndef LETTER_MAX
        #define LETTER_MAX 65536
    #endif
#endif

char symbols[] = {"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
int symbol_recurrence = 0, int_symbols_used[32];

int main(int argc, char *argv[])
{
    char word[256][32], recurrent_words[128][32];
    int ranges[256][2], repeats_positions[128], total_words, total_characters, quantity[128], recurrencies, used_symbols_num, total_common_words;
    word_fetch("sample.txt", word, ranges, symbols, int_symbols_used, symbol_recurrence, &total_words, &total_characters);
    recurrencies = word_ocurrence(total_words, word, recurrent_words, quantity);
    used_symbols_num = eliminate_reps(symbol_recurrence, int_symbols_used);
    remove_present_symbols(symbols, used_symbols_num, int_symbols_used);
    total_common_words = index_repeats(recurrencies, total_words, recurrent_words, repeats_positions, word);
    for (int a = 0; a < recurrencies; a++) {printf("%s\t%c\n", recurrent_words[a], symbols[a]);}
    printf("/*/ Total words = %i   Total Chars = %i\n\n", total_words, total_characters);
    for (int b = 0; b < total_common_words; b++)
    {
        if (b % 2 == 0)
        {
            printf("%i / %i \t", ranges[repeats_positions[b]][0], ranges[repeats_positions[b]][1]);
        } else {
            printf("%i / %i \n", ranges[repeats_positions[b]][0], ranges[repeats_positions[b]][1]);
        }
    }
}