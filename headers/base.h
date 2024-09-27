/* base.h */

#define _BASE_H 1

#if !defined(_STDIO_H) || !defined(_STDLIB_H) || !defined(_STRING_H) || !defined(_CONST_H)
    #ifndef _STDIO_H
        #warning "Needed 'stdio.h' header file has not been included, including now"
        #include <stdio.h>
    #endif
    #ifndef _STDLIB_H
        #warning "Needed 'stdlib.h' header file has not been included, including now"
        #include <stdlib.h>
    #endif
    #ifndef _STRING_H
        #warning "Needed 'string.h' header file has not been included, including now"
        #include <string.h>
    #endif
#endif

void word_fetch(char* FILENAME, char words[256][32], int range[256][2], char* SYMBOLS, int PRESENT_SYMBOLS_POSITIONS[32], int PRESENT_SYMBOL_QUANTITY, int* TOTAL_WORD, int* TOTAL_CHAR)
{
    FILE* fptr;
    fptr = fopen(FILENAME, "r");
    int total_word, character_count = 0, null_word = 0;
    if (fptr == NULL) {printf("'%s' file couldn't be opened, exiting...\n", FILENAME); exit(0);}
    else {
        for (int word_count = 0, word_count_checked = 0, letter_count = 0; word_count < 256;)
        {
            char c = fgetc(fptr);
            if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
            {
                for (int i = 0; i < strlen(SYMBOLS); i++)
                {
                    if (c == SYMBOLS[i]) {PRESENT_SYMBOLS_POSITIONS[PRESENT_SYMBOL_QUANTITY] = i; PRESENT_SYMBOL_QUANTITY++;}
                }
            }
            if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == ';' || c == ')' || c == ']')
            {
                if (!(range[word_count_checked][0]) && word_count_checked > 0)
                {
                    word_count_checked--;
                } else
                {
                    range[word_count_checked][1] = character_count;
                }
                word_count++;
                word_count_checked++;
                letter_count = 0;
            }
            else if (c == EOF) {break;}
            else 
            {
                if (letter_count == 0) {range[word_count_checked][0] = character_count;}
                words[word_count][letter_count] = c;
                letter_count++;
            }
            character_count++;
            total_word = word_count;
        }
        for (int s = 0; s < total_word; s++) {if (words[s][0] == '\0') {null_word++;}}
        for (int io = 0; io < null_word; io++)
        {
            for (int word_num = 0; word_num <= total_word; word_num++)
            {
                if (words[word_num][0] == '\0')
                {
                    for (int k = 0; k < strlen(words[word_num + 1]); k++)
                    {
                        words[word_num][k] = words[word_num + 1][k];
                        if (k + 1 == strlen(words[word_num + 1])) {words[word_num][k + 1] = '\0';}
                        else if (strlen(words[word_num + 1]) == 0) {break;}
                    }
                    words[word_num + 1][0] = '\0';
                }
            }
        }
    }
    for (int i = 0; i < total_word; i++)
    {
        for (int j = 0; words[i][j] != '\0'; j++)
        {
            if (words[i][j] >= 'A' && words[i][j] <= 'Z') {words[i][j] += 32;}
            else if (words[i][j] < 0) {words[i][j] = '\0';}
        }
    }
    total_word = total_word - null_word;
    *TOTAL_WORD = total_word;
    *TOTAL_CHAR = character_count;
    fclose(fptr);
}
