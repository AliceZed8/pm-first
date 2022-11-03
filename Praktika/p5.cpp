#include <iostream>

class Array {
    private:
        int* arr;
        unsigned int size;

    public:
        Array () {
            size = 0;
            arr = new int[size];
        }

        void push_back(int item) {
            int* new_array = new int[size + 1];
            for (int i = 0; i < size; i++) {
                new_array[i] = arr[i];
            }
            new_array[size] = item;
            delete[] arr;
            size += 1;
            arr = new_array;
        }

        int len() {return size;}

        int& operator[] (int i) {
            if ((i >=0) && (i < size)) {
                return arr[i];
            }
            else if ((i <= -1) && (i > -(size))) {
                return arr[size + i];
            }
            else std::cout << "IndexError ";
        }

        void pop(int i) {
            int * new_array = new int[size-1];
            int t = 0;
            if (i < 0) i += size;

            if (((i >= 0) && (i < size)) || ((i <= -1) && (i > -(this->size)))) { 
                for (int j = 0; j < size; j++) { 
                    if (j!= i) {
                        new_array[t] = arr[j];
                        t += 1;
                    }
                }
                delete[] arr;
                size -= 1;
                arr = new_array;
            }
            else std::cout << "IndexError ";
        }

        void insert(int i, int item) {
            int* new_array = new int[size + 1];
            if (i < 0) i += size;

            if (((i >= 0) && (i < size)) || ((i <= -1) && (i > -(this->size)))) {
                for (int j = 0; j < i; j++) {
                    new_array[j] = arr[j];
                }
                new_array[i] = item;
                for (int j = i + 1; j < size; j++) {
                    new_array[j] = arr[j-1];
                }
                delete[] arr;
                size += 1;
                arr = new_array;
            }
            else std::cout << "IndexError ";
        }

        void print() {
            for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
            std::cout << std::endl;
        }

        ~Array() {
            delete[] arr;
        }

};

void run_test() {
    Array mas;
    for (int i = 0; i < 10; i++) {
        mas.push_back(i*3);
    }

    std::cout << mas[123] << std::endl;

    std::cout << "Fill" << std::endl;
    mas.print();
    std::cout << std::endl;

    std::cout << "Push back" << std::endl;
    mas.push_back(134);
    mas.print();
    std::cout << std::endl;

    std::cout << "Size = " << mas.len() << std::endl;
    std::cout << std::endl;

    std::cout << "Get element by index" << std::endl;
    mas.print();
    std::cout << "Index 3 = " << mas[3] << std::endl;
    std::cout << "Index -6 = " << mas[-6] << std::endl;
    std::cout << std::endl;

    std::cout << "Change element by index" << std::endl;
    mas.print();
    std::cout << "Index 3 = 777" << std::endl;
    mas[3] = 777;
    mas.print();

    std::cout << "Index -6 = 999" << std::endl;
    mas[-6] = 999;
    mas.print();
    std::cout << std::endl;

    std::cout << "Pop" << std::endl;
    mas.print();
    std::cout << "Pop index = 8" << std::endl;
    mas.pop(8);
    mas.print();
    std::cout << std::endl;

    std::cout << "Insert" << std::endl;
    mas.print();
    std::cout << "Insert index = 5, element 10" << std::endl;
    mas.insert(5, 10);
    mas.print();
}


int main () {
    run_test();
}