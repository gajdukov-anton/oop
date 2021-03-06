#pragma once

#include "CMyIterator.h"
#include "CMyRevIterator.h"
#include <string>
#include <iostream>
#include <memory>
#include <cassert>
#include <sstream>

template <typename T>
class CMyArray
{
public:

	CMyArray() = default;
	CMyArray(std::initializer_list<T> arr);
	CMyArray(const CMyArray& arr);
	CMyArray(CMyArray&& arr);
	CMyArray<T>& operator=(const CMyArray& other);
	CMyArray<T>& operator=(CMyArray && other);
	void Append(const T& newElement);
	const T& operator[](const size_t index) const;
	T& operator[](const size_t index);
	void GetAll() const;
	void Resize(const size_t newSize);
	size_t GetSize() const;
	size_t GetCapacity()const;
	void Clear();
	CMyIterator<T> Begin() const;
	CMyIterator<T> End() const;
	CMyRevIterator<T> RBegin() const;
	CMyRevIterator<T> REnd() const;
	~CMyArray();

private:

	void Copy(std::initializer_list<T> from, T* const begin, size_t size, T* & end)
	{
		end = begin;
		for (auto elem : from)
		{
			new (end)T(elem);
			++end;
		}
	}

	static void DeleteItems(T *begin, T *end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
	size_t m_length = 0;
};

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& arr)
{
	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_begin = RawAlloc(size);
		try
		{
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_endOfCapacity = m_end;
		}
		catch (...)
		{
			DeleteItems(m_begin, m_end);
			throw;
		}
	}
	m_length = static_cast<size_t>(m_end - m_begin);
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& arr)
	:CMyArray(arr)
{
	arr.Clear();
}

template <typename T>
CMyArray<T>::CMyArray(std::initializer_list<T> arr)
	:m_length(arr.size())
{
	m_begin = RawAlloc(m_length);
	Copy(arr, m_begin, m_length, m_end);
	m_endOfCapacity = m_end;
	m_length = static_cast<size_t>(m_end - m_begin);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray& other)
{
	if (std::addressof(other) != this)
	{
		CMyArray tmpCopy(other);
		std::swap(m_begin, tmpCopy.m_begin);
		std::swap(m_end, tmpCopy.m_end);
		std::swap(m_endOfCapacity, tmpCopy.m_endOfCapacity);

	}
	m_length = static_cast<size_t>(m_end - m_begin);
	return *this;
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator =(CMyArray && other)
{
	if (&other != this)
	{
		m_begin = nullptr;
		m_end = nullptr;
		m_endOfCapacity = nullptr;
		m_length = 0;
		std::swap(m_begin, other.m_begin);
		std::swap(m_end, other.m_end);
		std::swap(m_endOfCapacity, other.m_endOfCapacity);
		std::swap(m_length, other.m_length);
	}
	m_length = static_cast<size_t>(m_end - m_begin);
	return *this;
}

template <typename T>
void CMyArray<T>::Append(const T & value)
{
	if (m_end == m_endOfCapacity) 
	{
		size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

		auto newBegin = RawAlloc(newCapacity);
		T *newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			new (newEnd)T(value);
			++newEnd;
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newCapacity;
	}
	else
	{
		new (m_end) T(value);
		++m_end;
	}
	m_length = static_cast<size_t>(m_end - m_begin);
}

template <typename T>
const T& CMyArray<T>::operator[](const size_t index) const
{
	if (m_begin + index >= m_end)
	{
		throw std::out_of_range("index is out of range");
	}

	return *(m_begin + index);
}

template <typename T>
T& CMyArray<T>::operator[](const size_t index)
{
	if (index < m_length && m_length > 0)
		return  *(m_begin + index);
	else
		throw std::out_of_range("index is out of range");
}

template <typename T>
void CMyArray<T>::GetAll() const
{
	for (size_t i = 0; i <  m_length; i++)
		std::cout << i << ": " << *(m_begin + i) << ' ';
}

template <typename T>
void CMyArray<T>::Resize(const size_t newSize)
{
	if (newSize > GetCapacity())
	{
		auto newBegin = RawAlloc(newSize);
		T *newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);		
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newSize;
	}
	if (newSize < m_length)
	{
		DestroyItems(m_begin + newSize, m_end);
		m_end = m_begin + newSize;
	}
	if (newSize > m_length)
	{
		for (size_t i = 0; i < newSize - GetSize(); i++)
		{
			new (m_end) T();
			++m_end;
		}
	}
	m_length = static_cast<size_t>(m_end - m_begin);
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
	return m_length;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_endOfCapacity - m_begin;
}

template <typename T>
void CMyArray<T>::Clear()
{
	if (GetSize() != 0)
	{
		DeleteItems(m_begin, m_end);
		m_begin = nullptr;
		m_end = nullptr;
		m_endOfCapacity = nullptr;
		m_length = static_cast<size_t>(m_end - m_begin);
	}
}

template <typename T>
CMyIterator<T> CMyArray<T>::Begin() const
{
	return CMyIterator<T>(m_begin);
}

template <typename T>
CMyIterator<T> CMyArray<T>::End() const
{
	return CMyIterator<T>(m_end - 1);
}

template <typename T>
CMyRevIterator<T> CMyArray<T>::RBegin() const
{
	return CMyRevIterator<T>(m_end - 1);
}

template <typename T>
CMyRevIterator<T> CMyArray<T>::REnd() const
{
	return CMyRevIterator<T>(m_begin);
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

