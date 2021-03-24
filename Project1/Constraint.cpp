#include <vector>
#include <iostream>
#include <cmath>
#include "Constraint.h"


template <typename T>
std::ostream& operator << 
(std::ostream& os, const std::vector<T>
	& vec)
{
	os << '(';
	for (int i = 0; i < vec.size(); i++)
	{
		os << vec[i];
		if (i != vec.size() - 1)
		os << ', ';
	}
	os << ')';
	return os;
}

template <typename T>
std::ostream& operator <<
(std::ostream& os, const std::vector<std::vector<T>>
	& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		os << '(';
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			os << std::ceil(matrix[i][j] * 100.0) / 100.0;
			
			if (j == 0)
			{
				os << ", ";
			}
		}
		os << ')';
		os << std::endl;
	}
	return os;
}

int Constraint::getM() { return m; }
int Constraint::getN() { return n; }
int Constraint::getNumCols() { return numCols; }
std::vector<std::vector<double>> Constraint::getXions() { return xions; }

std::vector<std::vector<double>> Constraint::getXIncps()
{
	return xIncps;
}

std::vector<std::vector<double>> Constraint::getYIncps()
{
	return yIncps;
}


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

void Constraint::xAndYIntercepts()
{
	/*
	Record x and y intercepts.
	*/

	for (int j = 0; j < this->getM(); j++)
	{
		for (int i = 0; i < cCoeff[j].size() - 1; i++)
		{
			if (cCoeff[j][i] != 0)
			{
				if (i == 0)
				{
					if (cCoeff[j][i] > 0)
						xIncps.push_back({ (cCoeff[j].back() / cCoeff[j][i]) , 0 });
				}
				else
				{
					if (cCoeff[j][i] > 0)
						yIncps.push_back({ 0, (cCoeff[j].back() / cCoeff[j][i]) });
				}
			}
		}
	}
}

std::vector<std::vector<double>> Constraint::findIntersections()
{
	/*
	Take each constraint.
	*/
	for (int a = 0; a < this->getM(); a++)
	{

		/*
		Check the given constraint's intersection with the constraints below it.
		*/
		for (int b = a + 1; b < this->getM(); b++)
		{
			// Don't want to examine intersection with itself!
			double determinant = cCoeff[a][0] * cCoeff[b][1] - cCoeff[b][0] * cCoeff[a][1];

			if (determinant == 0)
			{
				// Parallel lines;
				xions.push_back({ DBL_MAX, DBL_MAX });
			}
			else
			{
				double x = (cCoeff[b][1] * cCoeff[a][2] - cCoeff[a][1] * cCoeff[b][2]) / determinant;
				double y = (cCoeff[a][0] * cCoeff[b][2] - cCoeff[b][0] * cCoeff[a][2]) / determinant;

				xions.push_back({ x, y });
			}
		}
	}
	xions.push_back({ 0, 0 });
	return std::vector<std::vector<double>>();
}

std::vector<std::vector<double>> Constraint::idFeasibles()
{
	/*
	First check intercepts for feasibility.

	X first.
	*/

	int satisfies;
	for (int i = 0; i < xIncps.size(); i++)
	{
		satisfies = 0;
		// Check x-ints meets all conditions
		if (xIncps[i][0])
		{
			for (int j = 0; j < cCoeff.size(); j++)
			{
					
				if ((cCoeff[j][0] * xIncps[i][0]) <= cCoeff[j].back())
				{
					satisfies++;
				}
			}

			/*
		Check if given x-intercept satisfies every constraint.
		*/
			if (satisfies == this->getM() + 1)
			{
				cPoints.push_back(xIncps[i]);
			}
		}
	}

	// Test y-ints for feasibility.
	for (int i = 0; i < yIncps.size(); i++)
	{
		satisfies = 0;
		if (yIncps[i][1] > 0)
		{
			for (int j = 0; j < cCoeff.size(); j++)
			{
					if ((cCoeff[j][1] * yIncps[i][1]) <= cCoeff[j].back())
					{
						satisfies++;
					}
			}

			/*
			Check if given y-intercept satisfies every constraint.
			*/
			if (satisfies == this->getM())
			{
				cPoints.push_back(yIncps[i]);
			}
		}
	}

	/*
	Test intersection points for feasibility.
	*/
	for (int i = 0; i < xions.size(); i++)
	{
		satisfies = 0;

		if (xions[i][0] >= 0 && xions[i][1] >= 0)
		{
			for (int j = 0; j < cCoeff.size(); j++)
			{
				if ((cCoeff[j][0] * xions[i][0] + cCoeff[j][1] * xions[i][1]) <= cCoeff[j].back())
				{
					satisfies++;
				}
			}

			if (satisfies == cCoeff.size())
			{
				cPoints.push_back(xions[i]);
			}
		}
	}
	return cPoints;
	std::cout << "cPoints: " << cPoints;
}

void Constraint::findOptimal(std::vector<double> obj)
{
	double opt; // Store optimal.

		if (cPoints.empty())
		{
			std::cout << std::endl << "There is no corner point which satisfies every constraint." << std::endl;
		}
		else
		{
			if (cPoints[0][0] == DBL_MAX || cPoints[0][1] == DBL_MAX)
			{
				std::cout << std::endl << "There are parallel lines and thus infinitely many solutions." << std::endl;
			}
			else
			{
			// Problem in 2 vars.
			if (obj.size() == 2)
			{
				opt = obj[0] * cPoints[0][0] + obj[1] * cPoints[0][1];
				double temp;

				std::cout << '(' << cPoints[0][0] << ", " << cPoints[0][1] << ')' << ": " << opt << std::endl;
				for (int i = 1; i < cPoints.size(); i++)
				{
					temp = obj[0] * cPoints[i][0] + obj[1] * cPoints[i][1];
					std::cout << '(' << cPoints[i][0] << ", " << cPoints[i][1] << ')' << ": " << temp << std::endl;
					if (temp > opt)
					{
						opt = temp;
					}
				}
			}
			else // Problem in 1 var.
			{
				opt = obj[0] * cPoints[0][0];
				double temp;

				std::cout << '(' << cPoints[0][0] << ", " << cPoints[0][1] << ')' << ": " << opt << std::endl;
				for (int i = 1; i < cPoints.size(); i++)
				{
					temp = obj[0] * cPoints[i][0] + obj[1] * cPoints[i][1];
					std::cout << '(' << cPoints[i][0] << ", " << cPoints[i][1] << ')' << ": " << temp << std::endl;
					if (temp > opt)
					{
						opt = temp;
					}
				}
			}

			std::cout << std::endl << "Thus the optimal value of the objective function is " << opt << '.' << std::endl << std::endl;
		}
	}
}


