/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-car <bede-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:58:57 by ddiniz            #+#    #+#             */
/*   Updated: 2023/09/24 21:16:23 by bede-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// allowed libraries
# include "../lib/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// local libraries
# include "./defines.h"
# include "./prototypes.h"
//#define READ_END 0 
// #define WRITE_END 1

// char	**str_parse(char *exp_input);
// int	cmd_run(char *root, char *input);
#endif
