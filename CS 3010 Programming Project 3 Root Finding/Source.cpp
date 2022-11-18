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
double calcDerivFuncA(double x); //f'(x)=6x^{2}-23.4x+17.7
double calcDerivFuncB(double x); //f'(x)=(50sinh(50/x))/x - cosh(50/x) + 1

double calcL2Norm(double xi, double yi);

void Bisection(double (*func)(double), double a, double b, int equationNum);
void NewtonRaphson(double (*func)(double), double (*funcPrime)(double), double x, int equationNum);
void Secant(double (*func)(double), double a, double b, int equationNum);
void FalsePosition(double (*func)(double), double a, double b, int equationNum);

void printToFile(vector<double> data, string fileName);


int main()
{
	//Initialize cout to print only 2 places after decimal points
	cout << fixed;
	cout << setprecision(6);

	//Indicate Program Has Started
	cout << "Program is Running" << endl;
	int equationNum = 0;
	double a, b;

	//Check which functin the user wants to find the roots of
	cout << "Which equation do you want to find the roots for:" << endl;
	cout << "1. f(x)=2x^{3}-11.7x^{2}+17.7x-5" << endl;
	cout << "2. f(x)=x+10-xcosh(50/x)" << endl;
	cin >> equationNum;
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

	//User wants to use f(x)=2x^{3}-11.7x^{2}+17.7x-5 as their equation
	if (equationNum == 1)
	{
		//Makes sure that user enters valid a and b values
		while (calcFunctionA(a) * calcFunctionA(b) >= 0)
		{
			//Output error message and ask for new values for a and b
			//system("clear");
			cout << "Error: Please enter diffrent values for a and b" << endl;
			cout << "Please enter a value for a: " << endl;
			cin >> a;

			cout << "Please enter a value for b: " << endl;
			cin >> b;
		}
		//Finds roots using 4 methods
		Bisection(calcFunctionA, a, b, equationNum);
		NewtonRaphson(calcFunctionA, calcDerivFuncA, a, equationNum);
		Secant(calcFunctionA, a, b, equationNum);
		FalsePosition(calcFunctionA, a, b, equationNum);
	}
	//User wants to use f(x)=x+10-xcosh(50/x) as their equation
	else
	{
		//Makes sure that user enters valid a and b values
		while (calcFunctionB(a) * calcFunctionB(b) >= 0)
		{
			//Output error message and ask for new values for a and b
			cout << "Error: Please enter diffrent values for a and b" << endl;
			cout << "Please enter a value for a: " << endl;
			cin >> a;

			cout << "Please enter a value for b: " << endl;
			cin >> b;
		}
		//Finds roots using 4 methods
		Bisection(calcFunctionB, a, b, equationNum);
		NewtonRaphson(calcFunctionB, calcDerivFuncB, a, equationNum);
		Secant(calcFunctionB, a, b, equationNum);
		FalsePosition(calcFunctionB, a, b, equationNum);

	}

	//Indicate Program Has Ended
	cout << "Program Has Reached Its End";
}

