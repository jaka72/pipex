/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaka <jaka@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 10:28:50 by jaka          #+#    #+#                 */
/*   Updated: 2021/11/25 16:50:45 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <stdio.h> 
# include <errno.h> 
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct data
{
	pid_t		pid1;
	pid_t		pid2;
	int			pipe_end[2];
	int			fd2;
	int			fd1;
	char		*command1;
	char		*command2;
	char		**cmd1;
	char		**cmd2;
	int			cmd1_is_local;
	int			cmd2_is_local;
	char		*infile;
	char		*outfile;
	char		*envp_path;
	char		*path_cmd1;
	char		*path_cmd2;
	char		**bin_all_paths_cmd1;
	char		**bin_all_paths_cmd2;
	int			cmd1_can_execute;
	int			cmd2_can_execute;
	int			exit_code;
	int			err;
}	t_data;

int		check_args_and_get_data(t_data *d, int argc, char *envp[],
			char *argv[]);
int		init_data_and_get_commands(char *argv[], t_data *d);
int		find_paths(char *envp[], t_data *d);
int		append_cmd1_to_all_paths(t_data *d);
int		append_cmd2_to_all_paths(t_data *d);
int		find_correct_path_of_cmd(t_data *d);
int		free_all(t_data *d, int exit_code);
void	exit_with_code(t_data *d);

#endif
