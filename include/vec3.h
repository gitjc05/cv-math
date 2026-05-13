#define EPS 0.000001f

class vec3
{
public:
	float x;
	float y;
	float z;

	vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	vec3 operator+(const vec3& other);

	vec3 operator-(const vec3& other);

	vec3 operator*(const vec3& other);

	vec3 operator+(const float& offset);

	vec3 operator*(const float& scale);

	bool equals(const vec3& other);

	float dot(vec3& other);
};