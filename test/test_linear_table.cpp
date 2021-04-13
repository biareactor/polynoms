#include "gtest/gtest.h"
#include "polynom.h"
#include "linear_table.h"

TEST(LineTable, can_create_linear_table)
{
	ASSERT_NO_THROW(LineTable testTab);
}

TEST(LineTable, can_insert_elem_in_tab)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(LineTable, can_insert_elem_in_tab_when_its_not_empty)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testP";
	testData.Poly = testP;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(LineTable, cant_insert_elem_with_same_name)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testPoly";
	testData.Poly = testP;
	ASSERT_ANY_THROW(testTab.Insert(testData));
}

TEST(LineTable, cant_find_when_is_empty)
{
	LineTable testTab;
	string testStr = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	EXPECT_EQ(nullptr, testTab.Find(testStr));
}

TEST(LineTable, can_find_elem_in_tab)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	string tS = testString;
	string testName = "testPoly";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = testName;
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);
	Data* testD = testTab.Find(testName);
	EXPECT_EQ(tS, testD->PolyString);
}

TEST(LineTable, cant_find_elem_in_tab_when_it_isnt_there)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);
	EXPECT_EQ(nullptr, testTab.Find("testP"));
}

TEST(LineTable, cant_delete_elem_when_its_empty)
{
	LineTable testTab;

	try
	{
		testTab.Delete("testPoly");
	}
	catch (int err)
	{
		EXPECT_EQ(1, err);
	}
}

TEST(LineTable, can_delete_existing_elem)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);

	ASSERT_NO_THROW(testTab.Delete("testPoly"));
}

TEST(LineTable, cant_delete_non_existing_elem)
{
	Data testData;
	string testString = "10x^8y^2z^3 - 2x^2y^9z^4 + 50x^3y^7z^8";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LineTable testTab;
	testTab.Insert(testData);

	try
	{
		testTab.Delete("testP");
	}
	catch (int err)
	{
		EXPECT_EQ(2, err);
	}
}