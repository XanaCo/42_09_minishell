/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:16 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 18:26:03 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define PARSING_STOPPER "|<>\'\""

typedef enum e_token
{
	TK_ERROR = -1,
	TK_WORD,
	TK_VENV,
	TK_PIPE,
	TK_EXEC,
	TK_INF,
	TK_SUP,
	TK_DINF,
	TK_DSUP,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_EOF,
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_op;
	char	*cmd_path;
}		t_cmd;

typedef struct s_tree
{
	t_token			tktype;
	char			*token;
	char			*file_name;
	t_cmd			exec;
	int				hd_fd[2];
	char			*key_w;
	t_list			*heredoc;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

typedef struct s_gcol
{
	void			*ptr;
	int				id;
	struct s_gcol	*next;
}	t_gcol;

typedef struct s_env
{
	void			*content;
	char			*var;
	char			*path;
	struct s_env	*next;
}	t_env;

typedef struct s_source
{
	char	*content;
	size_t	cur;
	size_t	len;
	int		error;
}	t_source;

typedef struct s_mini
{
	char		*prompt;
	t_source	line;
	t_tree		*tree;
	char		**path;
	char		**env_t;
	t_env		*env;
	int			shlvl;
	int			n_hd;
	int			hd_fd;
	int			hd_error;
	int			n_pipes;
	int			pipe[1024][2];
	int			pids[1024];
	int			wstatus;
	t_gcol		*gc;
	int			gc_id;
}	t_mini;

#endif
