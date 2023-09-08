/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-car <bede-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:58:57 by ddiniz            #+#    #+#             */
/*   Updated: 2023/08/24 20:16:20 by bede-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0 
#define WRITE_END 1

char	**str_parse(char *exp_input);
int	cmd_run(char *root, char *input);
#endif
