# **Syntax**
```ts
const item: scope = {
    a: number = 5;
    b = 2;
    c: scope = {
        a: string = "5";
    };
    d: object = {
        f = 1
    };
}

func {
    // without scopee
    return a + b;
}

func/scope(); // 7 -> a = 5, b = 2
// func() -> thows error; a and b undefined

log(scope);
/* output (like in JS) */
{
    __parent: this,
    a: 5,
    b: 2,
    c: { __parent: this, a: "5" },
    d: { f: 1 }
}

func1(x, y) {
    x + y;
}

const a, { __scope: b } = func1(1, 2);
a // 3
b // x = 1, y = 2;
```

# **Types**
* *scope*
* *closure*
* *function*
* *object*
* *null*
* *number*
