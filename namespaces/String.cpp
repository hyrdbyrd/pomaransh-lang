namespace Pomaransh
{
    template <typename T>
    class Array
    {
    public:
        int length()
        {
            return this->len;
        }

        int toVector()
        {
            return this->list;
        }

        Array()
        {
        }

        template <typename... REST>
        Array(const REST &... rest)
        {
            this->push(rest...);
        }

        int push(const T content)
        {
            this->list.push_back(content);
            return ++this->len;
        }

        template <typename... REST>
        int push(const T first, const REST &... items)
        {
            this->push(first);
            this->push(items...);
        }

    private:
        int len = 0;
        vector<T> list;
    };
}
