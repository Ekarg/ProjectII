#include "master.h"

struct list* initlist()
{
  struct list* node = (struct list*)calloc(1,sizeof(struct list));
  node->next = NULL; 
  return(node);
}


void addlist(int id,char* userid,struct list* head)
{
  struct list* node =head;
  while(node->next) 
  {node = node->next;}
  node->id =id;
  strcpy(node->userid,userid);
  node->next = initlist();
}


struct list* deletelist(int id,struct list* head)
{
  struct list* node =head;
  if(node->id ==id)
  {
    head = node->next;
    free(node);
    return(head) ;
  }
  
  do{
    if(node->next->id == id) 
    {
      struct list* next =node->next->next;
      free(node->next);
      node->next = next;
      return(head);
    }
    else
      node = node->next;
  }while(node->next->next) ;
}



int searchlist(int id,struct list* head,char* userid)
{
  struct list* node =head;
  while(node->next)
  {
    if(node->id == id){
    strcpy(userid,node->userid);
    return(1);
    }
    node = node->next;
  }
  return(0);
}



int check_list(struct list* head, char* userid)
{
 struct list*node =head;
 while(node->next)
 {
  if(strcmp(userid,node->userid)==0)
  return(0);
  node = node->next;
 }
return(1);
}



int list_size(struct list* new)
{
  struct list* node =new;
  int count=0;
  while(node->next)
  {
      count++;
      node=node->next;
  }  
  return(count);
}


void printlist(struct list* new)
{
  struct list* node =new;
  while(node->next)
  {
      printf("id:%d\tuser:%s\n",node->id,node->userid);
      node = node->next;
  }     
}
