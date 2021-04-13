#include "gtest/gtest.h"
#include "polynom.h"
#include "linear_table_on_lists.h"

TEST(LinTabList, can_create_linear_table)
{
	ASSERT_NO_THROW(LinTabList testTab);
}

TEST(LinTabList, can_insert_elem_in_tab)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(LinTabList, can_insert_elem_in_tab_when_its_not_empty)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testP";
	testData.Poly = testP;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(LinTabList, cant_insert_elem_with_same_name)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testPoly";
	testData.Poly = testP;
	ASSERT_ANY_THROW(testTab.Insert(testData));
}

TEST(LinTabList, cant_find_when_is_empty)
{
	LinTabList testTab;
	string testStr = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	EXPECT_EQ(nullptr, testTab.Find(testStr));
}

TEST(LinTabList, can_find_elem_in_tab)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	string tS = testString;
	string testName = "testPoly";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = testName;
	testData.Poly = testPoly;

	LinTabList testTab;
	testTab.Insert(testData);
	Data* testD = testTab.Find(testName);
	EXPECT_EQ(tS, testD->PolyString);
}

TEST(LinTabList, cant_find_elem_in_tab_when_it_isnt_there)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
	testTab.Insert(testData);
	EXPECT_EQ(nullptr, testTab.Find("testP"));
}

TEST(LinTabList, cant_delete_elem_when_its_empty)
{
	LinTabList testTab;

	try
	{
		testTab.Delete("testPoly");
	}
	catch (int err)
	{
		EXPECT_EQ(1, err);
	}
}

TEST(LinTabList, can_delete_existing_elem)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
	testTab.Insert(testData);

	ASSERT_NO_THROW(testTab.Delete("testPoly"));
}

TEST(LinTabList, cant_delete_non_existing_elem)
{
	Data testData;
	string testString = "6x^5y^4z^2 - 20x^4y^4z^2 + 2x^6y^4z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	LinTabList testTab;
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