#include "array.cpp"
#include <iostream>

using namespace std;
using namespace Pomaransh;

int main() {
    Array<int> a;

    a.push(3, 2, 3);

    cout << a.length();

    return 0;
}
