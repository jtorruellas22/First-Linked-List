#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;
template <typename T> class LinkedList {
public:
	// Nested Class
	class Node
	{
	public:
		Node* next;
		Node* prev;
		T data;
		Node(T value);
	};

	// Constructors
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();


	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;
	

	// Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;


	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	//Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	bool operator==(const LinkedList<T>& rhs) const;

private:
	unsigned int node_count;
	Node* head;
	Node* tail;
};
#endif


// Behavior Definitions
template<class T> void LinkedList<T>::PrintForward() const
{
	Node* current = head;
	while (current) {
		cout << current->data << endl;
		current = current->next;
	}

}

template<class T> void LinkedList<T>::PrintReverse() const
{
	Node* current = tail;
	while (current) {
		cout << current->data << endl;
		current = current->prev;
	}

}

template<class T> void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	Node* newNode = head;
	while (newNode != node)
		newNode = newNode->next;
	while(newNode)
	{
		cout << newNode->data << endl;
		newNode = newNode->next;
	}
}

template<class T> void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	Node* newNode = tail;
	while (newNode != node)
		newNode = newNode->prev;
	while (newNode)
	{
		cout << newNode->data << endl;
		newNode = newNode->prev;
	}
}

// Accessors Definitions
template<class T> unsigned int LinkedList<T>::NodeCount() const
{
	return node_count;
}

template<typename T>inline void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	Node* newNode;
	newNode = head;
	for (unsigned int i = 0; i < node_count; i++)
	{
		T x = newNode->data;
		if (x == value)
		{
			outData.push_back(newNode);
		}
		newNode = newNode->next;
	}
}

template<typename T> const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* newNode;
	newNode = head;
	for (unsigned int i = 0; i < node_count; i++)
	{
		if (newNode->data == data)
		{
			return newNode;
		}
		else
			newNode = newNode->next;
	}
	return nullptr;
}

template<typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* newNode;
	newNode = head;
	for (unsigned int i = 0; i < node_count; i++)
	{
		if (newNode->data == data)
		{
			return newNode;
		}
		else
			newNode = newNode->next;
	}
	return nullptr;
}

template<typename T>
inline const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{

	if (index >= node_count)
		throw out_of_range("Error! Index out of range!");


	Node* current;
	current = head;

	for (unsigned int i = 0; i < index; i++)
		current = current->next;

	return current;
}

template<typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{

	if (index >= node_count)
		throw out_of_range("Error! Index out of range!");

	Node* current;
	current = head;

	for (unsigned int i = 0; i < index; i++)
		current = current->next;

	return current;
}

template<typename T>inline typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template<typename T>
inline const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template<typename T> typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template<typename T>
inline const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

// Insertion Definitions
template<class T> void LinkedList<T>::AddHead(const T& data)
{
	Node* newHead = new Node(data);
	newHead->next = head;

	if (head != nullptr)
		head->prev = newHead;

	head = newHead;

	if (tail == nullptr)
		tail = head;

	node_count += 1;

}

template<class T> void LinkedList<T>::AddTail(const T& data)
{
	Node* newTail = new Node(data);
	newTail->prev = tail;

	if (tail != nullptr)
		tail->next = newTail;

	tail = newTail;

	if (head == nullptr)
		head = tail;

	node_count += 1;

}

template<class T> void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (int i = count; i-- > 0; ) {
		AddHead(data[i]);
	}
}

template<class T> void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}

template<typename T>
inline void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	if (node == tail) {
		AddTail(data);
		return;
	}
	Node* newNode = new Node(data);
	newNode->prev = node;
	newNode->next = node->next;
	node->next = newNode;
	node_count += 1;
}

template<typename T>
inline void LinkedList<T>::InsertBefore(Node* node, const T& data)
{	
	if (node == head) {
		AddHead(data);
		return;
	}

	Node* newNode = new Node(data);
	newNode->next = node;
	newNode->prev = node->prev;
	node->prev->next = newNode;
	node->prev = newNode;
	node_count += 1;

}

template<typename T>
inline void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	if (index == node_count)
	{
		AddTail(data);
		return;
	}
	Node* current = GetNode(index);
	InsertBefore(current, data);
	
}

// Removal Definitions
template<typename T> bool LinkedList<T>::RemoveHead()
{
	Node* newNode = head;
	head = newNode->next;
	if (newNode->next != nullptr)
		head->prev = nullptr;
	delete newNode;
	node_count -= 1;
	if (node_count == 0) {
		head = nullptr;
		tail = nullptr;
		return false;
	}
		
	return true;
}

template<typename T> bool LinkedList<T>::RemoveTail() 
{
	Node* newNode = tail;
	tail = newNode->prev;
	if (newNode->prev != nullptr)
		tail->next = nullptr;
	delete newNode;
	node_count -= 1;
	if (node_count == 0) {
		head = nullptr;
		tail = nullptr;
		return false;
	}
	return true;
}

template<typename T> unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int removed = 0;
	Node* current = head;
	Node* remove;
	while(current)
	{
		if(current->data == data)
		{
			current->next->prev = current->prev;
			current->prev->next = current->next;
			removed += 1;
			node_count -= 1;
			remove = current;
			current = current->next;
			delete remove;
		}
		else
			current = current->next;
	}
	
	return removed;
}

template<typename T> bool LinkedList<T>::RemoveAt(unsigned int index)
{
	if (index >= node_count)
		return false;
	if (index == node_count) {
		node_count -= 1;
		return RemoveTail();
	}
	if (index == 0) {
		node_count -= 1;
		return RemoveHead();
	}
	Node* newNode = GetNode(index);

	newNode->prev->next = newNode->next;
	newNode->next->prev = newNode->prev;

	if (newNode->prev == nullptr)
		head = newNode->next;

	if (newNode->next == nullptr)
		tail = newNode->prev;

	delete newNode;
	node_count -= 1;
	return true;
}

template <class T>
void LinkedList<T>::Clear() {
	// clear old memory
	Node* current = head;
	while (current != nullptr) {
		head = head->next;
		delete current;
		current = head;
	}

	// reset memembers to default state
	node_count = 0;
	head = nullptr;
	tail = nullptr;
}

//Operators
template<typename T>
inline const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index >= node_count)
	{
		throw out_of_range("Error! Index out of range!");
	}

	return GetNode(index)->data;
}

template<class T> T& LinkedList<T>::operator[](unsigned int index)
{
	if (index >= node_count)
	{
		throw out_of_range("Error! Index out of range!");
	}
	return GetNode(index)->data;
}

template<class T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	// clear any old allocations
	Clear();

	//copy data into linked list
	for (unsigned int i = 0; i < rhs.NodeCount(); i++) {
		AddTail(rhs[i]);
	}

	return *this;
}

template<typename T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	if (head->data == rhs.head->data and tail->data == rhs.tail->data and node_count == rhs.node_count)
		return true;
	return false;
}

// Contructors/Destructors
template<class T> LinkedList<T>::LinkedList()
{
	node_count = 0;
	head = nullptr;
	tail = nullptr;
}

template<class T> LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	node_count = 0;
	head = nullptr;
	tail = nullptr;

	for (unsigned int i = 0; i < list.NodeCount(); i++) {
		AddTail(list[i]);
	}

}

template<class T> LinkedList<T>::~LinkedList()
{
	Clear();
}

// Node class
template<typename T>
inline LinkedList<T>::Node::Node(T value)
{
	data = value;
	next = nullptr;
	prev = nullptr;
}