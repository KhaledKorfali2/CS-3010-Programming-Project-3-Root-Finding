#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include<vector>
#include <iomanip>
using namespace std;

//constants
const int NMAX = 100;
const double EBSOL = 0.01;

//function prototypes
double calcFunctionA(double x); //f(x)=2x^{3}-11.7x^{2}+17.7x-5
double calcFunctionB(double x); //f(x)=x+10-xcosh(50/x)
double calcDerivFuncA(double x);
double calcDerivFuncB(double x);
void Bisection(double (*func)(double), double a, double b);
int main()
{
	cout << "Program is Running" << endl;
	int equationNum = 0;
	double a, b;

	//Check which functin the user wants to find the roots of
	cout << "Which equation do you want to find the roots for:" << endl;
	cout << "1. f(x)=2x^{3}-11.7x^{2}+17.7x-5" << endl;
	cout << "2. f(x)=x+10-xcosh(50/x)" << endl;
	while (equationNum != 1 && equationNum != 2)
	{
		//system("clear");
		cin.clear();                        // clear error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty buffer 
		cout << "Error: Please enter an integer between 1 and 2 (inclusive)." << endl;
		cin >> equationNum;
	}
	//get starting values from user
	cout << "Please enter a value for a: " << endl;
	cin >> a;

	cout << "Please enter a value for b: " << endl;
	cin >> b;

	if (equationNum == 1)
	{
		while (calcFunctionA(a) * calcFunctionA(b) >= 0)
		{
			//system("clear");
			cout << "Error: Please enter diffrent values for a and b" << endl;
			cout << "Please enter a value for a: " << endl;
			cin >> a;

			cout << "Please enter a value for b: " << endl;
			cin >> b;
		}
	}
	else
	{
		while (calcFunctionB(a) * calcFunctionB(b) >= 0)
		{
			cout << "Error: Please enter diffrent values for a and b" << endl;
			cout << "Please enter a value for a: " << endl;
			cin >> a;

			cout << "Please enter a value for b: " << endl;
			cin >> b;
		}
	}

	cout << "Program Has Reached Its End";
}

void Bisection(double (*func)(double), double a, double b)
{
	cout << endl << "****************" << endl;
	cout << "Bisection Method" << endl;
	cout << "****************" << endl;
	int n, nmax;
	double c, fa, fb, fc, error;
	fa = func(a);
	fb = func(b);
	if (fa * fb >= 0)
	{
		cout << a << " " << b << " " << fa << " " << fb << endl;
		cout << "function has same signs at a and b" << endl;
		return;
	}
	error = b - a;
	for (n = 0; n < NMAX;n++)
	{
		error /= 2;
		c = a + error;
		fc = func(c);
		cout << "n: " << n << "c: " << c << "fc: " << fc << "error: " << error << endl;
		if (abs(error) < EBSOL)
		{
			cout << "convergence" << endl;
			return;
		}
		if (fa * fc < 0)
		{
			b = c;
			fb = fc;
		}
		else
		{
			a = c;
			fa = fc;
		}

	}
}

void NewtonRaphson(double (*func)(double), double (*funcPrime)(double), double x)
{
	cout << endl << "****************" << endl;
	cout << "Newton-Raphson Method" << endl;
	cout << "****************" << endl;
	double fx, fp, d;
	fx = func(x);
	cout << "n: " << 0 << "x: " << x << "fx: " << fx << endl;
	for (int n = 1; n < NMAX;n++)
	{
		fp = funcPrime(x);
		if (abs(fp) < EBSOL)
		{
			cout << "Small Derivative" << endl;
			return;
		}
		d = fx / fp;
		x -= d;
		fx = func(x);
		cout << "n: " << n << "x: " << x << "fx: " << fx << endl;
		if (d < EBSOL)
		{
			cout << "convergance" << endl;
			return;
		}
	}
}

void Secant(double (*func)(double), double a, double b)
{
	cout << endl << "****************" << endl;
	cout << "Secant Method" << endl;
	cout << "****************" << endl;
	double fa, fb, d;
	fa = func(a);
	fb = func(b);
	if (abs(fa) > abs(fb))
	{
		a = b;
		fa = fb;
	}
	cout << "n: " << 0 << "a: " << a << "fa: " << fa << endl;
	cout << "n: " << 1 << "b: " << b << "fb: " << fb << endl;
	for (int n = 2; n < NMAX; n++)
	{
		if (abs(fa) > abs(fb))
		{
			a = b;
			fa = fb;
		}
		d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;
		if (abs(d) < EBSOL)
		{
			cout << "converges" << endl;
		}
		a = a - d;
		fa = func(a);
		cout << "n: " << n << "a: " << a << "fa: " << fa << endl;

	}
}

void FalsePosition(double (*func)(double), double a, double b)
{
	cout << endl << "****************" << endl;
	cout << "False-Position Method" << endl;
	cout << "****************" << endl;
	double fa, fb, d;
	fa = func(a);
	fb = func(b);
	if (abs(fa) > abs(fb))
	{
		a = b;
		fa = fb;
	}
	cout << "n: " << 0 << "a: " << a << "fa: " << fa << endl;
	cout << "n: " << 1 << "b: " << b << "fb: " << fb << endl;
	for (int n = 2; n < NMAX; n++)
	{
		if (abs(fa) > abs(fb))
		{
			a = b;
			fa = fb;
		}
		d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;
		if (abs(d) < EBSOL)
		{
			cout << "converges" << endl;
		}
		a = a - d;
		fa = func(a);
		cout << "n: " << n << "a: " << a << "fa: " << fa << endl;

	}
}


//f(x)=2x^{3}-11.7x^{2}+17.7x-5
double calcFunctionA(double x)
{
	return (2 * x * x * x) - (11.7 * x * x) + (17.7 * x) - 5;
}

//f'(x)=6x^{2}-23.4x+17.7
double calcDerivFuncA(double x)
{
	return (6 * x * x) - (23.4 * x) + 17.7;
}


//f(x)=x+10-xcosh(50/x)
double calcFunctionB(double x)
{
	return (x + 10) - (x * cosh(50/x));
}

//f'(x)=(50sinh(50/x))/x - cosh(50/x) + 1
double calcDerivFuncB(double x)
{
	return ((50 * sinh(50 / x)) / x) - cosh(50 / x) + 1;
}