#ifndef __TLISTK_H__
#define __TLISTK_H__
#include <iostream>
#include <string>
#include <vector>
template <typename ValType>
class Node
{
public:
	ValType Data = 0;
	Node *next = 0;
	Node(ValType _Data = 0, Node* _next = 0)
	{
		this->Data = _Data;
		this->next = _next;
	}
};
template <typename ValType>
class MIFL
{
private:
	Node<ValType>* ptr;
public:
	MIFL();
	MIFL(const MIFL& A);
	MIFL(Node<ValType>* A);
	MIFL& operator++();
	MIFL operator++(int);
	MIFL& operator= (const MIFL& A);
	ValType& operator*();
	bool operator== (const MIFL& A)
	{
		return (ptr == A.ptr);
	}
	bool operator!= (const MIFL& A)
	{
		return (ptr != A.ptr);
	}
};
template <typename ValType>
class List
{
	Node<ValType>* head;
	Node<ValType>* tail;
public:
	int Size;
	List();
	List(int n);
	List(const List<ValType>& other)
	{
		if (other.head == nullptr)
			return;
		Node<ValType>* dummyHead = new Node<ValType>;
		Node<ValType>* curr = dummyHead;
		Node<ValType>* othcurr = other.head;
		for (; othcurr != nullptr; othcurr = othcurr->next)
		{
			curr->next = new Node<ValType>;
			curr = curr->next;
			//	std::cout << (curr->Data = othcurr->Data) << ",";
			curr->next = nullptr;
		}
		head = dummyHead->next;
		delete dummyHead;
	}
	List<ValType>& operator=(const List<ValType>& LST)
	{
		if (this != &LST)
		{
			clear();
			Size = LST.Size;
			Node<ValType>* curr = LST.head;
			for (int i = 0; i < LST.Size; i++)
			{
				head = new Node<ValType>(curr->Data, head);
				curr = curr->next;
			}
		}
		return *this;
	}
	bool operator==(const List& list2) const
	{
		Node<ValType>* L = head;
		Node<ValType>* Ll = list2.head;
		bool res = true;

		if ((L && !Ll) || (!L && Ll))
			res = false;
		if (res)
		{
			while (L && Ll)
			{
				if (L->Data != Ll->Data)
				{
					res = false;
					L = L->next;
					Ll = Ll->next;
				}
				else
				{
					L = L->next;
					Ll = Ll->next;
				}
			}
		}
		return res;
	}
	void Insert(ValType Data, Node<ValType>* prev);
	void Insert(ValType Data, int Ind);
	void Remove(Node<ValType>* prev);
	void Remove(int Ind);
	void push_back(ValType Data);
	ValType pop_back();
	void pop_front();
	void push_front(ValType Data);
	ValType Front();
	ValType Back();
	ValType& operator [](int n);
	void clear();
	~List();
	Node<ValType>* GetHead()
	{
		return head;
	}
	int GetSize()
	{
		return Size;
	}
	MIFL<ValType> begin()
	{
		MIFL<ValType> A(head);
		return A;
	}
	MIFL<ValType> end()
	{
		MIFL<ValType> A;
		return A;
	}
};

