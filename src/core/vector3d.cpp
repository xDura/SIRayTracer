#include "vector3d.h"

Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

Vector3D::Vector3D(double a) : x(a), y(a), z(a)
{
}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_)
{
}

Vector3D::Vector3D(const Vector3D &v_) : x(v_.x), y(v_.y), z(v_.z)
{
}

// Sum two vectors and return the result as a new object
Vector3D Vector3D::operator+(const Vector3D &v) const
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

// Subtract two vectors and return the result as a new object
Vector3D Vector3D::operator-(const Vector3D &v) const
{
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

// Return the negative of the vector as a new object
Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

// Multiply a vector by a scalar and return the result as a new object
Vector3D Vector3D::operator*(const double a) const
{
    return Vector3D(x*a, y*a, z*a);
}

// Divide a vector by a scalar and return the result as a new object
Vector3D Vector3D::operator/(const double a) const
{
    return Vector3D(x/a, y/a, z/a);
}

// Add a vector to the current one
Vector3D& Vector3D::operator+=(const Vector3D &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

// Subtract a vector to the current one
Vector3D& Vector3D::operator-=(const Vector3D &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

// Multiply the current vector by a scalar
Vector3D& Vector3D::operator*=(const double a)
{
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

// Divide the current vector by a scalar
Vector3D& Vector3D::operator/=(const double a)
{
    x /= a;
    y /= a;
    z /= a;

    return *this;
}

// Squared length of the current vector
double Vector3D::lengthSq() const
{
    return x*x + y*y + z*z;
}

// Length of the current vector
double Vector3D::length() const
{
    //[T] : check line 572 of vector.h in mitsuba
    return std::sqrt(lengthSq());
}

// Returns the normalized version of the current vector
Vector3D Vector3D::normalized() const
{
    return (*this)/length();
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const Vector3D &v)
{
    out << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    return out;
}



//*************** VECTOR2D ****************************

Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(double a) : x(a), y(a)
{
}

Vector2D::Vector2D(double x_, double y_) : x(x_), y(y_)
{
}

Vector2D::Vector2D(const Vector2D &v_) : x(v_.x), y(v_.y)
{
}

// Sum two vectors and return the result as a new object
Vector2D Vector2D::operator+(const Vector2D &v) const
{
	return Vector2D(x + v.x, y + v.y);
}

// Subtract two vectors and return the result as a new object
Vector2D Vector2D::operator-(const Vector2D &v) const
{
	return Vector2D(x - v.x, y - v.y);
}

// Return the negative of the vector as a new object
Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

// Multiply a vector by a scalar and return the result as a new object
Vector2D Vector2D::operator*(const double a) const
{
	return Vector2D(x*a, y*a);
}

// Divide a vector by a scalar and return the result as a new object
Vector2D Vector2D::operator/(const double a) const
{
	return Vector2D(x / a, y / a);
}

// Add a vector to the current one
Vector2D& Vector2D::operator+=(const Vector2D &v)
{
	x += v.x;
	y += v.y;

	return *this;
}

// Subtract a vector to the current one
Vector2D& Vector2D::operator-=(const Vector2D &v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

// Multiply the current vector by a scalar
Vector2D& Vector2D::operator*=(const double a)
{
	x *= a;
	y *= a;

	return *this;
}

// Divide the current vector by a scalar
Vector2D& Vector2D::operator/=(const double a)
{
	x /= a;
	y /= a;

	return *this;
}

// Squared length of the current vector
double Vector2D::lengthSq() const
{
	return x*x + y*y;
}

// Length of the current vector
double Vector2D::length() const
{
	//[T] : check line 572 of vector.h in mitsuba
	return std::sqrt(lengthSq());
}

// Returns the normalized version of the current vector
Vector2D Vector2D::normalized() const
{
	return (*this) / length();
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const Vector2D &v)
{
	out << "[" << v.x << ", " << v.y  << "]";
	return out;
}
