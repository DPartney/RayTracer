#pragma once
template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
	return (a * (1.0f - t)) + (b * t);
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
	return v - 2.0f * glm::dot(n, v) * n;
}