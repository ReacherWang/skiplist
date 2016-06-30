/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 六  6/25 14:35:26 2016
 ************************************************************************/

#include<stdio.h>
#include"skiplist.h"

int compare(DataType v1, DataType v2)
{
    if(v1 > v2)
    {
        return 1;
    }
    if(v1 < v2)
    {
        return -1;
    }
    return 0;
}

int main()
{
    Skiplist *head = create();
    for(int i = 1; i < 25; ++i)
    {
        insert(head, i, &compare);
    }
    output(head);
    printf("Please input deleted data:");
    int data = 0;
    scanf("%d", &data);
    deleted(head, data, &compare);
    output(head);
    printf("Please input sraech data:");
    scanf("%d", &data);
    int result = search(head, data, &compare);
    printf("Result is: %d\n", result);
    destroy(&head);
    return 0;
}
