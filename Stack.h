#ifndef __STACK__H__
#define __STACK__H__

#include <iostream>

template <class T>
class Stack
{
	friend std::ostream& operator<<(std::ostream& os, Stack const& stack)
	{
		for (int i = stack.size - 1; i >= 0; i--)
			os << *stack.stack[i];

		return os;
	}

private:
	int size;
	int capacity;
	T *stack;
	
	bool isFull() const;
	bool isEmpty() const;

public:
	Stack(int capacity);
	~Stack();
	Stack(Stack const& copy);
	Stack& operator=(Stack const& copy);

	Stack *push(T data);
	T pop();
};

template <class T>
Stack<T>::Stack(int capacity) : size(0), capacity(capacity), stack(0)
{
	stack = new T[capacity];
}

template <class T>
Stack<T>::~Stack()
{
	for(int i = 0; i < capacity; i++)
	{
		delete stack[i];
	}

	delete[] stack;
}

template <class T>
Stack<T>::Stack(Stack const& copy) : size(copy.size), capacity(copy.capacity), stack(0)
{
	stack = new T[capacity];

	for (int i = 0; i < size; i++) {
		stack[i] = copy.stack[i];
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack const& copy)
{
	if(this != &copy)
	{
		size = copy.size;
		capacity = copy.capacity;

		delete[] stack;

		stack = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			stack[i] = copy.stack[i];
		}
	}

	return *this;
}

template <class T>
Stack<T> *Stack<T>::push(T data)
{
	if(isFull())
		std::cout << "Error : Capacity has been reached." << std::endl;
	else
		stack[size++] = data;

	return this;
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty())
	{
		std::cout << "Error: Stack is empty." << std::endl;
		exit(-1);
	}
	
	return stack[--size];
}

template <class T>
bool Stack<T>::isFull() const { return size == capacity; }  

template <class T>
bool Stack<T>::isEmpty() const { return size == 0; }

#endif
