#pragma once
#include  <iostream>
/**
 * \brief
 * \tparam T : it is basically the data member of the node class
 *			   using ADT
 */
template<class T>
class node
{
public:
	node();
	node(node<T> * next, T data);
	T data;
	node<T> * next;
	~node();

	/**
	 * \brief
	 * \param first : first object to be swapped
	 * \param second: second object to be swapped
	 * 	Making the swap function, a friend. So, it can use the data elements
	 * 	of the object and closes as the namespace closes. Its is being used
	 * 	in the copy-swap idiom
	 */
	friend void swap(node& first, node& second) noexcept(true);

	/**
	 * \brief
	 * \param temp : Here temp is being passed by copy because we are using the
	 *				 copy-swap idiom which is basically. Copying the contents of
	 *				 the given objects before they change. This idiom is used to
	 *				 avoid any kind of exception and object corruption.
	 * \return
	 */
	node<T>& operator=(node<T> temp);
};

//Default Constructor
template <class T>
node<T>::node() : next(nullptr)
{
}

//Parameterized Constructor
template <class T>
node<T>::node(node<T>* next, T data) : next(nullptr)
{
	this->data = data;
	this->next = next;
}

//swap function which is being used in copy-swap idiom
template <class T>
void swap(node<T>& first, node<T>& second) noexcept(true)
{
	using std::_Has_ADL_swap_detail::swap;
	swap(first.data, second.data);
	swap(first.next, second.next);
}

//Default destructor
template <class T>
node<T>::~node() = default;

//a safe copy constructor
template <class T>
node<T>& node<T>::operator=(node<T> temp)
{
	swap(*this, temp);
	return *this;
}