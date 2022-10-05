#pragma once
#include <cmath>

namespace squampernaut
{
	struct Vector3
	{
		float x, y, z;
			//homework: add z to everything here

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z }{}
		Vector3(float v) : x{ v }, y{ v }, z{ v }{}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }


		//arithmetic operators
		//Vector3 = Vector3 + Vector3
		Vector3 operator + (const Vector3& v) const { return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ this->x / v.x, this->y / v.y, this->z / v.z }; }

		//Vector3 = Vector3 + float
		Vector3 operator + (float s) const { return Vector3{ this->x + s, this->y + s, this->z + s }; }
		Vector3 operator - (float s) const { return Vector3{ this->x - s, this->y - s, this->z - s }; }
		Vector3 operator * (float s) const { return Vector3{ this->x * s, this->y * s, this->z * s }; }
		Vector3 operator / (float s) const { return Vector3{ this->x / s, this->y / s, this->z / s }; }

		//Assignment opperators
		Vector3& operator += (const Vector3& v) { this->x += v.x, this->y += v.y, this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { this->x -= v.x, this->y -= v.y, this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x, this->y *= v.y, this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x, this->y /= v.y, this->z /= v.z; return *this; }

		Vector3& operator += (float s) { this->x += s, this->y += s, this->z += s; return *this; }
		Vector3& operator -= (float s) { this->x -= s, this->y -= s, this->z -= s; return *this; }
		Vector3& operator *= (float s) { this->x *= s, this->y *= s, this->z *= s; return *this; }
		Vector3& operator /= (float s) { this->x /= s, this->y /= s, this->z /= s; return *this; }

		//Unary
		//Vector3 = -Vector3
		Vector3 operator - () const { return Vector3{ -x, -y, -z }; }

		//Comparison
		//Vector3 == Vector3
		bool operator == (const Vector3& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator != (const Vector3& v) const { return (*this == v); }

			//functions
		float lengthSqr();
		float length();

		float distanceSqr(const Vector3& v);
		float distance(const Vector3& v);

		Vector3 Normalized();
		void Normalize();
	};

	inline float Vector3::lengthSqr()
	{
		return x * x + y * y + z * z;
	}

	inline float Vector3::length()
	{
		return std::sqrt(lengthSqr());
	}

	inline float Vector3::distanceSqr(const Vector3& v)
	{
		return ((*this) - v).lengthSqr();
	}

	inline float Vector3::distance(const Vector3& v)
	{
		return 0.0f;
	}


}
