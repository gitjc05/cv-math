#include "geolocation.h"

#include "quaternion.h"
#include "rotation.h"

namespace
{
	Quaternion ComposePlatformRotation(float bearing, float roll, float pitch)
	{
		Vec3<float> eastAxis(1.0f, 0.0f, 0.0f);
		Vec3<float> northAxis(0.0f, 1.0f, 0.0f);
		Vec3<float> upAxis(0.0f, 0.0f, 1.0f);

		Quaternion yaw = Rotation::GetRotationQuaternion(upAxis, -bearing);
		Quaternion pitchRotation = Rotation::GetRotationQuaternion(eastAxis, pitch);
		Quaternion rollRotation = Rotation::GetRotationQuaternion(northAxis, roll);

		return yaw * pitchRotation * rollRotation;
	}

	Quaternion ComposeRayRotation(float bearing, float pitch)
	{
		Vec3<float> eastAxis(1.0f, 0.0f, 0.0f);
		Vec3<float> upAxis(0.0f, 0.0f, 1.0f);

		Quaternion yaw = Rotation::GetRotationQuaternion(upAxis, -bearing);
		Quaternion pitchRotation = Rotation::GetRotationQuaternion(eastAxis, pitch);

		return yaw * pitchRotation;
	}

	Vec3<float> RotateForward(Quaternion& rotation)
	{
		Vec3<float> forward(0.0f, 1.0f, 0.0f);
		Quaternion point = Rotation::PointQuaternion(forward);
		Quaternion rotated = Rotation::QuaternionRotate(point, rotation);

		return Vec3<float>(rotated.x, rotated.y, rotated.z);
	}
}

geolocation::geolocation()
	: platformBearing(0.0f),
	platformRoll(0.0f),
	platformPitch(0.0f),
	platformLongitude(0.0f),
	platformLatitude(0.0f),
	platformAltitude(0.0f)
{
}

void geolocation::setplatform(float bearing, float roll, float pitch, float longitude, float latitude, float altitude)
{
	platformBearing = bearing;
	platformRoll = roll;
	platformPitch = pitch;
	platformLongitude = longitude;
	platformLatitude = latitude;
	platformAltitude = altitude;
}

Vec3<float> geolocation::getcartesianenuvector(float bearing, float pitch) const
{
	Quaternion platformRotation = ComposePlatformRotation(platformBearing, platformRoll, platformPitch);
	Quaternion rayRotation = ComposeRayRotation(bearing, pitch);
	Quaternion enuRotation = platformRotation * rayRotation;

	return RotateForward(enuRotation);
}

Vec3<float> geolocation::GetCartesianENUVector(float bearing, float pitch) const
{
	return getcartesianenuvector(bearing, pitch);
}

float geolocation::bearing() const
{
	return platformBearing;
}

float geolocation::roll() const
{
	return platformRoll;
}

float geolocation::pitch() const
{
	return platformPitch;
}

float geolocation::longitude() const
{
	return platformLongitude;
}

float geolocation::latitude() const
{
	return platformLatitude;
}

float geolocation::altitude() const
{
	return platformAltitude;
}
