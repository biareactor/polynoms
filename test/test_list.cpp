#include "gtest/gtest.h"
#include "list.h"
#include "polynom.h"

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> testList);
}

TEST(List, can_create_copied_list)
{
	List<int> testList1;

	for (int i = 0; i < 5; i++)
		testList1.push_back(i);

	List<int> testList2(testList1);
	EXPECT_EQ(testList1, testList2);
}

TEST(List, can_get_amount)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	EXPECT_EQ(5, testList.GetAmount());
}

TEST(List, can_push_back_in_void)
{
	List<int> testList;
	int testValue = 5;

	ASSERT_NO_THROW(testList.push_back(5));
}

TEST(List, cant_pop_front_when_list_is_void)
{
	List<int> testList;

	ASSERT_ANY_THROW(testList.pop_front());
}

TEST(List, can_pop_first_element_from_list)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_NO_THROW(testList.pop_front());
}

TEST(List, can_get_element)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	EXPECT_EQ(3, testList[3]);
}

TEST(List, cant_get_element_with_negative_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList[-9]);
}

TEST(List, cant_get_element_with_large_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList[5]);
}

TEST(List, can_find_element_in_list)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	EXPECT_EQ(3, (testList.FindElem(3))->inner);
}

TEST(List, cant_find_element_with_negative_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList.FindElem(-9));
}

TEST(List, cant_find_element_with_large_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList.FindElem(7));
}

TEST(List, can_assign_lists_of_non_equal_size)
{
	List<int> testList1;
	List<int> testList2;

	for (int i = 0; i < 1; i++)
		testList1.push_back(i);

	for (int i = 0; i < 4; i++)
		testList2.push_back(i + 1);

	testList2 = testList1;
	EXPECT_EQ(testList1, testList2);
}

TEST(List, can_assign_list_to_itself)
{
	List<int> testList;

	for (int i = 0; i < 4; i++)
		testList.push_back(i + 1);

	ASSERT_NO_THROW(testList = testList);
}

TEST(List, assign_operator_changes_amount)
{
	List<int> testList1;
	List<int> testList2;

	for (int i = 0; i < 1; i++)
		testList1.push_back(i);

	for (int i = 0; i < 4; i++)
		testList2.push_back(i + 1);

	testList2 = testList1;
	EXPECT_EQ(1, testList2.GetAmount());
}

TEST(List, compare_equal_lists)
{
	List<int> testList1;
	List<int> testList2;

	srand(time(0));

	for (int i = 4; i > -1; i--)
		testList1.push_back(rand() % 100 - 1);

	testList2 = testList1;

	EXPECT_EQ(testList1, testList2);
}

TEST(List, can_find_elem_in_list)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	EXPECT_NE(nullptr, testList.FindElem(3));
}

TEST(List, cant_find_elem_with_negative_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList.FindElem(-8));
}

TEST(List, cant_find_elem_with_large_index)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	ASSERT_ANY_THROW(testList.FindElem(7));
}

TEST(List, can_delete_element_in_list)
{
	List<int> testList;

	for (int i = 0; i < 5; i++)
		testList.push_back(i);

	Node<int>* p = testList.FindElem(2);
	Node<int>* p1 = testList.FindElem(1);
	Node<int>* p2 = testList.FindElem(3);

	p = testList.DelELem(p);

	EXPECT_EQ(p2, p1->pNext);
	EXPECT_EQ(p1, p);
}

TEST(List, can_sort_list)
{
	List<int> testList;

	srand(time(0));

	for (int i = 4; i > -1; i--)
		testList.push_back(rand() % 100 - 1);

	testList.Sort();

	bool f = true;
	int i = 0;

	while ((!f) && (i < testList.GetAmount()))
	{
		if (testList[i] > testList[i + 1])
			f = false;
		i++;
	}

	EXPECT_EQ(true, f);
}