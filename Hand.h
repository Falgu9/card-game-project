#ifndef __HAND__H__
#define __HAND__H__

#include "Linkedlist.h"

template <typename T>
class Hand
{
	friend std::ostream& operator<<(std::ostream& os, Hand const& hand)
	{
		return os << *(hand.hand);
	}
	
private:
	Linkedlist<T> *hand;

public:
	Hand();
	Hand(Hand& copy);
	Hand& operator=(Hand<T> const& copy);
	~Hand();

	T getHead() const;
	T getTail() const;
	T getAtIndex(int index) const;
	int getSize() const;

	void insertAtIndex(T data, int index);

	T removeAtIndex(int index);
	T remove(T data);

	bool isEmpty() const;
	bool contains(T data) const;
	int search(T data) const;

	T operator[](int index);
};

template <typename T>
Hand<T>::Hand() : hand(0)
{
	hand = new Linkedlist<T>();
}
template <typename T>
Hand<T>::Hand(Hand<T>& copy) : hand(0)
{
	hand = new Linkedlist<T>(*(copy.hand));
}

template <typename T>
Hand<T>& Hand<T>::operator=(Hand<T> const& copy)
{
	if(this != &copy)
	{
		delete hand;
		hand = new Linkedlist<T>(*(copy.hand));
	}

	return *this;
}

template <typename T>
Hand<T>::~Hand() { delete hand; }

template <typename T>
T Hand<T>::getHead() const
{
	return hand -> getHead();
}

template <typename T>
T Hand<T>::getTail() const
{
	return hand -> getTail();
}

template <typename T>
T Hand<T>::getAtIndex(int index) const
{
	return hand -> getAtIndex(index);
}

template <typename T>
int Hand<T>::getSize() const
{
	return hand -> getSize();
}

template <typename T>
void Hand<T>::insertAtIndex(T data, int index)
{
	hand -> insertAtIndex(data, index);
}

template <typename T>
T Hand<T>::removeAtIndex(int index)
{
	return hand -> removeAtIndex(index);
}

template <typename T>
T Hand<T>::remove(T data)
{
	return hand -> remove(data);
}

template <typename T>
bool Hand<T>::isEmpty() const
{
	return hand -> isEmpty();
}

template <typename T>
bool Hand<T>::contains(T data) const
{
	return hand -> contains(data);
}

template <typename T>
int Hand<T>::search(T data) const
{
	return hand -> search(data);
}

template <typename T>
T Hand<T>::operator[](int index)
{
	return hand -> operator[](index);
}

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Hand<T>& hand)
// {
// 	os << *(hand.hand);
// 	return os;
// }

#endif
