/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command_paths.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 15:22:23 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/10 18:34:24 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_and_free(char *s1, char const *s2)
{
	char	*newstr;

	if ((newstr = ft_strjoin(s1, s2)) == NULL)
		return (NULL);
	free(s1);
	return (newstr);
}

// APPEND CMD_1 TO END OF EACH PATH
int append_cmd1_to_all_paths(t_data *d)
{
    int i;

	i = 0;
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		if ((d->bin_all_paths_cmd1[i] = ft_strjoin_and_free(d->bin_all_paths_cmd1[i], d->cmd1[0])) == NULL)
		{
			perror("Append error 1\n"); // NOT NECESSARY
			free_all(d, 0);
		}
		i++;
	}
    return (0);
}

// APPEND CMD_2 TO END OF EACH PATH
int append_cmd2_to_all_paths(t_data *d)
{
    int i;
    
	i = 0;
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
		if ((d->bin_all_paths_cmd2[i] = ft_strjoin_and_free(d->bin_all_paths_cmd2[i], d->cmd2[0])) == NULL)
		{
			perror("Append error 2\n"); // NOT NECESSARY
			free_all(d, 0);
		}
		i++;
	}
    return (0);
}

int find_correct_path_of_cmd(t_data *d)
{
    int i;
//	int	err;

	i = 0;      //	FIND CORRECT PATH OF CMD_1
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		if (access(d->bin_all_paths_cmd1[i], X_OK) == 0)	// THIS DOSENOT NEED TO BE CHECKED, THE EXECVE
			d->path_cmd1 = d->bin_all_paths_cmd1[i];		// WILL LATER GIVE ERROR, IF PATH IS NOT CORRECT
		// if (err == -1)
		// {		// Probably this message desn't have to be displayed ,becase later it will
		// 	printf("err %d, errno %d\n", err, errno); // cause error when command will be called by execve
		// 	perror("  pipex error: The access() returned -1. Bash");
		// 	//free_all(d);
		// 	return (-1);
		// }
		i++;
	}
	if (d->path_cmd1 == NULL) // MAYBE THIS NOT NEEDED, BECAUSE IT HAS TO RETURN, WHEN 
	{							// THE REAL COMMAND RETURNS 127, WHEN IT IS NOT FOUND
		//d->path_cmd1 = "./nopath"; 	// NOT SURE IF THIS IS FUNCTIONAL, 
									//IT HAS TO HAVE SOME WRONG PATH INSTEAD OF NULL,
									// OTHERWISE THE EXEC RETURNS 0 INSTEAD OF 127
		//perror("pipex error: Command 1 not found; bash");
		//perror("");
	}
	i = 0;      //	FIND CORRECT PATH OF CMD_2
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
		if (access(d->bin_all_paths_cmd2[i], X_OK) == 0)
			d->path_cmd2 = d->bin_all_paths_cmd2[i];
		i++;	
	}
	if (d->path_cmd2 == NULL)
		perror("pipex error: Command 2 not found; bash");
    return (0);
}

// FIND PATHS IN ENVP[], AND SPLIT THEM INTO SEPARATE PATHS
int	find_paths(char *envp[], t_data *d)
{ 
	int i;
	
	i = 0;
	while (envp[i] != NULL)
	{	
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			d->envp_path = envp[i];
			d->bin_all_paths_cmd1 = ft_split(d->envp_path, ':');
			d->bin_all_paths_cmd2 = ft_split(d->envp_path, ':');
		}
		i++;
	}
	if (d->bin_all_paths_cmd1 == NULL || d->bin_all_paths_cmd2 == NULL)
	{
		perror("pipex error: The variable PATH not found in envp[]\n");
		free_all(d, 0);
		exit(0);
	}
	return (0);
}
