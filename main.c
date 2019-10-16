#include <poemsort.h>

const char INPUT_FILE[] = "E:/Programming/NewOnegin/hamlet.txt";
const char OUTPUT_FILE[] = "E:/Programming/NewOnegin/hamlet-for-mathmatics.txt";

int main()
{
    printf("%s\n", INPUT_FILE);

    FILE *inp_file = fopen(INPUT_FILE, "r");
    FILE *out_file = fopen(OUTPUT_FILE, "w");

    if(inp_file == NULL) printf("BAN1\n");
    if(out_file == NULL) printf("BAN2\n");

    int nCount = 0;
    long int charCount = 0;
    file_params(inp_file, &nCount, &charCount);
    char *text = file_to_array(inp_file, charCount);
    struct String* Line = text2lines(text, nCount);

    qsort(Line, nCount, sizeof(struct String), sort1);
    for (int i = 0; i < nCount; i++)
    {
        fwrite(Line[i].start, sizeof(char), Line[i].len, out_file);
        fprintf(out_file,"\n");
    }

    qsort(Line, nCount, sizeof(struct String), sort2);
    for (int i = 0; i < nCount; i++)
    {
        fwrite(Line[i].start, sizeof(char), Line[i].len, out_file);
        fprintf(out_file,"\n");
    }

    for(int i = 0; i < charCount; i++)
    {
        if(text[i] == '\0')
        {
            fputc('\n', out_file);
            continue;
        }
        fputc(text[i], out_file);
    }

    fclose(inp_file);
    fclose(out_file);
    free(text);
    free(Line);

}
