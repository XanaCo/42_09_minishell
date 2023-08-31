/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:16 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 22:50:24 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define END 0
# define TMP 1
# define USER "ancolmen"
# define POSTE "paul-f4Br8s1"
# define COLOR_START "\033[1:4;93m"
# define COLOR_END "\033[0m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/src/libft.h"
# include "structures.h"

extern unsigned char	g_error_value;

/*ENVIRONMENT*/
void	ft_copy_env(t_mini *shell, char *envp[]);
int		ft_strchr_pos(const char *s, char c);
void	ft_lstadd_front_env(t_env **lst, t_env *new);
void	ft_lstdel_env(t_env **env, char *to_del);
char	*get_var_env(t_mini *shell, char *word);
int		valid_export(char *str);
char	*ft_find_var(t_mini *shell, char *to_find);
void	get_shlvl(t_mini *shell);

/*LEXING*/
char	*get_tk(t_mini *shell);
t_token	peek_tk(t_mini *shell);
t_token	give_tk(char *token);

/*PARSING*/
t_tree	*parsing(t_mini *shell, char *line);
t_tree	*parse_data(t_mini *shell);
t_tree	*parse_exec(t_mini *shell);
t_tree	*parse_redir(t_mini *shell);

/*TREE*/
t_tree	*create_branch(t_mini *shell, int tktype, char *token);
t_tree	*create_pipe_branch(t_mini *shell, t_tree *left, t_tree *right);
t_tree	*create_redir_branch(t_mini *shell, t_tree *left,
			int tktype, char *file_name);
t_tree	*create_exec_branch(t_mini *shell, char **cmd);
void	add_left_branch(t_tree **root, t_tree *branch);

/*HEREDOC*/
void	init_heredoc(t_mini *shell, t_tree *branch, char *key_word);
char	*get_endheredoc(t_mini *shell);
char	*get_hd_line(t_mini *shell, char *str);

/*QUOTES*/
int		check_unclosed_quotes(const char *line);
int		quote_flag(int flag, char c);
char	*get_squotes(t_mini *shell);
char	*get_dquotes(t_mini *shell);

/*UTILS*/
char	**add_cmd_arg(t_mini *shell, char **cmd, char *arg);
char	**get_cmd(t_mini *shell, char **cmd, char *arg);
char	*get_word(t_mini *shell);
int		is_redir(t_token tktype);
int		is_word(t_token tktype);
int		pos_str(char *str, char c);

/*EXEC*/
void	execution_time(t_mini *shell, t_tree *node);
void	main_process_exec(t_mini *shell, t_tree *node);
void	multi_process_exec(t_mini *shell, t_tree *node);
void	exec_cmd(t_mini *shell, t_tree *node);
void	prepare_execve(t_mini *shell, t_tree *node);

/*PIPES*/
void	create_pipes(t_mini *shell, t_tree *node);
void	close_all_pipes(t_mini *shell);
void	first_process(t_mini *shell, t_tree *node);
void	middle_process(t_mini *shell, t_tree *node, int i);
void	last_process(t_mini *shell, t_tree *node);
void	wait_for_all(t_mini *shell);
void	check_child_return(int wstatus);

/*REDIRECTIONS*/
void	check_redirections(t_mini *shell, t_tree *node);
void	redir_hd(t_mini *shell, t_tree *node);
void	redir_in(t_mini *shell, t_tree *node);
void	redir_out(t_mini *shell, t_tree *node);

/*BUILT-INS*/
int		check_built_in(t_tree *node);
int		check_parent_built_in(t_tree *node);
void	exec_built_in(t_mini *shell, t_tree *node);
int		bltn_cd(t_mini *shell, t_tree *node);
int		bltn_echo(t_mini *shell, t_tree *node);
int		bltn_env(t_mini *shell, t_tree *node);
int		bltn_exit(t_mini *shell, t_tree *node);
int		bltn_pwd(t_mini *shell, t_tree *node);
int		bltn_export(t_mini *shell, t_tree *node);
int		bltn_unset(t_mini *shell, t_tree *node);
void	export_to_env(t_mini *shell, void *data);

/*GARBAGE COLLECTOR*/
int		add_to_garbage(t_mini *shell, void *ptr, int id);
void	clean_all(t_mini *shell);
void	clean_tmp(t_mini *shell);
void	clean_garbage(t_mini *shell, int flag);
void	*ft_malloc_gc(t_mini *shell, int id, size_t size);
void	*ft_calloc_gc(t_mini *shell, int id, size_t nmemb, size_t size);
char	*ft_strdup_gc(t_mini *shell, int id, const char *s);
char	*ft_strjoin_gc(t_mini *shell, int id, char const *s1, char const *s2);
char	*ft_substr_gc(t_mini *shell, char const *s,
			unsigned int st, size_t len);

/*UTILS*/
char	*get_prompt(void);
void	print_title(void);

/*SIGNALS*/
void	init_parent_signals(void);
void	sigint_handler_parent(int signal);
int		signal_handler_child(int signal);
void	init_child_signals(void);
void	sigint_handler_child(int signal);
void	sigquit_handler_child(int signal);
void	init_hd_child_signal(void);
void	sigint_handler_hd(int signal);
void	sigquit_handler_hd(int signal);
t_mini	*locate_shell(t_mini *ptr, int status);
void	here_doc_signal(t_mini *shell);

/*EXIT*/
void	free_and_exit(t_mini *shell, char *str, int error);
void	error_handling_custom(char *str, int error);
int		cd_error_msg(int error);
void	end_program_failsafe(t_mini *shell);

/*DEBUG AND TESTING*/
void	print_garbage(t_mini *shell);
void	print_list(t_mini *shell);
void	print_node_for_exec(t_mini *shell, t_tree *node);
void	print_env(t_mini *shell);

/*PRINT TREE*/
char	*get_tk_str(int tktype);
void	print_tree(t_mini *shell, t_tree *root, int nb);

#endif
