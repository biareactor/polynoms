#include "gtest/gtest.h"
#include "polynom.h"
#include "ordered_line_table.h"

TEST(ordered_line_table, can_create_linear_table)
{
	ASSERT_NO_THROW(ordered_line_table testTab);
}

TEST(ordered_line_table, can_insert_elem_in_tab)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(ordered_line_table, can_insert_elem_in_tab_when_its_not_empty)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testP";
	testData.Poly = testP;
	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(ordered_line_table, cant_insert_elem_with_same_name)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	string testStr = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
	testTab.Insert(testData);

	testData.PolyString = testStr;
	Polynom testP(testStr);
	testData.key = "testPoly";
	testData.Poly = testP;
	ASSERT_ANY_THROW(testTab.Insert(testData));
}

TEST(ordered_line_table, cant_find_when_is_empty)
{
	ordered_line_table testTab;
	string testStr = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	EXPECT_EQ(nullptr, testTab.Find(testStr));
}

TEST(ordered_line_table, can_find_elem_in_tab)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	string tS = testString;
	string testName = "testPoly";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = testName;
	testData.Poly = testPoly;

	ordered_line_table testTab;
	testTab.Insert(testData);
	Data* testD = testTab.Find(testName);
	EXPECT_EQ(tS, testD->PolyString);
}

TEST(ordered_line_table, cant_find_elem_in_tab_when_it_isnt_there)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
	testTab.Insert(testData);
	EXPECT_EQ(nullptr, testTab.Find("testP"));
}

TEST(ordered_line_table, cant_delete_elem_when_its_empty)
{
	ordered_line_table testTab;

	try
	{
		testTab.Delete("testPoly");
	}
	catch (int err)
	{
		EXPECT_EQ(2, err);
	}
}

TEST(ordered_line_table, can_delete_existing_elem)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
	testTab.Insert(testData);

	ASSERT_NO_THROW(testTab.Delete("testPoly"));
}

TEST(ordered_line_table, cant_delete_non_existing_elem)
{
	Data testData;
	string testString = "x^5y^3z^2 + x^3y^3z^3 - 5x^2y^3z^2";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	ordered_line_table testTab;
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

TEST(ordered_line_table, can_compare_more)
{
	ordered_line_table testTab;
	EXPECT_EQ(1, testTab.Compare("abd", "abc"));
}

TEST(ordered_line_table, can_compare_equal)
{
	ordered_line_table testTab;
	EXPECT_EQ(0, testTab.Compare("abc", "abc"));
}

TEST(ordered_line_table, can_compare_less)
{
	ordered_line_table testTab;
	EXPECT_EQ(-1, testTab.Compare("abc", "abd"));
}