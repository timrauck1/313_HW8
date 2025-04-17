#include <cstdio>
#include <cstdlib>

class matrix{
    public:
        
        //default constructor
        matrix(){
            m_col = 0;
            m_row = 0;
            m_matrix = nullptr;
        }
        
        //constructor
        matrix(int row, int col, int defaultValue){
            m_col = col;
            m_row = row;
            m_matrix = new int *[m_row];
            for(int i = 0; i < m_row; i++){
                m_matrix[i] = new int[m_col];
            }
            for(int i = 0; i < m_row; i++){
                for(int j = 0; j < m_col; j++){
                    m_matrix[i][j] = defaultValue;
                }
            }
        }

        //destructor
        ~matrix() {
            if (m_matrix != nullptr) {
                for(int i = 0; i < m_row; i++) {
                    delete[] m_matrix[i];
                }
                delete[] m_matrix;
            }
        }
        
        //getters
        int getCol() const{return m_col;}
        int getRow() const{return m_row;}
        
        //multiplies the matrix by the integer passed through
        void multMatrixByInt(int integer){
            for(int i = 0; i < m_row; i++){
                for(int j = 0; j < m_col; j++){
                    m_matrix[i][j] = m_matrix[i][j] * integer;
                }
            }
        }

        //adds the matrix with the matrix passed through
        void addMatrices(const matrix &matrixToAdd){
            //the matrices have to be the same dimesions to add them together
            if(m_col != matrixToAdd.getCol() || m_row != matrixToAdd.getRow()){
                printf("Matrix sizes don't match, can't add.");
            }else{
                for(int i = 0; i < m_row; i++){
                    for(int j = 0; j < m_col; j++){
                        int matrixToAddValue = matrixToAdd.getElement(i,j);
                        m_matrix[i][j] = m_matrix[i][j] + matrixToAddValue;
                    }
                }
            }
            
        }
        
        //gets the value at a given coordinate in the matrix
        int getElement(int row, int col) const {
            if (row < 0 || row >= m_row || col < 0 || col >= m_col) {
                printf("Index out of bounds");
                return 0;
            }
            return m_matrix[row][col];
        }
        
        //sets the value of the matrix
        void setElement(int row, int col, int value) {
            if (row < 0 || row >= m_row || col < 0 || col >= m_col) {
                printf("Index out of bounds");
            }
            m_matrix[row][col] = value;
        }

        //multiples the two matrices passed in
        void multiplyMatrices(const matrix& matrixOne, const matrix& matrixTwo){
            
            //for it to be valid, the col size of matrix one has equal the row size of matrix two
            if(matrixOne.getCol() != matrixTwo.getRow()){
                printf("Not a valid multiplication size");
                return;
            }
            int matchingValue = matrixOne.getCol();
            m_row = matrixOne.getRow();
            m_col = matrixTwo.getCol();
            
            m_matrix = new int *[m_row];
            for(int i = 0; i < m_row; i++){
                m_matrix[i] = new int[m_col];
            }
            
            for(int i = 0; i < m_row; i++){
                for(int j = 0; j < m_col; j++){
                    int m_sum = 0;
                    for(int x =0; x < matchingValue; x++){
                        int firstValue = matrixOne.getElement(i, x);
                        int secondValue = matrixTwo.getElement(x, j);
                        m_sum += (firstValue * secondValue);
                        m_matrix[i][j] = m_sum;
                    }
                }
            }
            
            
        }

        //FOR TESTING
        void setValuesForA(){
            m_matrix[0][0] =6;
            m_matrix[0][1] =4;
            m_matrix[1][0] =8;
            m_matrix[1][1] =3;
        }
        void setValuesForB(){
            m_matrix[0][0] = 1;
            m_matrix[0][1] = 2;
            m_matrix[0][2] = 3;
            m_matrix[1][0] = 4;
            m_matrix[1][1] = 5;
            m_matrix[1][2] = 6;
        }
        void setValuesForC(){
            m_matrix[0][0] = 2;
            m_matrix[1][0] = 4;
            m_matrix[2][0] = 6;
            m_matrix[0][1] = 1;
            m_matrix[1][1] = 3;
            m_matrix[2][1] = 5;
        }
    private:
        int m_col;
        int m_row;
        int ** m_matrix;

};

//prints the matrix passed in
void printMatrix(const matrix &matrix){
    for(int i = 0; i < matrix.getRow(); i++){
        for(int j = 0; j < matrix.getCol(); j++){
            int value = matrix.getElement(i,j);
            printf("%d ", value);
        }
        printf("\n");
    }
}

int main(){
    matrix a = matrix(2,2,0);
    matrix b = matrix(2,3,0);
    matrix c = matrix(3,2,0);
    a.setValuesForA();
    b.setValuesForB();
    c.setValuesForC();
    b.multMatrixByInt(3);
    matrix d = matrix();
    d.multiplyMatrices(b,c);
    d.addMatrices(a);
    printMatrix(d);
     
    
    return 0;
    
}

