
#include "ABB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char  global1[30] , global2[30], global3[30] , global4[30], global5[30] , global6[30] ;

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

  No* Sucessor(No* no){
  if(no->dir != NULL){
    return Minimo(no->dir);
  }
  No* y = no->pai;
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
  
  abb_libera_no(no->dir);  
  free(no);
 
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
    No* y = Sucessor(no);
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
  if (no == NULL) {
      return "#";
  }


  if(no!=NULL){
strcpy(global1,(&(no->conteudo)));
strcat(global2,global1);
abb_pre_ordem(no->esq);
abb_pre_ordem(no->dir);
    
    
}   
    return global2;
 
  }

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_ordem(No *no) {
 if(no==NULL){
    return "#";
  }


  if(no!=NULL){ 
    
  abb_ordem(no->esq);
  
strcpy(global3,(&(no->conteudo)));
strcat(global4,global1);
  abb_ordem(no->dir);
  
  }  

  return global4;
}
/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pós-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pos_ordem(No *no) {
   if(no==NULL){
    return "#";
  }
 if(no!=NULL){
  
  abb_pos_ordem(no->esq);
abb_pos_ordem(no->dir);
strcpy(global5,(&(no->conteudo)));
strcat(global6,global1);
  
  
  }  
return global6;
}


