#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct nod
{
  int inf;
  int fii;
  struct nod* nr[100];
};

struct node_bin
{
    int key;
    struct node_bin *left;
    struct node_bin *right;
    int height;
};
 

struct nod* coada[50];
struct node_bin * root_bin = NULL;
struct nod * adaugare(void);
void largime(struct nod *); 



// Functia ce gaseste maximul dintre 2 cifre
int max(int a, int b);
 
// Gasirea inaltimei
int height(struct node_bin *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
// Functia ce creeaza un nou nod de tip FRUNZA 
struct node_bin* newnode_bin(int key)
{
    struct node_bin* node_bin = (struct node_bin*)
                        malloc(sizeof(struct node_bin));
    node_bin->key   = key;
    node_bin->left   = NULL;
    node_bin->right  = NULL;
    node_bin->height = 1;  
    return(node_bin);
}
 
// ROTIREA ARBORELUI (Dreapta)
struct node_bin *rightRotate(struct node_bin *y)
{
    struct node_bin *x = y->left;
    struct node_bin *T2 = x->right;
 
    //ROTIREA
    x->right = y;
    y->left = T2;
 
    // Inoirea inaltimelor
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Returnam nou radacina 
    return x;
}
 
// ROTIREA ARBORELUI (stinga)

struct node_bin *leftRotate(struct node_bin *x)
{
    struct node_bin *y = x->right;
    struct node_bin *T2 = y->left;
 
    // Efectuam Rotirea
    y->left = x;
    x->right = T2;
 
    //  Innoim inaltimele 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Returnam radacina noua 
    return y;
}
 
// Controlam daca arborele e balansat
int getBalance(struct node_bin *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Inserarea nodului
 
struct node_bin* insert(struct node_bin* node_bin, int key)
{
    
    if (node_bin == NULL)
        return(newnode_bin(key));
 
    if (key < node_bin->key)
        node_bin->left  = insert(node_bin->left, key);
    else
        node_bin->right = insert(node_bin->right, key);
 
    // Innoim inaltimele la nodurile predecesori
    node_bin->height = max(height(node_bin->left), height(node_bin->right)) + 1;

 
    // Controlam balansarea
    int balance = getBalance(node_bin);
 
    // In caz ca nu este balansat :
 
    // cazul STINGA STINGA 
    if (balance > 1 && key < node_bin->left->key)
        return rightRotate(node_bin);
 
    // cazul DREAPTA DREAPTA 
    if (balance < -1 && key > node_bin->right->key)
        { 
    return leftRotate(node_bin);
    }
 
    // Cazul STINGA DREAPTA
    if (balance > 1 && key > node_bin->left->key)
    {
        
    node_bin->left =  leftRotate(node_bin->left);
    return rightRotate(node_bin);
    }
 
    // Cazul DREAPTA STINGA
    if (balance < -1 && key < node_bin->right->key)
    {
        
    node_bin->right = rightRotate(node_bin->right);
    return leftRotate(node_bin);
   }
 
    
   return node_bin;
}
 
// Parcurgere in preordine 

void preOrder(struct node_bin *root)
{
    if(root != NULL)
    {
       printf("\r\n Nodul : %d \t Inaltimea : %d\r\n", root->key,root->height);
       preOrder(root->left);
       preOrder(root->right);
    }
}
 
 


int main()
{

  	struct nod *root=NULL;
  	
  	root = adaugare();
  	
  	printf("\r\n\nParcurgere in latime:");
  	largime(root);

  	printf("\r\n Arborle binar : ");
  	preOrder(root_bin);

  	return 0;

}

struct nod * adaugare()
{
  	int inf;
  	int n, i;
 	struct nod *p;
  	printf("Valoarea = ");
  	scanf("%d", &inf);
  	p =(nod*) malloc( sizeof(struct nod) );
  	p->inf = inf;
  	printf("Numarul de fii lui %d : " , p->inf);
  	scanf("%d", &n);
  	p->fii = n;
  	for(i = 0; i < n; i++)
	 p->nr[i] = adaugare();
  	return p;
}

void largime(struct nod *p)
{
  	struct nod *coada[100];
  	struct nod *t; int front = 0, back = 0;
  	int i;
  	coada[ front++ ] = p;
  	while ( front != back) 
  	{
	 t = coada[ back ]; back++;
	 printf("%d ", t->inf);
	 for(i = 0; i < t->fii; i++)
	coada[ front++ ] = t->nr[i];

	root_bin=insert(root_bin,t->inf);
	free(t);

  		}

} 


