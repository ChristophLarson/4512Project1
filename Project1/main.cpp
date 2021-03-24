#include <iostream>
#include <cstdio>
#include <vector>
#include "Constraint.h"


void printResults(Constraint c, std::vector<double> obj)
{
    c.findIntersections();
    c.xAndYIntercepts();

    std::cout << std::endl << "Intercepts: " << std::endl << c.getYIncps() << c.getXIncps() << std::endl;

    if (obj.size() == 1)
    {
        std::cout << "There is only one constraint. The LP is therefore unbounded." << std::endl;
        return;
    }

    std::cout << "Intersections" << std::endl << c.getXions() << std::endl;

    std::cout << "Subset of feasible points: " << std::endl << c.idFeasibles() << std::endl;

    std::cout << "Value of objective at each corner point: " << std::endl;
    c.findOptimal(obj);
}

int main()
{
    // Problem 1

    printf("--------------------PROBLEM 1-------------------- \n");
    std::vector<std::vector<double>> constraints1
    {
        {6, 4, 24},
        {1, 2, 6},
        {-1, 1, 1},
        {0, 1, 2}
    };

    std::vector<double> obj1 = { 5, 4 };

    Constraint c1(4, 2, constraints1);

    printResults(c1, obj1);
    // Problem 2
    printf("--------------------PROBLEM 2-------------------- \n");
    std::vector<std::vector<double>> constraints2
    {
        {6, 4, 24},
        {1, 2, 6},
        {-1, 1, 1},
        {0, 1, 2}
    };

    std::vector<double> obj2 = { 5, 10 };

    Constraint c2(4, 2, constraints2);

    printResults(c2, obj2);


    // Problem 3
    printf("--------------------PROBLEM 3-------------------- \n");
    std::vector<std::vector<double>> constraints3
    {
        {6, 4, 24},
        {1, 2, 6},
        {-1, 1, 1},
        {-1, 0, -5},
        {0, 1, 2}

    };

    std::vector<double> obj3 = { 5, 4 };

    Constraint c3(5, 2, constraints3);

    printResults(c3, obj3);

    // Problem 4
    printf("--------------------PROBLEM 4-------------------- \n");
    std::vector<std::vector<double>> constraints4
    {
        {3, 2, 12},
        {2, 4, 12},
        {-1, 1, 1},
        {0, 2, 4}
    };

    std::vector<double> obj4 = { 10, 8 };

    Constraint c4(4, 2, constraints4);

    printResults(c4, obj4);


    // Problem 5
    printf("--------------------PROBLEM 5-------------------- \n");
    std::vector<std::vector<double>> constraints5
    {
        {-5, 0, -20},
        {-2, 0, -30},
        {-1, 0, -6},
        {-3, 0, -24}
    };

    std::vector<double> obj5 = { 3 };

    Constraint c5(4, 1, constraints5);

    printResults(c5, obj5);
   

    // Problem 6
    printf("--------------------PROBLEM 6-------------------- \n");
    std::vector<std::vector<double>> constraints6
    {
        {1, 5, 20},
        {-1, 0, -2}
    };

    std::vector<double> obj6 = { 3, 2 };

    Constraint c6(2, 2, constraints6);

    printResults(c6, obj6);

    // Problem 7
    printf("--------------------PROBLEM 7-------------------- \n");
    std::vector<std::vector<double>> constraints7
    {
        {5, 0, 20}
    };

    std::vector<double> obj7 = { 3 };

    Constraint c7(1, 1, constraints7);

    printResults(c7, obj7);

    std::cout << "Done!";
    //std::getchar();
}
