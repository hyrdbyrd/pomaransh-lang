#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "helpers.h"

// Max size of hashtable
#define HASH_SIZE 8

// For create one hash item
#define HashInitilize memoryType(struct HashItem)
#define CreateHashTable(item) Hash item[HASH_SIZE] = {};
#define CreateHashItem(item) Hash item = HashInitilize;

// @TODO: replace to 'any' type
typedef int dataVal;
// @TODO replace to string type
typedef string keyVal;

struct HashItem {
   dataVal data;
   string key;
};

typedef struct HashItem* Hash;

bool scmp(char* a, char* b) {
   if (!strcmp(a, b)) return true;
   return false;
}

// @TODO O(n) -> O(log(n))
int get(Hash *self, keyVal key) {
   int i;
   for (i = 0; i < HASH_SIZE; i++) {
      if (self[i] == NULL) continue;
      if (scmp(self[i]->key, key)) return self[i]->data;
   }

   return NULL;
}

// @TODO O(n) -> O(log(n))
void insert(Hash *self, keyVal key, int data) {
   CreateHashItem(item);

   item->data = data;
   item->key = key;

   int i;
   for (i = 0; self[i] != NULL; i++);

   if (self[i] != NULL) printf("Object size limit is %d", HASH_SIZE);
   else self[i] = item;
}

// @TODO O(n) -> O(log(n))
dataVal del(Hash *self, keyVal key) {
   int i;
   for (i = 0; i < HASH_SIZE; i++) {
      if (self[i] == NULL) continue;
      else if (scmp(self[i]->key, key)) break;
   }

   if (self[i] == NULL) return NULL;

   dataVal temp = self[i]->data;
   self[i] = NULL;

   return temp;
}

void displayHashTable(Hash *self) {
   int i;

   printf("{\n");
   for(i = 0; i < HASH_SIZE; i++) {
      if (self[i] != NULL) {
         printf("  %s: %d\n", self[i]->key, self[i]->data);
      }
   }
   printf("}\n");
}

int main() {
   CreateHashTable(table);

   displayHashTable(table);

   const string key = "key1";

   insert(table, key, 1);
   insert(table, "key2", 2);
   insert(table, "key3", 3);
   insert(table, "key4", 4);

   displayHashTable(table);

   int item = get(table, key);

   if(item != NULL) printf("Got item {%d}\n", item);
   else printf("Error: no exists\n");

   del(table, key);
   item = get(table, key);

   if (item == NULL) printf("Deleted\n");
   else printf("Error: Not Deleted {%d}\n", item);

   return 0;
}
