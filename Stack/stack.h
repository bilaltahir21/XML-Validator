#pragma once
#include "node.h"

/**
 * \brief
 * \tparam T : Here T is an ADT
 */
template<class T>
class stack
{
public:
	/**
	 * \brief : It is a default constructor for stack class
	 *			which is just initializing its 'top_' member
	 *			as 'nullptr' for a good start of the stack.
	 */
	stack();
	/**
	 * \brief : It is a default destructor which is using default method.
	 */
	~stack();
	/**
	 * \brief
	 * \return : Making it a 'const' to make sure that it does not change
	 *			 any value. As it is a boolean which is returning if the
	 *			 'stack' is empty.
	 */
	bool isEmpty() const;
	/**
	 * \brief
	 * \param val : This variable is the main thing which is being stored
	 *				its an ADT. So, it can be of any data type.
	 *				This 'push' function always stores the coming element
	 *				at the top of the stack. 'top_' always points to the
	 *				value 'val' which is given as the input value.
	 *
	 *  logic:Its handling both of the cases, one in which the
	 *				stack is empty. So, the 'top_' points to the new value
	 *				and the new node points to the nullptr.
	 *				Similarly, in the second case is executed when teh stack
	 *				is initialized with something.
	 */
	void push(const T& val);
	/**
	 * \brief
	 *
	 * logic:
	 *				It is handling both of the cases, one in which the stack is
	 *				empty so it only displays the message that "Stack is empty"
	 *				In the other case it is deleting the node being pointed by
	 *				the 'top_'. And, it is making the 'top_' to point to the next
	 *				of the node being deleted.
	 * \param val : this is the value which is being changed with the value
	 *				which is being deleted(popped from the stack)
	 * \return :	This return statement is simply returning the value which
	 *				is being deleted.
	 */
	bool pop(T & val);
	/**
	 * \brief
	 * \return : It is just returning the to element data member of the stack.
	 */
	T top();
	/**
	 * \brief : It is printing the value of the stack from top to the bottom.
	 */
	void print() const;
private:
	node<T> * top_;	// it is the main thing which is representing top of the stack.

	node<T> * topX;
	node<T> * top1;

};

//Default constructor
template <class T>
stack<T>::stack(): topX(nullptr), top1(nullptr)
{
	top_ = nullptr;
}

//Destructor
template <class T>
stack<T>::~stack()
{
	top1 = topX;
	while (top1!=nullptr)
	{
		top1 = topX->next;
		delete topX;
		topX = top1;
		top1 = top1->next;
	}
	delete top1;
	topX = nullptr;
}

//Returning if the stack is empty
template <class T>
bool stack<T>::isEmpty() const
{
	return (top_ == nullptr);
}

//storing the data in the stack in LIFO
template <class T>
void stack<T>::push(const T& val)
{
	node<T>* holder = new node<T>(nullptr, val);
	if (isEmpty())
	{
		holder->next = nullptr;
	}
	holder->next = top_;
	top_ = holder;
}

//making the data to pop out of the stack
template <class T>
bool stack<T>::pop(T& val)
{
	if (isEmpty())
	{
		std::cout << "\nStack is empty\n";
		return false;
	}
	node<T>* holder = top_;
	val = holder->data;
	top_ = holder->next;
	delete holder;
	return true;
}

//returning the data element at the top
template <class T>
T stack<T>::top()
{
	return (top_->data);
}

//print data from top to bottom
template <class T>
void stack<T>::print() const
{
	if (isEmpty())
	{
		std::cout << "\nThere is nothing to display.\n";
	}
	else
	{
		node<T>* temp = top_;
		while (temp->next != nullptr)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << temp->data;
	}
}
