
#include<iostream>
#include<fstream>
#include <iomanip>
using namespace std;

void linearRegression(int testNumber, int N, float *X, float *Y);
void quadraticRegression(int testNumber, int N, float *X, float *Y);
float sigma(float *arr, int N);

int main(){

	fstream inFile("in.txt"); 
	if (!inFile.is_open()) {
		cout << "file is not opened" << endl;
		exit(1);
	}
	int N; 
	int testNumber = 1;

	do{
		inFile >> N;

		float *X = new float[N];
		float *Y = new float[N];

		for (int i = 0; i < N; i++){
			inFile >> X[i] >> Y[i];
		}

		linearRegression(testNumber, N, X, Y);
		quadraticRegression(testNumber, N, X, Y);
		++testNumber;

		delete []X;
		delete []Y;
	} while (!inFile.eof());
	  
	
}

//linearRegression
void linearRegression(int testNumber, int N, float *X, float *Y){
	float a0, a1;
	
	float *mul_x_y = new float[N];
	float *mul_x_x = new float[N];

	for (int i = 0; i < N; i++){
		mul_x_y[i] = X[i] * Y[i];
		mul_x_x[i] = X[i] * X[i];
	}

	float sigma_x = sigma(X, N);
	float sigma_y = sigma(Y, N);

	//system equation from derivative
	a1 = (N * sigma(mul_x_y, N) - sigma_x * sigma_y) / (N * sigma(mul_x_x, N) - sigma_x * sigma_x);
	a0 = sigma_y / N - (sigma_x*a1) / N;
	
	cout << "Test " << testNumber << endl;
	cout << "Linear regression: y = " << setprecision(4) << a0 << " + " << a1 << "x" << endl;

	delete[]mul_x_y;
	delete[]mul_x_x;
}


//quadraticRegression with naive gauss elimination
void quadraticRegression(int testNumber, int N, float *X, float *Y){
	float a0, a1, a2;
	

	float *mul_x_y = new float[N];
	float *square_x = new float[N];
	float *cube_x = new float[N];
	float *mul_y_square_x = new float[N];
	float *x_power_of_4 = new float[N];
	for (int i = 0; i < N; i++){
		mul_x_y[i] = X[i] * Y[i];
		square_x[i] = pow(X[i], 2);
		cube_x[i] = pow(X[i], 3);
		mul_y_square_x[i] = Y[i] * square_x[i];
		x_power_of_4[i] = pow(X[i], 4);
	}

	//the result of derivative
	float c[3][4];
	c[0][3] = sigma(Y,N);
	c[0][0] = (float)N;
	c[0][1] = sigma(X, N);
	c[0][2] = sigma(square_x, N);
	
	c[1][3] = sigma(mul_x_y, N);
	c[1][0] = sigma(X, N);
	c[1][1] = sigma(square_x, N);
	c[1][2] = sigma(cube_x, N);

	c[2][3] = sigma(mul_y_square_x, N);
	c[2][0] = sigma(square_x, N);
	c[2][1] = sigma(cube_x, N);
	c[2][2] = sigma(x_power_of_4, N);

	//gauss elimination 
	for (int i = 0; i < 2; i++){
		for (int j = i+1; j <= 2; j++){
			float ratio = (c[j][i] / c[i][i]);
			for (int k = 0; k < 4; k++){
				c[j][k] = c[j][k] - c[i][k] * ratio;
			}
		}
	}

	a2 = c[2][3] / c[2][2];
	a1 = (c[1][3] - c[1][2] * a2) / c[1][1];
	a0 = (c[0][3] - c[0][2] * a2 - c[0][1] * a1) / c[0][0];

	cout << "Quadratic regression: y = " << setprecision(4) << a0 << " + " << a1 << "x" << " + " << a2 << "x^2" << endl;
	
	delete[]mul_x_y;
	delete[]square_x;
	delete[]cube_x;
	delete[]mul_y_square_x;
	delete[]x_power_of_4;
}

//Array sum function
float sigma(float *arr, int N){
	float sum = 0;
	for (int i = 0; i < N; i++){
		sum += arr[i];
	}
	return sum;
}