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

	double length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	double length_squared() const
	{
		return x * x + y * y + z * z;
	}

	bool near_zero()
	{
		double s = 1e-160;

		if ((std::fabs(x) <= s) && (std::fabs(y) <= s) && (std::fabs(z) <= s))
			return true;

		return false;
	}

	static Vec3 random()
	{
		return Vec3(random_double(), random_double(), random_double());
	}

	static Vec3 random(double in_min, double in_max)
	{
		return Vec3(random_double(in_min, in_max), random_double(in_min, in_max), random_double(in_min, in_max));
	}
};

inline Vec3 unit(const Vec3& vec)
{
	return vec * (1/vec.length());
}

inline Vec3 random_unit_vector()
{
	while (true)
	{
		auto v = Vec3::random(-1.0, 1.0);
		auto lensq = v.length_squared(); // See if vector fits inside r = 1.0 circle

		if (1e-160 < lensq && lensq <= 1)
			return v/std::sqrt(lensq);
	}
}


inline double dot(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x +
			a.y * b.y +
			a.z * b.z);
}

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	return Vec3({ a.y * b.z - a.z * b.y  ,
				-(a.x * b.z - a.z * b.x) ,
				  a.x * b.y - a.y * b.x });
}

inline std::ostream& operator << (std::ostream& os, const Vec3& vec)
{
	os << "[ " << vec.x << ", " << vec.y << ", " << vec.z << " ]";
	return os;
}

inline Vec3 operator*(double t, const Vec3& v)
{
	return v * t;
}

inline Vec3 random_on_hemisphere(Vec3& in_normal)
{
	auto random_vector = random_unit_vector();

	if (dot(random_vector, in_normal) > 0.0)
		return random_vector;
	else
		return -1*random_vector;
}

using Point3 = Vec3;

#endif