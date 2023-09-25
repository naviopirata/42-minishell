/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-car <bede-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:27:56 by bede-car          #+#    #+#             */
/*   Updated: 2023/09/24 21:49:09 by bede-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


#include "../incl/minishell.h"

char *prompt(void)
{
	char *input;
	input = readline("minihell$");
	add_history(input);
	return(input);
}



int main(int argc, char **argv)
{
	char *user_input;

	if (argc > 1 && argv)
		return(1);
	while(1)
	{
	user_input = prompt();
	ft_printf("%s\n", user_input);
	}
	return(0);
}
