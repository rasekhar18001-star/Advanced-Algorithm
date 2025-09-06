#include <iostream>
using namespace std;

// Structure to store non-zero element
struct Element {
    int row;
    int col;
    int value;
};

// Sparse Matrix Class
class SparseMatrix {
private:
    int rows, cols, nonZeroCount;
    Element *elements;   // dynamic array for non-zero elements

public:
    // Constructor
    SparseMatrix(int r, int c, int nz) {
        rows = r;
        cols = c;
        nonZeroCount = nz;
        elements = new Element[nonZeroCount];
    }

    // Destructor
    ~SparseMatrix() {
        delete[] elements;
    }

    // Read sparse matrix
    void read() {
        cout << "Enter non-zero elements (row col value):\n";
        for (int i = 0; i < nonZeroCount; i++) {
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }

    // Display full matrix
    void display() {
        int k = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < nonZeroCount && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k].value << " ";
                    k++;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int rows, cols, nz;

    cout << "Enter dimensions of matrix (rows cols): ";
    cin >> rows >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> nz;

    SparseMatrix sm(rows, cols, nz);
    sm.read();

    cout << "\nSparse Matrix (full form):\n";
    sm.display();

    return 0;
}