/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:58:57 by ddiniz            #+#    #+#             */
/*   Updated: 2023/06/26 06:30:54 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <string.h>

typedef struct s_tree 
{
	int value;
	int count;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

/* AUXILIAR FUNCTIONS */
/* SIGNAL FUNCTIONS */
void	signals_init(void);
void	abstree_init(void);

#endif
