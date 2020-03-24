#ifndef __TTABLE_H__
#define __TTABLE_H__
#include "Polymonial.h"
#include <ctime>
#include <list>
class UNSortedTABLE
{	
public:
	std::vector<NamedPoly> Table;
	UNSortedTABLE()
	{

	}
	UNSortedTABLE(NamedPoly _Data)
	{
		Table.push_back(_Data);
	}
	void Insert(const NamedPoly _Data)
	{
		Table.push_back(_Data);
	}
	void Delete (int ind)
	{
		NamedPoly Tmp = Table[Table.size()-1];
		Table[Table.size()-1] = Table[ind];
		Table[ind] = Tmp;
		Table.pop_back();
	}
	NamedPoly& Search(const std::string key)
	{
		for (int i = 0; i < Table.size(); i++)
		{
			if (Table[i].Name == key)
				return Table[i];
		}
		throw "No Poly found";
	}
	void Delete(std::string key)
	{
		for (int i = 0; i < Table.size(); i++)
		{
			if (Table[i].Name == key)
				Delete(i);
		}
	}
	friend std::ostream& operator<<(std::ostream &out, UNSortedTABLE &T)
	{
		if (T.Table.size() == 0)
			out << "This table is empty";
		else
		{
			out << "Name" << "           " << "Data" << std::endl;
			for (int i = 0; i < T.Table.size(); i++)
				out << T.Table[i] << std::endl;
		}
		return out;
	}
};

class Some_kind_of_table
{
	virtual void Delete(const std::string key) = 0;
	virtual NamedPoly& Search(const std::string key) = 0;
	virtual void Insert(const NamedPoly _Data) = 0;
};
class SortedTable:public Some_kind_of_table
{
public:
	std::vector<NamedPoly> Table;
	SortedTable()
	{

	}
	SortedTable(NamedPoly _Data)
	{
		Table.push_back(_Data);
	}
	int SearchByKey(const std::string key)
	{
		int left = 0;
		int right = Table.size();
		int mid = 0;

		while (!(left >= right))
		{
			mid = left + (right - left) / 2;

			if (Table[mid].Name == key)
				return mid;

			if (Table[mid].Name > key)
				right = mid;
			else
				left = mid + 1;
		}

		return -(1 + left);
	}
	NamedPoly& Search(const std::string key)
	{
		int _key = SearchByKey(key);
		if (_key < 0)
			throw "key not  found";
		return Table[_key];
	}
	void Delete(const std::string key)
	{
		int _key = SearchByKey(key);
		std::vector<NamedPoly>::iterator it;
		if (_key < 0)
			throw "key not  found";
		it = Table.begin() + _key;
		Table.erase(it);
	}
	void Insert(const NamedPoly _Data)
	{
		std::vector<NamedPoly>::iterator it;
		std::string key = _Data.Name;
		int Left = -1;
		int Right = Table.size();
		int Mid;
		while (Left < Right - 1)
		{
			Mid = (Left + Right) / 2;
			if (Table[Mid].Name < key)
				Left = Mid;
			else
				Right = Mid;
		}
		it = Table.begin()+Right;
		Table.insert(it,_Data);
	}
	friend std::ostream& operator<<(std::ostream &out, SortedTable &T)
	{
		if (T.Table.size() == 0)
			out << "This table is empty";
		else
		{
			out << "Name" << "           " << "Data" << std::endl;
			for (int i = 0; i < T.Table.size(); i++)
				out << T.Table[i] << std::endl;
		}
		return out;
	}
};
class HashTableSeparateChaining:public Some_kind_of_table
{
public:
	std::vector<std::list<NamedPoly>> HashTable;
	int FirstRandomNumber; 
	int SecondRandomNumber;
	HashTableSeparateChaining(int _size = 13)
	{
		HashTable = std::vector <std::list<NamedPoly>> (_size);
		srand(time(0));
		FirstRandomNumber = rand() % _size;
		SecondRandomNumber = rand() % _size;
	}
	int HashFuction(std::string key)
	{
		int Sum = 0;
		for (int i = 0; i < key.size(); i++)
			Sum = Sum + (int)(key[i]);
	//	return ((FirstRandomNumber*Sum + SecondRandomNumber) % HashTable.size());
		return 8;
	}
	void Delete(const std::string key)
	{
		int Pos = HashFuction(key);
		if (!HashTable[Pos].empty())
			for (auto iter = HashTable[Pos].begin(); iter != HashTable[Pos].end(); iter++)
			{
				if ((*iter).Name == key)
				{
					HashTable[Pos].erase(iter);
					break;
				}
			}
	}
	void Insert(const NamedPoly _Data)
	{
		int Pos = HashFuction(_Data.Name);
		if (HashTable[Pos].empty())
		{
			HashTable[Pos].push_back(_Data);
		}
		else
		{
			for (auto iter = HashTable[Pos].begin(); iter != HashTable[Pos].end(); iter++)
			{
				if ((*iter).Name == _Data.Name)
				{
					throw "Incorrect key";
				}
			}
			HashTable[Pos].push_back(_Data);
		}
	}
	NamedPoly& Search(const std::string key)
	{
		int Pos = HashFuction(key);
		if (HashTable[Pos].empty())
		{
			throw "Not found";
		}
		for (auto iter = HashTable[Pos].begin(); iter != HashTable[Pos].end(); iter++)
		{
			if ((*iter).Name == key)
			{
				return (*iter);
			}
		}
		throw "Not found";
	}
};
#endif