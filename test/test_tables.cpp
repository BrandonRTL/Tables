#include <gtest.h>
#include <vector>
#include "Tables.h"

TEST(TNamedPoly, can_create_named_polynomial)
{
	std::string a = "2X^2Y^2";
	std::string b = "A";

	EXPECT_NO_THROW(NamedPoly C(b, a));
}

TEST(TUTable, can_create_unsorted_table)
{
	std::string a = "2X^2Y^2";
	std::string b = "A";
	NamedPoly C(b, a);


	EXPECT_NO_THROW(UNSortedTABLE D(C));
}
TEST(TUTable, can_insert_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	NamedPoly B(ab, bb);
	UNSortedTABLE D1;
	D1.Insert(B);

	EXPECT_EQ(B.Name, D1.Table[0].Name);
}
TEST(TUTable, can_search_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	NamedPoly B(ab, bb);
	UNSortedTABLE D1;
	D1.Insert(B);
	NamedPoly A = D1.Search("AB");

	EXPECT_EQ(A, D1.Table[0]);
}
TEST(TUTable, throw_when_search_nonexistent_element)
{
	UNSortedTABLE D1;

	EXPECT_ANY_THROW(D1.Search("A"));
}
TEST(TUTable, can_delete_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	NamedPoly B(ab, bb);
	UNSortedTABLE D1;
	D1.Insert(B);
	D1.Delete("AB");

	EXPECT_EQ(0, D1.Table.size());
}