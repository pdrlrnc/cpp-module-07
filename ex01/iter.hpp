/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:14:41 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 15:14:44 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_H
#define ITER_H

template <typename T>
void iter(T* arr, const int len, void(*f)(T&))
{
	if (!arr)
		return ;

	int i = 0;

	while (i < len)
		f(arr[i++]);
}

#endif
