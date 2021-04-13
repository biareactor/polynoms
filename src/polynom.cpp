#include "polynom.h"

//using namespace std;

void TransformStr(string& s)
{
	int i;

	while ((i = s.find(' ')) != string::npos)
	{
		s.erase(i, 1);
	}

	while ((i = s.find(',')) != string::npos)
	{
		s.replace(i, 1, ".");
	}

	if (s[0] != '-')
		s = '+' + s;

	s = s + '+';
}

unsigned int RetPowX(string& s, int& num, int& end)
{
	int Result = 0;
	int j = num + 1;

	if (j == end)
		return 1;

	if ((s[j] == 'y') || (s[j] == 'z'))
	{
		num = j;
		return 1;
	}

	if (s[j] == '^')
		while ((j < end) && (s[j] != 'y') && (s[j] != 'z'))
			j++;

	string c = s.substr(num + 2, j - num - 2);
	Result = stoi(c);

	num = j;

	return Result;
}

unsigned int RetPowY(string& s, int& num, int& end)
{
	int Result = 0;
	int j = num + 1;

	if (j == end)
		return 1;

	if ((s[j] == 'x') || (s[j] == 'z'))
	{
		num = j;
		return 1;
	}

	if (s[j] == '^')
		while ((j < end) && (s[j] != 'x') && (s[j] != 'z'))
			j++;

	string c = s.substr(num + 2, j - num - 2);
	Result = stoi(c);

	num = j;

	return Result;
}

unsigned int RetPowZ(string& s, int& num, int& end)
{
	int Result = 0;
	int j = num + 1;

	if (j == end)
		return 1;

	if ((s[j] == 'x') || (s[j] == 'y'))
	{
		num = j;
		return 1;
	}

	if (s[j] == '^')
		while ((j < end) && (s[j] != 'x') && (s[j] != 'y'))
			j++;

	string c = s.substr(num + 2, j - num - 2);
	Result = stoi(c);

	num = j;

	return Result;
}

unsigned int GetPowX(unsigned int& d)
{
	unsigned int i = d / 100;
	if (i)
		return i;
	else
		return 0;
}

unsigned int GetPowY(unsigned int& d)
{
	unsigned int i = d / 10 % 10;

	if (i)
		return i;
	else
		return 0;
}

unsigned int GetPowZ(unsigned int& d)
{
	int i = d % 10;

	if (i)
		return i;
	else
		return 0;
}

Polynom::Polynom()
{
}

Polynom::Polynom(const Polynom& polyOut)
{
	Monoms = polyOut.Monoms;
}

Polynom::Polynom(string& s)
{
	CreatePolynom(s);
}

Polynom::~Polynom()
{
}

void Polynom::CreatePolynom(string& s)
{
	string tS = s;
	if (tS.size() == 0)
	{
		Monom newMonom(0, 0);
		Monoms.push_back(newMonom);
		return;
	}

	TransformStr(tS);

	while (tS.size() != 1)
	{
		int st = -1, end = -1, num = -1;
		double mul;
		unsigned int degree;
		unsigned int powx = 0, powy = 0, powz = 0;

		// выделяем моном
		for (int i = 0; i < tS.size(); i++)
			if ((tS[i] == '+') || (tS[i] == '-'))
			{
				st = i;
				break;
			}

		for (int i = st + 1; i < tS.size(); i++)
			if ((tS[i] == '+') || (tS[i] == '-'))
			{
				end = i;
				break;
			}

		// выделяем коэффициент
		for (int i = st; i < end; i++)
			if ((tS[i] == 'x') || (tS[i] == 'y') || (tS[i] == 'z'))
			{
				num = i;
				break;
			}

		if (num == -1)
		{
			string c = tS.substr(st + 1, end - st - 1);
			mul = stod(c);

			if (tS[st] == '-')
				mul = -1 * mul;
		}
		else
			if (num - st == 1)
				mul = 1;
			else
			{
				string c = tS.substr(st + 1, num - st - 1);
				mul = stod(c);
			}

		if (num == -1)
		{
			Monom newMonom(mul, 0);
			Monoms.push_back(newMonom);
			tS.erase(st, end - st);
			continue;
		}

		bool f1 = false, f2 = false;

		// выделяем степени
		if ((tS[num] == 'x') && (num < end) && (!f1))
		{
			powx = RetPowX(tS, num, end);
			f1 = true;

			if ((num < end) && (tS[num] == 'y') && (!f2))
			{
				powy = RetPowY(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'z'))
					powz = RetPowZ(tS, num, end);
			}

			if ((num < end) && (tS[num] == 'z') && (!f2))
			{
				powz = RetPowZ(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'y'))
					powy = RetPowY(tS, num, end);
			}
		}

		if ((tS[num] == 'y') && (num < end) && (!f1))
		{
			powy = RetPowY(tS, num, end);
			f1 = true;

			if ((num < end) && (tS[num] == 'x') && (!f2))
			{
				powx = RetPowX(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'z'))
					powz = RetPowZ(tS, num, end);
			}

			if ((num < end) && (tS[num] == 'z') && (!f2))
			{
				powz = RetPowZ(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'x'))
					powx = RetPowX(tS, num, end);
			}
		}

		if ((tS[num] == 'z') && (num < end) && (!f1))
		{
			powz = RetPowZ(tS, num, end);
			f1 = true;

			if ((num < end) && (tS[num] == 'y') && (!f2))
			{
				powy = RetPowY(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'x'))
					powx = RetPowX(tS, num, end);
			}

			if ((num < end) && (tS[num] == 'x') && (!f2))
			{
				powx = RetPowX(tS, num, end);
				f2 = true;
				if ((num < end) && (tS[num] == 'y'))
					powy = RetPowY(tS, num, end);
			}
		}

		if ((powx >= MAX_POLYNOM_POW) || (powy >= MAX_POLYNOM_POW) || (powz >= MAX_POLYNOM_POW))
			throw 6;

		degree = powx * 100 + powy * 10 + powz;

		if (tS[st] == '-')
			mul = -1 * mul;

		Monom newMonom(mul, degree);
		Monoms.push_back(newMonom);

		// удаляем обработанный моном
		tS.erase(st, end - st);
	}
	Monoms.Sort();
}

