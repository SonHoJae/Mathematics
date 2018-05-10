#include<iostream>
#include<fstream> 
using namespace std;

const static int MAX_LINE = 1000;
const static int LIMIT_ITERATIONS = 1000; // choosen arbitrarily
const static float THRESHOLD = 0.00001; // 0.001% given from problem

void bisectionMethod(float leftBoundary, float rightBoundary, float * coefficient, int * exponent, int n);
void newtonRapsonMethod(float initialValue, float * coefficient, int * exponent, int n);
float derivativeFunction(float x, float *coefficient, int *exponent, int n);
float given_function(float x, float * coefficient, int * exponent, int n); // return polynomial function value
void setBoundaryValue(float &, float &); // xl < xu

int main(){
	ifstream is("in.txt");
	float initialValue, leftBoundary, rightBoundary;
	is >> leftBoundary >> rightBoundary >> initialValue;
	setBoundaryValue(leftBoundary, rightBoundary);

	int n;
	is >> n;

	float *c = new float[n];
	int *a = new int[n];

	for (int i = n - 1; i >= 0; --i){
		is >> c[i] >> a[i];
		if (a[i] > 1000){
			cout << " exponent is less than or equal to 1000" << endl;
		}
	}

	bisectionMethod(leftBoundary, rightBoundary, c, a, n);
	newtonRapsonMethod(initialValue, c, a, n);
	delete a;
	delete c;
	is.close();
}
void bisectionMethod(float leftBoundary, float rightBoundary, float * coefficient, int * exponent, int n){
	float xl = leftBoundary;
	float xu = rightBoundary;
	//if boundary doesn't satisfy with pre-condition, it doesn't look up anymore.
	if (given_function(leftBoundary, coefficient, exponent, n) * given_function(rightBoundary, coefficient, exponent, n) > 0){
		cout << "Bisection: Failed" << endl;
		return;
	}

	bool isFoundRoot = false; //to check this method can find the root given maximum_iterations

	int iterations = 0;
	for (int i = 0; i <= LIMIT_ITERATIONS; i++){
		//found root -> (leftBoundary + rightBoundary)/2 
		if (given_function(leftBoundary, coefficient, exponent, n) * given_function((leftBoundary + rightBoundary) / 2, coefficient, exponent, n) == 0){
			cout << "Bisection: " << (leftBoundary + rightBoundary) / 2 << "(" << i+1 << " iterations)" << endl;
			iterations = i;
			isFoundRoot = true;
			break;
		}
		//if the root exists in left side
		else if (given_function(leftBoundary, coefficient, exponent, n) * given_function((leftBoundary + rightBoundary) / 2, coefficient, exponent, n) < 0){
			rightBoundary = (leftBoundary + rightBoundary) / 2;
		}
		//if the root exists in right side
		else{
			leftBoundary = (leftBoundary + rightBoundary) / 2;
		}
		//Ea < Es
		if ((abs(leftBoundary - rightBoundary) / 2) / (abs(leftBoundary + rightBoundary) / 2) < THRESHOLD){
			cout << "Bisection: " << (leftBoundary + rightBoundary) / 2 << "(" << i+1 << " iterations)" << endl;
			iterations = i+1;
			isFoundRoot = true;
			break;
		}
	}
	if (!isFoundRoot){
		cout << "Bisection: Failed" << endl;
	}
}
void newtonRapsonMethod(float initialValue, float * coefficient, int * exponent, int n){
	float x = initialValue;
	bool isFoundRoot = false; //to check this method can find the root given maximum_iterations
	for (int i = 0; i < LIMIT_ITERATIONS; i++){
		if (given_function(x, coefficient, exponent, n) == 0){
			cout << "Newton-Raphson: " << x << "(" << i+1 << " iterations)" << endl;
			isFoundRoot = true;
			break;
		}
		float prevX = x;
		float *tempCoeff = new float[n];
		int *tempExpon = new int[n];
		for (int i = 0; i < n; i++){
			tempCoeff[i] = coefficient[i];
			tempExpon[i] = exponent[i];
		}

		float derivativeValue = derivativeFunction(x, tempCoeff, tempExpon, n);
		if (derivativeValue == 0){
			break;
		}
		x = x - given_function(x, coefficient, exponent, n) / derivativeValue;

		delete tempCoeff;
		delete tempExpon;

		if ((abs((x - prevX) / x)) < THRESHOLD){
			cout << "Newton-Raphson: " << x << "(" << i+1 << " iterations)" << endl;
			isFoundRoot = true;
			break;
		}
	}
	if (!isFoundRoot){
		cout << "Newton-Raphson: Failed" << endl;
	}
}
float derivativeFunction(float x, float *coefficient, int *exponent, int n){
	bool isConstant = false;
	//polynomial derivative
	for (int i = n - 1; i >= 0; i--){
		if (exponent[i] == 0){
			isConstant = true;
			continue;
		}
		coefficient[i] *= exponent[i];
		exponent[i] -= 1;
	}
	//if there is a constant, don't move element
	if (isConstant){
		for (int i = 0; i < n - 1; i++){
			coefficient[i] = coefficient[i + 1];
			exponent[i] = exponent[i + 1];
		}
		coefficient[n - 1] = 0;
		exponent[n - 1] = 0;
		n = n - 1;
	}
	return given_function(x, coefficient, exponent, n);
}
float given_function(float x, float * coefficient, int * exponent, int n){
	float result = 0;
	for (int i = n - 1; i >= 0; --i){
		result += pow(x, exponent[i]) * coefficient[i];
	}
	return result;
}
void setBoundaryValue(float &left, float &right){
	float temp = left;
	left = right;
	right = temp;
}
