#include <vector>
#include <typeinfo>

using namespace std;

namespace Pomaransh {
    template<typename T>
    class Array {
        public:
            template <typename ...REST>
            Array(const T first, const REST &...rest) {
                this->push(first, rest...);
            }
            Array() {}

            int length() {
                return this->len;
            }

            template<typename C>
            Array<C> map(C (*handler)(T, int, Array<T>&)) {
                Array<C> newArray;
                for (unsigned idx = 0; idx < this->len; idx++) {
                    newArray.push(handler(this->list.at(idx), idx, &this));
                }

                return newArray;
            }

            template<typename C>
            Array<C> map(C (*handler)(T, int)) {
                Array<C> newArray;
                for (unsigned idx = 0; idx < this->len; idx++) {
                    newArray.push(handler(this->list.at(idx), idx));
                }

                return newArray;
            }

            template<typename C>
            Array<C> map(C (*handler)(T)) {
                Array<C> newArray;
                for (unsigned idx = 0; idx < this->len; idx++) {
                    newArray.push(handler(this->list.at(idx)));
                }

                return newArray;
            }

            // TODO: must work with strings (as generic)
            string join(string joiner) {
                const int len = this->len;
                string result = "";

                for (unsigned idx = 0; idx < len; idx++) {
                    T const item = this->list.at(idx);

                    result += to_string(item);
                    result += (idx < len - 1) ? joiner : "";
                }

                return result;
            }


            int push(const T content) {
                this->list.push_back(content);
                return ++this->len;
            }

            int push(const T content) const {
                this->list.push_back(content);
                return ++this->len;
            }

            template<typename ...REST>
            int push(const T first, const REST &...items) {
                this->push(first);
                this->push(items...);

                return this->len;
            }

            Array<T> operator+=(T item) {
                this->push(item);
                return *this;
            }

            Array<T> operator+=(T item) const {
                this->push(item);
                return *this;
            }

            Array<T> operator+(T item) {
                this->push(item);
                return *this;
            }

            Array<T> operator+(T item) const {
                this->push(item);
                return *this;
            }

            T pop() {
                vector<T> &list = this->list;

                T result = list.back();
                list.pop_back();

                this->len--;
                return result;
            }

            T get(const int idx) {
                return this->list.at(idx);
            }

            T operator[](int idx) {
                return this->get(idx);
            }

        private:
            int len = 0;
            vector<T> list;
    };
}
