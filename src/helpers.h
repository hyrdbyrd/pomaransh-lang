#define unused(i) ((void)i)
#define refVar(type, to, from) type *to = &from
#define memoryType(type) (type*)malloc(sizeof(type))
#define lenArray(item) sizeof(item) / sizeof(*item);

typedef char* string;
