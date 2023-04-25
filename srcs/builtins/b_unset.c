//	NORM
//		-missing header

#include "spash_environ.h"
#include "spash_error.h"
#include "spash.h"

int get_env_index(char **env, char *var)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var) + 1) == '=')
			return (i);
		i++;
	}
	return (ERROR);
}

void	unset_var(t_data *data, char *var)
{
	int	i;
	int	j;
	int env_size;
	char **tmp_env;

	j = -1;
	i = get_env_index(data->env, var);
	if (i == ERROR)
		return ;
	env_size = 0;
	while (data->env && data->env[env_size])
		env_size++;
	tmp_env = (char **)ft_calloc(env_size, sizeof (char *));
	if (!tmp_env)
		return (sperr(data, MFAIL, "unset_var", 139));
	while (++j < i)
		tmp_env[j] = data->env[j];
	free(data->env[i]);
	while (j + 1 < env_size)
	{
		tmp_env[j] = data->env[j + 1];
		j++;
	}
	free(data->env);
	data->env = tmp_env;
	__environ = tmp_env;
}

int	b_unset(int argc, char **argv, void *ptr)
{
	int 	i;
	t_data	*data;

	i = 1;
	data = (t_data *)ptr;
	while (i < argc && argv[i])
	{
		unset_var(data, argv[i]);
		i++;
	}
	return (data->exit_status);
}
