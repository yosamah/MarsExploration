#pragma once
#include <iostream>
#include "Node.h"


template <typename T>
class PriQ
{
private:
	Node<T>* Head;

public:
	//Constructor
	PriQ()
	{
		Head = NULL; //Amr Aho
	}

	//Function that enqueues the elemtents sorted according to the key
	bool enqueue(T* newEntry, const int& newKey)
	{
		//Creating the new node to be inserted 
		Node<T>* temp = new Node<T>(newEntry, newKey);
		Node<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == NULL || (temp->getKey() < Head->getKey()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		return true;
	}

	//Function the takes out elements out of the queue
	bool dequeue(T* frntEntry, int& frntKey)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = Head;
		frntEntry = Head->getData();
		frntKey = Head->getKey();
		Head = Head->getNext();

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;

		return true;

	}

	//Function that checks whether the queue is empty or not
	bool isEmpty()
	{
		return (Head == NULL);
	}

};