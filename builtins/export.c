#include "../builtins.h"

static int	check_args(char **to_export, t_tab *tabs)
{
	int	j;
	int	error_count;

	if (to_export[0] && !to_export[1])
		return (printf("taille de exp %d\n", len_env(tabs->exp)), display(tabs->exp), EXIT_FAILURE);
	error_count = 0;
	j = 1;
	while (to_export[j])
	{
		if (!((to_export[j][0] >= 'a' && to_export[j][0] <= 'z') ||
			(to_export[j][0] >= 'A' && to_export[j][0] <= 'Z') ||
				to_export[j][0] == '_'))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(to_export[j], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			error_count++;
		}
		j++;
	}
	if (error_count > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**updated_to_export(t_tab *tabs, int index)
{
	char	**new_to_export;
	int		i;

	i = 0;
	new_to_export = malloc(sizeof(char *) * 3);
	new_to_export[0] = malloc(2);
	new_to_export[0][0] = 'u';
	new_to_export[0][1] = '\0';
	new_to_export[1] = malloc(ft_strlen(tabs->exp[index]) + 1);
	if (tabs->exp[index])
	{
		while (tabs->exp[index][i] != '=' && tabs->exp[index][i] != '\0')
		{
			new_to_export[1][i] = tabs->exp[index][i];
			i++;
		}
	}
	new_to_export[1][i] = 0;
	new_to_export[2] = NULL;
	display(new_to_export);
	return (new_to_export);
}

int	execute_builtin_export(t_tab *tabs, char **to_export)
{
	int		index[4];
	char	**cpy_env_ex;
	char	**cpy_exp_ex;

	if (check_args(to_export, tabs))
		return (EXIT_FAILURE);
	index[0] = len_env(tabs->env);
	index[3] = len_env(tabs->exp);
	cpy_env_ex = cpy_env_extend(tabs->env, to_export);
	cpy_exp_ex = cpy_env_extend(tabs->exp, to_export);
	if (!cpy_env_ex || !cpy_exp_ex)
		return (EXIT_FAILURE);
	index[1] = 1;
	while (to_export[index[1]])
	{
		index[2] = 0;
		// printf("on trouve ou bien %d\n", found_export_name_with_value(tabs->exp, to_export[index[1]]));
		if ((to_export[index[1]][0] == '_' && !to_export[index[1]][1]) || (to_export[index[1]][0] == '_' && to_export[index[1]][1] == '=') || found_name(tabs->exp, to_export[index[1]]) != -1)
		{
			index[1]++;
			continue ;
		}
		// printf("on trouve ou bien %d\n", found_export_name_with_value(tabs->exp, to_export[index[1]]));
		else if (found_export_name_with_value(tabs->exp, to_export[index[1]]) != -1)
		{
			// printf("ca passe ou bien\n");
			// printf("on trouve ou bien %d\n", found_export_name_with_value(tabs->exp, to_export[index[1]]));
			// execute_builtin_unset(tabs, &to_export[index[1]]);
			execute_builtin_unset(tabs, updated_to_export(tabs, found_export_name_with_value(tabs->exp, to_export[index[1]])));
			// execute_builtin_export(tabs, &to_export[index[1]++]);
			// free_2d_tab(&cpy_env_ex);
			// cpy_env_ex = NULL;
			free_2d_tab(&cpy_exp_ex);
			cpy_exp_ex = NULL;
			// printf("abort avant ou aps \n\n");
			cpy_env_ex = cpy_env_extend(tabs->env, to_export);
			cpy_exp_ex = cpy_env_extend(tabs->exp, to_export);
			// display(cpy_exp_ex);
			// printf("\n\n\n\n\n\n\n\n\n\n");
			index[0] = len_env(tabs->env);
			index[3] = len_env(tabs->exp);
			// printf("ca passe ou bien\n");
			cpy_exp_ex[index[3]++] = ft_strdup_export(to_export[index[1]], 0, 0);
			cpy_env_ex[index[0]++] = ft_strdup(to_export[index[1]]);
			// printf("taille apres la copie %d et valeur de index %d\n\n\n", len_env(tabs->exp), index[1]);
		}
		else
		{
			while (to_export[index[1]][index[2]])
			{
				if (to_export[index[1]][index[2]] == '=')
					break ;
				index[2]++;
			}
			if (to_export[index[1]][index[2]] == '=')
				cpy_env_ex[index[0]++] = ft_strdup(to_export[index[1]]);
			cpy_exp_ex[index[3]++] = ft_strdup_export(to_export[index[1]], 0, 0);
		}
		cpy_env_ex[index[0]] = 0;
		cpy_exp_ex[index[3]] = 0;
		index[1]++;
		tabs->env = cpy_env_ex;
		tabs->exp = cpy_exp_ex;
	}
	// tabs->env = cpy_env_ex;
	// tabs->exp = cpy_exp_ex;

	return (EXIT_SUCCESS);
}

// int	main(int ac, char **ag, char **env)
// {
// 	int	y;

// 	y = 0;
// 	if (!execute_builtin_export(&ag, &env, ag))
// 	{	
// 		for (int i = 0; env[i] != NULL; i++)
// 			printf("%s\n", env[i]);
// 		printf("\nenv au dessus\n\n\n\n\n\n\n\n\n\nexport en dessous\n\n");
// 		for (int i = 0; ag[i] != NULL; i++)
// 			printf("%s\n", ag[i]);
// 	}
// 	return 0;
// }