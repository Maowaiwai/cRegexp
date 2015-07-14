#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define STRING_MAX_LEN 200

char g_str_regexp[STRING_MAX_LEN];

int is_substring(char *src, char *dest)
{
    return strncmp(src, dest, strlen(dest));
}

int search_substring(char *target, char *pattern)
{
    char *stemp = target;
    int times = 0;

    //printf("search substring %s ...\n", pattern);
    while(*stemp != '\0')
    {
        if(is_substring(stemp, pattern) == 0)
            times++;

        stemp++;
    }
    printf("  pattern %s found %d times\n", pattern, times);
    //printf("Done!\n");

    return 0;
}

int regexp_match(char *src, char *regexp)
{
    char *str_temp = regexp;
    int tpos1 = 0, tpos2 = 0;
    int index = 0;
    int value = 0;
    int search_flag = 0;
    int j_inc_flag = 1;
    int j = 0;

    while(*str_temp != '\0')
    {
        switch(*str_temp)
        {
            case '{' :
                tpos1 = index;
                j_inc_flag = 0;
                printf("'{' : %2d %s\n", j, g_str_regexp);
                break;

            case '}' :
                tpos2 = index;
                j_inc_flag = 1;
                if(tpos2 > tpos1)
                    value = atol(regexp + tpos1 + 1);
                memset(g_str_regexp + tpos1, *(regexp + tpos1 - 1), value - 1);
                j += value - 1;
                
                printf("'}' : %2d %s\n", j, g_str_regexp);
                search_substring(src, g_str_regexp);
                break;
            
            case '?' :
                j_inc_flag = 1;
                g_str_regexp[j - 1] = '\0';
                printf("'?' : %2d %s\n", j, g_str_regexp);
                search_substring(src, g_str_regexp);

                g_str_regexp[j - 1] = *(regexp + index - 1);
                j++;
                printf("'?' : %2d %s\n", j, g_str_regexp);
                search_substring(src, g_str_regexp);
                break;
            
            default :
                if(j_inc_flag)
                    g_str_regexp[j++] = *str_temp;
                printf("'d' : %2d %s\n", j, g_str_regexp);
        }
        if(search_flag)
            search_substring(src, g_str_regexp);
        index++;
        str_temp++;
    }
}

int main(int argc, char *argv[])
{
    int i;
    char *pattern = NULL;

    memset(g_str_regexp, 0, sizeof(g_str_regexp));
   
    //printf("argc=%d\n", argc);
    //for(i = 0; i < argc; i++)
    //    printf("argv[%d]=%s\n", i, argv[i]);

    regexp_match(argv[1], argv[2]);
       
    return 0;
}


