#pragma once
#include <cmath>

namespace math
{
	constexpr float pie = 3.14159f;	//180
	constexpr float twoPie = 6.28318f; // 360
	constexpr float halfPie = 1.57079f;	//90

	constexpr float DegToRad(float degrees)
	{
		return degrees * (pie / 180);
	}
	constexpr float RadToDeg(float radians)
	{
		return radians * (180 / pie);
	}

	int sqr(int v);
	inline int half(int v) { return v / 2; }

		//clamps the value between a minimum and maximum value
	template <typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}
		//interpolates between min and max by the interpolant t.
	template <typename T>
	T Lerp(T min, T max, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return min + ((max - min) * t);
	}
		
		//takes a value between min and max and returns the normalized value (0-1)
	template <typename T>
	T Normalize(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}

		//takes a value within a given input range and maps it to a given output range
	template <typename T>
	T Remap(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return Lerp(outMin, outMax, Normalize(value, inMin, inMax));
	}

		//wraps the value within the min and max range
	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));

		return value;
	}

}