template <typename ValType>
void List<ValType>::push_front(ValType Data)
{
	head = new Node<ValType>(Data, head);
	if (Size == 0)
		tail = head;
	Size++;
}
template <typename ValType>
ValType List<ValType>::pop_back()
{
	int Counter = 0;
	ValType Tmp;
	Node<ValType> *current = this->head;
	while (current)
	{
		if (Counter == Size - 1)
		{
			Tmp = current->Data;
		}
		current = current->next;
		Counter++;
	}
	Remove(Size - 1);
	return Tmp;
}
template <typename ValType>
ValType List<ValType>::Front()
{
	if (Size != 0)
	{
		return head->Data;
	}
	else throw "Cant front from empty list";
}
template <typename ValType>
ValType List<ValType>::Back()
{
	if (Size != 0)
	{
		return operator [](Size - 1);
	}
	else throw "Cant back from empty list";
}
template <typename ValType>
void List<ValType>::pop_front()
{
	Node<ValType> *tmp = head;
	head = head->next;
	delete tmp;
	Size--;
}
template <typename ValType>
ValType& List<ValType>::operator [](int n)
{
	int Counter = 0;
	if (n < 0 || n > Size)
	{
		throw "Incorrect index";
	}
	Node<ValType> *current = this->head;
	while (current)
	{
		if (Counter == n)
		{
			return current->Data;
		}
		current = current->next;
		Counter++;
	}
}
template <typename ValType>
List<ValType>::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}
template <typename ValType>
List<ValType>::List(int n)
{
	if (n < 0)
		throw "Not correct";
	head = 0;
	tail = 0;
	Size = n;
	for (int i = 0; i < Size; i++)
	{
		head = new Node<ValType>(0, head);
	}
}
template <typename ValType>
void List<ValType>::Insert(ValType Data, int n)
{
	if (n == 0)
	{
		push_front(Data);
	}
	else
	{
		Node<ValType> *Prev = this->head;
		for (int i = 0; i < n - 1; i++)
		{
			Prev = Prev->next;
		}
		Node<ValType> *New = new Node<ValType>(Data, Prev->next);
		Prev->next = New;
		Size++;
	}
}
template <typename ValType>
void List<ValType>::Insert(ValType Data, Node<ValType>* prev)
{
	Node<ValType>* a = new Node;
	a->Data = Data;
	Node<ValType>* b = prev->next;
	prev->next = a;
	a->next = b;
	Size++;
}
template <typename ValType>
void List<ValType>::push_back(ValType Data)
{
	if (head == nullptr)
		head = new Node<ValType>(Data);
	else
	{
		Node<ValType> * current = this->head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new Node<ValType>(Data);
	}
	Size++;
}
template <typename ValType>
void List<ValType>::Remove(Node<ValType>* prev)
{
	Node<ValType>* tmp = prev->next;
	delete prev->next;
	prev->next = tmp;
	Size--;
}
template <typename ValType>
void List<ValType>::Remove(int Ind)
{
	if (Ind == 0)
	{
		pop_front();
	}
	else
	{
		Node<ValType> *Prev = this->head;
		for (int i = 0; i < Ind - 1; i++)
		{
			Prev = Prev->next;
		}
		Node<ValType> *tmp = Prev->next;
		Prev->next = tmp->next;
		delete tmp;
		Size--;
	}
}
template <typename ValType>
List<ValType>::~List()
{
	clear();
}
template<typename ValType>
void List<ValType>::clear()
{
	while (Size)
	{
		pop_front();
	}
}
template<typename ValType>
MIFL<ValType>::MIFL()
{
	ptr = 0;
}

template<typename ValType>
MIFL<ValType>::MIFL(const MIFL & A)
{
	ptr = A.ptr;
}
template<typename ValType>
MIFL<ValType>::MIFL(Node<ValType>* A)
{
	ptr = A;
}

template<typename ValType>
MIFL<ValType>& MIFL<ValType>::operator++()
{
	ptr = ptr->next;
	return *this;
}


template<typename ValType>
MIFL<ValType> MIFL<ValType>::operator++(int)
{
	MIFL<ValType> tmp(ptr);
	ptr = ptr->next;
	return tmp;
}

template<typename ValType>
MIFL<ValType>& MIFL<ValType>::operator=(const MIFL & A)
{
	ptr = A.ptr;
	return *this;
}

template<typename ValType>
ValType & MIFL<ValType>::operator*()
{
	return ptr->Data;
}
class Monom
{
public:
	double coef;
	int degree;

