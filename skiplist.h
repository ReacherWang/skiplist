/*************************************************************************
	> File Name: skiplist.h
	> Author: 
	> Mail: 
	> Created Time: 三  6/22 15:39:43 2016
 ************************************************************************/

#ifndef _SKIPLIST_H
#define _SKIPLIST_H

//跳跃表最大层数
#define MAX_LEVEL 6 

//跳跃表存储数据类型
typedef int DataType;

//跳跃表节点类型
typedef struct node
{
    DataType data;
    struct node *nexts[0];//柔性数组
}Node;

//跳跃表数据类型
typedef struct skiplist
{
    int level;//层数
    Node *head;//指向头结点
}Skiplist;

static Node *createnode(int level, DataType data);

static int destroynode(Node **node);

Skiplist *create();

void insert(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2));

int deleted(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2));

int search(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2));

void destroy(Skiplist **head);

void output(Skiplist *head);

#endif
