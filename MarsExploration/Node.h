#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node
{
	T* data;
	int key;
	Node<T>* next;
public:
	Node()
	{
		next = NULL;
		key = -1;
	}
	Node(T* d, int k = -1)
	{
		data = d;
		next = NULL;
		key = k;
	}
	void setData(T* d)
	{
		// Must overlooad(=) at user-defined classes "Copy Constructor".
		data = d;
	}
	void setKey(int k)
	{
		key = k;
	}
	void setNext(Node<T>* n)
	{
		next = n;
	}
	T* getData()
	{
		return data;
	}
	int getKey()
	{
		return key;
	}
	Node<T>* getNext()
	{
		return next;
	}
};