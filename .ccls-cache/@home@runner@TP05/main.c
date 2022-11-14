#include "ABB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int chave;
  char conteudo;
  No *esq;
  No *dir;
  No *pai;
};

No* Minimo(No* no){
  if(no == NULL) return NULL;
  
  while (no->esq!= NULL){
    no = no->esq;
  }
  return no;
}

No* Achar_pai(No *no, No *raiz){
  No* x = raiz;
  No* y = NULL;
  while( x!=no){
    
    if(no->chave < x->chave){
      y = x;
      x = x->esq;      
    }
    else if(no->chave > x->chave ){
      y = x;
      x= x->dir;
    }
   
    }
    no->pai = y;
   if(y == NULL){ // caso o nó seja a raiz
      return NULL;
    }
  return no->pai;
} 

  No* Sucessor(No* no, No* raiz){
  if(no->dir != NULL){
    return Minimo(no->dir);
  }
  No* y = Achar_pai(no, raiz);
    while(y != NULL && no == y->dir){
      no = y;
      y = no->pai;
    }
    return y;
}

/* Aloca e retorna um No com os dados passados por parâmetro. Retorna no nó
 * criado ou NULL caso não seja posivel criar o nó. */
No *abb_cria_no(int chave, char conteudo) {
  No* no = (No*) malloc(sizeof(No));
  if(no==NULL){
    return NULL;
  }
  no->esq = NULL;
no->dir = NULL;
  no->conteudo = conteudo; 
  no->chave = chave;
  return no;
}




/* Libera a memória de um nó e toda as suas sub-árvores. Retorna 1 se for
 * possivel fazer a liberação ou 0 caso o nó seja NULL. */
int abb_libera_no(No *no) {
  if(no==NULL) return 0;


  if(no!= NULL){
  abb_libera_no(no->esq);
  free(no);
  no = NULL;  
  abb_libera_no(no->dir);  
  free(no);
  no =NULL;  
  }

  

  return 1;
}

/* Retorna a chave do nó ou -1 caso o nó seja NULL.  */
int abb_chave_no(No *no) {
  if(no==NULL) return -1;
  return no->chave;
}

/* Retorna o conteúdo do no ou '#' caso o nó seja NULL. */
char abb_conteudo_no(No *no) {
  if(no==NULL) return '#';
  return no->conteudo;
}

/* Adiciona um nó à esquerda ou à direita do no raiz. Retorna a raiz da árvore
 * resultante ou NULL caso (i) a raiz e o nó sejam NULL e (ii) caso o nó possua
 * mesma chave que outro nó previamente inserido na árvore. */
No *abb_insere_no(No *raiz, No *no) {
 if(raiz ==NULL && no == NULL) return NULL;
  No* x = raiz;
  No* y = NULL;
  while(x!=NULL){
    y = x;
    if(no->chave < x->chave){
      x = x->esq;      
    }
    else if(no->chave > x->chave ){
      x= x->dir;
    }
    else{ // caso o nó possua a mesma chave
      return NULL;
    }
  }
    no->pai = y;
    if(y == NULL){
      raiz = no;
    }
    else if(no->chave < y->chave){
      y->esq = no;
    }
    else {
      y->dir = no;
    }
    
  return raiz;
}

/* Procura o nó pela chave. Retorna o nó caso a busca obtenha sucesso ou NULL
 * em caso contrário. */
No *abb_busca_no(No *raiz, int chave) {
if (raiz==NULL || raiz->chave==chave){
return raiz;
}
if(chave<raiz->chave){
return abb_busca_no(raiz->esq, chave); 
} 
  return abb_busca_no(raiz->dir, chave); 
}

/* Substitui a árvore enraizada em x pela árvore enraizada em y 
*/
void Transplantar(No* u, No* v, No*raiz){
 u->pai = Achar_pai(u, raiz);
 if(Achar_pai(u,raiz)==NULL){
   raiz =v;
 }
else if(u == u->pai->esq){
  u->pai->esq = v ;
}
  else{
    u->pai->dir = v;
  }
  if(v!= NULL){
    v->pai = u->pai;
  }
}
  

/* Remove o nó com a chave fornecida. Retorna a raiz da arvore atualizada ou
 * NULL em caso a raiz fornecida seja NULL. */
