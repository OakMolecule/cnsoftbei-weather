#include <stdio.h>
#include <string.h>
void num2cn(int num, char *buf)
{
    long n,i;
    int a[20];
    char s[10][5] = {"两","一","二","三","四","五","六","七","八","九",};
    char w[1][5] = {" ","十","百","千"};
    for(i = 0; num > 0; i++)
    {
        a[i] = num % 10;
        num = num / 10;
    }
    a[i] = 999;
    for(int j = i - 1; j >= 0; j--)
    {

        if(a[j] == 0)
        {
                if(a[j-1]!=0&&j!=4&&j!=8&&j!=0)
                printf("%s", s[a[j]]);
                sprintf(buf, "%s%s", buf, s[a[j]]);
        }
        else
        {
            if(!((j==i-1)&&(a[j]==1))) {
                printf("%s", s[a[j]]);
                sprintf(buf, "%s%s", buf, s[a[j]]);
            }
            switch((j+1)%4)
            {
                case 2:
                    printf("十");
                    sprintf(buf, "%s十", buf);
                    break;
                case 3:
                    printf("百");
                    sprintf(buf, "%s百", buf);
                    break;
                case 0:
                    printf("千");
                    sprintf(buf, "%s千", buf);
                    break;
                default:
                    break;
            }
        }
        if(j==4) {
            printf("万");
            sprintf(buf, "%s万", buf);
        }

        if(j==8) {
            printf("亿");
            sprintf(buf, "%s亿", buf);
        }
    }
    printf("\n");
    printf("%s\n", buf);
}

