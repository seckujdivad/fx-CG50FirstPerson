#pragma once

#include <stdlib.h>

#ifndef _WIN32
#include <fxcg/heap.h>
#endif

#include "rvalue_refs.h"

template<typename T>
class ListNode
{
private:
	T m_value;
	ListNode<T>* m_child = nullptr;

public:
	inline ListNode(T value) : m_value(value) {};

	inline ListNode(const ListNode<T>& copy_from)
	{
		*this = copy_from;
	}

	inline ListNode<T>& operator=(const ListNode<T>& copy_from)
	{
		this->m_value = copy_from.m_value;
		if (copy_from.m_child == nullptr)
		{
			this->m_child = nullptr;
		}
		else
		{
			this->m_child = new ListNode<T>(*copy_from.m_child);
		}
		return *this;
	}

	inline ListNode(ListNode<T>&& move_from)
	{
		*this = move(move_from);
	}

	inline ListNode<T>& operator=(ListNode<T>&& move_from)
	{
		this->m_value = move_from.m_value;
		this->m_child = move_from.m_child;
		move_from.m_child = nullptr;
		return *this;
	}

	inline ~ListNode()
	{
		delete this->m_child;
	}

	inline ListNode<T>* GetChild() const
	{
		return this->m_child;
	}

	inline T& GetValue()
	{
		return this->m_value;
	}

	inline const T& GetValue() const
	{
		return this->m_value;
	}

	inline ListNode<T>* InsertAfter(T value)
	{
		ListNode<T>* new_child = new ListNode<T>(value);
		if (this->m_child == nullptr)
		{
			this->m_child = new_child;
		}
		else
		{
			new_child->m_child = this->m_child;
			this->m_child = new_child;
		}
		return this->m_child;
	}

#ifndef _WIN32
	inline void* operator new(size_t size)
	{
		return sys_malloc(size);
	}

	inline void operator delete(void* ptr)
	{
		if (ptr != nullptr)
		{
			sys_free(ptr);
		}
	}
#endif
};

template<typename T>
class List
{
private:
	ListNode<T>* m_child = nullptr;

public:
	inline List() {};

	inline List(const List& copy_from)
	{
		*this = copy_from;
	}

	inline List& operator=(const List& copy_from)
	{
		if (copy_from.m_child == nullptr)
		{
			this->m_child = nullptr;
		}
		else
		{
			this->m_child = new ListNode<T>(*copy_from.m_child);
		}
	}

	inline List(List&& move_from)
	{
		*this = move(move_from);
	}

	inline List& operator=(List&& move_from)
	{
		this->m_child = move_from.m_child;
		move_from.m_child = nullptr;
	}

	inline ~List()
	{
		delete this->m_child;
	};

	inline T& operator[](size_t index)
	{
		return this->At(index);
	}

	inline size_t Size()
	{
		if (this->m_child == nullptr)
		{
			return 0;
		}
		else
		{
			size_t size = 1;
			ListNode<T>* node = this->m_child;
			while (node != nullptr)
			{
				node = node->GetChild();
				size += 1;
			}
			return size;
		}
	}

	inline size_t Append(T value)
	{
		if (this->m_child == nullptr)
		{
			this->m_child = new ListNode<T>(value);
			return 0;
		}
		else
		{
			size_t index = 1;
			ListNode<T>* node = this->m_child;
			while (node->GetChild() != nullptr)
			{
				node = node->GetChild();
				index += 1;
			}

			node->InsertAfter(value);

			return index;
		}
	}

	inline ListNode<T>* GetChild() const
	{
		return this->m_child;
	}

	inline T& At(size_t index)
	{
		ListNode<T>* node = this->m_child;
		for (size_t i = 0; i < index; i++)
		{
			node = node->GetChild();
		}
		return node->GetValue();
	}

#ifndef _WIN32
	inline void* operator new(size_t size)
	{
		return sys_malloc(size);
	}

	inline void operator delete(void* ptr)
	{
		if (ptr != nullptr)
		{
			sys_free(ptr);
		}
	}
#endif
};