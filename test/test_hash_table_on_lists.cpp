#include "gtest/gtest.h"
#include "polynom.h"
#include "hash_table_on_lists.h"

TEST(hash_table_on_lists, can_create_hash_table)
{
	ASSERT_NO_THROW(hash_table_on_lists testTab);
}

TEST(hash_table_on_lists, can_hash_string)
{
	string testString = "check";
	int testHash = HashIt(testString);
	int rightHash = 0;

	for (unsigned int i = 0; i < testString.size(); i++)
		rightHash += (int)testString[i];

	rightHash *= testString.size();
	rightHash %= 1000;

	EXPECT_EQ(rightHash, testHash);
}

TEST(hash_table_on_lists, can_insert_data)
{
	Data testData;
	string testString = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	hash_table_on_lists testTab;

	ASSERT_NO_THROW(testTab.Insert(testData));
}

TEST(hash_table_on_lists, cant_insert_twice)
{
	Data testData;
	string testString = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	hash_table_on_lists testTab;
	testTab.Insert(testData);

	ASSERT_ANY_THROW(testTab.Insert(testData));
}

TEST(hash_table_on_lists, cant_insert_data_with_same_name)
{
	string testString = "y^2 +2x^2y + 3z^2y";
	string addS = "+2xz";
	hash_table_on_lists testTab;

	Data testData;
	string tS = testString;

	testData.PolyString = tS;
	Polynom testPoly(tS);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	testTab.Insert(testData);
	testString += addS;

	tS = testString;

	testData.PolyString = tS;
	Polynom testPoly1(tS);

	testData.key = "testPoly";
	testData.Poly = testPoly1;

	ASSERT_ANY_THROW(testTab.Insert(testData));
}

TEST(hash_table_on_lists, cant_find_anything)
{
	hash_table_on_lists testTab;
	EXPECT_EQ(nullptr, testTab.Find("testData"));
}

TEST(hash_table_on_lists, can_find_data)
{
	Data testData;
	string testString = "y^2 +2x^2y + 3z^2y";
	string tS = testString;
	int rightHash = 0;

	for (unsigned int i = 0; i < testString.size(); i++)
		rightHash += (int)testString[i];

	rightHash *= testString.size();
	rightHash %= 1000;

	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	hash_table_on_lists testTab;
	testTab.Insert(testData);
	Data* testAdd = testTab.Find("testPoly");

	EXPECT_EQ(tS, testAdd->PolyString);
}

TEST(hash_table_on_lists, cant_delete_data_when_empty)
{
	hash_table_on_lists testTab;
	ASSERT_ANY_THROW(testTab.Delete("testPoly"));
}

TEST(hash_table_on_lists, can_delete_data)
{
	hash_table_on_lists testTab;

	Data testData;
	string testString = "y^2 +2x^2y + 3z^2y";
	testData.PolyString = testString;
	Polynom testPoly(testString);

	testData.key = "testPoly";
	testData.Poly = testPoly;

	testTab.Insert(testData);
	ASSERT_NO_THROW(testTab.Delete("testPoly"));
}