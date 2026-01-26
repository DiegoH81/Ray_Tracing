#ifndef VEC_3_H
#define VEC_3_H

#include <cmath>
#include <iostream>

class Vec3
{
public:
	double x, y, z;
	Vec3() : x(0.0), y(0.0), z(0.0) {}
	Vec3(const double &in_x, const double &in_y, const double &in_z) :
		x(in_x), y(in_y), z(in_z) {};

	Vec3 operator - ()
	{
		return Vec3(-x, -y, -z);
	}

	double operator[] (int in_index)
	{
		switch (in_index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			std::clog << "Out of bounds!\n";
			return -1.0;
		}
	}

	Vec3& operator += (const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3& operator *= (double number)
	{
		x *= number;
		y *= number;
		z *= number;

		return *this;
	}

	Vec3& operator /= (double number)
	{
		return *this *= (1/number);
	}

	Vec3 operator + (const Vec3& other) const
	{
		return Vec3({ x + other.x, y + other.y, z + other.z });
	}

	Vec3 operator - (const Vec3& other) const
	{
		return Vec3({ x - other.x, y - other.y, z - other.z });
	}

	Vec3 operator * (double number) const
	{
		return Vec3(x * number, y * number, z * number);
	}

	Vec3 operator / (double number) const
	{
		return *this * (1 / number);
	}

	double dot(const Vec3& other) const
	{
		return (x * other.x +
				y * other.y +
				z * other.z );
	}

	Vec3 cross(const Vec3& other) const
	{
		return Vec3({ y * other.z - z * other.y  ,
					-(x * other.z - z * other.x) ,
					  x * other.y - y * other.x });
	}

	double length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}
};

inline Vec3 unit(const Vec3& vec)
{
	return vec * (1/vec.length());
}

std::ostream& operator << (std::ostream& os, const Vec3& vec)
{
	os << "[ " << vec.x << ", " << vec.y << ", " << vec.z << " ]";
	return os;
}

using Point3 = Vec3;

#endif