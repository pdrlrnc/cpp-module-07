/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:46:11 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 15:46:12 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename T>
class Array
{
	private:
		unsigned int _length;
		T* _data;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array& other);
		~Array();
		Array& operator=(const Array& other);
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;
		unsigned int size() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array);

#include "Array.tpp"

#endif
