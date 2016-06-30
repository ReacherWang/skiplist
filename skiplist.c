/*************************************************************************
	> File Name: skiplist.c
	> Author: 
	> Mail: 
	> Created Time: 三  6/22 15:39:30 2016
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"skiplist.h"
#include"util.h"

static Node *createnode(int level, DataType data)
{
    Node *node = (Node *)malloc(sizeof(Node) + level * sizeof(Node*));
    
    assert(NULL != node);

    node->data = data;

    return node;
}

static int destroynode(Node **node)
{
    if(NULL == *node)
    {
        return 0;
    }
    free(*node);
    *node = NULL;
    return 1;
}

Skiplist *create()
{
    Skiplist *head = (Skiplist *)malloc(sizeof(Skiplist));
    
    assert(NULL != head);
    
    head->level = 0;
    head->head = createnode(MAX_LEVEL, 0);

    for(int i = 0; i < MAX_LEVEL; ++i)
    {
        head->head->nexts[i] = NULL;
    }
    return head;
}

void insert(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2))
{
    Node *next = NULL;
    Node *cur = head->head;

    Node *updates[MAX_LEVEL] = {NULL};
    for(int i = head->level - 1; i >= 0; --i)
    {
        while((next = cur->nexts[i]) && compare(data, next->data) > 0)
        {
            cur = next;
        }
        updates[i] = cur;
    }

    int level = randomlevel(MAX_LEVEL);
    if(level > head->level)
    {
        for(int i = head->level; i < level; ++i)
        {
            updates[i] = head->head;
        }
        head->level = level;
    }

    Node *node = createnode(level, data);
    for(int i = level - 1; i >= 0; --i)
    {
        node->nexts[i] = updates[i]->nexts[i];
        updates[i]->nexts[i] = node;
    }
}

int deleted(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2))
{
    if(NULL == head)
    {
        return 0;
    }
    Node *next = NULL;
    Node *cur = head->head;

    Node *updates[MAX_LEVEL] = {NULL};
    for(int i = head->level - 1; i >= 0; --i)
    {
        while((next = cur->nexts[i]) && compare(data, next->data) > 0)
        {
            cur = next;
        }
        updates[i] = cur;
    }
    if(NULL != next && compare(data, next->data) != 0)
    {
        return 0;
    }
    for(int i = head->level - 1; i >= 0; --i)
    {
        if(updates[i]->nexts[i] == next)
        {
            updates[i]->nexts[i] = next->nexts[i];
            if(NULL == head->head->nexts[i])
            {
                head->level--;
            }
        }
    }
    return destroynode(&next);
}

int search(Skiplist *head, DataType data, int (*compare)(DataType v1, DataType v2))
{
    if(NULL == head)
    {
        return 0;
    }
    Node *next = NULL;
    Node *cur = head->head;

    for(int i = head->level - 1; i >= 0; --i)
    {
        while((next = cur->nexts[i]) && compare(data, next->data) > 0)
        {
            cur = next;
        }
        if(NULL != next && data == next->data)
        {
            return 1;
        }
    }
    return 0;

}

void destroy(Skiplist **head)
{
    if(NULL == *head)
    {
        return;
    }
    Node *node = NULL;
    while(NULL != (node = (*head)->head))
    {
        (*head)->head = node->nexts[0];
        destroynode(&node);
    }
    free(*head);
    *head = NULL;
}

void output(Skiplist *head)
{
    Node *node = NULL;
    for(int i = head->level - 1; i >= 0; --i)
    {
        node = head->head->nexts[i];
        printf("leve %d: ", i + 1);
        while(NULL != node)
        {
            printf("%d---->", node->data);
            node = node->nexts[i];
        }
        printf("\b\b\b\b\b\n");
    }
}
