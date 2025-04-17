#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int m_col;
    int m_row;
    int** m_matrix;
} matrix;

// Initialize an empty matrix
void matrix_init(matrix* m) {
    m->m_col = 0;
    m->m_row = 0;
    m->m_matrix = NULL;
}

// Create a matrix with dimensions and default value
void matrix_create(matrix* m, int row, int col, int defaultValue) {
    m->m_col = col;
    m->m_row = row;
    m->m_matrix = (int**)malloc(row * sizeof(int*));
    
    for(int i = 0; i < row; i++) {
        m->m_matrix[i] = (int*)malloc(col * sizeof(int));
    }
    
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            m->m_matrix[i][j] = defaultValue;
        }
    }
}

// Free memory
void matrix_free(matrix* m) {
    if (m->m_matrix != NULL) {
        for(int i = 0; i < m->m_row; i++) {
            free(m->m_matrix[i]);
        }
        free(m->m_matrix);
        m->m_matrix = NULL;
    }
}

// Getters
int matrix_getCol(const matrix* m) {
    return m->m_col;
}

int matrix_getRow(const matrix* m) {
    return m->m_row;
}

// Get element at position
int matrix_getElement(const matrix* m, int row, int col) {
    if (row < 0 || row >= m->m_row || col < 0 || col >= m->m_col) {
        printf("Index out of bounds");
        return 0;
    }
    return m->m_matrix[row][col];
}

// Set element at position
void matrix_setElement(matrix* m, int row, int col, int value) {
    if (row < 0 || row >= m->m_row || col < 0 || col >= m->m_col) {
        printf("Index out of bounds");
        return;
    }
    m->m_matrix[row][col] = value;
}

// Multiply matrix by integer
void matrix_multByInt(matrix* m, int integer) {
    for(int i = 0; i < m->m_row; i++) {
        for(int j = 0; j < m->m_col; j++) {
            m->m_matrix[i][j] = m->m_matrix[i][j] * integer;
        }
    }
}

// Add matrices of the same size
void matrix_add(matrix* result, const matrix* matrixToAdd) {
    if(result->m_col != matrixToAdd->m_col || result->m_row != matrixToAdd->m_row) {
        printf("Matrix sizes don't match, can't add.");
        return;
    }
    
    for(int i = 0; i < result->m_row; i++) {
        for(int j = 0; j < result->m_col; j++) {
            int matrixToAddValue = matrix_getElement(matrixToAdd, i, j);
            result->m_matrix[i][j] = result->m_matrix[i][j] + matrixToAddValue;
        }
    }
}

// Multiply matrices
void matrix_multiply(matrix* result, const matrix* matrixOne, const matrix* matrixTwo) {
    if(matrixOne->m_col != matrixTwo->m_row) {
        printf("Not a valid multiplication size");
        return;
    }
    
    // Makes sure the result matrix is empty before multiplication
    matrix_free(result);
    
    int matchingValue = matrixOne->m_col;
    result->m_row = matrixOne->m_row;
    result->m_col = matrixTwo->m_col;
    
    result->m_matrix = (int**)malloc(result->m_row * sizeof(int*));
    for(int i = 0; i < result->m_row; i++) {
        result->m_matrix[i] = (int*)malloc(result->m_col * sizeof(int));
    }
    
    for(int i = 0; i < result->m_row; i++) {
        for(int j = 0; j < result->m_col; j++) {
            int sum = 0;
            for(int x = 0; x < matchingValue; x++) {
                int firstValue = matrix_getElement(matrixOne, i, x);
                int secondValue = matrix_getElement(matrixTwo, x, j);
                sum += (firstValue * secondValue);
            }
            result->m_matrix[i][j] = sum;
        }
    }
}

// Prints matrix passed in
void matrix_print(const matrix* m) {
    for(int i = 0; i < m->m_row; i++) {
        for(int j = 0; j < m->m_col; j++) {
            int value = matrix_getElement(m, i, j);
            printf("%d ", value);
        }
        printf("\n");
    }
}

// Test functions

//sets the default values for the matrices used in the test equation
void matrix_setValuesForA(matrix* m) {
    m->m_matrix[0][0] = 6;
    m->m_matrix[0][1] = 4;
    m->m_matrix[1][0] = 8;
    m->m_matrix[1][1] = 3;
}

void matrix_setValuesForB(matrix* m) {
    m->m_matrix[0][0] = 1;
    m->m_matrix[0][1] = 2;
    m->m_matrix[0][2] = 3;
    m->m_matrix[1][0] = 4;
    m->m_matrix[1][1] = 5;
    m->m_matrix[1][2] = 6;
}

void matrix_setValuesForC(matrix* m) {
    m->m_matrix[0][0] = 2;
    m->m_matrix[1][0] = 4;
    m->m_matrix[2][0] = 6;
    m->m_matrix[0][1] = 1;
    m->m_matrix[1][1] = 3;
    m->m_matrix[2][1] = 5;
}

int main() {
    //creates the a b c and d matrices
    matrix a, b, c, d;
    
    matrix_init(&a);
    matrix_init(&b);
    matrix_init(&c);
    matrix_init(&d);
    
    matrix_create(&a, 2, 2, 0);
    matrix_create(&b, 2, 3, 0);
    matrix_create(&c, 3, 2, 0);
    
    //sets the default values for a b and c
    matrix_setValuesForA(&a);
    matrix_setValuesForB(&b);
    matrix_setValuesForC(&c);
    
    //test equation
    matrix_multByInt(&b, 3);
    matrix_multiply(&d, &b, &c);
    matrix_add(&d, &a);
    
    matrix_print(&d);
    //deallocates memory
    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&c);
    matrix_free(&d);
    
    return 0;
}
