#include <iostream>
#include <assert.h>
#include "array.cpp"

using namespace std;
using namespace Pomaransh;

void testContructor() {
    Array<int> a(1, 2, 3);

    assert(a.length() == 3);
}

void testPop() {
    // Should add two items
    Array<int> a;
    a.push(1, 2);
    assert(a.length() == 2);

    // Should be correct
    Array<int> b;
    const int item = 1;
    b.push(item);
    assert(b.get(0) == item);
}

void testPush() {

}

void testMap() {

}

int main() {
    testContructor();
    testPush();
    testPop();

    return 0;
}
