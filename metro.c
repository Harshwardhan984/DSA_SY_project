#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "metro.h"


void init(list *l){
    l->front = NULL;
    l->rear = NULL;
}


int isempty(list l){
    if(l.front ==NULL)
         return 1;
    return 0;
}



void insertright(list *l,  char* d) {
  node *newnode = (node*)malloc(sizeof(node));
  newnode->next =NULL;
  newnode->prev =NULL;
   newnode->data = (char*)malloc(strlen(d) + 1); 
    strcpy(newnode->data, d);
  if(!isempty(*l)){
     node *temp = l->front;
     while(temp->next!=NULL)
            temp = temp->next;
     temp->next = newnode;
     newnode->prev = temp;
     l->rear = newnode;
  }
  else{
     l->front = newnode;
     l->rear = newnode;
  }
}

void insertAtLeft(list *lst,  char* d) {
    node *newNode = (node*)malloc(sizeof(node));
    if(newNode){
    	 newNode->data = (char*)malloc(strlen(d) + 1); 
    strcpy(newNode->data, d);
    	newNode->next = lst->front;
    	newNode->prev = NULL;
    }
    else
    	return;

    if (lst->front != NULL) {
        lst->front->prev = newNode;
    }
     else {
        lst->rear = newNode;  
    }
    lst->front = newNode;
    return;
}



void printlistLR(list l) {    
    node *p;
    printf("Fwd: [ ");
    p = l.front;
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%s , ", p->data);
        p = p->next;
    }while(p != NULL);
    printf("]\n");
}

void printlistRL(list l) {
    node *p;
    printf("BWD: [ ");
    p = l.rear;
    printf("%s , ", p->data);
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%s , ", p->data);
        p = p->prev;
    }while(p != NULL);
    printf("]\n");


}

int length(list l){
       int count =0 ;
       node*p = l.rear;
       while(p){
             count++;
             p = p->prev;
    }
    return count;
}


void reverse(list *l){
   node  *p1, *p2;
    char* temp;
   p1 = l->front; 
   p2 = l->rear;
   
   while(p1!=p2 && p2 != p1->prev){
        temp = p1->data;
        p1->data = p2->data;
        p2->data = temp;
        p1=p1->next;
        p2=p2->prev;
   }
  
}


void removelast(list* l){
	if(isempty(*l))
            return;
           node *p = l->rear;
           p->prev->next = NULL;
           l->rear = p->prev;
           free(p);
	return;
}

void removeEle(list* l, const char* d){
	node *current = l->front;
	while(current != NULL ){
		if(strcmp(current->data, d) == 0)
			break;
		current = current->next;
	}
	if (current == NULL) {
    
        return;
    }
	node *left = current->prev;
	node *right = current->next;
	if (left == NULL) {
        l->front = right;
    } else {
        left->next = right;
    }
	if (right == NULL) {
        l->rear = left;
    } else {
        right->prev = left;
    }
    	
	free(current);
	
	printf("%s removed from Data\n", d);
	return;
}

void addStation(list *metroLine, const char *newStation, const char *line) {
    char afterStation[100];
    node *afterNode = NULL;

    // Loop until the user enters a valid existing station
    do {
        printf("Enter the name of the station after which to add '%s': ", newStation);
        scanf("%s", afterStation);
        strlwr(afterStation);

        if (search(*metroLine, afterStation)) {
            afterNode = pointloc(metroLine, afterStation);
            break;
        } else {
            printf("Station '%s' not found in the list. Please try again.\n", afterStation);
            printwithinit(afterStation[0], line);
        }
    } while (1);

    // Create the new station node
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = (char *)malloc(strlen(newStation) + 1);
    if (!newNode->data) {
        printf("Memory allocation failed.\n");
        free(newNode);
        return;
    }
    strcpy(newNode->data, newStation);

    // Insert the new node into the list
    newNode->next = afterNode->next;
    newNode->prev = afterNode;

    if (afterNode->next) {
        afterNode->next->prev = newNode;
    } else {
        metroLine->rear = newNode; // Update the rear if added at the end
    }
    afterNode->next = newNode;

    printf("Station '%s' successfully added after '%s'.\n", newStation, afterStation);
}


