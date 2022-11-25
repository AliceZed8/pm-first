#include <iostream>
#include <vector>


class Item {
    private:
    int a, b, c;
    public:
    Item (int ab, int bb, int bc): a(ab), b(bb), c(bc) {}
};



void write_vector(std::vector <int> &arr) {
    for (unsigned int i = 0; i<arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
} 


void run_test() {
    std::vector <int> array;
    std::cout << "Operation push_back" << std::endl;
    for (unsigned int j = 1; j < 7; j++) {
        array.push_back(j*3);
    }
    write_vector(array);


    std::cout << "Operation Erase" << std::endl;
    std::vector<int>::iterator it = array.begin();
    array.erase(it);
    write_vector(array);


    std::cout << "Operation Insert" << std::endl;
    array.insert(it, 3000);
    write_vector(array);

    
    std::cout << "Operation Emplace_back" << std::endl;
    std::vector<Item> item_array;
    item_array.push_back(Item(1, 3, 5));
    item_array.emplace_back(1, 3, 5);

    std::cout << "Operation Resize" << std::endl;
    array.resize(3);
    write_vector(array);
    array.resize(10, 1);
    write_vector(array);

    std::cout << "Operation Reserve" << std::endl;
    std::cout << "Capacity " << array.capacity() << std::endl;
    array.reserve(20);
    std::cout << "Capacity " << array.capacity() << std::endl;

    std::cout << "Operation shrink_to_fit" << std::endl;
    array.shrink_to_fit();
    std::cout << "Capacity " << array.capacity() << std::endl;

    std::cout << "Operation []" << std::endl;
    write_vector(array);
    array[0] = 10;
    write_vector(array);

    std::cout << "Sizeof" << " " << sizeof(array) << std::endl;



}


int main() {
    run_test();
}