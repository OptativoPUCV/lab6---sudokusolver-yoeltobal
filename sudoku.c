#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  int arr[10];

  //filas
  for (int i = 0; i < 9; i++) {

    for (int k = 0; k < 10; k++) arr[k] = 0;
    
    for (int k = 0; k < 9; k++) {
      
      if (n->sudo[i][k] != 0) {
        if (arr[n->sudo[i][k]] == 1) return 0;
        arr[n->sudo[i][k]] = 1;
      }
    }
  }
  //columnas
  for (int i = 0; i < 9; i++) {

    for (int k = 0; k < 10; k++) arr[k] = 0;

    for (int k = 0; k < 9; k++) {

      if (n->sudo[k][i] != 0) {
        if (arr[n->sudo[k][i]] == 1) return 0;
        arr[n->sudo[k][i]] = 1;
      }
    }
  }

  for (int i = 0; i < 9; i++) {

    for (int k = 0; k < 10; k++) arr[k] = 0;

    for (int p = 0; p < 9; p++) {
      
      int fil = 3 * (i / 3) + (p / 3);
      int col = 3 * (i % 3) + (p % 3);
      if (n->sudo[fil][col] != 0) {
        if (arr[n->sudo[fil][col]] == 1) return 0;
        arr[n->sudo[fil][col]] = 1;
      }
    }
  }

  
  return 1;
}


List* get_adj_nodes(Node* n){
  
  List* list=createList();

  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9 ; k++) {
      if (n->sudo[i][k] == 0) {
        for (int num = 1 ; num <= 9; num++) { 
          Node * new_node = copy(n);
          new_node->sudo[i][k] = num;
          if (is_valid(new_node)) 
            pushBack(list, new_node);
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){

  for (int i = 0; i < 9 ; i++) {
    for (int k = 0; k < 9; k++)
      if (n->sudo[i][k] == 0) return 0;
  }
  
  return 1;
}

Node* DFS(Node* initial, int* cont){
  
  Stack* S = createStack();
  push(S, initial);

  while (S != NULL) {
    Node* n = top(S);
    pop(S);

    if (is_final(n)) return n;

    List* adj = get_adj_nodes(n);

    while (adj != NULL) {
      Node* aux = first(adj);
      push(S, aux);
    }
    cont++;

    free(n);
    
  }

  
  
  
  return NULL;
}
/*
d) Agregue los nodos de la lista (uno por uno) al stack S.

e) Libere la memoria usada por el nodo.

Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.

Puede ver un código de ejemplo en las diapos.
Recuerde revisar las operaciones del TDA Stack en el archivo list.h.
*/


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/