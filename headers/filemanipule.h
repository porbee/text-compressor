/* filemanipule.h */

#define _FILEMANIPULE_H 1

#if !defined(_STRING_H) || !defined(_CONST_H) || !defined(_STDIO_H)
    #ifndef _STRING_H
        #warning "Needed 'string.h' header file has not been included, including now"
        #include <string.h>
    #endif
    #ifndef _STDIO_H
        #warning "Needed 'stdio.h' header file has not been included, including now"
        #include <stdio.h>
    #endif
#endif

#if !defined(WORD_MAX) || !defined(LETTER_MAX)
    #ifndef WORD_MAX
        #define WORD_MAX 1024
    #endif
    #ifndef LETTER_MAX
        #define LETTER_MAX 65536
    #endif
#endif

int replace_word(int final_letter, int first_letter, char character, int total_characters, char* filename)
{
    if (first_letter == 0)
    {
        char symbol[LETTER_MAX] = {character, '\0'};
        FILE* d_fptr;
        d_fptr = fopen(filename, "r");
        char last[LETTER_MAX];
        fseek(d_fptr, final_letter, SEEK_SET);
        int l = final_letter;
        for (int i = 0; l < total_characters; i++)
        {
            char c = fgetc(d_fptr);
            if (l + 1 == total_characters) {last[i] = c; last[i + 1] = '\0'; break;}
            else {last[i] = c;}
            l++;
        }
        strcat(symbol, last);
        d_fptr = fopen(filename, "w");
        fputs(symbol, d_fptr);
        fclose(d_fptr);
        return(strlen(symbol));
    } else if (first_letter > 0 && final_letter < total_characters)
    {
        char symbol[2] = {character, '\0'};
        FILE* d_fptr;
        d_fptr = fopen(filename, "r");
        if (d_fptr == NULL) {printf("HELLO"); return -1;}
        char first[LETTER_MAX], last[LETTER_MAX];
        //fseek(d_fptr, 0, SEEK_SET);
        for (int i = 0; i < first_letter; i++)
        {
            fseek(d_fptr, i, SEEK_SET);
            char c = fgetc(d_fptr);
            //printf(" %c,%li", c, ftell(d_fptr));
            if (i + 1 == first_letter) {first[i] = c; first[i + 1] = '\0'; //printf(" %s\n", first); break;
            }
            else {first[i] = c;}
        }
        strcat(first, symbol);
        fseek(d_fptr, final_letter, SEEK_SET);
        for (int i = 0, l = final_letter; i < total_characters; i++, l++)
        {
            char c = fgetc(d_fptr);
            if (l + 1 == total_characters) {last[i] = c; last[i + 1] = '\0'; break;}
            else {last[i] = c;}
        }
        strcat(first, last);
        d_fptr = fopen(filename, "w");
        fputs(first, d_fptr);
        return(strlen(first));
        fclose(d_fptr);
    } else if (final_letter == total_characters)
    {
        char symbol[2] = {character, '\0'};
        FILE* d_fptr;
        d_fptr = fopen(filename, "r");
        char first[LETTER_MAX];
        fseek(d_fptr, 0, SEEK_SET);
        for (int i = 0; i < first_letter; i++)
        {
            char c = fgetc(d_fptr);
            if (i + 1 == final_letter) {first[i] = c; first[i + 1] = '\0'; break;}
            else {first[i] = c;}
        }
        strcat(first, symbol);
        d_fptr = fopen(filename, "w");
        fputs(first, d_fptr);
        fclose(d_fptr);
        return(strlen(first));
    }
    return 0;
}