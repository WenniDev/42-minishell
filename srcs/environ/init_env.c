//	NORM
//		-missing header

#include "spash_environ.h"
#include "spash_error.h"
#include "spash.h"

void	new_environ(t_data *data)
{
	char *path;

	data->env = ft_split(DEFAULT_ENV, ENV_SEP);
	if (!data->env)
		(sperr(data, MFAIL, "new_environ", 139), exit_prg(data));
	path = ft_strdup(DEFAULT_PATH);
	if (!path)
		(sperr(data, MFAIL, "new_environ", 139), exit_prg(data));
	free(data->env[0]);
	data->env[0] = path;
}

void	copy_environ(t_data *data)
{
	int i;
	int env_size;

	i = 0;
	env_size = 0;
	while (__environ && __environ[env_size])
		env_size++;
	data->env = (char **)ft_calloc(env_size + 1, sizeof (char *));
	if (!data->env)
		(sperr(data, MFAIL, "copy_environ", 139), exit_prg(data));
	while (i < env_size)
	{
		data->env[i] = ft_strdup(__environ[i]);
		if (!data->env[i])
			(sperr(data, MFAIL, "copy_environ", 139), exit_prg(data));
		i++;
	}
}

void	init_env(t_data *data)
{
	if (!__environ || !*__environ)
		new_environ(data);
	else
		copy_environ(data);
	if (!data->env)
		(sperr(data, MFAIL, "init_env", 139), exit_prg(data));
	__environ = data->env;
}