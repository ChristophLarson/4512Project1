#include <vector>
#include <iostream>
#include "Constraint.h"

template <typename T>
std::ostream& operator <<
(std::ostream& os, const std::vector<std::vector<T>>
	& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			os << matrix[i][j] << ", ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}

int Constraint::getM() { return m; }
int Constraint::getN() { return n; }
int Constraint::getNumCols() { return numCols; }
std::vector<double[2]> Constraint::getXions() { return xions; }


void Constraint::setVal(int i, int j, double n)
{
	cCoeff.at(i).at(j) = n;

	//return cCoeff.at(i).at(j);
}
std::vector<std::vector<double>> Constraint::getCoeff() { return cCoeff; }

double Constraint::at(int i, int j)
{
	return cCoeff.at(i).at(j);
}

std::vector<double> Constraint::at(int i)
{
	return cCoeff.at(i);
}


Constraint::Constraint(int m, int n, std::vector<std::vector<double>> coefficients)
{
	this->m = m;
	this->n = n;
	this->numCols = n + 1;

	cCoeff = coefficients;
}

void Constraint::printConstraint()
{
	std::cout << cCoeff;
}

std::vector<double> Constraint::xIntercepts()
{
	return std::vector<double>();
}

std::vector<double> Constraint::yIntercepts()
{
	return std::vector<double>();
}

std::vector<std::vector<double>> Constraint::intersections()
{
	/*
	Take each constraint and find its intersection with every other constraint.
	*/
	for (int a = 0; a < this->getM(); a++)
	{

		/*TODO:
		Record x and y intercepts. Figure out which are corner points.
		*/
		for (int b = 0; b < this->getM(); b++)
		{
			// Don't want to examine intersection with itself!
			if (a != b)
			{
				double determinant = cCoeff[a][0] * cCoeff[b][1] - cCoeff[b][0] * cCoeff[a][1];

				if (determinant == 0)
				{
					// Parallel lines
					double xion[] = { DBL_MAX, DBL_MAX };
					xions.push_back(xion);
				}
				else
				{
					double x = (cCoeff[b][1]*cCoeff[a][2] - cCoeff[a][1]*cCoeff[b][2]) / determinant;
					double y = (cCoeff[a][0]*cCoeff[b][2] - cCoeff[b][0]*cCoeff[a][2]) / determinant;

					double xion[] = { x, y };
					xions.push_back(xion);
				}
			}
		}
	}
	return std::vector<std::vector<double>>();
}

double Constraint::findOptimal()
{
	return 0.0;
}