string Polynom::CreateString()
{
	string Result;
	unsigned int powX, powY, powZ;
	double mulMonom;

	Node<Monom>* p = Monoms.GetHead();

	if (p != nullptr)
	{
		powX = GetPowX(p->inner.GetDeg());
		powY = GetPowY(p->inner.GetDeg());
		powZ = GetPowZ(p->inner.GetDeg());
		mulMonom = p->inner.GetMul();

		if (mulMonom == -1)
			Result += '-';
		else
			if (mulMonom != 1)
				Result += to_string(mulMonom);

		if (powX)
			if (powX != 1)
				Result = Result + "x^" + to_string(powX);
			else
				Result += 'x';

		if (powY)
			if (powY != 1)
				Result = Result + "y^" + to_string(powY);
			else
				Result += 'y';

		if (powZ)
			if (powZ != 1)
				Result = Result + "z^" + to_string(powZ);
			else
				Result += 'z';

		while (p->pNext != nullptr)
		{
			p = p->pNext;

			powX = GetPowX(p->inner.GetDeg());
			powY = GetPowY(p->inner.GetDeg());
			powZ = GetPowZ(p->inner.GetDeg());
			mulMonom = p->inner.GetMul();

			if (mulMonom == -1)
				Result += '-';

			if (mulMonom > 0)
				Result += '+';

			if (mulMonom != 1)
				Result += to_string(mulMonom);

			if (powX)
				if (powX != 1)
					Result = Result + "x^" + to_string(powX);
				else
					Result += 'x';

			if (powY)
				if (powY != 1)
					Result = Result + "y^" + to_string(powY);
				else
					Result += 'y';

			if (powZ)
				if (powZ != 1)
					Result = Result + "z^" + to_string(powZ);
				else
					Result += 'z';
		}
	}

	return Result;
}

Polynom& Polynom::operator=(const Polynom& polyOut)
{
	if (this != &polyOut)
		Monoms = polyOut.Monoms;

	return *this;
}

bool Polynom::operator==(const Polynom& polyOut) const
{
	return Monoms == polyOut.Monoms;
}

bool Polynom::operator!=(const Polynom& polyOut) const
{
	return Monoms != polyOut.Monoms;
}

Polynom& Polynom::operator+=(Polynom& polyOut)
{
	Polynom Result(polyOut);

	Node<Monom>* p = Monoms.GetHead();
	Node<Monom>* pp;

	if (p != nullptr)
	{
		if ((p->pNext == nullptr) && (p->inner.GetMul() == 0))
		{
			*this = Result;
			return *this;
		}

		if (*this == polyOut * (-1))
		{
			polyOut* (-1);
			string tmps = "";
			Polynom tmp(tmps);
			*this = tmp;
			return *this;
		}

		polyOut* (-1);

		pp = Result.FindDeg(p->inner.GetDeg());

		if (pp != nullptr)
			pp->inner += p->inner;
		else
			Result.Monoms.push_back(p->inner);

		while (p->pNext != nullptr)
		{
			p = p->pNext;
			pp = Result.FindDeg(p->inner.GetDeg());

			if (pp != nullptr)
				pp->inner += p->inner;
			else
				Result.Monoms.push_back(p->inner);
		}

		Result.ClearZero();
		Result.Monoms.Sort();

		*this = Result;

		return *this;
	}
	else throw exception("smth goes wrong");
}

