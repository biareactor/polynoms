#include "gtest/gtest.h"
#include "polynom.h"

TEST(Polynom, can_create_polynom)
{
	string s = "5 x - 74 ,9 7y + 2, 75 z - 9 7 x^3y + 1, 9 9 9y^7x^3z - 11,7 zx^5 + 11";
	ASSERT_NO_THROW(Polynom testP(s));
}

TEST(Polynom, can_create_copied_polynom)
{
	string s = "5 x - 74 ,9 7y + 2, 75 z - 9 7 x^3y + 1, 9 9 9y^7x^3z - 11,7 zx^5 + 11";
	Polynom testP1(s);
	Polynom testP2(testP1);

	EXPECT_EQ(testP1, testP2);
}

TEST(Polynom, can_assign_polynoms)
{
	string s = "5 x - 74 ,9 7y + 2, 75 z - 9 7 x^3y + 1, 9 9 9y^7x^3z - 11,7 zx^5 + 11";
	Polynom testP1(s);
	Polynom testP2;

	testP2 = testP1;
	EXPECT_EQ(testP1, testP2);
}

TEST(Polynom, can_assign_polynom_to_itself)
{
	string s = "5 x - 74 ,9 7y + 2, 75 z - 9 7 x^3y + 1, 9 9 9y^7x^3z - 11,7 zx^5 + 11";
	Polynom testP1(s);

	ASSERT_NO_THROW(testP1 = testP1);
}

TEST(Polynom, can_transform_string_to_polynom)
{
	string s = "5 x - 74 ,9 7y + 2, 75 z - 9 7 x^3y + 1, 9 9 9y^7x^3z - 11,7 zx^5 + 11";

	Polynom testP;
	ASSERT_NO_THROW(testP.CreatePolynom(s));
}

TEST(Polynom, can_add_polynoms_1)
{
	string s1 = "3,75x^2 + y^2 - 7xz +x^2y + 1,5z^2y - 0,75";
	string s2 = "-3,75x^2 + 7xz + x^2y + 1,5z^2y + 0,75";
	string s3 = "y^2 +2x^2y + 3z^2y";

	Polynom testP1(s1);
	Polynom testP2(s2);
	Polynom testResult(s3);

	testP1 += testP2;
	EXPECT_EQ(testResult, testP1);
}

TEST(Polynom, can_add_polynoms_2)
{
	string s1 = "3,75x^2 + y^2 - 7xz +x^2y + 1,5z^2y - 0,75";
	string s2 = "-3,75x^2 + 7xz + x^2y + 1,5z^2y + 0,75";
	string s3 = "y^2 +2x^2y + 3z^2y";

	Polynom testP1(s1);
	Polynom testP2(s2);
	Polynom testResult(s3);

	Polynom tR = testP1 + testP2;
	EXPECT_EQ(testResult, tR);
}

TEST(Polynom, can_add_with_zero_polynom)
{
	string s1 = "3,75x^2 + y^2 - 7xz +x^2y + 1,5z^2y - 0,75";
	string s2 = "";
	string s3 = "3,75x^2 + y^2 - 7xz +x^2y + 1,5z^2y - 0,75";

	Polynom testP1(s1);
	Polynom testP2(s2);
	Polynom testResult(s3);

	testP1 += testP2;
	EXPECT_EQ(testResult, testP1);
}

TEST(Polynom, can_multiply_polynoms)
{
	string s1 = "2xyz - 3x^2 + 7y^2z";
	string s2 = "5x^2y^5 - 6z^7";
	string s3 = "10x^3y^6z - 15x^4y^5 + 35x^2y^7z - 12xyz^8 + 18x^2z^7 - 42y^2z^8";

	Polynom testP1(s1);
	Polynom testP2(s2);

	Polynom testResult(s3);
	Polynom tR;
	tR = testP1 * testP2;

	EXPECT_EQ(testResult, tR);
}

TEST(Polynom, can_multiply_polynoms_2)
{
	string s1 = "2x^3yz - 4yzx^2";
	string s2 = "5x^2y^3z + y^3zx^3";
	string s3 = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";

	Polynom testP1(s1);
	Polynom testP2(s2);

	Polynom testResult(s3);
	testP1 *= testP2;

	EXPECT_EQ(testResult, testP1);
}

TEST(Polynom, can_multiply_with_zero_polynom)
{
	string s1 = "2x^3yz - 4yzx^2";
	string s2 = "";
	string s3 = "";

	Polynom testP1(s1);
	Polynom testP2(s2);

	Polynom testResult(s3);
	testP1 *= testP2;

	EXPECT_EQ(testResult, testP1);
}

TEST(Polynom, can_multiply_polynom_on_scalar)
{
	string s1 = "2x - 7 + 1,7z^5x + x^2y^5 - 0,6yz^4x^3";
	string s2 = "4x - 14 + 3,4z^5x + 2x^2y^5 - 1,2yz^4x^3";

	Polynom testP(s1);
	Polynom testResult(s2);
	testP = testP * 2;

	EXPECT_EQ(testResult, testP);
}

TEST(Polynom, can_multiply_zero_polynom_on_scalar)
{
	string s1 = "";
	string s2 = "";

	Polynom testP(s1);
	Polynom testResult(s2);
	testP = testP * 2;

	EXPECT_EQ(testResult, testP);
}

TEST(Polynom, can_compute_value_in_point)
{
	string s1 = "2x - 7,4 + 1,7z^5x + x^2y^3";
	Polynom testP(s1);

	double testResult = testP.ValuePoint(2, 3, 1);

	EXPECT_EQ(108, testResult);
}

TEST(Polynom, can_integrate_polynom_dx)
{
	string s1 = "2x - 7,4 + 1,7z^5x + x^3y^3";
	string s2 = "x^2 - 7,4 x + 0,85 x^2z^5 + 0,25 x^4y^3";
	Polynom testP(s1);
	Polynom testQ(s2);

	testP.IntegrateDX();
	EXPECT_EQ(testQ, testP);
}

TEST(Polynom, can_integrate_polynom_dy)
{
	string s1 = "2x - 7,4 + 1,7z^5x + x^3y^3";
	string s2 = "2xy -7,4y + 1,7z^5xy + 0,25x^3y^4";
	Polynom testP(s1);
	Polynom testQ(s2);

	testP.IntegrateDY();
	EXPECT_EQ(testQ, testP);
}

TEST(Polynom, can_integrate_polynom_dz)
{
	string s1 = "2x - 7,4 + 1,8z^5x + z^4y^3";
	string s2 = "2xz - 7,4z + 0,3z^6x + 0,2z^5y^3";
	Polynom testP(s1);
	Polynom testQ(s2);

	testP.IntegrateDZ();
	EXPECT_EQ(testQ, testP);
}

TEST(Polynom, cant_integrate_polynom_dxdydz)
{
	string s1 = "2x^9 - 7,4 + 1,8z^9x + z^4y^9";
	Polynom testP(s1);
	unsigned int err = 0;

	try
	{
		testP.IntegrateDX();
	}
	catch(int k)
	{
		if (k == 8) err++;
	}

	try
	{
		testP.IntegrateDY();
	}
	catch (int k)
	{
		if (k == 8) err++;
	}

	try
	{
		testP.IntegrateDZ();
	}
	catch (int k)
	{
		if (k == 8) err++;
	}

	EXPECT_EQ(3, err);
}