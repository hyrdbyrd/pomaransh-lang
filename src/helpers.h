#define unused(i) ((void)i)
#define refVar(type, to, from) type *to = &from
#define memoryType(type) (type*)malloc(sizeof(type))

typedef char* string;
