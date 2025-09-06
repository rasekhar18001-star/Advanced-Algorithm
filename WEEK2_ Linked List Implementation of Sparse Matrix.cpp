#include <iostream>
using namespace std;

// Node structure for sparse matrix
struct Node {
    int row;
    int col;
    int value;
    Node* next;

    Node(int r, int c, int v) {
        row = r;
        col = c;
        value = v;
        next = nullptr;
    }
};

// Sparse Matrix class
class SparseMatrix {
private:
    int rows, cols;
    Node* head;

public:
    // Constructor
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    // Insert a non-zero value into the matrix
    void insert(int r, int c, int val) {
        if (val == 0) return; // Skip zeros

        Node* newNode = new Node(r, c, val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Display sparse representation
    void displaySparse() {
        Node* temp = head;
        cout << "Row  Col  Value\n";
        while (temp) {
            cout << temp->row << "    " << temp->col << "    " << temp->value << endl;
            temp = temp->next;
        }
    }

    // Display the full matrix
    void displayMatrix() {
        Node* temp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (temp && temp->row == i && temp->col == j) {
                    cout << temp->value << " ";
                    temp = temp->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

// Main function
int main() {
    int rows, cols, n;

    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    SparseMatrix sm(rows, cols);

    cout << "Enter number of non-zero elements: ";
    cin >> n;

    cout << "Enter row, column, and value for each non-zero element:\n";
    for (int i = 0; i < n; i++) {
        int r, c, v;
        cout << "Element " << i + 1 << ": ";
        cin >> r >> c >> v;
        sm.insert(r, c, v);
    }

    cout << "\nSparse Representation:\n";
    sm.displaySparse();

    cout << "\nMatrix Form:\n";
    sm.displayMatrix();

    return 0;
}