#include <iostream>
#include <cmath>
#include <vector>

class OutputElement {
    unsigned char* ptr;
    uint8_t pos;
    bool data;

    friend std::vector<bool>;
    OutputElement(unsigned char * pt, uint8_t pos): ptr(pt), pos(pos) {
        data = (bool)((*ptr >> (7 - pos)) & (1));
    }

public:
    operator bool() {
        return data;
    }

    void operator = (bool val) {
        if (data == val) return;

        if (data && !val) {
            *ptr -= std::pow(2, 7 - pos);
            return;
        }
        if (!data && val) {
            *ptr += std::pow(2, 7 - pos);
            return;
        } 
    }
};



template<>
class std::vector<bool> {
    std::vector<unsigned char> bytes;
    size_t sz = 0;

public:
    OutputElement operator[] (int index) {
        return OutputElement(&bytes[index / 8], index % 8);
    }

    void push_back(bool value) {
        sz++;
        if (sz % 8 == 1) {
            bytes.push_back(0);
        }

        (*this)[sz - 1] = value;
    }

    size_t size() {
        return sz;
    }

    void insert(size_t pos, bool value) {
        this->push_back((bool) ((*this)[sz - 1]));
        for (int i = sz - 1; i >= pos; i--) {
            (*this)[i] = (bool) ((*this)[i - 1]);
        }
        (*this)[pos] = value;
     }

     void erase(int pos) {
        for (int i = pos; i < sz - 1; i++) {
            (*this)[i] = (bool) ((*this)[i + 1]);
        }
        sz--;
        if (sz % 8 == 0){
            bytes.erase(bytes.end());
        }
    }


    void print() {
        for(size_t i = 0; i < sz; i++) {
            std::cout << (int) this->operator[](i) << " ";
        }

        std::cout << std::endl;
    }


};



int main()
{
    std::vector<bool> vect;
    vect.push_back(false);
    vect.push_back(true);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(true);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(false);
    vect.push_back(true);
    vect.print();
    vect.insert(true, 1);
    vect.print();
    vect.erase(2);
    vect.print();


}
