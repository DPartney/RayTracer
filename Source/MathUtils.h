#pragma once
class MathUtils
{
	template <typename T>
	inline T lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}
};