#include "TList.h"

#pragma once

template<class _T>
TList<_T>::TList()
{
	this->_size = 0;
	this->_ptrHead = nullptr;
}

template<class _T>
TList<_T>::~TList()
{

}

template<class _T>
size_t TList<_T>::size()
{
	return this->_size;
}

template<class _T>
void TList<_T>::push_back(_T data)
{
	if (this->_ptrHead == nullptr)
	{
		this->_ptrHead = new TNode<_T>(data);
	}
	else
	{
		// Берём головную ноду, чтобы найти последнюю
		TNode<_T>* current_node = this->_ptrHead;

		// Пробегаемся по нодам, проверяя следующий элемент ноды на null
		while (current_node->_ptrNext != nullptr)
		{
			// перемещаем текущую ноду на следующую
			current_node = current_node->_ptrNext;
		}

		current_node->_ptrNext = new TNode<_T>(data);
	}

	// Увеличиваем размер листа
	this->_size++;
}

template<class _T>
void TList<_T>::push_front(_T data)
{
}

template<class _T>
void TList<_T>::insert_in(int index)
{

}

template<class _T>
void TList<_T>::remove_at(int index)
{
}

