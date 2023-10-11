#pragma once

namespace PenguinEngine::Math
{
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };
			std::array<float, 3> v; // same as float v[3], but much better
		};

		constexpr Vector3() noexcept : Vector3(0.0f) {} // Default to 0 with no arguments
		explicit constexpr Vector3(float f) noexcept : Vector3(f, f, f) {} // Set everything to f
		constexpr Vector3(float x, float y, float z) noexcept: x(x), y(y), z(z) {} // Specific values for each

		// Commonly used vectors
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;
			
		constexpr Vector3 operator-() const { return { -x, -y, -z }; }
		constexpr Vector3 operator+(const Vector3& v) const { return { x + v.x, y + v.y, z + v.z}; }
		constexpr Vector3 operator-(const Vector3& v) const { return { x - v.x, y - v.y, z - v.z}; }
		constexpr Vector3 operator*(const float rhs) const { return { x * rhs, y * rhs, z * rhs }; }
		constexpr Vector3 operator/(const float rhs) const { return { x / rhs, y / rhs, z / rhs }; }

		constexpr Vector3 operator+=(const Vector3& v) { return { x += v.x, y += v.y, z += v.z }; }
		constexpr Vector3 operator-=(const Vector3& v) { return { x -= v.x, y -= v.y, z -= v.z }; }
		constexpr Vector3 operator*=(const float rhs) { return { x *= rhs, y *= rhs, z *= rhs }; }
		constexpr Vector3 operator/=(const float rhs) { return { x /= rhs, y /= rhs, z /= rhs }; }
	};
}