/*************************************************************************
	> File Name: util.c
	> Author: 
	> Mail: 
	> Created Time: 五  6/24 20:35:47 2016
 ************************************************************************/

#include<stdlib.h>

int randomlevel(int max)
{
    int level = 1;
    while(rand() % 2)
    {
        ++level;
    }
    return max > level ? level : max;
}
