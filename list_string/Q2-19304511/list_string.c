//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_string.h"



// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string * new_list_string(char * text) {
    struct list_string * newString;
    newString= malloc(sizeof(struct list_string));
    struct ls_node * node;
    node= malloc(sizeof(struct ls_node));
    int j=0,length=0,i;
    while (text[j]!='\0')
    {
        length++;
        j++;
    }
    node->c=text[0];
    node->next=NULL;
    newString->head= node;
    for (i = 1; i<length; i++) 
    {
        struct ls_node *temp = malloc(sizeof(struct ls_node));
        node->next = temp;
        temp->c = text[i];
        temp->next = NULL;
        node = temp;
    }
    return newString;
}

// find the length of the list string
int list_string_length(struct list_string * this) {

    struct ls_node * node;
    node= malloc(sizeof(struct ls_node));
    int count=0;
    if(this->head==NULL)
    {
        return count;
    }
    else
    {
        for(node=this->head; node!=NULL; node= node->next)
        {
            count++;
        }
    }
    return count;
}


// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd". 
int list_string_compare(struct list_string * s1, struct list_string * s2) {
    struct ls_node * node1;
    struct ls_node * node2;
    node1=s1->head;
    node2=s2->head;
    while(node1&&node2&&node1->c==node2->c)
    {
        if(node1->c=='\0' && node2->c=='\0')
        {
            break;
        }
        node1=node1->next;
        node2=node2->next;
    }

    if(node1&&node2)
    {
        if(node1->c<node2->c)
        {
            return -1;
        }
        else if(node1->c==node2->c)
        {
            return 0;
        }
        else if(node1->c>node2->c)
        {
            return 1;
        }
    }
    else if(node1&&!node2)
    {
        return 1;
    }     
    else if(!node1&&node2) 
    {
        return -1;
    }
    return 0;
}


// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string * text, struct list_string * str) {
    struct ls_node * node1;
    struct ls_node * node2;
    struct ls_node * nodeTp;

    node1=text->head;
    int text_length=list_string_length(text);
    int str_length= list_string_length(str);

    for(int i=0; i<=(text_length-str_length); i++)
    {
        int j;
        node2=str->head;
        nodeTp=node1;
        for(j=0;j<str_length; j++)
        {
            if(nodeTp->c!=node2->c)
            {
                break;
            }
            else if(nodeTp->c==node2->c)
            {
                nodeTp=nodeTp->next;
                node2=node2->next;
            }    
        }
        if(j==str_length)
            {
                return 1;
            }
        node1=node1->next;
    }
    return 0;
}