//Finds a root of a function using values for a and b through Bisection Method
void Bisection(double (*func)(double), double a, double b, int equationNum)
{
	//Checks which equation user wanted to decide output files
	string outputFile;
	if (equationNum == 1)
	{
		outputFile = "BisectionA.txt";
	}
	else
	{
		outputFile = "BisectionB.txt";
	}
	cout << endl << "****************" << endl;
	cout << "Bisection Method" << endl;
	cout << "****************" << endl;
	vector<double> relApproxErr;
	int n;
	double c, fa, fb, fc, error, REerror, cprev;
	fa = func(a);
	fb = func(b);
	c = 0;
	//Checks if values for a and b are valid, exits out of program if not
	if (fa * fb >= 0)
	{
		cout << a << " " << b << " " << fa << " " << fb << endl;
		cout << "function has same signs at a and b" << endl;
		return;
	}
	error = (b - a);
	//relApproxErr.push_back(error);
	for (n = 0; n < NMAX;n++)
	{
		error /= 2;
		cprev = c;
		c = a + error;
		REerror = abs(c - cprev)/abs(c);
		relApproxErr.push_back(REerror);
		fc = func(c);
		cout << "n: " << n << " c: " << c << " fc: " << fc << " REerror: " << REerror << endl;
		//Checks whether Relative Approxomate Error is less than toleratable error
		//Originally abs(error) < EBSOL
		if (abs(REerror) < EBSOL)
		{
			cout << "convergence" << endl;
			printToFile(relApproxErr, outputFile);
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

//Finds a root of a function using the value for a through Newton Method
void NewtonRaphson(double (*func)(double), double (*funcPrime)(double), double x, int equationNum)
{
	//Checks which equation user wanted to decide output files
	string outputFile;
	if (equationNum == 1)
	{
		outputFile = "NewtonA.txt";
	}
	else
	{
		outputFile = "NewtonB.txt";
	}
	cout << endl << "****************" << endl;
	cout << "Newton-Raphson Method" << endl;
	cout << "****************" << endl;
	vector<double> relApproxErr;
	double fx, fp, d, REerror, xprev;
	REerror = 1;
	fx = func(x);
	xprev = 0;
	cout << "n: " << 0 << " x: " << x << " fx: " << fx << " REerror: " << REerror  << endl;
	relApproxErr.push_back(REerror);
	for (int n = 1; n < NMAX;n++)
	{
		fp = funcPrime(x);
		//Checks if values for a and b are valid, exits out of program if not
		if (abs(fp) < EBSOL)
		{
			cout << "Small Derivative" << endl;
			return;
		}
		d = fx / fp;
		xprev = x;
		x -= d;
		REerror = abs(x - xprev) / abs(x);
		relApproxErr.push_back(REerror);
		fx = func(x);
		cout << "n: " << n << " x: " << x << " fx: " << fx << " REerror: " << REerror << endl;
		//Checks whether Relative Approxomate Error is less than toleratable error
		//originally abs(d) < EBSOL
		if (abs(REerror) < EBSOL)
		{
			cout << "convergance" << endl;
			printToFile(relApproxErr, outputFile);
			return;
		}
	}
	
}

//Finds a root of a function using values for a and b through Secant Method
void Secant(double (*func)(double), double a, double b, int equationNum)
{
	//Checks which equation user wanted to decide output files
	string outputFile;
	if (equationNum == 1)
	{
		outputFile = "SecantA.txt";
	}
	else
	{
		outputFile = "SecantB.txt";
	}
	cout << endl << "****************" << endl;
	cout << "Secant Method" << endl;
	cout << "****************" << endl;
	vector<double> relApproxErr;
	double fa, fb, d, temp, prev, REerror;
	fa = func(a);
	fb = func(b);
	REerror = 1;
	relApproxErr.push_back(REerror);
	if (abs(fa) > abs(fb))
	{
		temp = a;
		a = b;
		b = temp;

		temp = fa;
		fa = fb;
		fb = temp;
	}
	cout << "n: " << 0 << " a: " << a << " fa: " << fa << " REerror: " << REerror << endl;
	cout << "n: " << 1 << " b: " << b << " fb: " << fb << " REerror: " << REerror <<  endl;
	for (int n = 2; n < NMAX; n++)
	{
		if (abs(fa) > abs(fb))
		{
			temp = a;
			a = b;
			b = temp;

			temp = fa;
			fa = fb;
			fb = temp;
		}
		d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;
		//Checks whether Relative Approxomate Error is less than toleratable error
		//Originally abs(d) < EBSOL
		if (abs(REerror) < EBSOL)
		{
			cout << "converges" << endl;
			printToFile(relApproxErr, outputFile);
			return;
		}
		prev = a;
		a -= d;
		REerror = abs(a - prev) / abs(a);
		relApproxErr.push_back(REerror);
		fa = func(a);
		cout << "n: " << n << " a: " << a << " fa: " << fa << " REerror: " << REerror << endl;

	}
}

//Finds a root of a function using values for a and b through False-Position Method
void FalsePosition(double (*func)(double), double a, double b, int equationNum)
{
	//Checks which equation user wanted to decide output files
	string outputFile;
	if (equationNum == 1)
	{
		outputFile = "FalseA.txt";
	}
	else
	{
		outputFile = "FalseB.txt";
	}
	cout << endl << "****************" << endl;
	cout << "False-Position Method" << endl;
	cout << "****************" << endl;
	vector<double> relApproxErr;
	int n;
	double c, fa, fb, fc, error, cprev, REerror;
	fa = func(a);
	fb = func(b);
	c = 0;
	//Checks if values for a and b are valid, exits out of program if not
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
		cprev = c;
		c = (((a * func(b)) - (b * func(a))) / (func(b) - func(a)));
		REerror = abs(c - cprev) / abs(c);
		relApproxErr.push_back(REerror);
		fc = func(c);
		cout << "n: " << n << " c: " << c << " fc: " << fc << " REerror: " << REerror << endl;
		//Checks whether Relative Approxomate Error is less than toleratable error
		//Originally abs(error) < EBSOL
		if (abs(REerror) < EBSOL)
		{
			cout << "convergence" << endl;
			printToFile(relApproxErr, outputFile);
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

double calcL2Norm(double xi, double yi)
{
	double L2Norm = 0;
	double sum = 0;


	sum += pow(abs(xi - yi), 2);
	L2Norm = sqrt(sum);

	return L2Norm;
}

void printToFile(vector<double> data, string fileName)
{
	fstream outputFile;
	outputFile.open(fileName, ios::out);
	if (outputFile.is_open())
	{
		//outputFile << "line" << " " << "approximate relative percent error" << endl;
		for (int i = 0; i < data.size(); i++)
		{
			outputFile << to_string(i) << " " << to_string(data[i]) << endl;
		}
		outputFile.close();
	}

}