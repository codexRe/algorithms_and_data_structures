#include<bits/stdc++.h>
using namespace std;

// Sparse Matrix Linked List Representation
struct SparseNode{
    int value;
    int row;
    int column;
    SparseNode* next;
    SparseNode(int v, int r, int c) : value(v), row(r), column(c), next(nullptr) {}
};

SparseNode* createSNLL(vector<vector<int>> arr, int row, int col){ // Create a sparse matrix
    SparseNode* head = nullptr;
    SparseNode* tail = nullptr;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++){
            if(arr[i][j]){
                SparseNode* newNode = new SparseNode(arr[i][j], i, j);
                if(head == nullptr) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail -> next = newNode;
                    tail = newNode;
                }
            }
        }
    return head;
}

void displaySN(SparseNode* head){
    SparseNode* ptr = head;
    if(head == nullptr){
        cout << "\nThat's an empty list!\n";
        return;
    }
    int i = 1;
    cout << "\nHere's your list: \n";
    while(ptr && ptr -> value){
        cout << " Node "<< i<<" - Row: " << ptr->row << "\t" 
             << "Col: " << ptr->column << "\t" 
             << "Val: " << ptr->value << "\n";
        ptr = ptr -> next;
        ++i;
    }
}

// Sparse Matrix Compressed Row Storage (CRS or CSR - Compressed Sparse Row)
struct SparseMatrixCSR {
    int* values;
    int* col;
    int* row_ptr;
    int rows;
    int cols;
    int nnz;

    SparseMatrixCSR(int r, int c, int n) : rows(r), cols(c), nnz(n) {
        values = nullptr;
        col = nullptr;
        row_ptr = new int[rows + 1];
        for(int i = 0; i <= rows; i++) {
            row_ptr[i] = 0;
        }
    }
};

SparseMatrixCSR* createCSR(vector<vector<int>>matrix, int nnz){
    int rows = matrix.size();
    int cols = matrix[0].size();
    int idx = 0;
    
    SparseMatrixCSR* csr = new SparseMatrixCSR(rows, cols, nnz);
    csr -> values = new int[nnz];
    csr -> col = new int[nnz];
    csr -> row_ptr[rows] = nnz;

    for(int i = 0; i < rows; i++){
        csr -> row_ptr[i] = idx;
        for(int j = 0; j < cols; j++){
            if(matrix[i][j]){
                csr -> values[idx] = matrix[i][j];
                csr -> col[idx] = j;
                ++idx;
            }
        }
    }
    return csr;
}

void displayCSR(SparseMatrixCSR* csr){
    cout << "\n\n CSR of Matrix: \n";
    cout << "values  : | ";
    for(int i = 0; i < csr->nnz; i++) {
        cout << csr->values[i] << " | ";
    }
    cout << "\n";
    
    cout << "column  : | ";
    for(int i = 0; i < csr->nnz; i++) {
        cout << csr->col[i] << " | ";
    }
    cout << "\n";
    
    cout << "row_ptr : | ";
    for(int i = 0; i <= csr->rows; i++) {
        cout << csr->row_ptr[i] << " | ";
    }
    cout << "\n";
}

void displayCSR_uncompressed(SparseMatrixCSR* csr){
    cout << "\n Uncompressed CSR (Value | Row | Column):";
    
    for(int i = 0; i < csr -> rows; i++){
        int val_begin = csr ->row_ptr[i];
        int val_end = csr -> row_ptr[i+1];
        for(int j = val_begin; j < val_end; j++){
            cout << "\n Non-zero Element " << j << ": " << csr -> values[j] << " | " << i << " | " << csr -> col[j];
        }
    }
}

int main(){
    int row = 0, col = 0;
    cout << "\n\nEnter the number of rows and columns: ";
    cin >> row >> col;

    vector<vector<int>> matrix(row, vector<int>(col, 0));

    cout << "\nEnter elements in the form of: row col value";
    bool in = 1;
    int r = 0, c = 0, v = 0;
    int nnz = 0;
    do{
        cout << "\nEnter an element [0: No | 1: Yes]: ";
        cin >> in;
        if (in){
            cout <<"\nEnter element: ";
            cin >> r >> c >> v;
            if(r >= 0 && r < row && c >= 0 && c < col && v) {
                matrix[r][c] = v;
                ++ nnz;
            }
            else {
                cout << "\nInvalid Position or Value = 0!\n";
            }
        }
    }while(in);

    cout << "\nOriginal Matrix: \n";
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    // Sparse Matrix LL
    SparseNode* SNLL =  createSNLL(matrix, row, col);
    displaySN(SNLL);

    // Sparse Matrix CSR
    SparseMatrixCSR* CSR = createCSR(matrix, nnz);
    displayCSR(CSR);
    displayCSR_uncompressed(CSR);

    cout << endl;
    return 0;

}