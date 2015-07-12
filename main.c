#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int split_string(char *pstr)
{
    int i = 0;
    char cc;
    char *temp = pstr;
    char *ss[20];
    int clen1 = 0, clen2 = 0;
    int start1 = 0, end1 = 0;
    int start2 = 0, end2 = 0;
    char flag1 = 0, flag2 = 0;

    for(i = 0; i < 20; i++)
        ss[i] = NULL;

    printf("target string=%s\n", pstr);
    printf("temp string=%s\n", temp);

    i = 0;
    while(*temp != '\0')
    {
        cc = *temp;
        clen1++;
        clen2++;
        switch(cc)
        {
            case '{' :
                   start1 = clen1 - 1;
                   flag1++;
                   printf("find { at %d\n", start1);
                   break;
            case '}' :
                   end1 = clen1 - 1;
                   if(flag1 != 0)
                   {
                       flag1--;
                       printf("find } at %d,len=%d\n", end1, end1 - start1 - 1);
                       ss[i] = malloc(end1 - start1 + 2);
                       strncpy(ss[i++], pstr + start1 - 1, end1 - start1 + 2);
                   }
                   else
                   {
                       printf("find } at %d, but no {\n", end1);
                       clen1 = start1 = end1 = 0;
                   }
                   break;
            case '[' :
                   start2 = clen2 - 1;
                   flag2++;
                   printf("find [ at %d\n", start2);
                   break;
            case ']' :
                   end2 = clen2 - 1;
                   if(flag2 != 0)
                   {
                       flag2--;
                       printf("find ] at %d,len=%d\n", end2, end2 - start2 - 1);
                       ss[i] = malloc(end2 - start2 + 2);
                       strncpy(ss[i++], pstr + start2 - 1, end2 - start2 + 2);
                   }
                   else
                   {
                       printf("find ] at %d, but no [\n", end2);
                       clen2 = start2 = end2 = 0;
                   }
                   break;
            case '*' :
                   break;
            case '|' :
                   break;
            case '?' :
                   break;
            case '+' :
                   break;
            default :
                   break;
        }
        temp++;
    }

    for(i = 0; i < 20; i++)
    {
        printf("%d:%s\n", i, ss[i]);
        if(ss[i] != NULL)
            free(ss[i]);
    }

    return i;
}

int main(int argc, char *argv[])
{
    int i;
    printf("argc=%d\n", argc);
    for(i = 0; i < argc; i++)
        printf("argv[%d]=%s\n", i, argv[i]);

    split_string(argv[1]);

    return 0;
}