Polynom Polynom::operator+(const Polynom& polyOut)
{
	Polynom Result(polyOut);
	Result += *this;

	return Result;
}

Polynom& Polynom::operator*(const double& scal)
{
	Node<Monom>* p = Monoms.GetHead();

	if (scal == 0)
	{
		string s = "";
		Polynom Result(s);
		*this = Result;
		return *this;
	}

	if (p != nullptr)
	{
		p->inner.ScalMul(scal);

		while (p->pNext != nullptr)
		{
			p = p->pNext;
			p->inner.ScalMul(scal);
		}
	}

	return *this;
}

Polynom& Polynom::operator*=(Polynom& polyOut)
{
	Polynom Result;

	Result = (*this) * polyOut;
	(*this) = Result;

	return *this;
}

Polynom Polynom::operator*(Polynom& polyOut)
{
	Node<Monom>* p = Monoms.GetHead();
	Node<Monom>* pp = polyOut.Monoms.GetHead();

	unsigned int NewDeg;
	unsigned int x1, y1, z1;
	unsigned int x2, y2, z2;
	double NewC;
	Polynom Result;

	if ((p != nullptr) && (pp != nullptr))
	{
		if ((p->pNext == nullptr) && (p->inner.GetMul() == 0))
		{
			Result.Monoms.push_back(p->inner);
			return Result;
		}

		if ((pp->pNext == nullptr) && (pp->inner.GetMul() == 0))
		{
			Result.Monoms.push_back(pp->inner);
			return Result;
		}

		x1 = GetPowX(p->inner.GetDeg());
		y1 = GetPowY(p->inner.GetDeg());
		z1 = GetPowZ(p->inner.GetDeg());

		x2 = GetPowX(pp->inner.GetDeg());
		y2 = GetPowY(pp->inner.GetDeg());
		z2 = GetPowZ(pp->inner.GetDeg());

		if (((x1 + x2) < MAX_POLYNOM_POW) && ((y1 + y2) < MAX_POLYNOM_POW) && ((z1 + z2) < MAX_POLYNOM_POW))
		{
			NewC = (p->inner.GetMul()) * (pp->inner.GetMul());
			NewDeg = (p->inner.GetDeg()) + (pp->inner.GetDeg());
			Node<Monom>* tmp = Result.FindDeg(NewDeg);
			Monom newMonom(NewC, NewDeg);
			if (tmp != nullptr)
				tmp->inner += newMonom;
			else
				Result.Monoms.push_back(newMonom);
		}
		else
			throw 6;

		while (pp->pNext != nullptr)
		{
			pp = pp->pNext;

			x2 = GetPowX(pp->inner.GetDeg());
			y2 = GetPowY(pp->inner.GetDeg());
			z2 = GetPowZ(pp->inner.GetDeg());

			if (((x1 + x2) < 10) && ((y1 + y2) < 10) && ((z1 + z2) < 10))
			{
				NewC = (p->inner.GetMul()) * (pp->inner.GetMul());
				NewDeg = (p->inner.GetDeg()) + (pp->inner.GetDeg());
				Node<Monom>* tmp = Result.FindDeg(NewDeg);
				Monom newMonom(NewC, NewDeg);
				if (tmp != nullptr)
					tmp->inner += newMonom;
				else
					Result.Monoms.push_back(newMonom);
			}
			else
				throw 6;
		}

		pp = polyOut.Monoms.GetHead();

		while (p->pNext != nullptr)
		{
			p = p->pNext;

			x1 = GetPowX(p->inner.GetDeg());
			y1 = GetPowY(p->inner.GetDeg());
			z1 = GetPowZ(p->inner.GetDeg());

			x2 = GetPowX(pp->inner.GetDeg());
			y2 = GetPowY(pp->inner.GetDeg());
			z2 = GetPowZ(pp->inner.GetDeg());

			if (((x1 + x2) < 10) && ((y1 + y2) < 10) && ((z1 + z2) < 10))
			{
				NewC = (p->inner.GetMul()) * (pp->inner.GetMul());
				NewDeg = (p->inner.GetDeg()) + (pp->inner.GetDeg());
				Node<Monom>* tmp = Result.FindDeg(NewDeg);
				Monom newMonom(NewC, NewDeg);
				if (tmp != nullptr)
					tmp->inner += newMonom;
				else
					Result.Monoms.push_back(newMonom);
			}
			else
				throw 6;

			while (pp->pNext != nullptr)
			{
				pp = pp->pNext;

				x2 = GetPowX(pp->inner.GetDeg());
				y2 = GetPowY(pp->inner.GetDeg());
				z2 = GetPowZ(pp->inner.GetDeg());

				if (((x1 + x2) < 10) && ((y1 + y2) < 10) && ((z1 + z2) < 10))
				{
					NewC = (p->inner.GetMul()) * (pp->inner.GetMul());
					NewDeg = (p->inner.GetDeg()) + (pp->inner.GetDeg());
					Node<Monom>* tmp = Result.FindDeg(NewDeg);
					Monom newMonom(NewC, NewDeg);
					if (tmp != nullptr)
						tmp->inner += newMonom;
					else
						Result.Monoms.push_back(newMonom);
				}
				else
					throw 6;
			}

			pp = polyOut.Monoms.GetHead();
		}
	}

	Result.Monoms.Sort();

	return Result;
}

