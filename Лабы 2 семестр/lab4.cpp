#include <iostream>

#define BAD_ALLOC(ptr) { if (ptr == nullptr) {std::cerr << "Bad Alloc"; exit(-1);} };
#define LOG(str) printf("%s\n", str);


template <typename Type>
class Matrix {
    Type** matrix;
    uint64_t s, n;

    Type Det(Type** mtx, size_t rows, size_t cols) {
        if (rows != cols) return 0;
        
        switch (rows) {
        case 2: {
            return mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0];
        }
        default: {
            Type res = 0;
            uint64_t i, j, k;
            Type** minor = new Type * [rows - 1];
            BAD_ALLOC(minor);
            for (i = 0; i < rows - 1; i++) {
                minor[i] = new Type[cols - 1];
                BAD_ALLOC(minor[i])
            }

            for (i = 0; i < cols; i++) {
                


                for (j = 1; j < rows; j++) {
                    uint64_t step = 0;
                    for (k = 0; k < cols; k++) {
                        if (k != i) {
                            minor[j - 1][step] = mtx[j][k];
                            step++;
                        }
                    }
                }


                res += std::pow(-1, i) * mtx[0][i] * Det(minor, rows - 1, cols - 1);
            }
            
           
            for (i = 0; i < rows - 1; i++)
                delete[] minor[i];
            delete[] minor;

            return res;
        }
        }
    }

public:

    Type GetDet() {
        return Det(matrix, s, n);
    }

    uint64_t GetS() const {
        return s;
    }
    uint64_t GetN() const {
        return n;
    }

    //constructors
    template <typename elem_type>
    Matrix(elem_type s, elem_type n):
        s(s), n(n) {
        LOG("Constructor SxN");
        matrix = new Type * [s];
        BAD_ALLOC(matrix);
        for (uint64_t i = 0; i < s; i++) {
            matrix[i] = new Type[n];
            BAD_ALLOC(matrix[i]);
            memset((void*) matrix[i], 0, sizeof(Type) * n);
        }  
    }

    template <size_t rows, size_t cols>
    Matrix(const Type (&mtx) [rows][cols]): s(rows), n(cols)
    {
        LOG("Constructor arr[][]");
        matrix = new Type * [s];
        BAD_ALLOC(matrix);
        for (uint64_t i = 0; i < s; i++) {
            matrix[i] = new Type[n];
            BAD_ALLOC(matrix[i]);
            memcpy((void*) matrix[i], (void*) mtx[i], sizeof(mtx[i]));
        }
    }

    Matrix(const Matrix<Type>& mtx): s(mtx.s), n(mtx.n) {
        LOG("Copy Constructor");
        matrix = new Type*[mtx.s];
        BAD_ALLOC(matrix);
        for (uint64_t i = 0; i < s; i++) {
            matrix[i] = new Type[n];
            BAD_ALLOC(matrix[i]);
            memcpy((void*)(matrix[i]), (void*)(mtx[i] ), sizeof(Type)*n);
        }
    }

    Matrix<Type>& operator=(Matrix<Type> mtx) {
        LOG("Operator =");
        std::swap(s, mtx.s);
        std::swap(n, mtx.n);
        std::swap(matrix, mtx.matrix);
        return *this;
    }


    void operator += (const Matrix<Type>& mtx) {
        LOG("Operator +=");
        if (!((s == mtx.s) && (n == mtx.n))) return;

        for (uint64_t i = 0; i < s; i++) {
            for (uint64_t j = 0; j < n; j++) {
                matrix[i][j] += mtx.matrix[i][j];
            }
        }
        return;
    }
    
    Matrix<Type> operator++() {
        for (uint64_t i = 0; i < s; i++) {
            for (uint64_t j = 0; j < n; j++) {
                matrix[i][j] += 1;
            }
        }
        return *this;
    }

    void operator *= (const Matrix<Type>& mtx) {
        LOG("Operator *=");
        if (this->matrix == mtx.matrix) {
            Matrix<Type> copy(mtx);
            *this *= copy;
            return;
        }
        if (!(n == mtx.s)) return;

        this->n = mtx.n;
        Type** oldmatrix = matrix;
        uint64_t i;

        //new matrix**
        matrix = new Type*[s];
        BAD_ALLOC(matrix);

        for (i = 0; i < s; i++) {
            matrix[i] = new Type[n];
            BAD_ALLOC(matrix[i]);
        }

        for (i = 0; i < s; i++) {
            for (uint64_t j = 0; j < n; j++) {
                Type sum = 0;
                for (uint64_t k = 0; k < n; k++)
                    sum += oldmatrix[i][k] * mtx.matrix[k][j];
                matrix[i][j] = sum;
            }
        }


        for (i = 0; i < s; i++)
            delete[] oldmatrix[i];
        delete[] oldmatrix;

        return;
    }



    friend Matrix<Type> operator + (const Matrix<Type>& mtx1, const Matrix<Type>& mtx2) {
        Matrix<Type> mtx(mtx1);
        LOG("Operator +");
        mtx += mtx2;
        return mtx;
    }

    friend Matrix<Type> operator * (const Matrix<Type>& mtx1, const Matrix<Type>& mtx2) {
        Matrix<Type> mtx(mtx1);
        LOG("Operator *");
        mtx *= mtx2;
        return mtx;
    }

    ~Matrix() {
        LOG("Destructor");
        for (uint64_t i = 0; i < s; i++) {
            if (matrix[i] != nullptr) delete[] matrix[i];
        }

        if (matrix != nullptr) delete[] matrix;
    }

  
    template <typename elem_type>
    Type* operator[](elem_type i) const {
        return matrix[i];
    }



    //cout 
    friend std::ostream& operator << (std::ostream& stream, const Matrix<Type>& matrix) {
        for (uint64_t i = 0; i < matrix.GetS(); i++) {
            for (uint64_t j = 0; j < matrix.GetN(); j++) {
                stream << matrix[i][j] << " ";
            }
            stream << "\n";
        }
        return stream;
    }

    //cin
    friend std::istream& operator >> (std::istream& stream, const Matrix<Type>& matrix) {
        for (uint64_t i = 0; i < matrix.GetS(); i++) {
            for (uint64_t j = 0; j < matrix.GetN(); j++) {
                stream >> matrix[i][j];
            }}
        return stream;
    }
    
};

int main()
{
    int64_t  mtx2[6][6]{
        {41, 18, 64, 20, 19, 14},
        {55, 25, 28, 27, 61, 91},
        {91, 14, 32, 13, 92, 82 },
        {47, 26, 71, 38, 9, 92},
        {73, 11, 32, 33, 13, 44},
        {27, 24, 32, 27, 237, 19}
    };
    Matrix<int64_t> matrix1(mtx2);
  
    std::cout << matrix1;
    std::cout << matrix1.GetDet() << std::endl;
}
