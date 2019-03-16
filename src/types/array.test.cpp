#include <iostream>
#include <assert.h>
#include "array.cpp"

using namespace std;
using namespace Pomaransh;

void testContructor() {
    // Should create with items
    Array<int> a(1, 2, 3);
    assert(a.length() == 3);

    // Should create without items
    Array<int> b;
    assert(b.length() == 0);

    // Should set correct values
    const int item = 1;
    Array<int> c(item);
    assert(c.get(0) == item);
}

void testPop() {
    // Should delete last item
    Array<int> a(1, 2, 3);
    a.pop();
    assert(a.length() == 2);

    // Should return correct result
    const int lastItem = 3;
    Array<int> b(1, 2, lastItem);
    assert(b.pop() == lastItem);
}

void testPush() {
    // Should add two items
    Array<int> a;
    a.push(1, 2);
    assert(a.length() == 2);

    // Should be correct
    Array<int> b;
    const int item = 1;
    b.push(item);
    assert(b.get(0) == item);

    // Operator sugar
    Array<int> c;
    const int newItem = 2;
    c += newItem;
    assert(c.get(0) == newItem);
}

int increment(int item) {
    return item + 1;
}

void testMap() {
    // Should return new modified array
    Array<int> a(0, 1, 2);
    Array<int> newA = a.map(increment);
    assert(newA.get(0) == 1 && newA.get(1) == 2 && newA.get(2));
}

// void testJoin() {
//     // Should return correct result
//     Array<string> a("0", "1", "2");
//     assert(a.join(", ") == "0, 1, 2");

//     // Should convert types
//     Array<int> b(0, 1, 2);
//     assert(b.join(", ") == "0, 1, 2");
// }

int main() {
    testContructor();
    testPush();
    testPop();
    testMap();

    return 0;
}
