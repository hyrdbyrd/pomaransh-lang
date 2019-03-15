#include <vector>

using namespace std;

namespace Pomaransh {
    template<typename T>
    class Array {
        public:
            int length() {
                return this->len;
            }

            vector<T> to_vector() {
                return this->list;
            }

            Array() {}

            template<typename ...REST>
            Array(const REST &...rest) { this->push(rest...); }

            int push(const T content) {
                this->list.push_back(content);
                return ++this->len;
            }

            int pop() {
                this->list.pop_back();
                return --this->len;
            }

            T get(const int idx) {
                return this->list[idx];
            }

            template<typename C>
            Array<C> map(T (*handler)(C, int, Array<T>&)) {
                Array<C> newArray;

                for (unsigned idx = 0; idx < this->length; idx++) {
                    newArray.push(handler(this->list, idx, &this));
                }

                return newArray;
            }

            template<typename ...REST>
            int push(const T first, const REST &...items) {
                this->push(first);
                this->push(items...);
            }

        private:
            int len = 0;
            vector<T> list;
    };
}
