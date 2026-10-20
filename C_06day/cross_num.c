#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int ch, sum = 0;

    printf("Enter phone number: ");
    while ((ch = getchar()) != '\n' && ch != EOF) {
       
            switch (toupper(ch)) {       /* 统一按大写判断 */
                case 'A': case 'E': case 'I':case 'N':case 'O':case 'R':case 'S':case 'T':case 'U':case 'L':
                    ch = 1;sum += ch; break;
                case 'D': case 'G':
                   ch = 2;sum += ch; break;
                case 'B': case 'C': case 'M': case 'P':
                    ch = 3;sum += ch; break;
                case 'F': case 'H': case 'V': case 'W': case 'Y': 
                   ch = 4;sum += ch; break;
                case 'K':
                   ch = 5;sum += ch; break;
                case 'J': case 'X':
                   ch = 6;sum += ch; break;
                case 'Q':case 'Z':
                   ch = 7;sum += ch; break;
                
                default:                     /* 括号、空格、连字符等直接忽略 */
                    break;
            }
        }
    
        printf("sum = %d",sum);

    return 0;
}
