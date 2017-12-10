//____________________
//Nathanael Fixx
//CSS 342 - Project 3
//17 hours
//Cygwin
//____________________

#include <iostream>
#include "LLStack.h"
#include <stdexcept>
using namespace std;

//_______________________
//Default Constructor
//_______________________
template<class Type>
LLStack<Type>::LLStack()
{
	head = NULL;
	counter = 0;
}

//_______________________
//Copy Constructor
//_______________________
template<class Type>
LLStack<Type>::LLStack(const LLStack & stk)
{
	counter = 0;
	*this = stk; //uses equal operator
}

//____________________________
//Overloading Operator Equals
//____________________________
template<class Type>
LLStack<Type>& LLStack<Type>::operator=(const LLStack<Type>& rhs)
{
	//checking if equal
	Node * lft = head;
	Node * rht = rhs.head;

	if (rht != NULL || lft != NULL) {
		while (rht == lft) {
			if (rht->next == NULL || lft->next == NULL)
				break;
			rht = rht->next;
			lft = lft->next;
		}
	}

	if (rht != NULL && lft != NULL) { //if the lists are the same, return

		if (rht->next == NULL && lft->next == NULL && counter > 1)
			return *this;
	}

	//deleting the left hand side of equation

	if (counter > 0) {
		Node * cur = head;
		Node * prev = head;
		while (cur != NULL) {
			prev = cur;
			cur = cur->next;
			delete prev;
			prev = NULL;
			counter--;
		}
	}

	//making the copy
	if (rhs.counter == 0) {
		head = NULL;
	}

	else if (rhs.counter == 1) {
		head = new Node(*rhs.head);
		counter++;
	}

	else {
		Node * oldList, *current, *prev;


		head = new Node(*rhs.head);
		prev = head;
		current = head->next;
		oldList = (rhs.head->next);
		counter++;

		while (oldList != NULL) {
			current = new Node(*oldList);
			prev->next = current;
			oldList = oldList->next;
			prev = prev->next;
			current = current->next;
			counter++;
		}
		prev->next = NULL;
	}
	return *this;
}

//___________________________________________
//Push
//
//Takes data and pushes it onto the top of
//the stack.
//___________________________________________
template<class Type>
void LLStack<Type>::push(const Type & newItem)
{
	
	//empty stack
	if (counter == 0) {
		Node * add = new Node;
		add->element = newItem;
		head = add;
		head->next = NULL;
		counter++;
	}

	else {
		Node * add = new Node;
		add->element = newItem;
		add->next = head;
		head = add;
		counter++;
	}
}

//___________________________________________
//Pop
//
//Deletes the top item of the stack
//___________________________________________
template<class Type>
void LLStack<Type>::pop()
{
	//empty stack
	if (counter == 0) {
		return;
	}
	
	//one item in stack
	if (counter == 1) {
		delete head;
		head = NULL;
		counter--;
		return;
	}

	else {
		Node * temp = head;
		head = head->next;
		delete temp;
		counter--;
	}

}

//_______________________________________________
//Top
//
//Returns the value of the top item in the stack
//_______________________________________________
template<class Type>
Type & LLStack<Type>::top() const throw(logic_error)
{
	//throw error if stack is empty
	if (counter == 0) {
		throw logic_error("Priority Not Found!");
	}
	

	return head->element;
}


//_____________________________________________
//Empty
//
//Informs the client whether or not the stack
//is empty.
//_____________________________________________
template<class Type>
bool LLStack<Type>::empty() const
{
	if (counter == 0)
		return true;
	else
		return false;
}

//______________________________________________
//Size
//
//Returns a count of the number of elements in 
//the stack.
//______________________________________________
template<class Type>
int LLStack<Type>::size() const
{
	return counter;
}

//_________________________
//Destructor
//_________________________
template<class Type>
LLStack<Type>::~LLStack()
{
	//empty stack
	if (counter == 0) {
		return;
	}

	//one item
	if (counter == 1) {
		delete head;
		head = NULL;
		return;
	}

	Node * current = head->next;
	Node * prev = head;

	while (current->next != NULL) {
		Node * temp = prev;
		current = current->next;
		prev = prev->next;
		delete temp;
		counter--;
	}
	delete current;
}


