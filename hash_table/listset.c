#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {

  struct listset * result;
  result= malloc(sizeof(struct listset));
  assert(result != NULL);
  result-> head = NULL;
  return result;

}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {

  struct listnode * node;
  for(node= this->head;node!=NULL;node=node->next)
  {
    if(strcmp(node->str, item)==0)
    {
      return 1;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {

  if(listset_lookup(this,item)==0)
  {
    struct listnode * current_node;
    current_node= malloc(sizeof(struct listnode));
    current_node->str = item;
    current_node->next= this->head;
    this->head= current_node;
  }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {

  struct listnode * delete_node;
  struct listnode * previous_node;
  previous_node=NULL;
  delete_node= this->head;

  if(listset_lookup(this,item)==1)
  {
    if(strcmp(delete_node->str,item)==0)
    {
      this->head= delete_node->next;
      return;
    }
    //for(previous_node=this->head && delete_node=previous_node->next; previous_node!=NULL && delete_node!=NULL; 
      //            previous_node=previous_node->next && delete_node=delete_node->next)
    previous_node=this->head;
    delete_node=previous_node->next;
    while(previous_node!=NULL && delete_node!=NULL)              
    {
      if(strcmp(delete_node->str, item)==0)
      {
        previous_node->next=delete_node->next;
        delete_node->next=NULL;
        return;
      }
      previous_node=previous_node->next;
      delete_node=delete_node->next;
    }
  }
  return;

}
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
  
  struct listnode * node1;
  struct listnode * node2;
  for(node1=src1->head;node1!=NULL;node1=node1->next)
  {
    listset_add(dest,node1->str);
  }
  for(node2=src2->head;node2!=NULL;node2=node2->next)
  {
    if(listset_lookup(dest,node2->str)==0)
    {
      listset_add(dest,node2->str);
    }
  }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {

  struct listnode * node1;
  struct listnode * node2;
  for(node1=src1->head;node1!=NULL;node1=node1->next)
  {
    for(node2=src2->head;node2!=NULL;node2=node2->next)
    {
      if(strcmp(node1->str,node2->str)==0)
      {
        listset_add(dest,node2->str);
      }
    }
  }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
  
  struct listnode * node;
  node= malloc(sizeof(struct listset));
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
    return count;
  }
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
