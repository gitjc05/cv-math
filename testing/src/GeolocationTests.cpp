#include <gtest/gtest.h>

#include <math.h>

#include "geolocation.h"

namespace
{
	const float TEST_EPS = 0.0001f;

	void ExpectVecNear(Vec3<float> actual, Vec3<float> expected)
	{
		EXPECT_NEAR(actual.x, expected.x, TEST_EPS);
		EXPECT_NEAR(actual.y, expected.y, TEST_EPS);
		EXPECT_NEAR(actual.z, expected.z, TEST_EPS);
	}

	void ExpectUnitLength(Vec3<float> actual)
	{
		float magnitude = sqrtf(actual.x * actual.x + actual.y * actual.y + actual.z * actual.z);

		EXPECT_NEAR(magnitude, 1.0f, TEST_EPS);
	}
}

TEST(GeolocationTests, BearingPitchCreatesEnuVector)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> north = location.getcartesianenuvector(0.0f, 0.0f);
	Vec3<float> east = location.getcartesianenuvector(90.0f, 0.0f);
	Vec3<float> down = location.getcartesianenuvector(0.0f, -90.0f);

	EXPECT_TRUE(north.Equals(Vec3<float>(0.0f, 1.0f, 0.0f)));
	EXPECT_TRUE(east.Equals(Vec3<float>(1.0f, 0.0f, 0.0f)));
	EXPECT_TRUE(down.Equals(Vec3<float>(0.0f, 0.0f, -1.0f)));
}

TEST(GeolocationTests, BearingCanWrapToNorth)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> zeroBearing = location.getcartesianenuvector(0.0f, 0.0f);
	Vec3<float> fullCircleBearing = location.getcartesianenuvector(360.0f, 0.0f);

	ExpectVecNear(zeroBearing, fullCircleBearing);
	ExpectUnitLength(fullCircleBearing);
}

TEST(GeolocationTests, BearingPitchCreatesDiagonalEarthPointingRay)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> ray = location.getcartesianenuvector(45.0f, -30.0f);

	ExpectVecNear(ray, Vec3<float>(0.6123724f, 0.6123724f, -0.5f));
	ExpectUnitLength(ray);
}

TEST(GeolocationTests, WestBearingPointsAlongNegativeEastAxis)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> west = location.getcartesianenuvector(270.0f, 0.0f);

	ExpectVecNear(west, Vec3<float>(-1.0f, 0.0f, 0.0f));
	ExpectUnitLength(west);
}

TEST(GeolocationTests, PlatformBearingRotatesRayIntoEnu)
{
	geolocation location;
	location.setplatform(90.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> forward = location.getcartesianenuvector(0.0f, 0.0f);

	EXPECT_TRUE(forward.Equals(Vec3<float>(1.0f, 0.0f, 0.0f)));
}

TEST(GeolocationTests, PlatformAndRayBearingCompose)
{
	geolocation location;
	location.setplatform(45.0f, 0.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> ray = location.getcartesianenuvector(45.0f, 0.0f);

	ExpectVecNear(ray, Vec3<float>(1.0f, 0.0f, 0.0f));
	ExpectUnitLength(ray);
}

TEST(GeolocationTests, PlatformPitchCanPointRayAtEarth)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, -30.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> forward = location.getcartesianenuvector(0.0f, 0.0f);

	EXPECT_NEAR(forward.x, 0.0f, EPS);
	EXPECT_NEAR(forward.y, 0.8660254f, EPS);
	EXPECT_NEAR(forward.z, -0.5f, EPS);
}

TEST(GeolocationTests, PlatformAndRayPitchCompose)
{
	geolocation location;
	location.setplatform(0.0f, 0.0f, -15.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> ray = location.getcartesianenuvector(0.0f, -15.0f);

	ExpectVecNear(ray, Vec3<float>(0.0f, 0.8660254f, -0.5f));
	ExpectUnitLength(ray);
}

TEST(GeolocationTests, PlatformRollAffectsSideLookingRay)
{
	geolocation location;
	location.setplatform(0.0f, 90.0f, 0.0f, -71.0f, 42.0f, 100.0f);

	Vec3<float> ray = location.getcartesianenuvector(90.0f, 0.0f);

	ExpectVecNear(ray, Vec3<float>(0.0f, 0.0f, -1.0f));
	ExpectUnitLength(ray);
}

TEST(GeolocationTests, SetPlatformStoresPositionAndAttitude)
{
	geolocation location;
	location.setplatform(123.0f, -10.0f, -25.0f, -71.25f, 42.5f, 1500.0f);

	EXPECT_FLOAT_EQ(location.bearing(), 123.0f);
	EXPECT_FLOAT_EQ(location.roll(), -10.0f);
	EXPECT_FLOAT_EQ(location.pitch(), -25.0f);
	EXPECT_FLOAT_EQ(location.longitude(), -71.25f);
	EXPECT_FLOAT_EQ(location.latitude(), 42.5f);
	EXPECT_FLOAT_EQ(location.altitude(), 1500.0f);
}