	Monom(double _coef = 4815162342, int _degree = 0) // Если ты читаешь ети цифры и не знаешь, что они значат, то ты плохой человек, вот
	{
		coef = _coef;
		degree = _degree;
	}
	Monom(std::string StM)
	{
		degree = 0;
		coef = std::stod(StM);
		for (int i = 0; i < StM.size(); i++)
		{
			if (StM[i] == 'X')
			{
				degree += 100 * (StM[i + 2] - 48);
			}
			if (StM[i] == 'Y')
			{
				degree += 10 * (StM[i + 2] - 48);
			}
			if (StM[i] == 'Z')
			{
				degree += 1 * (StM[i + 2] - 48);
			}
		}
	}
	friend std::ostream& operator<<(std::ostream &out, Monom m)
	{
		out << m.coef;
		if (m.degree / 100)
			out << "X^" << m.degree / 100;
		if ((m.degree % 100) / 10)
			out << "Y^" << (m.degree % 100) / 10;
		if ((m.degree % 10))
			out << "Z^" << m.degree % 10;
		return out;
	}
	bool operator==(const Monom& v) const
	{
		bool res = 1;
		if (degree != v.degree && coef != v.coef)
			res = 0;
		return res;
	}
	bool operator!=(const Monom& v) const
	{
		return !(*this == v);
	}
	bool operator< (const Monom& v) const
	{
		bool res = 1;
		if (degree >= v.degree)
			res = 0;
		return res;
	}
	bool operator> (const Monom& v) const
	{
		bool res = 1;
		if (degree <= v.degree)
			res = 0;
		return res;
	}
};
class Polynom
{
public:
	List<Monom> Monoms;
	Polynom(std::string StP = "")
	{
		int j = 1;
		while (StP.size())
		{
			std::string SubString1;
			j = 1;
			while (j < StP.size() && StP[j] != '+' && StP[j] != '-')
				j++;
			SubString1 = StP.substr(0, j);
			StP.erase(0, j);
			//	std::cout << "SubStr " << SubString1 << std::endl;
			Monom tmp(SubString1);
			Monoms.push_back(tmp);
		}
		/*for (int i = 0; i < Monoms.GetSize(); i++)
		{
		std::cout << Monoms[i].coef << std::endl;
		std::cout << Monoms[i].degree << std::endl;
		}*/
		Monom x;
		/*for (int i = 0; i < Monoms.GetSize(); i++)
		{
		for (int j = i+1; j < Monoms.GetSize();j++)
		{
		if (Monoms[i].degree == Monoms[j].degree)
		{
		//	std::cout << Monoms[i].coef << "   " << Monoms[j].coef << std::endl;
		Monoms[i].coef += Monoms[j].coef;
		Monoms.Remove(j);
		}
		}
		}
		for (int i = 0; i < Monoms.GetSize(); i++)
		{
		for (j = Monoms.GetSize() - 1; j > i; j--)
		{
		if (Monoms[j - 1] > Monoms[j])
		{
		x = Monoms[j - 1];
		Monoms[j - 1] = Monoms[j];
		Monoms[j] = x;
		}
		}
		}*/
		Sort_and_summ_similar();
		/*	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
		for (int i = 0; i < Monoms.GetSize(); i++)
		{
		std::cout << Monoms[i].coef << std::endl;
		std::cout << Monoms[i].degree << std::endl;
		}
		*/
	}
	void Sort_and_summ_similar()
	{
		Monom x;
		for (int i = 0; i < Monoms.GetSize(); i++)
		{
			for (int j = i + 1; j < Monoms.GetSize(); j++)
			{
				if (Monoms[i].degree == Monoms[j].degree)
				{
					//	std::cout << Monoms[i].coef << "   " << Monoms[j].coef << std::endl;
					Monoms[i].coef += Monoms[j].coef;
					Monoms.Remove(j);
				}
			}
		}
		for (int i = 0; i < Monoms.GetSize(); i++)
		{
			for (int j = Monoms.GetSize() - 1; j > i; j--)
			{
				if (Monoms[j - 1] > Monoms[j])
				{
					x = Monoms[j - 1];
					Monoms[j - 1] = Monoms[j];
					Monoms[j] = x;
				}
			}
		}
	}
	Polynom(const Polynom& P)
	{
		Monoms = P.Monoms;
	}
	Polynom& operator=(const Polynom& V)
	{
		Monoms = V.Monoms;
		return *this;
	}
	Polynom operator*(double x)
	{
		Polynom Res("");
		Res.Monoms = Monoms;
		for (int i = 0; i < Res.Monoms.GetSize(); i++)
		{
			//	std::cout << std::endl << i << std::endl;
			Res.Monoms[i].coef *= x;
		}
		Res.Sort_and_summ_similar();
		return Res;
	}
	Polynom operator*(Polynom& P)
	{
		Polynom Res;
		MIFL<Monom> i(Monoms.GetHead());
		MIFL<Monom> j(P.Monoms.GetHead());
		while (i != 0)
		{
			while (j != 0)
			{
				Monom temp;
				if ((((*i).degree % 10 + (*j).degree % 10) >= 10) || (((*i).degree / 10 % 10 + (*j).degree / 10 % 10) >= 10) || (((*i).degree / 100 % 10 + (*j).degree / 100 % 10) >= 10))
				{
					throw "Ne ny tut slishkom bolshya stepen";
				}
				temp.degree = (*i).degree + (*j).degree;
				temp.coef = (*i).coef * (*j).coef;
				Res.Monoms.push_back(temp);
				j++;
			}
			j = P.Monoms.GetHead();
			i++;
		}
		Res.Sort_and_summ_similar();
		return Res;
	}
	Polynom operator+(Polynom& P)
	{
		Polynom Res;
		MIFL<Monom> i(Monoms.GetHead());
		MIFL<Monom> j(P.Monoms.GetHead());
		while ((i != 0) && (j != 0))
		{
			if ((*i).degree < (*j).degree)
			{
				Res.Monoms.push_back(*i);
				i++;
			}
			else if ((*i).degree >(*j).degree)
			{
				Res.Monoms.push_back(*j);
				j++;
			}
			else
			{
				Monom temp;
				temp.coef = (*i).coef + (*j).coef;
				temp.degree = (*i).degree;
				Res.Monoms.push_back(temp);
				i++;
				j++;
			}
		}
		return Res;
	}
	Polynom operator-(Polynom& P)
	{
		return *this + ((-1)*P);
	}
	friend Polynom operator*(double x, Polynom& P)
	{
		return P * x;
	}
	bool operator==(const Polynom& p) const
	{
		return (Monoms == p.Monoms);
	}
	friend std::ostream& operator<<(std::ostream &out, Polynom &P)
	{
		MIFL<Monom> i(P.Monoms.GetHead());
		while (i != 0)
		{
			Monom temp;
			temp.coef = (*i).coef;
			temp.degree = (*i).degree;
			if (temp.coef > 0)
				out << "+";
			out << temp;
			i++;
		}
		out << std::endl;
		return out;
	}
};
bool ITSFC(std::string S)
{
	int status = 0;
	bool res = 1;
	int point_count = 0;
	int x_count = 0;
	int y_count = 0;
	int z_count = 0;
	for (int i = 0; i < S.size(); i++)
	{
		//	std::cout << status;
		if (status == 0)
		{
			if (S[i] >= 48 && S[i] <= 57)
				status = 1;
			else if (S[i] == '-')
				status = 1;
			else if (S[i] == 'X')
			{
				x_count++;
				status = 2;
			}
			else if (S[i] == 'Y')
			{
				y_count++;
				status = 2;
			}
			else if (S[i] == 'Z')
			{
				z_count++;
				status = 2;
			}
			else if (i == S.size())
				status = 9;
			else
			{
				status = 10;
			}
		}
		else if (status == 1)
		{
			if (S[i] == 'X')
			{
				x_count++;
				status = 2;
			}
			else if (S[i] == 'Y')
			{
				y_count++;
				status = 2;
			}
			else if (S[i] == 'Z')
			{
				z_count++;
				status = 2;
			}
		}
		else if (status == 2)
		{
			if (S[i] == '^')
				status = 3;
			else
				status = 10;
		}
		else if (status == 3)
		{
			if (S[i] >= 48 && S[i] <= 57)
			{
				if (S[i + 1] == '-' || S[i + 1] == '+')
				{
					i++;
					status = 4;
				}
				else if (S[i + 1] == 'X' || S[i + 1] == 'Y' || S[i + 1] == 'Z')
					status = 1;
				else if (i == S.size() - 1)
				{
					status = 9;
				}
				else
					status = 10;
			}
			else
				status = 10;
		}
		else if (status == 4)
		{
			if (S[i] >= 48 && S[i] <= 57)
				status = 1;
			else if (S[i] == 'X')
			{
				x_count++;
				status = 2;
			}
			else if (S[i] == 'Y')
			{
				y_count++;
				status = 2;
			}
			else if (S[i] == 'Z')
			{
				z_count++;
				status = 2;
			}
			else
			{
				status = 10;
			}
		}
		else
			status = 10;
		//	std::cout << " " << status << std::endl << std::endl;
	}
	if (status == 10)
		res = 0;
	return res;
}
class NamedPoly : public Polynom
{
public:
	std::string Name;
	NamedPoly(std::string _Name = "A", std::string _Poly = "2X^2") : Polynom(_Poly)
	{
		Name = _Name;
	}
	bool operator==(const NamedPoly& p) const
	{
		return ((Monoms == p.Monoms) && (Name == p.Name));
	}
	friend std::ostream& operator<<(std::ostream &out, const NamedPoly &NP)
	{
		out << NP.Name << "          " << (Polynom)NP << std::endl;
		return out;
	}
};
#endif