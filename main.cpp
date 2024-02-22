#include <iostream>
#include <random>


void Matrix_random(double** matrix, int N, double* b){

    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 100;
		}
	}
	for (int j = 0; j < N; j++) {
		b[j] = rand() % 100;
	}
}

void Matrix_Hand(double** Matrix, int N, double* b){
    std::cout << "Enter " << N*N << " matrix elements:" << std::endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cin >> Matrix[i][j];
        }
    }
    std::cout << "Define vector b:" << std::endl;
    for (int s = 0; s < N; s++){
        std::cin >> b[s];
    }
}

double PrintSystem(double** matrix, int N, double* b){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "|" << b[i] << std::endl;
    }
    std::cout << std::endl;
}

double PrintMatrix(double** matrix, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double PrintVector(int N, double* b){
    for (int i = 0; i < N; i++){
        std::cout << b[i] << " ";
    }
}

void GaussPH(double** A, int N, double* b){
    double R;
    for (int i = 0; i < N; i++){
        R = A[i][i];
        if (R == 0){
            std::cout << "This system of equations cannot be solved" << std::endl;
            break;
        }
        if (R != 0){
            for(int j = i; j < N; j++){
                A[i][j] = A[i][j]/R;
            }
        b[i] = b[i]/R;
        for(int k = i+1; k < N; k++){
            R = A[k][i];
            for(int j = i; j < N; j++){
                A[k][j] = A[k][j] - A[i][j]*R;
            }
            b[k] = b[k] - b[i]*R;
        }
        }
    }
}

void GaussOH(double** A, double* b, int N, double* x){
    for(int i = N-1; i > 0; i--){
        x[i] = b[i];
        if(i != N-1){
        for(int j = i+1; j < N; j++){
            x[i] = x[i] - x[j]*A[i][j];
        }
    }
}
}

bool Check_Matrix(double** A, int N){
    if(N = 3){
        double a = (A[0][0]*A[1][1]*A[2][2])+(A[2][0]*A[0][1]*A[1][2])+(A[1][0]*A[2][1]*A[0][2])-(A[2][0]*A[1][1]*A[0][2])-(A[1][0]*A[0][1]*A[2][2])-(A[0][0]*A[1][2]*A[2][1]);
        if(a != 0)
        return true;
        if(a == 0)
        return false;
    }
    if(N=2){
        double a = A[0][0]*A[1][1] - A[0][1]*A[1][0];
        if(a != 0)
        return true;
        if(a == 0)
        return false;
    }
}

double Residual_vector(double* b, double** A, double* x, int N){
    double U = 0.0;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j<N; j++){
            U += A[i][j]*x[j];
        }
        U = b[i] - U;
        std::cout << U << " ";
        U = 0.0;
    }
}

int main(){
    int N;
    std::cout << "Set the size of the matrix:" << std::endl;
    std::cin >> N;

    if (N > 1 && N < 4){
    double** matrix = new double*[N];
        for(int i = 0; i < N; i++){
            matrix[i] = new double[N];
        }

    double* x = new double[N];
	for (int i = 0; i < N; i++)
		x[i] = 1;

    double* b = new double[N];

    std::cout << "Enter 1 to fill in the matrix randomly" << std::endl;
    std::cout << "Enter 2 to fill in the matrix manually" << std::endl;
    int f;
    std::cin >> f;
    switch(f){
        case 1: Matrix_random(matrix, N, b);
        PrintSystem(matrix, N, b);
        std::cout << std::endl;
        break;
        case 2: Matrix_Hand(matrix, N, b);
        PrintSystem(matrix, N, b);
        std::cout << std::endl;
        break;
        default: std::cout << "1 or 2" << std::endl;
    }
    
    double** matrix_1 = new double*[N];
        for(int i = 0; i < N; i++){
            matrix_1[i] = new double[N];
        }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matrix_1[i][j] = matrix[i][j];
        }
    }
    double* b_1 = new double[N];
    for(int i = 0; i < N; i++){
        b_1[i] = b[i];
    }

    bool w = Check_Matrix(matrix, N);
    if (w == true){
        GaussPH(matrix, N, b);
        PrintSystem(matrix, N, b);
        GaussOH(matrix, b, N, x);
        PrintVector(N, x);
        std::cout << "Deviation:" << " ";
        Residual_vector(b_1, matrix_1, x, N);
    }
    else{
        std::cout << "Error" << std::endl;
    }    
    }
    if (N<2 || N>3)
        std::cout << "Error" << std::endl;
    return 0;
}