double Polynom::ValuePoint(const double& x, const double& y, const double& z)
{
	double Result = 0;
	double tmp = 0;
	int powX, powY, powZ;

	Node<Monom>* p = Monoms.GetHead();

	if (p != nullptr)
	{
		tmp = p->inner.GetMul();
		powX = GetPowX(p->inner.GetDeg());
		powY = GetPowY(p->inner.GetDeg());
		powZ = GetPowZ(p->inner.GetDeg());

		if (powX)
			tmp = tmp * pow(x, powX);
		if (powY)
			tmp = tmp * pow(y, powY);
		if (powZ)
			tmp = tmp * pow(z, powZ);

		Result += tmp;

		while (p->pNext != nullptr)
		{
			p = p->pNext;

			tmp = p->inner.GetMul();
			powX = GetPowX(p->inner.GetDeg());
			powY = GetPowY(p->inner.GetDeg());
			powZ = GetPowZ(p->inner.GetDeg());

			if (powX)
				tmp = tmp * pow(x, powX);
			if (powY)
				tmp = tmp * pow(y, powY);
			if (powZ)
				tmp = tmp * pow(z, powZ);

			Result += tmp;
		}
	}

	return Result;
}

Polynom& Polynom::IntegrateDX()
{
	Node<Monom>* p = Monoms.GetHead();
	unsigned int newpowX;
	double newMul;

	if (p != nullptr)
	{
		newpowX = GetPowX(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowX;
		if (newpowX > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegX();
	}

	while (p->pNext != nullptr)
	{
		p = p->pNext;
		newpowX = GetPowX(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowX;
		if (newpowX > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegX();
	}

	return *this;
}

Polynom& Polynom::IntegrateDY()
{
	Node<Monom>* p = Monoms.GetHead();
	unsigned int newpowY;
	double newMul;

	if (p != nullptr)
	{
		newpowY = GetPowY(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowY;
		if (newpowY > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegY();
	}

	while (p->pNext != nullptr)
	{
		p = p->pNext;
		newpowY = GetPowY(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowY;
		if (newpowY > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegY();
	}

	return *this;
}

Polynom& Polynom::IntegrateDZ()
{
	Node<Monom>* p = Monoms.GetHead();
	unsigned int newpowZ;
	double newMul;

	if (p != nullptr)
	{
		newpowZ = GetPowZ(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowZ;
		if (newpowZ > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegZ();
	}

	while (p->pNext != nullptr)
	{
		p = p->pNext;
		newpowZ = GetPowZ(p->inner.GetDeg()) + 1;
		newMul = 1.0 / newpowZ;
		if (newpowZ > (MAX_POLYNOM_POW - 1)) throw 8;
		p->inner.ScalMul(newMul);
		p->inner.GrowDegZ();
	}

	return *this;
}

void Polynom::ClearZero()
{
	Node<Monom>* p = Monoms.GetHead();

	while (p->pNext != nullptr)
	{
		p = p->pNext;
		if (p->inner.GetMul() == 0)
			p = Monoms.DelELem(p);
	}

	p = Monoms.GetHead();

	if (p->inner.GetMul() == 0)
		p = Monoms.DelELem(p);

	p = Monoms.GetHead();
	int NewAmount = 1;

	while (p->pNext != nullptr)
	{
		p = p->pNext;
		NewAmount++;
	}

	Monoms.SetAmount(NewAmount);
}

Node<Monom>* Polynom::FindDeg(const unsigned int& degOut)
{
	if (degOut > MAX_DEG)
		throw std::exception("Wrong deg");

	Node<Monom>* p = Monoms.GetHead();

	if (p != nullptr)
	{
		if (p->inner.GetDeg() == degOut) return p;

		while (p->pNext != nullptr)
		{
			p = p->pNext;
			if (p->inner.GetDeg() == degOut) return p;
		}
	}
	return nullptr;
}

istream& operator>>(istream& in, Polynom& polyOut)
{
	string In;
	getline(cin, In);

	polyOut.CreatePolynom(In);

	return in;
}

ostream& operator<<(ostream& out, Polynom& polyOut)
{
	string Out = polyOut.CreateString();
	cout << Out << endl;

	return out;
}