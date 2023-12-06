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

inline bool approximately(float value1, float value2)
{
	// check if the difference between the values is less than epsilon
	return ((float)(glm::abs(value1) - (float)glm::abs(value2)) < FLT_EPSILON);
}

inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
{
	// normalize the incoming vector (v)
	glm::vec3 nv = glm::normalize(v);

	float dt = dot(nv, n);
	float discriminant = 1 - (index * index) * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
		return true;
	}

	return false;
}

inline float schlick(float cosine, float index)
{
	// calculate specular reflection coefficient, or probability of reflection
	float r0 = (1.0f - index) / (1 + index);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5);
}