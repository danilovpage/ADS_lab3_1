#pragma once
#include <iostream>
#include <complex>
#include <math.h>
#include <exception>
#include <string>
#include <vector>

struct IntPoint2
{
	int x;
	int y;
	IntPoint2() :x(0), y(0) {}
	IntPoint2(int x, int y) :x(x), y(y) {}

	bool operator == (const IntPoint2& Point) const
	{
		if ((x == Point.x) && (y == Point.y))
			return true;
		else return false;
	}

	float Distance(const IntPoint2& Point) const
	{
		return static_cast<float>(sqrt(pow(x - Point.x, 2) + pow(y - Point.y, 2)));
	}
};

std::ostream& operator<< (std::ostream& out, const IntPoint2& Point);
std::istream& operator>>(std::istream& in, IntPoint2& Point);


struct DoublePoint3
{
	double x;
	double y;
	double z;
	DoublePoint3() :x(0), y(0), z(0) {}
	DoublePoint3(double x, double y, double z) :x(x), y(y), z(z) {}

	double Distance(const DoublePoint3& Point) const
	{
		return sqrt(pow(x - Point.x, 2) + pow(y - Point.y, 2) + pow(z - Point.z, 2));
	}


	bool operator == (const DoublePoint3& Point) const
	{
		if ((x == Point.x) && (y == Point.y) && (z == Point.z))
			return true;
		else return false;
	}
};
std::ostream& operator << (std::ostream& out, const DoublePoint3& Point);
std::istream& operator>>(std::istream& in, DoublePoint3& Point);


std::ostream& operator<< (std::ostream& out, const std::complex<double>& Point);
std::istream& operator>>(std::istream& in, std::complex<double>& Point);


template <class T>
class Polyline
{
private:
	std::vector<T> Dots;
public:
	const T& begin() const
	{
		return Dots.begin();
	}

	const T& end() const
	{
		return Dots.end();
	}

	Polyline();
	Polyline(int N);
	int get_vertex() const;
	T& operator [] (const int Index);
	T operator[](const int Index) const;
	Polyline operator + (const Polyline& Line);
	bool operator == (Polyline& other) const;
	bool operator!=(const Polyline<T>& other) const;
	Polyline& operator > (T NewPoint);
	Polyline& operator < (T NewPoint);
	double Distance() const;
	friend std::ostream& operator << (std::ostream& out, const Polyline<T>& Point)
	{
		for (T i : Point.Dots)
		{
			out << i;
		}
		out << '\n';
		return out;
	}
};

template <class T>
std::istream& operator >>(std::istream& in, Polyline<T>& Point);

std::ostream& operator << (std::ostream& out, const IntPoint2& Point)
{
	out << "[" << Point.x << ";" << Point.y << "]";
	return out;
}

std::istream& operator>>(std::istream& in, IntPoint2& Point)
{
	char data[32] = { 0 };
	char* pointer = data;
	in.getline(pointer, 32);
	pointer = pointer + 1;
	char* tmp = strchr(pointer, ';');
	size_t len_data = (tmp - pointer) / sizeof(char);
	char data_x[32] = { 0 };
	for (size_t j = 0; j < len_data; j++)
	{
		data_x[j] = pointer[j];
	}
	Point.x = atoi(data_x);

	pointer = tmp + 1;

	tmp = strchr(pointer, ')');
	len_data = (tmp - pointer) / sizeof(char);
	char data_y[32] = { 0 };
	for (size_t j = 0; j < len_data; j++)
	{
		data_y[j] = pointer[j];
	}
	Point.y = atoi(data_y);
	return in;
}

std::istream& operator>>(std::istream& in, DoublePoint3& Point)
{
	char data[64] = { 0 };
	char* pointer = data;
	in.getline(pointer, 64);
	pointer = pointer + 1;
	char* tmp = strchr(pointer, ';');
	size_t len_data = (tmp - pointer) / sizeof(char);
	char data_x[32] = { 0 };
	for (size_t i = 0; i < len_data; i++)
	{
		data_x[i] = pointer[i];
	}
	Point.x = atof(data_x);

	pointer = tmp + 1;

	tmp = strchr(pointer, ';');
	len_data = (tmp - pointer) / sizeof(char);
	char data_y[32] = { 0 };
	for (size_t j = 0; j < len_data; j++)
	{
		data_y[j] = pointer[j];
	}
	Point.y = atof(data_y);

	pointer = tmp + 1;

	tmp = strchr(pointer, ')');
	len_data = (tmp - pointer) / sizeof(char);
	char data_z[32] = { 0 };
	for (size_t k = 0; k < len_data; k++)
	{
		data_z[k] = pointer[k];
	}
	Point.z = atof(data_z);
	return in;
}

