#include "minishell.h"
#include "builtins.h"

int	execute_builtins(char **argv, t_tab *tabs, t_redirections *redirect)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (execute_builtin_echo(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (execute_builtin_pwd());
	if (!ft_strcmp(argv[0], "exit"))
		return (execute_builtin_exit(argv, tabs, redirect));
	if (!ft_strcmp(argv[0], "unset"))
		return (execute_builtin_unset(tabs, argv));
	if (!ft_strcmp(argv[0], "export"))
		return (execute_builtin_export(tabs, argv));
	if (!ft_strcmp(argv[0], "env"))
		return (execute_builtin_env(tabs->env));
	if (!ft_strcmp(argv[0], "cd"))
		return (execute_builtin_cd(argv, tabs));
	return (0);
}
