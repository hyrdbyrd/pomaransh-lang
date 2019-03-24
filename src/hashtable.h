#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "helpers.h"

// Max size of hashtable
#define HASH_SIZE 8

// For create one hash item
#define HashInitilize memoryType(struct DataItem)

#define CreateHashTable(item) Hash item[HASH_SIZE] = {};

#define CreateHashItem(item) Hash item = HashInitilize;

// @TODO: replace to 'any' type
typedef int dataVal;
// @TODO replace to string type
typedef int keyVal;

struct DataItem {
   dataVal data;
   keyVal key;
};

typedef struct DataItem* Hash;

int hashCode(int key) {
   return key % HASH_SIZE;
}

bool scmp(char* a, char* b) {
   if (strcmp(a, b)) return true;
   return false;
}

int get(Hash *self, int key) {
   int hashIndex = hashCode(key);

   while(self[hashIndex] != NULL) {
      if(self[hashIndex]->key == key)
         return self[hashIndex]->data;

      hashIndex++;
      hashIndex %= HASH_SIZE;
   }

   return NULL;
}

void insert(Hash *self, int key, int data) {
   CreateHashItem(item);

   item->data = data;
   item->key = key;

   int hashIndex = hashCode(key);

   while(self[hashIndex] != NULL && self[hashIndex]->key != -1) {
      hashIndex++;
      hashIndex %= HASH_SIZE;
   }

   self[hashIndex] = item;
}

dataVal del(Hash *self, int key) {
   int hashIndex = hashCode(key);

   while(self[hashIndex] != NULL) {
      if(self[hashIndex]->key == key) {
         dataVal temp = self[hashIndex]->data;
         self[hashIndex] = NULL;

         return temp;
      }

      hashIndex++;
      hashIndex %= HASH_SIZE;
   }

   return NULL;
}

void displayHashTable(Hash *self) {
   int i;

   printf("{\n");
   for(i = 0; i < HASH_SIZE; i++) {
      if (self[i] != NULL) {
         printf("  %d: %d\n", self[i]->key, self[i]->data);
      }
   }
   printf("}\n");
}

int main() {
   CreateHashTable(table);

   insert(table, 2, 23);

   displayHashTable(table);

   const int key = 2;

   int item = get(table, key);

   if(item != NULL) {
      printf("Element found: %d\n", item);
   } else {
      printf("ERROR: Element not found\n");
   }

   del(table, key);
   item = get(table, key);

   if(item == NULL) {
      printf("Element found: %d\n", item);
   } else {
      printf("ERROR: Element not found\n");
   }

   return 0;
}
