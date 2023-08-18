#include "VMD.h"
#include <fstream>
#include <iostream>
using namespace Eigen;
using namespace std;
/*
<VMD_CPP: C++ implementation of Variational Mode Decomposition using Eigen.>
Copyright (C) <2019>  <Lang He: asdsay@gmail.com>
Mozilla Public License v. 2.0.
*/

int main() {

	// load the time series
	int sigLen = 0;
	vectord signal;

	ifstream fin;
	fin.open("Data/Sutong_4_1.txt",ios::in);
	if(!fin.is_open())
	{
		cerr << "file open failed" << endl;
		return -1;
	}
	double tmp = 0.0;
	while(!fin.eof())
	{
		++sigLen;
		fin >> tmp;
		signal.push_back(tmp);
	}
	cout << "data length: " << sigLen << endl;
	getchar();

	// initialize some input parameters
	const double alpha = 1500.0, tau = 0, tol = 1e-7, eps = 2.2204e-16;
	const int K = 7, DC = 0, init = 1;
	const static double CSVFormat(4);

	// Example 1: If you want to get the full results as a 2D matrix of VMD. 	
	MatrixXd u, omega;
	MatrixXcd u_hat;
	VMD(u, u_hat, omega, signal, alpha, tau, K, DC, init, tol, eps);


	// output example 
	cout << "Decomposition results" << endl;
	for (int i = 0; i < u.rows(); i++) {
		for (int j = 0; j < u.cols(); j++)
			cout << u(i, j) << ' ';
		cout << endl << endl;
	}
	string name = "Data/TestResult.txt";
	ofstream file1(name.c_str());
	
	for (int i = 0; i < u.rows(); i++) {
		for (int j = 0; j < u.cols(); j++)
			file1 << u(i,j) << " ";
		file1 << endl;
	}

	file1.close();
	
	return 0;
}; 