//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash.h"
#include "libft.h"

void	subcmd(t_data *data, t_cmd *cmd, t_token *tk)
{
	char	*new_line;
	size_t	size;

	if (!cmd->subcmd_line)
		cmd->subcmd_line = (char *) ft_calloc(1, sizeof (char));
	if (!cmd->subcmd_line)
		(sperr(data, MFAIL, "subcmd", 2), exit_prg(data));
	size = ft_strlen(cmd->subcmd_line) + ft_strlen(tk->value) + 2;
	new_line = (char *) ft_calloc(size, sizeof (char));
	if (!new_line)
		(sperr(data, MFAIL, "subcmd", 2), exit_prg(data));
	ft_strlcat(new_line, cmd->subcmd_line, size);
	ft_strlcat(new_line, " ", size);
	ft_strlcat(new_line, tk->value, size);
	free(cmd->subcmd_line);
	cmd->subcmd_line = new_line;
}
