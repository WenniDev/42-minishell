#include "minishell.h"
#include "minishell_builtins.h"

char	*get_dir(void);

void	set_prompt(t_data *msh)
{
	char	*prompt;
	char	*dir;
	char	*tmp;

	prompt = NULL;
	dir = get_dir();
	if (!dir)
		malloc_error();
	prompt = getenv("USER");
	prompt = ft_strjoin("\e[1;32m", prompt);
	if (!prompt)
		malloc_error();
	tmp = prompt;
	prompt = ft_strjoin(prompt, dir);
	free(tmp);
	free(dir);
	if (!prompt)
		malloc_error();
	tmp = prompt;
	if (msh->status)
		prompt = ft_strjoin(prompt, "\n\e[31m→ \e[0m");
	else
		prompt = ft_strjoin(prompt, "\n\e[32m→ \e[0m");
	free(tmp);
	if (!prompt)
		malloc_error();
	export_var("PS1", prompt, &msh->exec);
	free(prompt);
}

char	*get_dir(void)
{
	char	*dir;
	char	*dirpath;
	char	*ptr;
	size_t	len;

	len = 0;
	dirpath = getenv("PWD");
	ptr = dirpath + ft_strlen(dirpath);
	while (*ptr != '/')
	{
		ptr--;
		len++;
	}
	dir = ft_substr(dirpath, (unsigned int)(ptr - dirpath), len);
	if (!dir)
		malloc_error();
	dirpath = dir;
	dir = ft_strjoin("\e[1;34m", dir);
	free(dirpath);
	if (!dir)
		malloc_error();
	return (dir);
}
