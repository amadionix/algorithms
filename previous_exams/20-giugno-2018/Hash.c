/* Rispondete alle seguenti domande giustificando le risposte facendo riferimento alle porzioni di codice in cui si trovano gli elementi,
e inserendo dei commenti direttamente nel codice.
 
1. Per cosa si usa la struttura List?
 
Si sta implementanto il tipo di dato dizionario tramite una tabella di hash, implementata
con lista di collisione per gestire le collissioni: se la funzione di hash mi da' lo stesso 
intero, indice dell'array dict->array[], per due chiavi (in questo caso stringhe) diverse,
verranno entrambe inserite in una lista puntata da dict->array[i], dove i e' il valore
ritornato dalla funzione di hash.
La struttura dati List implementa proprio questa lista, tramite un tipo di dato puntatore
ad element.
 
2. Se t è una variabile di tipo Dict, cosa rappresenta t -> array[3] ?
 
Come detto prima, rappresentera' l'elemento 3 del dizionario, ovvero una lista formata
da tutti gli elementi per cui la funzione di hash ha ritornato il numero 3.
 
3. Cosa succede se si tenta di inserire nella tabella di hash
un Item con una chiave già presente nella tabella?
 
Viene inserito il doppioine in testa alla lista, come se fosse un normale elemento
 
4. Cosa succede se si prova a cercare nel dizionario una chiave che non c'è?
 
INSERIRE LA RISPOSTA
....
 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define HASHSIZE 10
 
 
typedef struct item {
  char key[10];
  int value;
} *Item;
 
 
Item newItem( char *key ) {
  Item p = malloc( sizeof( struct item ));
  strcpy( p -> key, key );
  return p;
}
 
void printItem( Item p ){
  printf( "chiave %s, valore %d\n", p -> key, p -> value  );
}
 
 
 
// ELEMENTO DI LISTA
struct element {  // definizione di un elemento della lista
  Item item;
  struct element *next;    // prossimo elemento
};
 
// LISTA DI COLLISIONE
typedef struct element *List;
Item list_find( List c, char *w );
List list_insert( List c, Item p ); // crea nuovo elemento, lo inserisce in testa alla catena e restituisce l'indirizzo della nuova testa
void list_print( List h );
 
// DIZIONARIO IMPLEMENTATO CON HASHTABLE
typedef struct ht {
  List array[HASHSIZE];
  int count; // parole inserite
} *Dict;
 
Dict dict_init ();
Item dict_lookup ( Dict t, char *key ); // Restituisce l'Item con chiave key, oppure NULL se key non è nel dizionario
void dict_add( Dict t, Item p ); // aggiunge l'item p nel dizionario
unsigned long hash ( char *s ); // funzione di hash
 
 
/* MAIN
**************/
 
 
int main(){
 
  Dict t = dict_init();
  char key[10];
  Item p;
 
  for ( int i = 0; i < 5; i++ ) {
    strcpy( key, "id" );
    key[2] = '0'+i;
    key[3] = '\0';
    p = newItem(key);
    p -> value = i;
    dict_add( t, p );
    printItem( p );
  }
 
  p = dict_lookup( t, "id3" );
  printItem( p );
  p -> value *=2;
 
  printItem( p );
 
  p = newItem("id0");
  dict_add( t, p );
  List q = t->array[hash("id0")];
  while (q) { printf("d"); q = q->next;}
  
  return 0;
 
}
 
 
 
 
/* FUNZIONI DI GESTIONE DELLA CHAIN (lista)
*******************************************/
 
 
// Inserisce in testa e restituisce la nuova testa.
List list_insert( List h, Item p ){
  struct element *new = malloc( sizeof( struct element ) );
  new -> item = p;
  new -> next = h;
  return new;
}
 
 
/* Cerca un item con chiave key nella list c. Se lo trova ne restituisce l'indirizzo, altrimenti restituisce NULL. */
Item list_find( List c, char *key ){
  struct element *p;
  for( p = c  ; p!= NULL; p = p->next ) {
    if( strcmp( p -> item -> key, key ) == 0 ) {
      return p -> item;
    }
  }
  return NULL;
}
 
 
/* Stampa gli elementi della Lista di trabocco */
void list_print( List h ){
  /* h e' usato  per attraversare la  lista */
  for( ; h!= NULL; h=h->next)
    printItem( h -> item );
  putchar('\n');
}
 
 
 
 
/* FUNZIONI DI GESTIONE DELLA HASHTABLE
*******************************************/
 
 
// Crea una hastable di con HASHSIZE buckets
Dict dict_init () {
    Dict t = malloc ( sizeof ( struct ht ) );
    t -> count = 0;
 
    for ( int i = 0; i < HASHSIZE; i++ )
        t -> array[i] = NULL;
    return t;
}
 
// funzione di hash
unsigned long hash( char *str )
{
    unsigned long hash = 5381;
    int c;
 
    while ( (c = *str++) )
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
 
    return hash % HASHSIZE;
}
 
// cerca l'item con chiave key
Item dict_lookup ( Dict t, char *key ) {
    return list_find( t -> array[hash(key)], key );
}
 
 
// inserisce l'item nel dizionario
 void dict_add( Dict t, Item p ){
    int i = hash( p -> key);
    t -> array[i] = list_insert ( t -> array[i], p );
    t -> count++;
//    printArray( t -> array[i] -> ln_arr, t -> array[i] -> count );
}
