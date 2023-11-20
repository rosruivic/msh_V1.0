/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:30:00 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/15 18:13:11 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_status(t_msh *data, int error)
{
	if (error == END)
		data->error = END;
	else if (error == ERROR_NO_PATHS)
	{
		ft_putstr_fd("Error, no existe la variable PATH\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_CMD_NOT_EXISTS)
	{ // viene de ejecutar un comando externo (con fork)
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		error = NO_ERROR;
		exit (127);
	}
	else if (error == ERROR_NO_SUCH_FILE_OR_DIRECTORY)
	{ // cuando al env le pongo argumentos, por ejemplo, no lo piden
		ft_putstr_fd(data->cmd_lst->c_args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		error = NO_ERROR;
		data->exit_code = 127;
	}
	else if (error == ERROR_PID)
		ft_putstr_fd("Error PID\n", 2);
}

/**
 * @brief  **  ERRORS GENERATED BY BUILTIN 'CD'  **
 *    (it's not necessary to handly-manipulate data->exit here)
 * @param data 
 * @param error 
 */
void	ft_error_cd(t_msh *data, int error)
{
	if (error == ERROR_CHDIR_FAILURE)
	{
		ft_putstr_fd("msh: cd: ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		error = NO_ERROR;
		data->exit_code = 127;
	}
	else if (error == ERROR_CHDIR_OLDPWD_NOT_SET)
	{
		ft_putstr_fd("msh: cd: OLDPWD not set\n", 2);
		error = NO_ERROR;
		data->exit_code = 1;
	}
	else if (error == ERROR_CHDIR_HOME_NOT_SET)
	{
		ft_putstr_fd("msh: cd: HOME not set\n", 2);
		error = NO_ERROR;
	}
}

/**
 * @brief   ** IN CASE OF EXECUTE 'MINISHELL' WITH ARGMTS **
 * 
 * @param argv_1 
 * @param error 
 */
void	ft_error_start(char *argv_1, int error)
{
	if (error == ERROR_START_NO_SUCH_FILE_OR_DIRECTORY)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(argv_1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	ft_error_signal(int error)
{
	if (error == ERROR_SIGACTION_FAILURE)
	{
		ft_putstr_fd("Sigaction failure\n", 2);
		exit(EXIT_FAILURE);
	}
}
