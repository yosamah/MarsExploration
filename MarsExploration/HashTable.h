#pragma once
#include <iostream>


template <typename T, int size>
class HashTable
{
	// Creating array of Node pointers to store in each node pinter a pointer of data of type T and its key and the next node(pointer).
	// Using this to handle Collision inside the hash table.
	Node<T>* arr[size];
public:
	HashTable()
	{
		// initializing pointers of nodes to NULL.
		for (int i = 0; i < size; i++)
			arr[i] = NULL;
	}
	void insert(T* element, int key)
	{
		// Determine the chosen index of this key. 
		int index = key % size;
		// Creating pointer to store the element pointer and its key and the next ode as well/
		Node<T>* newPtr = new Node<T>(element);
		Node<T>* ptr = arr[index];
		newPtr->setKey(key);

		if (!arr[index])
		{
			// First Node with this index.
			arr[index] = newPtr;
			return;
		}
		// Collision occurs.
		while (ptr->getNext())
			ptr = ptr->getNext();
		ptr->setNext(newPtr);

	}
	bool remove(Node<T>*& temp, int key)
	{
		int index = key % size;
		// Checking if the key is found
		if (!arr[index])
			return false;
		Node<T>* ptr = arr[index];
		if (ptr->getKey() == key)
		{
			//Assigning the removed node to temp(sent by reference from outside the class)
			temp = ptr;
			arr[index] = ptr->getNext();
			return true;
		}
		while (ptr->getNext())
		{
			if (ptr->getNext()->getKey() == key)
			{
				temp = ptr->getNext();
				ptr->setNext(temp->getNext());
				temp->setNext(NULL);
				return true;
			}
			ptr = ptr->getNext();
		}
		//Key is not found
		return false;

	}

	bool search(Node<T>*& temp, int key)
	{
		int index = key % size;
		// Checking if the key is found
		if (!arr[index])
			return false;
		Node<T>* ptr = arr[index];
		if (ptr->getKey() == key)
		{
			//Assigning the node with chosen key to temp(sent by reference from outside the class)
			temp = ptr;
			return true;
		}
		while (ptr->getNext())
		{
			if (ptr->getNext()->getKey() == key)
			{
				temp = ptr->getNext();
				return true;
			}
			ptr = ptr->getNext();
		}
		//Key is not found
		return false;
	}
};