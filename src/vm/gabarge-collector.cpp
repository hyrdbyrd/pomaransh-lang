#include <iostream>
#include <stdlib.h>

#define STACK_MAX_SIZE 256
#define IGCT 8

using namespace std;

typedef enum {
    INT,
    TWIN
}oType;

typedef struct refObject {
    oType type;
    bool marked;

    struct refObject* next;

    union {
        int value;
        struct {
            struct refObject *head;
            struct refObject *tail;
        };
    };
}Object;

typedef struct {
    Object* stack[STACK_MAX_SIZE];
    int stackSize;

    Object* firstObject;

    int numObjects;
    int maxObjects;
}vm;

int push(vm* vm, Object* val) {
    vm->stack[vm->stackSize++] = val;

    return vm->stackSize;
}

Object* pop(vm* vm) {
    return vm->stack[--vm->stackSize];
}

vm* newVm() {
    vm* mainVm = (vm*)(malloc(sizeof(vm)));

    mainVm->stackSize = 0;
    mainVm->firstObject = NULL;
    mainVm->numObjects = 0;
    mainVm->maxObjects = IGCT;

    return mainVm;
}

Object *newObject(vm* vm, oType type) {
    if (vm->numObjects == vm->maxObjects) {
        gc(vm);
    }

    Object* object = (Object*)malloc(sizeof(Object));
    object->type = type;

    vm->numObjects++;
    return object;
}

void pushInt(vm* vm, int intV) {
    Object *object = newObject(vm, INT);
    object->value = intV;

    push(vm, object);
}

Object* pushTwin(vm* vm) {
    Object* object = newObject(vm, TWIN);

    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

void mark(Object* object) {
    if (object->marked) return;

    object->marked = true;

    if (object->type == TWIN) {
        mark(object->head);
        mark(object->tail);
    }
}

void markAll(vm* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void markSweep(vm* vm) {
    // From the firstObject, we catch innerObject
    Object** object = &vm->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            Object* unreached = *object;
            *object = unreached->next;

            free(unreached);

        } else {
            (*object)->marked = false;
            object = &(*object)->next;
        }
    }
}

void gc(vm* vm) {
    int numObjects = vm->numObjects;

    markAll(vm);
    markSweep(vm);

    vm->maxObjects = vm->numObjects * 2;
}

void printObj(Object* object) {
    switch (object->type) {
        case INT:
            cout << object->value << endl;
            break;
        case TWIN:
            cout << "(" << object->head << ", " << object->tail << ")" << endl;
            break;
    }
}

int main() {
    return 0;
}
