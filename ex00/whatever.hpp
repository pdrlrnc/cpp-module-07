/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 14:16:12 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 14:16:12 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_H
#define WHATEVER_H

template <typename T>
void swap(T& a, T& b)
{
	T temp = a;

	a = b;
	b = temp;
}

template <typename T>
T min(T a, T b)
{
	return (a < b) ? a : b;
}

template <typename T>
T max(T a, T b)
{
	return (a > b) ? a : b;
}

#endif
