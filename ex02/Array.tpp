/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:51:16 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 15:51:17 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_T
#define ARRAY_T

template <typename T>
Array<T>::Array() : _length(0), _data(NULL) {}

template <typename T>
Array<T>::Array(unsigned int n) : _length(n), _data(new T[n]) {}

template <typename T>
Array<T>::Array(const Array&other) : _length(other.length), _data(new T[other.length])
{
	unsigned int i = 0;

	while (i <_length)
	{
		_data[i] = other[i]; 
		i++;
	}
}


template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}


template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		_length = other._length;
		delete[] _data;
		_data = new T[_length];
		unsigned int i = 0;
		while (i < _length)
		{
			_data[i] = other._data[i];
			i++;
		}
	}

	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _length)
		throw std::out_of_range("out of bounds");
	return _data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _length)
		throw std::out_of_range("out of bounds");
	return _data[index];
}


template <typename T>
unsigned int Array<T>::size() const
{
	return _length;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array)
{
	for (unsigned int i = 0; i < array.size(); ++i)
			out << array[i] << " ";
	return out;
}


#endif
