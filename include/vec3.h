#define EPS 0.000001f

template <typename T> class vec3
{
public:
	T x;
	T y;
	T z;

	vec3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3() {}


	bool equals(const vec3<T>& other) const
	{
		return (fabs(other.x - x) <= EPS) && (fabs(other.y - y) <= EPS) && (fabs(other.z - z) <= EPS);
	}

	vec3<T> operator+(const vec3<T>& other) const
	{
		vec3<T> result(x + other.x, y + other.y, z + other.z);
		return result;
	}

	vec3<T> operator-(const vec3& other) const
	{
		vec3<T> result(x - other.x, y - other.y, z - other.z);
		return result;
	}

	vec3<T> operator*(const vec3& other) const
	{
		vec3<T> result(x * other.x, y * other.y, z * other.z);
		return result;
	}

	vec3<T> operator+(const T& offset) const
	{
		vec3<T> result(offset + x, offset + y, offset + z);
		return result;
	}

	vec3<T> operator*(const T& scale) const
	{
		vec3<T> result(scale * x, scale * y, scale * z);
		return result;
	}

	T dot(vec3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	vec3<T> cross(vec3& other) const
	{
		vec3 result(
			y * other.z - z * other.y,
			x * other.z - z * other.x,
			x * other.y - y * other.x
		);
		return result;
	}
};