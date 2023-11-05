#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a2.h"


int match(char *regexp, char *text, int *indicies, int *match_count)
{
    if (regexp[0] == '^')
        return matchhere(regexp+1, text);
    int i = 0;
    
    do { 

        if(matchhere(regexp, text) && *text != '\0'){
            indicies[*match_count] = i;
            *match_count += 1;
        }
        
        i++;

        //greedy skip
        int skip = 0;
        if(regexp[0] == '['){
            for(int i = 0; i < strlen(regexp); i++){
                if(regexp[i] == '*' || regexp[i] == '+'){
                    skip = 1;
                } 
            }
            if(skip){
                while(*text >= regexp[1] && *text < regexp[3]){
                    *text++;
                    i++;
                }
                //printf("%c\n", *text);
            }
        } else{

            while(text[0] == text[1] && (regexp[1] == '*' || regexp[1] == '+')){
                *text++;
                i++;
            }
        }

    } while (*text++ != '\0');
    
    return *match_count > 0;
}

int matchhere(char *regexp, char *text)
{  
    if(regexp[0] == '/')
        return matchhere(regexp+1, text);
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp+2, text);
    if(regexp[1] == '+')
        return matchplus(regexp[0], regexp+2, text);
    if(regexp[1] == '?')
        return matchqmark(regexp[0], regexp+2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (regexp[0] == '[')
        return matchset(regexp + 1, text);
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return matchhere(regexp+1, text+1);

    return 0;
}

int matchstar(int c, char *regexp, char *text)
{
	char *t;

	for (t = text; *t != '\0' && (*t == c || c == '.'); t++)
		;
	do {	/* * matches zero or more */
		if (matchhere(regexp, t))
			return 1;
	} while (t-- > text);
	return 0;
}

int matchplus(int c, char *regexp, char *text)
{
    if (*text == c || (c == '.' && *text != '\0')) {
        if (matchhere(regexp, text + 1))
            return 1;
    }
    
    return 0;
}

int matchqmark(char c, char *regexp, char *text)
{
    if (*text == c || (c == '.' && *text != '\0')) {
        if (matchhere(regexp, text + 1) && !matchhere(regexp, text+2))
            return 1;
    }

    if (matchhere(regexp, text))
        return 1;

    return 0;
}


int matchset(char *regexp, char *text)
{
    //loop that determines if thers a quantifier ( * or ?)
    int quantifier = 0;
    for(int i = 0; i < strlen(regexp); i++){
        if(regexp[i] == '*' || regexp[i] == '?'){
            quantifier = 1;
        } 
    }

    while (regexp[0] != ']' && regexp[0] != '\0') {
        if(quantifier)
            return 1;
        if (regexp[1] == '-' && regexp[2] >= regexp[0]) {
            if (*text >= regexp[0] && *text <= regexp[2])
                return 1;
            //by two here since we automatically increment by one at the end of the loop so dont do the full three
            *regexp += 2;
        //checks for single character
        } else if (regexp[0] == *text) {
            return 1;
        }
        //increment text by one in case theres no - operand and no range
        *regexp++;
    }

    return 0;
}



int main(int argc, char *argv[])
{

    FILE *ptr = fopen(argv[argc - 1], "r");
    if (ptr == NULL) {
        printf("file dne");
        return 0;
    }

    char regex[2][1000];

    int line = 0;

    //read in each of the two lines
    while(!feof(ptr) && !ferror(ptr)){
        if(fgets(regex[line], 50, ptr) != NULL){
            line++;
        }
    }

    //remove newlines
    regex[0][strcspn(regex[0], "\n")] = 0;
    regex[1][strcspn(regex[1], "\n")] = 0;



    // printf("%s\n", regex[0]);
    // printf("%s\n", regex[1]);

    int indices[1000];
    int match_count = 0;


    if (match(regex[0], regex[1], indices, &match_count)) {
        printf("matches: ");
        for (int i = 0; i < match_count; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
    } else {
        printf("no match\n");
    }



    return 0;
}