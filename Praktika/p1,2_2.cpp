#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <map>


class crypto {

private:
    void shuffle(std::vector<std::string> &words, std::vector<uint32_t> & key) {
        srand(time(0));
        for (uint32_t k = 0; k < key.size(); k++) {
            uint32_t rnd = rand() % key.size();
            std::swap(key[k], key[rnd]);
            std::swap(words[k], words[rnd]);
        }
    }

    void qsort(std::vector<uint32_t>& key, std::vector<std::string>& words, int start, int end) {
        int i = start, j = end;
        uint32_t mid = key[(i + j) / 2];


        do {
            while (key[i] < mid) i++;
            while (mid < key[j]) j--;

            if (i <= j) {
                std::swap(key[i], key[j]);
                std::swap(words[i], words[j]);
                i++; j--;
            }

        } while (i <= j);

        if (start < j) qsort(key, words, start, j);
        if (i < end) qsort(key, words, i, end);
        
    }
public:
    std::string Encode(std::string str, std::vector<uint32_t> &key) {
        if (key.size() > 0) key.resize(0);
        uint32_t i = 0, j = 1;

        std::stringstream stream(str);
        std::vector<std::string> words;

        std::string encoded;
        std::string temp;

        while (std::getline(stream, temp, ' ')) {
            words.push_back(temp);
            key.push_back(i + j);
            std::swap(i, j);
            j += i;
        }
        
        shuffle(words, key);

        for (int _ = 0; _ < words.size(); _++) {
            if (_ == 0) { encoded += words[_]; continue; }
            encoded += " " + words[_];
        }

        words.resize(0);
        return encoded;
    }

    std::string Decode1(std::string encoded, std::vector<uint32_t> key) {
        std::stringstream stream(encoded);
        std::vector<std::string> words;
        std::string temp;
        std::string decoded;
        while (std::getline(stream, temp, ' ')) words.push_back(temp);

        qsort(key, words, 0, key.size() - 1);

        for (int i = 0; i < words.size(); i++) {
            if (i == 0) { decoded += words[i]; continue; }
            decoded += " " + words[i];
        }

        return decoded;
    }

    std::string Decode2(std::string encoded, std::vector<uint32_t> key) {
        std::map<uint32_t, std::string> dict;
        std::stringstream stream(encoded);
        std::string temp;
        std::string decoded;
        uint32_t index = 0;

        while (std::getline(stream, temp, ' ')) {
            dict[key[index]] = temp;
            index++;
        }
        int i = 0, j = 1;
        for (int k = 0; k < key.size(); k++) {
            if (k==0) decoded += dict[i + j];
            else decoded += " " + dict[i + j];
            std::swap(i, j);
            j += i;
        }
        return decoded;
    }

};


void test1()
{
    crypto cr;
    std::vector<uint32_t> key;

    std::string encoded = cr.Encode("Hello, my name is Ivan. Иван привет", key);
    printf("%s\n", encoded.c_str());

    printf("Key:");
    for (int i = 0; i < key.size(); i++) {
        printf(" %d", key[i]);
    }
    printf("\n");

    std::string decoded;

    decoded = cr.Decode1(encoded, key);
    printf("%s\n", decoded.c_str());

    decoded = cr.Decode2(encoded, key);
    printf("%s\n", decoded.c_str());
    
}

enum mode {
        Byte, Byte8
    };

template <typename T>
void copy(T* dest, T* src, uint64_t bytescount, mode Mode) {

    if (Mode == mode::Byte) {
        char* cdest = (char*)dest;
        char* csrc = (char*)src;
        for (uint64_t i = 0; i < bytescount; i++) cdest[i] = csrc[i];
    }
    else {
        uint64_t doubles = bytescount / 8;
        uint8_t mod = bytescount % 8;
        if (doubles > 0) {
            double* cdest = (double*)dest;
            double* csrc = (double*)src;
            for (uint64_t i = 0; i < doubles; i++) cdest[i] = csrc[i];

            if (mod != 0) copy(dest + doubles, src + doubles, mod, mode::Byte);
        }
        else copy(dest, src, mod, mode::Byte);
    }
}

int main() {
    test1();

    int N[10] = { 1,2,4,5,6,7,1000,12213,123, 2};
    int M[10];

    copy(M, N, sizeof(N), mode::Byte8);

}
