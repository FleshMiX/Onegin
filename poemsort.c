#include "poemsort.h"

struct String{
    char *start;
    int len;
};

/*!
This func recognize file parameters
\param[in] file file pointer
\param[out] nCount number of lines
\param[out] charCount number of symbols
\return -
*/

void file_params(FILE* file, int* nCount, long int* charCount)
{
    assert(file != 0);
    assert(nCount != 0);
    assert(charCount != 0);

    char c = 0;
    do {
        (*charCount)++;
        c = fgetc(file);
        if (c == '\n') (*nCount)++;
    } while (c != EOF);
    fseek(file, 0 , SEEK_SET);
}

/*!
This func read file into arr  !!!FREE(TEXT)!!!
\param[in] file file pointer
\param[in] charCount number of symbols
\return arr with file contents
*/

char* file_to_array(FILE* file, long int charCount)
{
    assert(file != 0);

    char* text = (char*)calloc(charCount, sizeof(char));
    for(int i = 0; i < charCount; i++)
    {
        text[i] = fgetc(file);
    }
    return text;
}

/*!
This func converts text array into array of struct Line  !!FREE(LINES)!!!
\param[in] text[] array with text
\param[in] nCount number of lines
\return arr of struct Lines
*/

struct String * text2lines(char text[], int nCount)
{
    assert(text != 0);

    struct String* line = (struct String*)calloc(nCount, sizeof(struct String));
    line[0].start = text;
    int n = 1;

    for(char *s = strchr(text, '\n'); s; s = strchr(s+1, '\n'))
    {
        *s = '\0';
        line[n].start = s+1;
        line[n-1].len = strlen(line[n-1].start);
        n++;
    }
    return line;
}

/*!
This func - adapter for strcmpX and struct Line (ingnoring punctuation)
\param[in] a 1st struct
\param[in] b 2nd struct
\return strcmpX(noPunct(line1->start), noPunct(line2->start))
*/

int sort1(const void *a, const void *b)
{
    assert(a != 0);
    assert(b != 0);

    struct String *line1 = (struct String*)a;
    struct String *line2 = (struct String*)b;
    return strcmpX(noPunct(line1->start), noPunct(line2->start));
}

/*!
This func - adapter for strcmpRev and struct Line
\param[in] a 1st struct
\param[in] b 2nd struct
\return strcmpRev(line1->start, line2->start)
*/

int sort2(const void *a, const void *b)
{
    assert(a != 0);
    assert(b != 0);

    struct String *line1 = (struct String*)a;
    struct String *line2 = (struct String*)b;
    return strcmpRev(line1->start, line2->start);
}

/*!
This func compare 2 strings (ignores high/low case) (like standard strcmp )
\param[in] p1 1st string
\param[in] p2 2nd string
\return less than, equal to or
   greater than zero if p1 is lexicographically less than,
   equal to or greater than p2.
*/

int strcmpX (const char *p1, const char *p2)
{
    assert(p1 != 0);
    assert(p2 != 0);

    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;

    unsigned char c1, c2;

    do
    {
        c1 = tolower((unsigned char) *s1++);
        c2 = tolower((unsigned char) *s2++);
        if (c1 == '\0')
            return c1 - c2;
    }
    while (c1 == c2);

    return c1 - c2;
}

/*!
This func compare 2 strings from the end (punctuation ignored)(like standard strcmp )
\param[in] p1 1st string
\param[in] p2 2nd string
\return less than, equal to or
   greater than zero if p1 is lexicographically less than,
   equal to or greater than p2.
*/

int strcmpRev (const char *p1, const char *p2)
{
    assert(p1 != 0);
    assert(p2 != 0);

    const char *s1 = p1 + strlen(p1) - 1;
    const char *s2 = p2 + strlen(p2) - 1 ;

    unsigned char c1, c2;

    while(!isalpha(*s1) && s1-- > p1);
    while(!isalpha(*s2) && s2-- > p2);

    do
    {
        c1 = (unsigned char) *s1--;
        c2 = (unsigned char) *s2--;
        if (c1 == '\0')
            return c1 - c2;
    }
    while (c1 == c2 && s1 > p1 && s2 > p2);
    return c1 - c2;
}

/*!
This func ignoring first non alpha symbols
\param[in] inp string
\return pointer to first alpha symbol
*/

char* noPunct(char *inp)
{
    assert(inp != 0);
    int i = 0;
    for(; i < strlen(inp); i++)
    {
        if(!isalpha(inp[i])) continue;
        else break;
    }
    return (inp+i);
}
