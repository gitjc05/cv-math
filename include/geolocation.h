#pragma once

#include "vec3.h"

class geolocation
{
public:
	geolocation();

	void setplatform(float bearing, float roll, float pitch, float longitude, float latitude, float altitude);

	Vec3<float> getcartesianenuvector(float bearing, float pitch) const;
	Vec3<float> GetCartesianENUVector(float bearing, float pitch) const;

	float bearing() const;
	float roll() const;
	float pitch() const;
	float longitude() const;
	float latitude() const;
	float altitude() const;

private:
	float platformBearing;
	float platformRoll;
	float platformPitch;
	float platformLongitude;
	float platformLatitude;
	float platformAltitude;
};
