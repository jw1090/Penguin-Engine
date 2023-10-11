#pragma once

namespace PenguinEngine::Math
{
	struct Vector4
	{
		union { float x; float r; };
		union { float y; float g; };
		union { float z; float b; };
		union { float w; float a; };

		constexpr Vector4() noexcept : Vector4(0.0f) {} // Default to 0 with no arguments
		explicit constexpr Vector4(float f) noexcept : Vector4(f, f, f, f) {} // Set everything to f
		constexpr Vector4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {} // Specific values for each

		constexpr Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
		constexpr Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
		constexpr Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
		constexpr Vector4 operator*(const Vector4& rhs) const { return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
		constexpr Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
		constexpr Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }

		constexpr Vector4& operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
		constexpr Vector4& operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
		constexpr Vector4& operator*=(const Vector4& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
		constexpr Vector4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
		constexpr Vector4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
	};
}