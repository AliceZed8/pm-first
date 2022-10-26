#include <iostream>
#include <vector>
#include <string>

class BInt {
    private:
        std::vector<int> number;
    
    public:
        BInt() {
            number.resize(1);
            number[0] =0;
        }
        BInt(std::string s) {
            for (int i = s.length() - 1; i >= 0; i--) {
                number.push_back(s[i] - '0' );
            }
        }
        BInt(std::vector <int> nw) {
            this->number = nw;
        } 

        void print() {
            for (int i = number.size() - 1; i>=0; i--) {
                std::cout << number[i];
            }
            std::cout << "\n";
        }

        void print_r() {
            for (int i = 0; i < number.size(); i++) {
                std::cout << number[i];
            }
            std::cout << "\n";
        }

        BInt operator + (BInt A) {
            std::vector <int> res;
            res.resize(std::max(this->number.size(), A.number.size()));
            int t = 0;
            for (int i =0; i < std::max(this->number.size(), A.number.size()); i++) {
                res[i] = (this->number[i] + A.number[i] + t)%10;
                t = (this->number[i] + A.number[i] + t) / 10;
            }
            if (t>0) res.push_back(t);
            BInt c(res);
            return c;
        }
    
};


int main () {
    BInt a("5000");
    BInt b("6000");
    BInt c = a + b;
    c.print();
}