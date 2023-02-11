#include <iostream>

class Complex {
private:
    double a;
    double b;

public:
    Complex(double a = 0, double b = 0): a(a), b(b) {}

    friend Complex operator+ (const Complex& a, const Complex& b) {
        return { a.a + b.a, a.b + b.b };
    }

    friend void operator += (Complex& a, const Complex& b) {
        a.a += b.a;
        a.b += b.b;
    }

    friend Complex operator* (const Complex& a, const Complex& b) {
        return { a.a*b.a - a.b*b.b, a.a*b.b + a.b*b.a};
    }

    friend void operator *= (Complex& a, const Complex& b) {
        a.a = a.a * b.a - a.b * b.b;
        a.b = a.a * b.b + a.b * b.a;
    }

     Complex operator++ (){
        return this->a += 1.00, *this;
     }

     Complex operator++ (int) {
         return this->a += 1.00, Complex(this->a - 1.00, this->b);
     }

     friend std::ostream& operator << (std::ostream& out, const Complex& a) {
         out << a.a << ' ' << a.b << 'i';
         return out;
     }
  
     friend std::istream& operator >> (std::istream& out, Complex& a) {
         try {
            out >> a.a >> a.b;
            
         }
         catch (...) {
             a.a = 0;
             a.b = 0;
         }
         return out;
         
     }


};


int main()
{
    Complex a = { 10, 3 };
    Complex b;
    std::cout << "a = " << a << std::endl;
    std::cin >> b;
    std::cout << "b = " << b << std::endl;

    a++;
    ++a;
    std::cout << "a = " << a << std::endl;

    Complex c = a++;
    std::cout << "c = " << c << std::endl;

    std::cout << "a = " << a << std::endl;
    Complex d = a * a;
    std::cout << "d = " << d << std::endl;

    
}
