#ifndef __TTABLE_H__
#define __TTABLE_H__
#include "Polymonial.h"
class UNSortedTABLE
{	
public:
	std::vector<NamedPoly> Table;
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

#endif