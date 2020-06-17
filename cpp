#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define M 5000
typedef struct node
{
	int count;
	char word[26];
	struct node *lchild, *rchild;  
	
}BTNode, *BTREE; 
int times = 0;
int get_word(char *temp_word, FILE *in);
BTREE insert(BTREE T, char temp_word[]); 
void inorder(BTREE root);
int main()
{
	char temp_word[26] = {0}; 
 
   	FILE *in;
    int i,j;
 
	if( (in = fopen("article.txt", "r")) == NULL )
    printf("No such file!\n");
    
    BTREE root = NULL;        
	while( !feof(in) )
	{
		char temp_word[26] = {0};
		get_word(temp_word,in);
		root = insert(root, temp_word);
	}
	printf("%s ", root->word);
	if(root->rchild != NULL && root->rchild->rchild == NULL)  
	printf("%s\n", root->rchild->word );
		
	else 
	printf("%s ", root->rchild->word );
		
	if(root->rchild->rchild != NULL)  
	printf("%s\n", root->rchild->rchild->word);
	
	inorder(root);  
	
	return 0;
}
 
int get_word(char *temp_word, FILE *in)
{
	int i = 0; 
    char temp = '0';
    temp = fgetc(in);
	while( !isalpha(temp) )
    {
		temp = fgetc(in);
		if(temp==EOF)
		return 1;
	}
 
	while(isalpha(temp) && !isspace(temp) )	
	{
		temp = tolower(temp);
		temp_word[i] = temp;
		i++;
		temp = fgetc(in);
	}
 
    return 0;
}
 
 
BTREE insert(BTREE p, char temp_word[])
{
	int cond;
	if(p == NULL)
	{
		p = (BTREE)malloc(sizeof(BTNode));
		strcpy(p->word, temp_word);
		p->count = 1;
		p->lchild = p->rchild = NULL;
	}
 
	else if( (cond  = strcmp(temp_word, p->word)) == 0)
	{
		p->count++;
	}
	else if( cond<0 )
	{
		p->lchild = insert(p->lchild, temp_word);
	}
	else 
	{
		p->rchild = insert(p->rchild, temp_word);
	}
	return (p);
}
 
void inorder(BTREE T) 
{
	 if(T!= NULL)
    {	
    	inorder(T->lchild);
    	if( strlen(T->word) >0 )
    	printf("%s %d\n", T->word, T->count);
    	inorder(T->rchild);
	}
}
