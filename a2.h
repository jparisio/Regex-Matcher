#ifndef A2_H
#define A2_H

int match(char *regexp, char *text, int *indicies, int *match_count);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);
int matchplus(int c, char *regexp, char *text);
int matchqmark(char c, char *regexp, char *text);
int matchset(char *regexp, char *text);

// int matchset(char *regexp, char *text)
// {
//     while (regexp[0] != ']' && regexp[0] != '\0') {
//         if (regexp[1] == '-' && regexp[2] >= regexp[0]) {
//             if (*text >= regexp[0] && *text <= regexp[2]) {
//                 return 1;
//             }
//             regexp += 3;
//         } else if (regexp[0] == *text) {
//             return 1;
//         }
//         regexp++;
//     }

//     return 0;
// }

#endif