No *abb_remove_no(No *raiz, int chave) {
 if(raiz== NULL) return NULL;
  
  No* no = abb_busca_no(raiz, chave);
  if(no->esq== NULL){
    Transplantar(no, no->dir, raiz);  
  }
  else if(no->dir == NULL){
    Transplantar(no, no->esq, raiz);  
  }
  else{
    No* y = Sucessor(no,raiz);
    Transplantar(y, y->dir, raiz);
    y->esq= no->esq;
    no->pai->esq = y;
    y->dir = no->dir;
    if (no->dir != NULL){
      no->pai->dir =y;
    }
    Transplantar(no,y,raiz);
    }
  return raiz;
}

/* Retorna a altura da árvore ou -1 caso a raiz seja NULL. */
int abb_altura(No *raiz) {
  if(raiz == NULL){
    return -1;
  }
    else{
  int aux1,aux2 ; 

		aux1 = abb_altura(raiz->esq);
		aux2 = abb_altura(raiz->dir);
		if(aux1 >=aux2){
      return aux1 +1;
    }
      else{
        return aux2 +1;
      }

      }
    
  
}

  

/* Retorna o número de nós da árvore ou -1 caso a raiz seja NULL. */
int abb_numero(No *raiz) {
if(raiz == NULL) return -1;
 int aux = 1;
   
  
  if(raiz!=NULL){
   
  if(abb_numero(raiz->esq)!=-1){
     aux= aux+abb_numero(raiz->esq);
  }
   
  if(abb_numero(raiz->dir)!=-1)
     aux= aux+abb_numero(raiz->dir);
    } 

    return aux;

}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pré-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pre_ordem(No *no) {
  if(no==NULL){
    return "#";
  }
  char aux;
  No* ant;

  if(no!=NULL ){
  abb_conteudo_no(no);
  abb_pre_ordem(no->esq);
  abb_pre_ordem(no->dir);
    } 
  
  
}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_ordem(No *no) {
 if(no==NULL){
    return "#";
  }
  char *aux, *aux2,*aux3;
  No* ant= NULL;
  
  if(no!=NULL){
  //abb_ordem(no->esq);
 if(ant!=NULL)  
 aux= strcat((&(ant->conteudo)),(&(no->conteudo)));
    
 // abb_ordem(no->dir);
 
    ant = no;
  }  

  return aux;
}
/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pós-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pos_ordem(No *no) {
   if(no==NULL){
    return "#";}
  }
  /*
char aux;
No* ant;  
 if (Achar_raiz(no)!=NULL){
   ant = NULL;
   aux = no->conteudo;
 } 
  No* aux;
  if(no!=NULL && ){
  aux = no;
  abb_pos_ordem(no->esq);
  abb_pos_ordem(no->dir);
  abb_conteudo_no(no);
   if(ant!=NULL){
    aux = strcat((&(ant->conteudo)),(&(no->conteudo))) ; 
  }
    
  return aux;
}
*/

int main(void){
 int chave1 = 2;
  char conteudo1 = 'A';
  No* raiz = abb_cria_no( chave1,  conteudo1);

  int chave2 = 3;
 char conteudo2 = 'B';
 No* novo =  abb_cria_no( chave2,  conteudo2); ;

    int chave3 = 4;
 char conteudo3 = 'C';
 No* novo2 =  abb_cria_no( chave3,  conteudo3); 
  
  No* aux;
  
    int chave4 = 1;
 char conteudo4 = 'D';
 No* novo3 =  abb_cria_no( chave4,  conteudo4); 
 No* novo4 = abb_cria_no(17, 'S');
   No* novo5 = abb_cria_no(0, 'r');
   No* novo6 = abb_cria_no(9, 'u');
   No* novo7 = abb_cria_no(2, 'i');
  
  raiz = abb_insere_no(raiz, novo);
  raiz = abb_insere_no(raiz, novo2);
 raiz = abb_insere_no(raiz, novo4);
   raiz = abb_insere_no(raiz, novo5);
   raiz = abb_insere_no(raiz, novo6);
 //  raiz = abb_insere_no(raiz, novo7);
   
  
  
 // char* test = abb_ordem(raiz) ;
  //printf("%s\n", test);
 int x = abb_numero(raiz);
  //printf("%d\n",x);
int y = abb_altura(raiz);
  
  char c[10] = "oi";
  int b = strlen(c);
 printf("%d",y);
  }
  

