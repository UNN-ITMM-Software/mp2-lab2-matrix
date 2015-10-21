#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <clocale>
#include <conio.h>
using namespace std;
class Vector
{int size;
double *Vec;
public:
	Vector(int n=1);
	~Vector();
	Vector(double *A, int n);
	Vector(const Vector &A);
	Vector operator +(const Vector &A);
	double operator *(const Vector &A);
	double lenvec();
	int operator ==(const Vector &A);
	void printv(void);
	friend ostream& operator<<(ostream& stream, const Vector& vec);
	friend istream& operator>>(istream& stream, Vector& vec);
	Vector& operator =(const Vector &A);
	Vector& operator +=(const Vector &A);
	double& operator [](int ind);
	Vector operator ++();
	Vector operator ++(int);
};
#endif