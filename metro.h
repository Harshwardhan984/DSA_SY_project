#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node {
     char * data;
    struct node *next, *prev;
}node;


typedef struct list{
        node  *front, *rear;
}list;


void init(list*);
int isempty(list);
void insertright(list*,  char *);
void insertAtLeft(list *lst,  char *);
void printlistLR(list );
void printlistRL(list );
void removelast(list* l);
int length(list );
void reverse(list *l);
void removeEle(list* l, const char* d);
void addStation(list *metroLine, const char *newStation, const char *line);
void freelist(list*);
int search(list l, char *);
node* pointloc(list* l, const char* d);
int alternate_search(list , const char * );
node* Find_middle(list );
list listunion(const list, list);
 void removeDuplicates(list *l);
 void printfromto(list l, node* p, node*q, int v);
 void findtheroad(list*purpal, list*aqua, char* curr, char* des);
 //file function
 void strlwr(char str[]);
 void loadmetrolist(list* l, const char * file);
 void savelist(list* l, const char * file);
 int isinfile(char*str, const char* file);          
void printwithinit(char a, const char* file);