void freelist(list *l){
      node *p = l->front;
      node * q;
      while(p){
        q= p;
        p=p->next;
        free(q);
     }
     l->front =NULL;
     l->rear =NULL;
}


int search(list l,  char* d){
     node *ptr = l.front;
     
     while(ptr){
     	if(strcmp(ptr->data ,d) == 0)
     		return 1;
 	ptr=ptr->next;
     }
             
    
        return 0;  
        
}

int alternate_search(list l, const char* d){
	node *p = l.front, *q = l.rear;
	while(p || q){
		
		if(strcmp(p->data, d) == 0)
			return 1;
		else
			p = p->next;
		if(strcmp(q->data, d) == 0)
			return 1;
		else
			q = q->prev;
		if(p == q)
			return 0;
		if(q -> next == p)
			return 0;
		
	}
	return 0;
}

node* pointloc(list* l, const char* d) {
    //printf("\n\n\n in function of pointloc\n\n\n");
    //printf("Received string: %s\n", d);
    if (!l || !l->front || !l->rear) {
        printf("List is empty or invalid.\n");
        return NULL;
    }
    node *p = l->front;
    while (p) {
    //printf("list data string: %s\n", p->data);
        if (p && strcmp(p->data, d) == 0)
            return p;
        
         p = p->next;
    }
    printf("Node with data '%s' not found.\n", d);
    return NULL;
}

node* Find_middle(list l){
	node *p = l.front, *q = l.rear;
	
	while(p || q){
		if(q->next == p)
			return NULL;
		if(p == q)
			return p;
		
		p = p->next;
		q = q->prev;
	}
	return NULL;
}


list listunion(const list l1, list l2){ 
       list l3;
       init(&l3);
       node* ptr1= l1.front;
       while(ptr1){
              insertright(&l3, ptr1->data);
              ptr1=ptr1->next;
       }
       
       node* ptr2 = l2.front;
       while(ptr2){
            if(!search(l3,ptr2->data)){
                 insertright(&l3, ptr2->data);
                 
            }
            ptr2=ptr2->next;
       }
                   
       return l3;
}
            
