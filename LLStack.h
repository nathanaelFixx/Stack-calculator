//____________________
//Nathanael Fixx
//CSS 342 - Project 3
//17 hours
//Cygwin
//____________________

//____________________________________________________________
//This class allows for the creation of stack objects. The
//user can set stack objects equal to each other. The client 
//can also push data onto the list, remove data from the list
//check the data at the top of the list, empty the list, and 
//check the size of a list.
//____________________________________________________________
#ifndef LLStack_H
#define LLStack_H
#include <stdexcept>

template<class Type>

class LLStack
{
public:
	//__________________
	//Constructors
	//__________________
	LLStack();
	LLStack(const LLStack & stk);
	
	//__________________
	//Operator Equals
	//__________________
	LLStack<Type> & operator = (const LLStack<Type> & rhs);
	
	//_________________________
	//Standard Stack Functions
	//_________________________
	void push(const Type & newItem);
	void pop();
	Type & top() const throw (std::logic_error);
	bool empty() const;
	int size() const;
	
	//_________________
	//Destructors
	//_________________
	virtual ~LLStack();

	
private:
//______________________
//Node class for stack
//______________________

	struct Node {
		Node * next;
		Type element; //data is stored here
	};
	
	Node * head;
	int counter;
};

#endif
