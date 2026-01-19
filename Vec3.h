#ifndef VEC_3_H
#define VEC_3_H

#include <cmath>
#include <iostream>

class Vec3
{
public:
	Vec3() : data{ 0.0, 0.0, 0.0 } {};
	Vec3(double i1, double i2, double i3) : data{ i1, i2, i3} {};

	Vec3 operator - ()
	{
		return Vec3(-data[0], -data[1], -data[2]);
	}

	double operator[] (int in_index)
	{
		return data[in_index];
	}

	Vec3& operator += (const Vec3& other)
	{
		data[0] += other.data[0];
		data[1] += other.data[1];
		data[2] += other.data[2];

		return *this;
	}

	Vec3& operator *= (double number)
	{
		data[0] *= number;
		data[1] *= number;
		data[2] *= number;

		return *this;
	}

	Vec3& operator /= (double number)
	{
		return *this *= (1/number);
	}

	Vec3 operator + (const Vec3& other)
	{
		return Vec3({ data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2] });
	}

	Vec3 operator - (const Vec3& other)
	{
		auto& o_data = other.data;

		return Vec3({ data[0] - o_data[0], data[1] - o_data[1], data[2] - o_data[2] });
	}

	double dot(const Vec3& other)
	{
		auto& o_data = other.data;
		return (data[0] * o_data[0] +
				data[1] * o_data[1] +
				data[2] * o_data[2]);
	}

	Vec3 cross(const Vec3% other)
	{
		auto& o_data = other.data;
		return Vec3({ data[1] * o_data[2] - data[2] * o_data[1]  ,
					-(data[0] * o_data[2] - data[2] * o_data[0] ),
					  data[0] * o_data[1] - data[1] * o_data[0] });
	}

	double length()
	{
		return std::sqrt(vec[0]* vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	Vec3 unit()
	{
		return *this / length();
	}
private:
	double data[3];
};

std::ostream& operator<<(ostream& os, const Vec3& vec)
{
	os << "[ " << vec[0] << ", " << vec[1] << ", " << vec[2] << " ]";
	return os;
}

#endif