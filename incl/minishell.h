/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-car <bede-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:58:57 by ddiniz            #+#    #+#             */
/*   Updated: 2023/09/06 12:27:03 by bede-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// allowed libraries
# include "../lib/libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define READ_END 0 
# define WRITE_END 1
# define OPER_APPEND 1
# define OPER_WRITE 2
# define OPER_PIPE 3

typedef struct s_box {
	int	pipeone[2];
	int	pipetwo[2];
	char	**cat;
	char	**sort;
	char	**tail;
} t_box ;

char	**str_parse(char *exp_input);

// EXECUTION FUNCTIONS
int	cmd_run(char *root, char *input);
int	cmd_run_pipe(int cmdid);
int	cmd_run_redirect(void);

t_box	*box_create();

# endif