std::ostream& operator<<(std::ostream& out, const DoublePoint3& Point)
{
	out << "[" << Point.x << ";" << Point.y << ";" << Point.z << "]";
	return out;
}

std::istream& operator>>(std::istream& in, std::complex<double>& Point)
{
	double _re = 0;
	double _im = 0;
	char data[32] = { 0 };
	char* pointer = data;
	in.getline(pointer, 32);
	pointer = pointer + 1;
	char* tmp = strchr(pointer, ';');
	size_t len_data = (tmp - pointer) / sizeof(char);
	char data_real[32] = { 0 };
	for (size_t j = 0; j < len_data; j++)
	{
		data_real[j] = pointer[j];
	}
	_re = std::stod(data_real);
	pointer = tmp + 1;

	tmp = strchr(pointer, ')');
	len_data = (tmp - pointer) / sizeof(char);
	char data_image[32] = { 0 };
	for (size_t j = 0; j < len_data; j++)
	{
		data_image[j] = pointer[j];
	}
	_im = std::stod(data_image);

	std::complex<double> temp(_re, _im);
	Point = temp;
	return in;
}

std::ostream& operator<<(std::ostream& out, const std::complex<double>& Point)//vertex output
{
	out << "[" << Point.real() << ";" << Point.imag() << "*i" << "]";
	return out;
}

template <class T>
Polyline<T>::Polyline() {}

template <class T>
Polyline<T>::Polyline(int N)
{
	Dots.resize(N);
}

template <class T>
int Polyline<T>::get_vertex() const
{
	return Dots.size();
}

template <class T>
T& Polyline<T>::operator [] (int Index)
{
	if (Dots.empty())
		throw "Polyline empty!";
	if (Index < 0 || Index > Dots.size())
		throw std::logic_error("out_of_bounds");
	else
		return Dots[Index];
}

template <class T>
T Polyline<T>::operator[](int Index) const
{
	if (Dots.empty())
		throw "Polyline empty!";
	if (Index < 0 || Index > Dots.size())
		throw std::logic_error("out_of_bounds");
	else
		return Dots[Index];
}

template <class T>
Polyline<T>& Polyline<T>::operator>(T NewPoint) // add end
{
	Dots.push_back(NewPoint);
	return *this;
}


template <class T>
Polyline<T>& Polyline<T>::operator <(T NewPoint) // add begin
{
	Dots.insert(Dots.begin(), NewPoint);
	return *this;
}

template <class T>
Polyline<T> Polyline<T>::operator + (const Polyline<T>& Line)
{
	Polyline res;
	res.Dots.insert(res.Dots.end(), Dots.begin(), Dots.end());
	res.Dots.insert(res.Dots.end(), Line.Dots.begin(), Line.Dots.end());
	return res;
}


template <class T>
bool Polyline<T>::operator==(Polyline<T>& other) const
{
	if (Dots.size() != other.Dots.size()) return false;
	for (int i = 0; i < get_vertex(); i++)
	{
		if (!(Dots[i] == other.Dots[i])) return false;
	}
	return true;
}


template <class T>
bool Polyline<T>::operator!=(const Polyline<T>& other) const
{
	if (Dots.size() != other.Dots.size()) return true;
	for (int i = 0; i < other.get_vertex(); i++)
	{
		if (!(Dots[i] == other.Dots[i])) return true;
	}
	return false;
}

template <class T>
double Polyline<T>::Distance() const
{
	double len = Dots[0].Distance(Dots[1]);
	for (int i = 1; i < get_vertex() - 1; i++)
	{
		len += Dots[i].Distance(Dots[i + 1]);
	}
	return len;
}

double Polyline < std::complex<double>>::Distance() const
{
	double len = 0;
	for (size_t i = 0; i < get_vertex() - 1; i++)
	{
		len += abs(Dots[i + 1] - Dots[i]);
	}
	return len;
}

template <class T>
std::istream& operator>>(std::istream& in, Polyline<T>& Point)
{
	int n;
	in >> n;
	in.get();
	Polyline<T> _p(n);
	for (size_t i = 0; i < n; i++)
	{
		T v;
		in >> v;
		_p[i] = v;
	}
	Point = _p;
	return in;
}