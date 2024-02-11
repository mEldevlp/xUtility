#pragma once

#include <iostream>
#include <functional>

#define EXIT_SUCCES 0
#define EXIT_FAILURE 1

#define UTIL_BEGIN_NAMESPACE namespace UTIL {
#define UTIL_END_NAMESPACE }

#define MAX_STACK_SIZE 128

UTIL_BEGIN_NAMESPACE

template <class _T>
class IBaseLinkedList
{
protected:
	template <class _T>
	class TNode
	{
	public:
		_T _data;
		TNode* _ptrNext;
		TNode(_T data = _T(), TNode* ptrNext = nullptr)
		{
			this->_data = data;
			this->_ptrNext = ptrNext;
		};
	};

	TNode<_T>* _ptrHead;
	size_t _size;

protected:
	void init();
	virtual bool add_node(TNode<_T>* left_node, _T data) = 0;
	virtual bool del_node(TNode<_T>* victim) = 0;

public:
	virtual ~IBaseLinkedList() = default;

	bool is_empty();
	size_t size();

	virtual _T pop() = 0;
	virtual bool pop_front() = 0;
	virtual bool push_front(_T data) = 0;
	virtual bool insert_in(_T data, size_t index) = 0;
	virtual void clear() = 0;
	virtual void display() = 0;
	virtual bool is_exists(_T data) = 0;
};

template<class _T>
inline void IBaseLinkedList<_T>::init()
{
	this->_size = 0;
	this->_ptrHead = nullptr;
}

template<class _T>
inline bool IBaseLinkedList<_T>::is_empty()
{
	return this->_size == 0;
}

template<class _T>
inline size_t IBaseLinkedList<_T>::size()
{
	return this->_size;
}

UTIL_END_NAMESPACE