void removeDuplicates(list *l) {
    node *current = l->front;

    while (current != NULL) {
        node *runner = current->next;
        while (runner != NULL) {
            if (strcmp(runner->data , current->data) == 0) {
                node *temp = runner;
                runner = runner->next;
                if (temp->next != NULL)
                	 temp->next->prev = temp->prev;
                if (temp->prev != NULL) 
                	temp->prev->next = temp->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return;
}


//will Print data from given two pointers [o for backward, 1 for forward]

void printfromto(list l, node* p, node*q, int v){
	int c = 0;
	printf("\n");
	//printf("\n\n\n in function of metro line printing\n\n\n");
	if(v == 1){
		node* t = l.front;
		while(t){
			if(t == p)
				c=1;
			if(t == q){
				printf(" %s \n  |  \n", t->data);
				c=0;
			}
			if(c == 1){
				printf(" %s \n  |  \n", t->data);	
			}
			t = t->next;
		}
		return;
	}
	else{
		node* t = l.rear;
		while(t){
			if(t == p)
				c=1;
			if(t == q){
				printf(" %s \n  |  \n", t->data);
				c=0;
			}
			if(c == 1){
				printf(" %s \n  |  \n", t->data);	
			}
			t = t->prev;
		}
		return;
	}
}

void findtheroad(list*purpal, list*aqua, char* curr, char* des){
	//printf("\n\n\n in function of metro\n\n\n");
	node* currpoint = NULL;
	node* despoint = NULL;
	// 1 for purpal line , 0 for aqua line
	int c, d;
	if(search(*purpal,  curr)){
		//printf("ur curr in purpal line\n");
		//printf("\n\n\n in function of metro of cheak line\n\n\n");
		c = 1;
		currpoint = pointloc(purpal, curr);
	}
	else{
		//printf("ur curr in aqua line\n");
		//printf("\n\n\n in function of metro of cheak line\n\n\n");
		c = 0;
		currpoint = pointloc(aqua, curr);
	}
	if(search(*purpal, des)){
		//printf("ur des in purpal line\n");
		//printf("\n\n\n in function of metro of cheak line\n\n\n");
		d = 1;
		despoint = pointloc(purpal, des);
	}
	else{
		//printf("ur des in aqua line\n");
		//printf("\n\n\n in function of metro of cheak line\n\n\n");
		d = 0;
		despoint = pointloc(aqua, des);
	}
	//find if in different line 
	
	node *civilpurpalpoint = pointloc(purpal, "civil_court");
	node *civilaquapoint = pointloc(aqua, "civil_court");
	
	node* trav;
	if(c==0 && d==0){
		trav = aqua->front;
		while(trav){
			if(trav == currpoint){
				printfromto(*aqua, currpoint, despoint, 1);
				break;
			}
			else if(trav == despoint){
				printfromto(*aqua, currpoint, despoint, 0);
				break;
			}
			trav = trav->next;
		}
	}
	
	 if(c==1 && d==1){
		trav = purpal->front;
		while(trav){
			if(trav == currpoint){
				printfromto(*purpal, currpoint, despoint, 1);
				break;
			}
			else if(trav == despoint){
				printfromto(*purpal, currpoint, despoint, 0);
				break;
			}
			trav = trav->next;
		}
	}
	
	//curr in aqua, des in purpal
	 if(c==0 && d==1){
		trav = aqua->front;
		while(trav){
			if(trav == currpoint){
				printfromto(*aqua, currpoint,civilaquapoint , 1);
				break;
			}
			else if(trav == civilaquapoint){
				printfromto(*aqua, currpoint, civilaquapoint, 0);
				break;
			}
			trav = trav->next;
		}
		printf("u have to change line to PURPLE(purple colour)\n");
		trav = purpal->front;
		while(trav){
			if(trav == despoint){
				printfromto(*purpal, civilpurpalpoint, despoint , 0);
				break;
			}
			else if(trav == civilpurpalpoint){
				printfromto(*purpal, civilpurpalpoint, despoint, 1);
				break;
			}
			trav = trav->next;
		}
	}
	
	//curr in purpal, des in aqua
	 if(c==1 && d==0){
		trav = purpal->front;
		while(trav){
			if(trav == currpoint){
				printfromto(*purpal, currpoint,civilpurpalpoint , 1);
				break;
			}
			else if(trav == civilpurpalpoint){
				printfromto(*purpal, currpoint, civilpurpalpoint, 0);
				break;
			}
			trav = trav->next;
		}
		printf("u have to change line to AQUA(blue colour)\n");
		trav = aqua->front;
		while(trav){
			if(trav == despoint){
				printfromto(*aqua, civilaquapoint, despoint , 0);
				break;
			}
			else if(trav == civilaquapoint){
				printfromto(*aqua, civilaquapoint, despoint, 1);
				break;
			}
			trav = trav->next;
		}
	}
	
	
	/*printf("%d\n",c);
	printf("%d\n",d);
	printf("%s\n", currpoint->data);
	printf("%s\n", despoint->data);
	*/
	
	return;
}

// File function 

void strlwr(char str[]){
	int i;
	for(i=0;str[i] != '\0'; i++){
		str[i] = tolower(str[i]);
	}
	return;
}

void loadmetrolist(list* l, const char * file){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[100]; 

    while (fscanf(fptr, "%99s", buffer) != EOF /*fgets(buffer, sizeof(buffer), fptr)!= NULL*/) {
    	strlwr(buffer);
        insertright(l, buffer); 
    }

    fclose(fptr);
       return;
}

void savelist(list* l, const char * file){
	FILE *fptr;
      fptr = fopen(file, "w"); 
      if (!fptr) {
        printf("Error opening file.\n");
        return;
    }

	node *p;
    p = l->front;
    while(p){
       fprintf(fptr, "%s\n", p->data);
        p = p->next;
    }
     fclose(fptr);
    return;
}

int isinfile( char*str, const char* file){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return -1;
    }
    char buffer[100]; 

    while (fscanf(fptr, "%99s", buffer) != EOF) {
    	strlwr(buffer);
        if(strcmp(str, buffer) == 0)
        	return 1; 
    }
    fclose(fptr);
    return 0;
    
}

void printwithinit(char a, const char* file){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return ;
    }
    char buffer[100]; 

    while (fscanf(fptr, "%99[^\n]\n", buffer) != EOF) {
        strlwr(buffer);
        if(buffer[0] == a){
        	printf("%s\n", buffer);
        }
    }
    fclose(fptr);
    return ;
}


