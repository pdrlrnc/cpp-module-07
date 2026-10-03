/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 14:15:56 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 14:15:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

#include <iostream>
#include <string>
#include <cctype>

int main(void)
{
	Array<int> empty;

	Array<int> values(5);
	unsigned int i = 0;
	while (i < values.size())
	{
		values[i] = i;
		i++;
	}

	std::cout << "values: " << values << std::endl;

	return 0;
}



