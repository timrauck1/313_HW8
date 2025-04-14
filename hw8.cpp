#include <cstdio>

class matrixFunctions{
    public:
    
    void addMatrices(int matrixOne[2][2], int matrixTwo[2][2],int matrixRow, int matrixCol){
        for(int i = 0; i < matrixRow;i++){
            for(int j = 0; j < matrixCol; j++){
                matrixOne[i][j] = matrixOne[i][j]+matrixTwo[i][j];
            }
        }
    }
    
    void multiplyMatrices(int matrixOne[2][3], int matrixTwo[3][2],int matrixOneRow, int matrixOneCol
    ,int matrixTwoRow, int matrixTwoCol, int result[2][2]){
        for(int i = 0; i <= 1; i++){
            for(int j = 0; j <= 1; j++){
                for(int z = 0; z < 3; z++){
                    result[i][j] += matrixOne[i][z] * matrixTwo[z][j];
                }
            }
        }
    }

    void multiplyMatrixByInt(int integer, int matrix[2][3], int rows, int cols){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j <cols; j++){
                matrix[i][j] = matrix[i][j] * integer;
            }
        }
    }
    
};

int main(){
    //creates the matrices
    int a[2][2] = {{6,4},{8,3}};
    int b[2][3] = {{1,2,3},{4,5,6}};
    int c[3][2] = {{2,1},{4,3},{6,5}};
    int d[2][2] = {0};
    matrixFunctions func;
    //multiplies 3 and b
    func.multiplyMatrixByInt(3, b, 2, 3);
    //multiplies b and c
    func.multiplyMatrices(b, c, 2, 3, 3, 2, d);
    //adds together the multiple of b and c with a to produce d
    func.addMatrices(d, a, 2, 2);
    
    //prints d
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%i ", d[i][j]);
        } 
        printf("\n");  
    }
    return 0;
}
