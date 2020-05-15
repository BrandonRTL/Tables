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

TEST(TSTable, can_create_sorted_table)
{
	std::string a = "2X^2Y^2";
	std::string b = "A";
	NamedPoly C(b, a);


	EXPECT_NO_THROW(SortedTable D(C));
}
TEST(TSTable, can_search_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	NamedPoly B(ab, bb);
	SortedTable A(B);

	EXPECT_EQ(B, A.Search(ab));
}
TEST(TSTable, cant_find_nonexistent_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	NamedPoly B(ab, bb);
	SortedTable A(B);

	EXPECT_ANY_THROW(A.Search("Gleb"));
}
TEST(TSTable, can_insert_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	std::string cb = "ABC";
	std::string db = "4X^2";
	NamedPoly B(ab, bb);
	NamedPoly C(cb, db);	
	SortedTable A;
	A.Insert(C);
	A.Insert(B);

	EXPECT_EQ(B, A.Table[0]);
	EXPECT_EQ(C, A.Table[1]);
}
TEST(TSTable, can_delete_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	std::string cb = "ABC";
	std::string db = "4X^2";
	NamedPoly B(ab, bb);
	NamedPoly C(cb, db);
	SortedTable A;
	A.Insert(C);
	A.Insert(B);
	A.Delete(ab);

	EXPECT_EQ(C, A.Table[0]);
}
TEST(THTable, can_create_hash_table)
{
	EXPECT_NO_THROW(HashTableSeparateChaining A(13));
}
TEST(THTable, can_insert_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	std::string cb = "ABC";
	std::string db = "4X^2";
	NamedPoly B(ab, bb);
	HashTableSeparateChaining A;
	A.Insert(B);

	EXPECT_EQ(B, A.HashTable[8].front());
}
TEST(THTable, can_search_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	std::string cb = "ABC";
	std::string db = "4X^2";
	NamedPoly B(ab, bb);
	HashTableSeparateChaining A;
	A.Insert(B);

	EXPECT_EQ(B, A.Search(ab));
}
TEST(THTable, can_delete_element)
{
	std::string ab = "AB";
	std::string bb = "3X^2";
	std::string cb = "ABC";
	std::string db = "4X^2";
	NamedPoly B(ab, bb);
	HashTableSeparateChaining A;
	A.Insert(B);
	A.Delete(ab);

	EXPECT_EQ(1, A.HashTable[8].empty());
}
