#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x_val, float y_val) :x(x_val), y(y_val) {}

	Vector2 operator+(const Vector2& vec)const
	{
		return Vector2(x + vec.x, y + vec.y);
	}


	Vector2 operator-(const Vector2& other)
	{
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2 operator*(const Vector2& other)
	{
		return Vector2(this->x * other.x, this->y * other.y);
	}

	Vector2 operator*(float scalar)
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	void operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	Vector2& operator=(const Vector2& other)
	{
		if (&other == this) return *this;
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	void operator-=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}

	bool operator==(const Vector2& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}
	Vector2 Normalized()
	{
		float len = length();
		if (len == 0)	return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}


};

#endif // !_VECTOR_H_
