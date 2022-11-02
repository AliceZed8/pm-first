#include <iostream>
#include <vector>
#include <string>

class BInt
{
    private:
        std::vector<int> number;

    public:
        BInt()
        {
            number.resize(1);
            number[0] = 0;
        }
        BInt(std::string s)
        {
            for (int i = s.length() - 1; i >= 0; i--)
            {
                number.push_back(s[i] - '0');
            }
        }
        BInt(std::vector<int> nw)
        {
            this->number = nw;
        }

        void print()
        {
            for (int i = number.size() - 1; i >= 0; i--)
            {
                std::cout << number[i];
            }
            std::cout << "\n";
        }

        void add_zero(int k) {
            for (int i =0; i < k; i++) this->number.insert(this->number.begin(), 0);
        }

        BInt operator * (int k)
        {
            std::vector<int> res;

            int t = 0;
            for (int i = 0; i < this->number.size(); i++)
            {
                res.push_back((this->number[i] * k + t) % 10);
                t = (this->number[i] * k + t) / 10;
            }
            if (t != 0)
                res.push_back(t);

            BInt c(res);
            return c;
        }

        BInt operator + (BInt A)
        {
            std::vector<int> res;
            if (this->number.size() >= A.number.size())
            {
                res.resize(this->number.size());
                A.number.resize(this->number.size());
            }
            else
            {
                res.resize(A.number.size());
                this->number.resize(A.number.size());
            }
            int t = 0;
            for (int i = 0; i < std::max(this->number.size(), A.number.size()); i++)
            {
                res[i] = (this->number[i] + A.number[i] + t) % 10;
                t = (this->number[i] + A.number[i] + t) / 10;
            }
            if (t > 0)
                res.push_back(t);
            BInt c(res);
            return c;
        }

        BInt operator * (BInt A)
        {
            BInt c;
            if (this->number.size() >= A.number.size()) {
                BInt BIG(this->number);
                for (int i = 0; i < A.number.size(); i++) {
                    BInt t = BIG * A.number[i];
                    t.add_zero(i);
                    c = c + t;
                }
            }
            else {
                BInt BIG(A.number);
                for (int i = 0; i < this->number.size(); i++) {
                    BInt t = BIG * this->number[i];
                    t.add_zero(i);
                    c = c + t;
                }
            }

            return c;
        }
    };

int main()
{ 
    std::string a, b;
    std::cin >> a >> b;
    BInt num1(a);
    BInt num2(b);
    BInt num3 = num1 * num2;
    num3.print();

    //std::cout << std::stoi(a) * std::stoi(b) << std::endl;
}
