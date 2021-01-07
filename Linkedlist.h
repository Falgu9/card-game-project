#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class Linkedlist
{
	friend std::ostream &operator<<(std::ostream &os, Linkedlist const &linkedlist)
	{
		Node *current = linkedlist.head;
		for (int i = 0; i < linkedlist.size; i++)
		{
			// linkedlist must contain pointer to be correctly displayed in os
			os << *current->getData();
			current = current->getNext();
		}

		return os;
	}

private:
	class Node
	{
	private:
		T data;
		Node *next;

	public:
		Node(T data) : data(data), next(NULL) {}
		Node(Node const &copy) : data(copy.data)
		{
			if (copy.next != NULL)
				next = new Node(*(copy.next));
			else
				next = NULL;
		}
		Node &operator=(Node const &copy)
		{
			if (this != &copy)
			{
				data = copy.data;
				if (copy.next != NULL)
					next = new Node(*(copy.next));
				else
					next = NULL;
			}

			return *this;
		}
		void setNext(Node *next) { this->next = next; }
		void setData(T data) { this->data = data; }
		Node *getNext() { return next; }
		T getData() { return data; }
	};

	Node *head;
	Node *tail;
	int size;

	void insertAtHead(Node *node);
	void insertAtTail(Node *node);

	T removeAtHead();
	T removeAtTail();

public:
	Linkedlist();
	Linkedlist(Linkedlist<T> const &copy);
	Linkedlist<T> &operator=(Linkedlist<T> const &copy);
	~Linkedlist();

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
	void print() const;
};

template <typename T>
Linkedlist<T>::Linkedlist() : head(NULL), tail(NULL), size(0) {}

template <typename T>
Linkedlist<T>::Linkedlist(Linkedlist<T> const &copy) : head(NULL), tail(NULL), size(copy.size)
{
	if (copy.size == 1)
	{
		head = new Node(*(copy.head));
		tail = head;
	}

	if (copy.size > 1)
	{
		head = new Node(*(copy.head));
		tail = new Node(*(copy.tail));
	}
}

template <typename T>
Linkedlist<T> &Linkedlist<T>::operator=(Linkedlist<T> const &copy)
{
	if (this != &copy)
	{
		size = copy.size;
		delete head;
		delete tail;
		head = new Node(*(copy.head));
		tail = new Node(*(copy.tail));
	}

	return *this;
}

template <typename T>
Linkedlist<T>::~Linkedlist()
{
	Node *tmp = NULL;
	for (int i = 0; i < size; i++)
		removeAtIndex(0);
}

template <typename T>
T Linkedlist<T>::getHead() const
{
	return head->getData();
}

template <typename T>
T Linkedlist<T>::getTail() const
{
	return tail->getData();
}

template <typename T>
T Linkedlist<T>::getAtIndex(int index) const
{
	if (index >= size - 1)
		return tail->getData();

	Node *tmp = head;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->getNext();
	}

	return tmp->getData();
}

template <typename T>
int Linkedlist<T>::getSize() const { return size; }

template <typename T>
void Linkedlist<T>::insertAtIndex(T data, int index)
{
	Node *inserted = new Node(data);
	if (isEmpty())
	{
		head = inserted;
		tail = inserted;
	}
	else if (index == 0)
		insertAtHead(inserted);
	else if (index > size - 1)
		insertAtTail(inserted);
	else
	{
		Node *current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->getNext();
		}

		inserted->setNext(current->getNext());
		current->setNext(inserted);
	}

	size++;
}

template <typename T>
void Linkedlist<T>::insertAtHead(Node *node)
{
	if (head != NULL)
		node->setNext(head);
	head = node;
}

template <typename T>
void Linkedlist<T>::insertAtTail(Node *node)
{
	if (tail != NULL)
		tail->setNext(node);
	tail = node;
}

template <typename T>
T Linkedlist<T>::removeAtIndex(int index)
{
	T data;

	if (isEmpty() || index < 0 || index > size - 1)
		return NULL;
	else if (index == 0)
		data = removeAtHead();
	else if (index == size - 1)
		data = removeAtTail();
	else
	{
		Node *current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->getNext();
		}

		data = current->getNext()->getData();
		Node *removed = current->getNext();
		current->setNext(current->getNext()->getNext());
		delete removed;
	}

	size--;
	return data;
}

template <typename T>
T Linkedlist<T>::removeAtHead()
{
	if (isEmpty())
		return NULL;

	T data = head->getData();
	Node *removed = head;
	head = head->getNext();
	delete removed;

	return data;
}

template <typename T>
T Linkedlist<T>::removeAtTail()
{
	if (isEmpty())
		return NULL;

	Node *current = head;
	for (int i = 0; i < size - 2; i++)
	{
		current = current->getNext();
	}

	Node *removed = tail;
	current->setNext(NULL);
	tail = current;
	T data = removed->getData();
	delete removed;

	return data;
}

template <typename T>
T Linkedlist<T>::remove(T data)
{
	return removeAtIndex(search(data));
}

template <typename T>
int Linkedlist<T>::search(T data) const
{
	if (isEmpty())
		return -1;

	Node *current = head;
	for (int i = 0; i < size; i++)
	{
		if (current->getData() == data)
			return i;
		current = current->getNext();
	}

	return -1;
}

template <typename T>
bool Linkedlist<T>::isEmpty() const
{
	return (size == 0);
}

template <typename T>
bool Linkedlist<T>::contains(T data) const
{
	return (search(data) >= 0);
}

template <typename T>
T Linkedlist<T>::operator[](int index)
{
	Node *current = head;

	for (int i = 0; i < index; i++)
	{
		current = current->getNext();
	}

	return current->getData();
}

template <typename T>
void Linkedlist<T>::print() const
{
	Node *current = head;
	for (int i = 0; i < size; i++)
	{
		std::cout << current->getData() << std::endl;
		current = current->getNext();
	}
}

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Linkedlist<T>& list)
// {
// 	Linkedlist<T>::Node *current = NULL;

// 	for (int i = 0; i < list.size; i++)
// 	{
// 		os << *current->getData() << std::endl;
// 		current = current->getNext();
// 	}

// 	return os;
// }

#endif