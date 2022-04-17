
#include <iostream>
using namespace std;
template <typename T>
class matrix {
private:
    T** M;
    int cols, rows;
public:
    matrix() {
        cols = rows = 0;
        M = nullptr;
    }
    matrix(int _m, int _n)
    {
        cols = _m;
        rows = _n;
        M = (T**) new T * [cols]; 
        for (int i = 0; i < cols; i++) {
            M[i] = (T *) new T[rows];
            for (int j = 0; j < rows; j++) {
                M[i][j] = 0;
            }
        }
    }
    matrix(const matrix& _M){
        cols = _M.cols;
        rows = _M.rows;
        M = (T**) new T * [cols]; 
        for (int i = 0; i <cols; i++) {
            M[i] = (T *) new T[rows];
            for (int j = 0; j < rows; j++) {
                M[i][j] = _M.M[i][j];
            }
        }
    }
    T ShowEl(int i, int j){
        if(cols > 0 && rows > 0){
            return M[i][j];
        }
        else{
            return 0;
        }
    };
    void CreateMatr() {
        for (int i = 0; i < cols; ++i) {
            
            for (int j = 0; j < rows; ++j) {
                std::cin >> M[i][j];
            }
        }
    }
    void CreateEdMatr(int cols1, int rows1) {
        if (cols1 != rows1) {
            cout << "Can't build matrix";
            return;
        }
        cols = cols1; rows = rows1;
        M = (T**)new T * [cols];
        for (int i = 0; i < cols; ++i) {
            M[i] = (T*)new T[rows];
            for (int j = 0; j < rows; ++j) {
                if (i == j) {
                    M[i][j] = 1;
                }
                else {
                    M[i][j] = 0;
                }
            }
        }
    }

    void ShowMatr() {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cout << M[i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    matrix operator=(const matrix& _M){
        if (rows > 0){
            for (int i = 0; i < cols; i++)
                delete[] M[i];
        }

        if (cols > 0){
            delete[] M;
        }
        cols = _M.cols;
        rows = _M.rows;
        M = (T**) new T * [cols]; 
        for (int i = 0; i < cols; i++)
            M[i] = (T*) new T[rows];
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                M[i][j] = _M.M[i][j];
            }
        }
        return *this;
    }
    matrix Transp() {
        matrix<T> R(rows, cols);
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                R.M[j][i] = M[i][j];
            }
        }
        if (rows > 0) {
            for (int i = 0; i < cols; i++)
                delete[] M[i];
        }

        if (cols > 0) {
            delete[] M;
        }
        cols = R.cols;
        rows = R.rows;
        M = (T**) new T * [cols];
        for (int i = 0; i < cols; i++)
            M[i] = (T*) new T[rows];
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                M[i][j] = R.M[i][j];
            }
        }
        return *this;
    }
    double det() {
        if (cols != rows) {
            cout << "Can't count determinant";
        }
        else {
            double determ = 1;
            matrix<T> R(cols, rows);
            R.M = M;
            for (int i = 1; i < cols; ++i){
                for (int k = i; k < cols; ++k)
                {
                    for (int j = cols - 1; j >= 0; --j)
                    {
                        R.M[k][j] -= R.M[k][i - 1] / R.M[i - 1][i - 1] * R.M[i - 1][j];
                    }
                }
            }
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << R.M[i][j] << "\t";
                }
                cout << endl;
            }
            for (int i = 0; i < cols; i++) {
                determ *= R.M[i][i];
            }
            return determ;
        }

        
    }
    matrix operator+(const matrix& E) {
        if (cols == E.cols && rows == E.rows) {
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    M[i][j] += E.M[i][j];
                }
            }
        }
        else {
            cout << "Can't sum";
        }
        return *this;
    }
    matrix operator+(const T &a) {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                M[i][j] += a;
            }
        }
        return *this;
    }
    matrix operator-(const T &a) {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                M[i][j] -= a;
            }
        }
        return *this;
    }
    matrix operator-(const matrix& E) {
        if (cols == E.cols && rows == E.rows) {
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    M[i][j] -= E.M[i][j];
                }
            }
            return *this;
        }
        else {
            cout << "Can't minus";
        }
    }
    matrix operator*(const T& a) {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                M[i][j] *= a;
            }
        }
        return *this;
    }
    matrix operator*(const matrix& E) {
        matrix<T> R(cols, E.rows);
        int k;
        if (rows == E.cols) {
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < E.rows; ++j) {
                    k = 0;
                    for (int l = 0; l < rows; ++l) {
                        cout << M[i][l] << " " << E.M[l][j] << endl;
                        k += M[i][l] * E.M[l][j];
                        cout << k << endl;
                    }
                    R.M[i][j] = k;
                }
            }
            if (rows > 0) {
                for (int i = 0; i < cols; i++)
                    delete[] M[i];
            }

            if (cols > 0) {
                delete[] M;
            }
            cols = R.cols;
            rows = R.rows;
            M = (T**) new T * [cols];
            for (int i = 0; i < cols; i++)
                M[i] = (T*) new T[rows];
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    M[i][j] = R.M[i][j];
                }
            }
            return *this;
        }
        else {
            cout << "Cant multiply";
        }
    }
    bool operator==(const matrix & E) {
        if (cols == E.cols && rows == E.rows){
            int flag = 0;
            for (int i = 0; i < cols; i++){
                for (int j = 0; j < rows; j++) {
                    if (M[i][j] != E.M[i][j]) {
                        flag = 1;
                    }
                }
            }
            if (flag == 0) {
                return true;
            }
            else {
                return false;
            }
         }
         else {
            return false;
         } 
    }
    bool operator!=(const matrix& E) {
        if (cols == E.cols && rows == E.rows) {
            int flag = 0;
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (M[i][j] != E.M[i][j]) {
                        flag = 1;
                    }
                }
            }
            if (flag == 0) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            return true;
        }
    }
    ~matrix(){
//        if (rows> 0)
//        {
//            for (int i = 0; i < cols; i++)
//                delete[] M[i];
//        }
//
//        if (cols > 0)
//            delete[] M;
//
    }//При создании деструктора исключение почему-то
};

int main() {
    matrix<double> M(3, 3);
    M.CreateMatr();
    matrix<double> E(3, 3);
    E.CreateMatr();
    M = M + E;
    M.ShowMatr();
}