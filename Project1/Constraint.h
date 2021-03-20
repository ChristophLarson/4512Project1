#pragma once

#include <vector>
#include <iostream>

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<std::vector<T>>& matrix);

class Constraint
{
private:

	int m; // Number of constraints.
	int n; // Number of variables.
	int numCols; // Includes slacks and z col.

	/*
	2D vector representing the coefficients of n variables in m
	equations plus the constant value on the RHS. This is the user-given
	description of the LP constraints.
	*/
	std::vector<std::vector<double>> cCoeff;

	/*
	2D vector of double pairs storing intersection points once they are determined.
	*/
	std::vector<double[2]> xions;
	

public:

	int getM();

	int getN();

	int getNumCols();

	std::vector<double[2]> getXions();

	void setVal(int i, int j, double n);

	std::vector<std::vector<double>> getCoeff();

	double at(int i, int j); // Element of the constraint matrix
	std::vector<double> at(int i); // Row of the constraint matrix

	Constraint(int m, int n, std::vector<std::vector<double>> coefficients);

	void printConstraint();

	std::vector<double> xIntercepts();

	std::vector<double> yIntercepts();

	std::vector<std::vector<double>> intersections();

	double findOptimal();
};

