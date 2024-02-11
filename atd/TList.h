#include "stdafx.h"

#pragma once

UTIL_BEGIN_NAMESPACE

template <class _T>
class TList : public IBaseLinkedList<_T>
{
	typedef typename IBaseLinkedList<_T>::template TNode<_T> TNode;
	class Iterator;

private:
	bool add_node(TNode* left_node, _T data) override;
	bool del_node(TNode* previous_before_victim) override;

	[[maybe_unused]] _T pop() override { return _T(); }
	[[maybe_unused]] bool is_exists(_T data) { return false; }

	std::function<void()> _fnCallback_display = nullptr;

public:
	explicit TList();
	explicit TList(std::initializer_list<_T> init_list);
	~TList();

	TList(const TList&) = default;

	_T& operator[](const int) = delete;

	bool pop_front() override;
	bool push_front(const _T data) override;
	void clear() override;
	void display() override;
	bool insert_after(const _T find_data, const _T insert_data) override;

	bool pop_back();
	bool push_back(const _T data);
	bool insert_before(const _T find_data, const _T insert_data);
	bool remove_by(const _T find_data);
	bool set_display_fn(std::function<void()> fn_to_display);
	void clear_display_fn();

	Iterator begin() const;
	Iterator end() const;
};

#pragma region("List Iterator")
template <class _T>
class TList<_T>::Iterator
{
private:
	friend class TList<_T>;

protected:
	TList::TNode* _node;
	const TList* _list;

public:
	Iterator() : _list(nullptr), _node(nullptr)
	{}

	Iterator(const TList* list, TList::TNode* node) : _list(list), _node(node)
	{}

	_T& operator*()
	{
		return this->_node->_data;
	}

	bool operator==(const Iterator& it) const
	{
		return (this->_list == it._list) && (this->_node == it._node);
	}

	bool operator!=(const Iterator& it) const
	{
		return !(*this == it);
	}

	Iterator& operator++()
	{
		if (this->_node != nullptr)
		{
			this->_node = this->_node->_ptrNext;
		}

		return *this;
	}

	Iterator next() const
	{
		return this->_node != nullptr ? Iterator(this->_list, this->_node->_ptrNext) : *this;
	}
};
#pragma endregion

template <class _T>
TList<_T>::TList()
{
	this->init();
}

template<class _T>
TList<_T>::TList(std::initializer_list<_T> init_list)
{
	this->init();

	for (auto it = init_list.begin(); it != init_list.end(); ++it)
	{
		this->push_back(*it);
	}
}

template <class _T>
TList<_T>::~TList()
{
	this->clear();
}

template<class _T>
bool TList<_T>::add_node(TNode* left_node, _T data)
{
	try
	{
		// Теперь новая нода указывает на следующий 
		// элемент относительно предыдущего индекса.
		// Т.е. мы передали указатель на следующий элемент нашей новой ноде
		TNode* new_node = new TNode(data, left_node->_ptrNext); // *(второй параметр это указатель на следующий элемент)

		// Теперь предыдщуая нода указывает на новую ноду
		left_node->_ptrNext = new_node;
		// В итоге получается prev -> new_node -> old_node_with_this_index

		this->_size++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<class _T>
bool TList<_T>::del_node(TNode* previous_before_victim)
{
	try
	{
		TNode* victim = previous_before_victim->_ptrNext;

		previous_before_victim->_ptrNext = victim->_ptrNext; // !!

		delete victim;

		this->_size--;

		return true;
	}
	catch (...)
	{
		return false;
	}
}

template <class _T>
bool TList<_T>::pop_front()
{
	if (this->_size > 0)
	{
		TNode* temp = this->_ptrHead;
		this->_ptrHead = this->_ptrHead->_ptrNext;
		delete temp;
		this->_size--;

		return true;
	}
	else
	{
		return false;
	}
}

template <class _T>
bool TList<_T>::pop_back()
{
	if (this->_size <= 1)
	{
		return this->pop_front();
	}
	else
	{
		// Идём к предпоследнему
		TNode* current_node = this->_ptrHead;
		for (size_t i = 0; i < (this->_size - 1) - 1; i++)
		{
			current_node = current_node->_ptrNext;
		}

		return this->del_node(current_node);
	}
}

template <class _T>
bool TList<_T>::push_back(const _T data)
{
	try
	{
		if (this->_size == 0)
		{
			this->_ptrHead = new TNode(data);
		}
		else
		{
			// Берём головную ноду, чтобы найти последнюю
			TNode* current_node = this->_ptrHead;

			// Пробегаемся по нодам, проверяя следующий элемент ноды на null
			while (current_node->_ptrNext != nullptr)
			{
				// перемещаем текущую ноду на следующую
				current_node = current_node->_ptrNext;
			}

			current_node->_ptrNext = new TNode(data);
		}

		// Увеличиваем размер коллекции
		this->_size++;

		return true;
	}
	catch (...)
	{
		return false;
	}
}

template <class _T>
bool TList<_T>::push_front(const _T data)
{
	try
	{
		TNode* old_head = this->_ptrHead;
		this->_ptrHead = new TNode(data, old_head); // Вернёт новую ноду с указателем на старый head
		this->_size++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<class _T>
bool TList<_T>::insert_before(const _T find_data, const _T insert_data)
{
	if (this->_size <= 0)
	{
		return false;
	}

	TNode* before_node = this->_ptrHead;

	if (before_node->_data == find_data)
	{
		return this->push_front(insert_data);
	}
	else
	{
		while (before_node->_ptrNext->_data != find_data)
		{
			before_node = before_node->_ptrNext;

			if (before_node->_ptrNext == nullptr) return false;
		}

		return this->add_node(before_node, insert_data);
	}
}

template<class _T>
bool TList<_T>::insert_after(const _T find_data, const _T insert_data)
{
	if (this->_size <= 0)
	{
		return false;
	}

	TNode* current_node = this->_ptrHead;

	while (current_node->_data != find_data)
	{
		if (current_node->_ptrNext == nullptr) return false;

		current_node = current_node->_ptrNext;
	}

	return this->add_node(current_node, insert_data);
}

template<class _T>
bool TList<_T>::remove_by(const _T find_data)
{
	TNode* prev_node = this->_ptrHead;

	if (prev_node->_data == find_data)
	{
		return this->pop_front();
	}
	else
	{
		while (prev_node->_ptrNext->_data != find_data)
		{
			prev_node = prev_node->_ptrNext;

			if (prev_node->_ptrNext == nullptr) return false;
		}

		return this->del_node(prev_node);
	}
}

template<class _T>
bool TList<_T>::set_display_fn(std::function<void()> fn_to_display)
{
	this->_fnCallback_display = fn_to_display;

	return static_cast<bool>(fn_to_display);
}

template<class _T>
void TList<_T>::clear_display_fn()
{
	this->_fnCallback_display = nullptr;
}

template <class _T>
void TList<_T>::clear()
{
	while (this->_size != 0)
	{
		this->pop_front();
	}
}

template<class _T>
void TList<_T>::display()
{
	if (this->_fnCallback_display != nullptr)
	{
		this->_fnCallback_display();
	}
}

template<class _T>
TList<_T>::Iterator TList<_T>::begin() const
{
	return Iterator(this, this->_ptrHead);
}

template<class _T>
TList<_T>::Iterator TList<_T>::end() const
{
	TNode* last_node = this->_ptrHead;

	while (last_node->_ptrNext != nullptr)
	{
		last_node = last_node->_ptrNext;
	}

	return Iterator(this, last_node).next();
}

UTIL_END_NAMESPACE