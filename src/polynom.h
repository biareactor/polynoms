//#pragma once

#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "list.h"
#include <string>
#include "list.cpp"

using namespace std;

const int MAX_POLYNOM_POW = 10;
const int MAX_DEG = 999;

class Monom
{
	double mul;
	unsigned int deg;
public:
	Monom() : mul(0), deg(0)
	{
	}

	Monom(const double& outMul, const unsigned int& outDeg) : mul(outMul), deg(outDeg)
	{
	}

	~Monom()
	{
		mul = 0;
		deg = 0;
	}

	double& GetMul() { return mul; }
	unsigned int& GetDeg() { return deg; }
	void ScalMul(const double& scal) { mul = scal * mul; }
	void GrowDegX() 
	{ 
		if (((deg + 100) / 100) < 10)
			deg = deg + 100; 
	}

	void GrowDegY() 
	{ 
		if ((((deg + 10) / 10) % 10) < 10)
			deg = deg + 10; 
	}

	void GrowDegZ() 
	{ 
		if (((deg + 1) % 10) < 10)
			deg = deg + 1;
	}

	Monom& operator=(const Monom& monomOut)
	{
		mul = monomOut.mul;
		deg = monomOut.deg;

		return *this;
	}

	Monom& operator+=(Monom& monomOut)
	{
		if (deg != monomOut.deg) throw 7;
		mul += monomOut.mul;
		return *this;
	}

	bool operator==(const Monom& monomOut) const
	{
		if ((mul == monomOut.mul) && (deg == monomOut.deg)) return true;
		else return false;
	}

	bool operator!=(const Monom& monomOut) const
	{
		return !(*this == monomOut);
	}

	bool operator<(const Monom& monomOut) const
	{
		if (deg < monomOut.deg) return true;
		else return false;
	}
};

class Polynom
{
	List<Monom> Monoms;
public:
	Polynom();
	Polynom(string& s);
	Polynom(const Polynom& polyOut);
	~Polynom();

	void CreatePolynom(string& s);
	string CreateString();

	Polynom& operator+=(Polynom& polyOut);
	Polynom operator+(const Polynom& polyOut);
	Polynom& operator*(const double& scal);
	Polynom& operator*=(Polynom& polyOut);
	Polynom operator*(Polynom& polyOut);
	double ValuePoint(const double& x, const double& y, const double& z);
	Polynom& IntegrateDX();
	Polynom& IntegrateDY();
	Polynom& IntegrateDZ();

	Polynom& operator=(const Polynom& polyOut);
	bool operator==(const Polynom& polyOut) const;
	bool operator!=(const Polynom& polyOut) const;

	void ClearZero();
	Node<Monom>* FindDeg(const unsigned int& degOut);

	friend istream& operator>>(istream& in, Polynom& polyOut);
	friend ostream& operator<<(ostream& out, Polynom& polyOut);
};

#endif