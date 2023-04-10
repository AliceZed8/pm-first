#include <iostream>

template <typename T>
class Stack {
    struct Element {
        Element* last = nullptr;
        T data;
        Element() {}
        Element(Element* elem, T dat): last(elem), data(dat) {
            std::cout << "Object\n" <<
            "Last: " << last << "\n" << 
            "Data: " << data << "\n" <<
            "This: " << this << "\n\n";
        }

    };

    size_t sz, max_sz;
    Element* lst;

    public:
    Stack(size_t max_size): sz(0), lst(nullptr), max_sz(max_size) {}
    ~Stack() {
        Element* el;
        while (lst != nullptr) {
            el = lst;
            std::cout << "delete " << el << std::endl;
            lst = (*lst).last;
            delete el;
        }
    }
    
    bool empty() {
        return (lst == nullptr) ? true : false;
    }

    size_t size() {
        return sz;
    }

    void push(T data) {
        if (sz == max_sz) throw std::overflow_error("Stack is full");
        try {
            lst = new Element(lst, data);
            sz++;
        } catch(std::bad_alloc &e) {
            throw;
        }
    }

    T& top() {
        if (sz == 0) throw std::logic_error("Stack is empty");
        return (*lst).data;
    }

    T pop() {
        if (sz == 0) throw std::out_of_range("Out of range. Size = 0");
        T data = (*lst).data;
        Element* topp = lst;
        lst = (*lst).last;
        delete topp;
        sz--;
        return data;
    }

};


int main() { 
    Stack<int> st(5);

    printf("Size %d\n", st.size());
    st.push(50);
    printf("Size %d\n", st.size());
    st.push(20);
    printf("Size %d\n", st.size());
    st.push(80);
    printf("Size %d\n", st.size());

    
    for (int i = 0; i < 5; i++) {
        try {
            st.push(i);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }


    printf("Top %d\n", st.top());
    st.top() = 2000;
    printf("Top %d\n", st.top());
    st.pop();
    printf("Top %d\n", st.top());
    st.pop();
}