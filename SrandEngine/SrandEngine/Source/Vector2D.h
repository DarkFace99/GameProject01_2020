#pragma once

#include <iostream>

template <class T>
struct Vector2D
{
	T x, y;

	Vector2D()
	{
		this->x = 0;
		this->y = 0;
	}
	Vector2D(T _x, T _y)
	{
		this->x = _x;
		this->y = _y;
	}

	/* vect1 + vec2 */
	inline Vector2D<T> operator+ (const Vector2D<T>& vec2)
	{
		return Vector2D<T>(x + vec2.x, y + vec2.y);
	}

	/* vect1 += vec2 */
	inline Vector2D<T> friend operator+= (Vector2D<T>& vec1, const Vector2D<T>& vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;

		return vec1;
	}

	/* vect1 - vec2 */
	inline Vector2D<T> operator- (const Vector2D<T>& vec2)
	{
		return Vector2D<T>(x - vec2.x, y - vec2.y);
	}
	inline Vector2D<T> friend operator-=(Vector2D<T>& vec1, const Vector2D<T>& vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;

		return vec1;
	}

	/* vect1 * vec2 */
	inline Vector2D<T> operator* (const T scalar)
	{
		return Vector2D<T>(x * scalar, y * scalar);
	}

	/* vect1 / vec2 */
	inline Vector2D<T> operator/ (const T denominator)
	{
		return (denominator == 0 ? Vector2D<T>(0, 0) : Vector2D<T>(x/denominator, y/denominator));
	}

	/* vect1->SetTo_Zero() */
	inline Vector2D<T>& SetTo_Zero()
	{
		this->x = 0;
		this->y = 0;

		return *this;
	}
	/* vect1->SetTo_One() */
	inline Vector2D<T>& SetTo_One()
	{
		this->x = 1;
		this->y = 1;

		return *this;
	}

	inline Vector2D<T>& Set_XY(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;

		return *this;
	}

	/* std::cout << vectorName << std::endl; */
	inline friend std::ostream& operator<< (std::ostream& stream, const Vector2D<T>& value)
	{
		stream << "(" << value.x << ", " << value.y << ")";
		return stream;
	}
};



/* Use this definition if you know for sure what type of variable is that */
using Vector2D_Int = Vector2D<int>;					
using Vector2D_UInt = Vector2D<unsigned int>;

using Vector2D_float = Vector2D<float>;
using Vector2D_double = Vector2D<double>;
