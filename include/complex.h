#pragma once
#include <iostream>
#include <exception>
#include <math.h>

class Complex
{
public:
	float r;
	float j;

	Complex(float r = 0.0f, float j = 0.0f)
	{
		this->r = r;
		this->j = j;
	}

	Complex operator+(Complex& other)
	{
		Complex result(r + other.r, j + other.j);
		return result;
	}

	Complex operator-(Complex& other)
	{
		Complex result(r - other.r, j - other.j);
		return result;
	}

	Complex operator*(Complex& other)
	{
		Complex result(
			r * other.r - j * other.j,
			r * other.j + j * other.r
		);
		return result;
	}

	Complex operator/(Complex& other)
	{
		if (other.j < EPS || other.r < EPS)
		{
			throw std::runtime_error("Zero division\n");
		}
		Complex result(
			r * (1.0f / other.r) - j * (1.0f / other.j),
			r * (1.0f / other.j) + j * (1.0f / other.r)
		);
		return result;
	}

	Complex operator+(float& other)
	{
		Complex result(r + other, j);
		return result;
	}

	Complex operator-(float& other)
	{
		Complex result(r - other, j);
		return result;
	}

	Complex operator*(float& other)
	{
		Complex result(
			r * other,
			j * other
		);
		return result;
	}

	Complex operator/(float& other)
	{
		if (other < EPS)
		{
			throw std::runtime_error("Zero division\n");
		}
		Complex result(
			r / other,
			j / other
		);
		return result;
	}

	bool IsEqual(Complex& other)
	{
		return std::fabs(r - other.r) < EPS && std::fabs(j - other.j) < EPS;
	}
};