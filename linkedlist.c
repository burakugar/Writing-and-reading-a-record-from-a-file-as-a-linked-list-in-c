#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct node{
	char country[20];
	char capital[20];
	int population;
	bool driving_side; /* true:right wrong: left */
}node;
typedef struct node1{
	char country[20];
	char capital[20];
	int population;
	bool driving_side; /* true:right wrong: left */
	struct node1* next;
}node1;
void addList(node** country,int i){
	int b; /* this function adds the elements to the struct array */
	printf("Country name: ");
	scanf("%s",(*country[i]).country);
	printf("\nCapital: ");
	scanf("%s",(*country[i]).capital);
	printf("\nPopulation of %s : ",(*country[i]).country);
	scanf("%d",&(*country[i]).population);
	printf("\nDo people in the %s drive on the right side? (Yes: 1, No:0) : ",(*country[i]).country);
	scanf("%d",&b);
	if(b==1){
		(*country[i]).driving_side= true;
	}
	else{
		(*country[i]).driving_side= false;
	}

}
void createFile(node** country,int i){
	FILE* fp= fopen("countries.txt","w"); /* creating the file */
	int j;
	for(j=0;j<i;j++){ /* writing data to the file */
		fprintf(fp,"%s %s %d ", (*country[i]).country,(*country[i]).capital,(*country[i]).population );
		if((*country[i]).driving_side==true){
			fprintf(fp,"Right"); /* handling bool driving side*/
		}
		else{
			fprintf(fp,"Left");
		}
		fprintf(fp,"\n"); 
	}
	fclose(fp);
}
void append(node1** head_ref, char country[20],char capital[20],int population,bool driving_side)
{
    /* 1. allocate node */
    node1* new_node = ( node1* ) calloc(1,sizeof(node1));
   	node1* last = *head_ref;  /* used in step 5*/
    /* 2. put in the data  */
    strcpy(new_node->country,country);
	strcpy(new_node->capital,capital);
  	new_node->population=population;
  	new_node->driving_side=driving_side;
 
    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    } 
      
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;   
}
void createList(int count,node1** head){
	FILE* fp= fopen("countries.txt","r"); /* reading the data from file by fgets line by line and parsing the data with sscanf */
	char country[20];
	char capital[20];
	int population;
	bool driving_side;
	char d[5];
	int j;
	char temp[100];
	for(j=0;j<count;j++){
		fgets(temp,100,fp); /* assingning the data to the fgets */
		sscanf(temp,"%s %s %d %s",country,capital,&population,d); /* parsing the temp */
		if(strcmp(d,"right")==0){
			driving_side=true;
		}
		else{
			driving_side=false;
		}
		append(head,country,capital,population,driving_side); /* appending the node at the end of the linked list */
	}
	fclose(fp);
}
void printList(node1* head){
     while (head != NULL) /* printing the linked list*/
  {
     printf(" Country: %s Capital: %s Population: %d", head->country,head->capital,head->population);
     if(head->driving_side==true){
     	printf("Driving side: Right\n");
	 }
	 else{
	 	printf("Driving side: Left\n");
	 }
	 head = head->next; /* moving head to the next node */
  }
}

int main(){
	int i=0,n,count=5;
	node1* head=NULL;
	int a;
	node* country= (node*) calloc(100,sizeof(node));
	while(1){
		printf("Please choose a menu !");
		printf("\n1: Enter new record: ");
		printf("\n2: Write to the file: ");
		printf("\n3: Read from the file: ");
		printf("\n4: Print the linked list : ");
		printf("\n5: Exit:\n");
		printf("Your choise: ");
		scanf("%d",&n);
		if(n==1){
		count+1;
		country=(node*)realloc(country,sizeof(node)*count);
		addList(&country,i);
		i++;	
		}
		else if(n==2){
			createFile(&country,i);
		}
		else if(n==3){
			createList(count,&head);
		}
		else if(n==4){
			printList(head);
		}
		else if(n==5){
			exit(1);
		}

	}
	return 0;
}
