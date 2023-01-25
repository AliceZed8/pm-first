#include <iostream>


class Allocator {
public:
    char* allocate(size_t bytes_count) {
        char* result;
        try {
            result = new char[bytes_count];
            result[0] = '\0';
            return result;
        }
        catch (const std::bad_alloc& e) {
            printf("Memory Allocation FAILED: %s \n", e.what());
            return nullptr;
        }

    }

    char* reallocate(const char* &start, size_t bytes_count) {
        char* result = allocate(bytes_count);
        if (result != nullptr) {
            std::copy(start, start + strlen(start) + 1, result);
        }
        return result;
    }

    char* reallocate(char*& start, size_t bytes_count) {
        char* result = allocate(bytes_count);
        if (result != nullptr) {
            std::copy(start, start + strlen(start) + 1, result);
        }
        return result;
    }
};



class String {
private:
    Allocator* allocator;
    char* arr;
    size_t size;
    size_t cap;


public:
    char* c_str() const {
        return arr;
    }

    size_t length() const {
        return size;
    }

    size_t capacity() const {
        return cap;
    }

    String(const char* str) {
        printf("%s\n", "Const Char* Constructor");
        size = strlen(str);
        cap = size + 1;
        arr = allocator->reallocate(str, cap);
       
    }
    String(char* str) {
        printf("%s\n", "Char* Constructor");
        size = strlen(str);
        cap = size + 1;
        arr = allocator->reallocate(str, cap);

    }

    //Empty Constructor
    String(size_t n = 20) {
        printf("%s\n", "Empty Constructor");
        size = 0;
        cap = n + 1;
        arr = allocator->allocate(cap);
    }

    //Copy Constructor*
    String(const String & str) {
        printf("%s\n", "Copy Constructor");
        size = str.length();
        cap = size + 1;
        char* p1 = str.c_str();
        arr = allocator->reallocate(p1, cap);
    }

    //Copy and Swap
    String& operator= (String str2) {
        printf("%s\n", "Copy and Swap");
        std::swap(size, str2.size);
        std::swap(cap, str2.cap);
        std::swap(arr, str2.arr);
        return *this;
    }

    //Destructor
    ~String() {
        printf("%s\n", "Destructor");
        if (arr != nullptr) {
            delete[] arr;
        }
            
    }


    //Operator []
    char& operator [] (size_t i) {
        printf("%s\n", "Operator []");
        return arr[i];
    }

    char& at(size_t i) {
        printf("%s\n", "at() ");
        if (i >= size) throw std::out_of_range("");
        else {
            return arr[i];
        }
    }

    //Bool
    bool operator > (String& str) {
        return this->size > str.length() ? true : false;
    }
    bool operator < (String& str) {
        return this->size < str.length() ? true : false;
    }

    bool operator== (String& str) {
        return strcmp(arr, str.c_str()) == 0;
    }

    //Add
    void add(const String &str) {
        printf("%s\n", "add() ");
        size_t old_length = size;
        size += str.length();

        if (size < cap) {
            std::copy(str.c_str(), str.c_str() + str.length() + 1, arr + old_length);
        }
        else {
            cap = size + 200;
            char* old_arr = arr;
            arr = allocator->reallocate(old_arr, cap);
            delete[] old_arr;
            std::copy(str.c_str(), str.c_str() + str.length() + 1, arr + old_length);
        }

    }

    //Resize
    void resize(size_t n) {
        printf("%s\n", "Resize");
        size_t old_length = size;
        char* old_arr = arr;

        if (n > old_length) {
            cap = n;
            arr = allocator->reallocate(old_arr,  cap);
            delete[] old_arr;
        }
        else if (n < old_length) {
            size = n;
            arr[old_length - n + 1] = '\0';
        }
    }


    //+= 
    void operator += (String str) {
        printf("%s\n", "Operator +=");
        this->add(str);
    }

    //+
    friend String operator + (String str1, String str2);
    //Cout OSTREAM
    friend std::ostream& operator << (std::ostream& out, String& str);
    //Cin ISTREAM
    friend std::istream& operator >> (std::istream& out, String& str);
    //Find
    int find(char c) {
        for (size_t i = 0; i < size; i++) {
            if (arr[i] == c) return i;
        }
        return -1;
    }

        
};

std::ostream& operator << (std::ostream& out, String& str) {
    printf("%s\n", "Operator <<");
    out << str.c_str();
    return out;
}
std::istream& operator >> (std::istream& out, String& str) {
    printf("%s\n", "Operator >>");
    out >> str.c_str();
    str.size = strlen(str.c_str());
    return out;
}

String operator + (String str1, String str2) {
    printf("%s\n", "Operator +");
    str1.add(str2);
    return str1;
}



int main()
{

    String a("HELLO");
    String b;
    b = a;
    printf("%s %zd %zd %zd\n", b.c_str(), b.capacity(), b.length(), sizeof(b));
    b += " WORLD " + a + "HELLO";
    printf("%s %zd %zd %zd\n", b.c_str(), b.capacity(), b.length(), sizeof(b));



}

