#include <stdio.h>

// parola e righe in cui compare
typedef struct {
  char *word;
  int *line_arr;      // numero di righe in cui compare una parola
} Item;
typedef struct HashTable {
  Chain array[HASHSIZE];
  int count; // parole inserite
} *Dict;
struct Element {
  Item *item;
  struct Element *next;
};
typedef struct element *Chain;

Item *NewItem(char *w, int ln);     // crea spazio per nuovo item e da' indiriz
void ItemModify(Item *p, int ln);   // aggiunge nuovo numero di riga

Item *ChainFind(Chain c, char *w);
Chain ChainInsert(Chain c, Item *p);
void ChainPrint(Chain h);

Dict DictInit();                    // alloca spazio per dict
Item *DictLookup(Dict t, char *w);  // restituisce Item contenente chiave w
void DictAdd(Dict t, Item *p);
void DictPrint(Dict h);

// read_line / read_word  individuare parole nell'input e metterle nel dict

// switch per lettura ed esecuzione di istruzioni della tabella
int main() {
  Dict dict = DictInit();
  int ln;

  while((com = getchar()) != ’f ’) {
    4switch(com) {
      case ’+ ’: // legge una riga e inserisce parole in dict
      ln ++;
      line ( dict , ln );
      break;
      case ’? ’:

      break; // stampa num di riga in cui compare la parola
      case ’n ’:

      break; //
      stampa il numero di parole lette
      case ’l ’:

      break; //
      stampa il numero di righe lette
      case ’p ’: // stampa il dizionario
      dict_print ( dict );
      break;
    }
  }
  
}

// hash function 
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
  hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % HASHSIZE ;
}
