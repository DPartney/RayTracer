#pragma once
#include <glm/glm.hpp>
#include "glm/gtx/color_space.hpp"

using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = glm::uint32;

inline color4_t RGBAToColor(const rgba_t& rgba)
{
	color4_t color = color4_t(0);

	color.r = ((rgba >> 24) & 0xff) / 255.0f;
	color.g = ((rgba >> 16) & 0xff) / 255.0f;
	color.b = ((rgba >> 8) & 0xff) / 255.0f;
	color.a = ((rgba >> 0) & 0xff) / 255.0f;

	return color;
}

inline rgba_t ColorToRGBA(const color4_t& color)
{
	rgba_t rgba = 0;

	rgba |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24;
	rgba |= uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16;
	rgba |= uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8;
	rgba |= uint8_t(glm::clamp(color.a, 0.0f, 1.0f) * 255) << 0;

	return rgba;
}