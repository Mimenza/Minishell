/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/29 12:02:01 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/Libft/libft.h"
# include "../libs/GNL/get_next_line.h"
# include <stdint.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define SIMPLE 0
# define DOUBLE 1

# define START 0
# define END 1
# define CUR 2
# define SIZE 3
# define QUOTES 4

# define FIRST 0	//first flag
# define RTF 1		//redirection to flag
# define RFF 2		//redirection from flag
# define HDF 3		//here doc flag
# define APPF 4		//append flag
# define EF 5		//error flag
# define FD 6		//file descriptor


//05_LOOK_FOR_DOLARS_2
# define AFTER 0
# define BEFORE 1
//READ_TABLE
# define F_D 0
# define OPTION_INDEX 1
# define STATE 2
# define T_TYPE 3
# define ACTION 4
# define NEXT_STATE 5
# define NBR_RED 6
# define STATE_LIST 0
# define C_STATE 1
//STEP_UTILS_2
# define I 0
# define MAX 1
//10_ACTIONS
# define TOKEN_1 0
# define TOKEN_2 1
# define TOKEN_3 2
# define TOKEN_4 3
# define START_STACK 4
# define JOIN_TOKEN 5
// # define STATES_LIST 0
// # define CURRENT_STATE 1

// # define STEP 0
// # define C_STEP 1

// # define DEF_OPT 0
// # define AVAIL_OPT 1

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SPACE_M 32
# define REDUCE -1
# define WORD 0
# define RED_TO 1
# define RED_FROM 2
# define DLESS 3
# define DGREAT 4
# define PIPE 5
# define PIPE_SEQUENCE 100
# define SIMPLE_CMD 101
# define CMD_NAME 102
# define CMD_WORD 103
# define CMD_PREFIX 104
# define CMD_SUFFIX 105
# define IO_REDIRECT 106
# define IO_FILE 107
# define FILENAME 108
# define IO_HERE 109
# define HERE_END 110
# define READ 0
# define WRITE 1

# ifndef ALLOW_WRITE
#  define ALLOW_WRITE 0
# endif

//Options of a state
typedef struct s_options
{
	int			index;
	int			state;
	int			t_type;
	int			action;
	int			next_state;
	int			nbr_red;
	struct s_options	*next;
}				t_options;

//State
typedef struct	s_states
{
	int					state;
	struct s_options	*options;
	struct s_states 	*next;
}				t_states;

//Tokens of the analyzer
typedef struct s_token
{
	char			*data;			//data of the token
	int				type;			//type of the token
	struct s_token	*next;			//ptr to the next token

	struct s_token	*left;			//once reduced ptr to the left token
	struct s_token	*right;			//once reduced ptr to the right token
	struct s_token	*middle;		//once reduced ptr to the middle token
}				t_token;

//Steps of the analyzer
typedef struct	s_step
{
	int				step_nbr;			//nbr of the current step
	int				state_nbr;			//nbr of the current state
	struct s_states *state;			//ptr to the current state
	int				option_nbr;			//nbr of the current option of the state
	struct s_token	*tree_stack;		//ptr to the tree/ stack
	struct s_token	*input;				//ptr to the input

	struct s_step	*next;			//ptr to the next step
	struct s_step	*prev;			//ptr to the prev step
}				t_step;


//main struct for the input
typedef struct s_input
{
	char				**token_raw;
	struct s_var_list	*ent_var;
	struct s_states		*parsing_table;
	struct s_var_parsed_table	*parsed_table;
	int							allow_input;
	char				*input;
}				t_input;

//linked list for the enviroment variables
typedef struct	s_var_list
{
	char				*name;
	int					is_printed;
	char				*content;
	struct	s_var_list 	*next;
	int					is_env;
}				t_var_list;

typedef struct s_var_parsed_table
{
	char						**env;
	char						**cmd_splited; //primera linea 'echo' segunda linea 'patata' cat -e 
	char						*cmd;
	char						*path; //nombre del comando con la ruta 'users/bin/ls'
	int							fd_in;
	int							fd_out; 
	int							fd_error;
	pid_t						pid;
	struct	s_var_parsed_table	*next;
	struct	s_var_parsed_table	*prev;
}				t_var_parsed_table;

//MAIN
static int	print_history(char *line, t_input **struct_input);

//MAIN_UTILS
void	beyond_pipe(char *input, size_t *control);
char	*join_line(char *input, size_t *control, t_input **struct_input);
int		add_space(char **input, char c, t_input **struct_input);
int		open_quotes(char *input);

//HISTORY
static int	check_history_file(void);
void		load_history(void);
void		save_history(char	*input);

//SIGNAL
static void	signal_handler(int	signal);
void		signal_receiver(void);

//VARIABLES
static void	print_env(char	**env);
void		save_env(char **envp, t_input **struct_input);

//LOOK FOR EQUALS
void		ft_print_var(t_input *input);
static void	ft_add_var(t_var_list **list, char *name, char *content,int id);
int			ft_var_found(t_var_list **list, char *name, char *content);
void		ft_trim_var_equal(char *token, int equal_pos, t_var_list **variable_list,int id);
int			ft_look_4_equal(char const *token, t_var_list **variable_list,int id);

//LOOK FOR DOLLARS 1
void		del_char(char **cadena, int position);
int			ft_find_variable(char *match_var_name, t_var_list **variable_list, char **content);
void		expand_var_ent(t_var_parsed_table **table, t_input **struct_input);

//LOOK FOR DOLLARS 2
int			ft_trim_var_dollar(char *token, t_var_list **variable_list, char **content, int index);
// void		ft_trim_var_dollar_aux(char *token, char **before, char **after, char **match_var_name, int index);
void		ft_trim_var_dollar_aux(char *token, char *(*src)[3], char **var_name, int index);
int			ft_look_4_dollar(char const *token, t_var_list **variable_list, char **content);
void		ft_look_4_d_aux(char **content, int i, int max, t_var_list **v_list);

//READ TABLE
void		print_options_for_state(t_states *states_list, int state_number);
void		read_table(t_input **struct_input);


//ANALYZER
void		create_tokens_analyzer(t_input **struct_input);
void		print_token_list(t_token *tokens);
void		add_last_token(t_token *last_token, t_token **tokens);

//STEPS
int			start_anaylizer(t_input **struct_input, t_token *input_token);
void		print_cmd_contents(t_var_parsed_table **head);
void 		remove_quotes_aux(char **cmd_ptr);

//STEPS UTILS 1
int			find_state(t_states *states_list, int state_number, t_states **state);
int			stack_size(t_token *stack);
t_options	*find_option(t_states *state, int token_type);
void		add_step(t_input *struct_input, t_options *options, t_token *tree_stack, t_token *input_token, t_step **c_step);
t_token		*last_node_stack(t_token *stack);

//STEPS UTILS 2
void		ret_to_prev(t_step **c_step);
void		remove_quotes_aux(char **cmd_ptr);
void		remove_quotes(t_var_parsed_table **head);
void		config_parsed_table(t_var_parsed_table **current);
t_step		*init_first_step(t_input **struct_input, t_token *input_token);

//ACTIONS
void		apply_action(t_options *options, t_step **c_step, t_token *c_token, int *end_flag);

//READ_TREE
void		walk_tree(t_var_parsed_table **table, t_token *tree);
void		read_tree(t_token *tree, t_var_parsed_table **table_node, int mode);
t_var_parsed_table	*init_parsed_table(t_var_parsed_table *prev_table);

//READ TREE UTILS
int		*reset_statics(int mode, int *array, t_var_parsed_table **table_node);
void	init_append_tree(t_token *tree, int *first_time, t_var_parsed_table **table_node);
void	set_fds(int *array, t_var_parsed_table **table_node);
void	create_table(t_token *tree, t_var_parsed_table **table_node);
int		*set_flags(t_token *tree, int *array);

//BASH SPLIT
static void	ignore_separator(char const *s, int *control, int *i);
static	int	ft_count(char const *s, char c, int *control);
static void	freeall(char **splits);
static int	check_str(char **str, int j);
char		**ft_bash_split(char const *s, char c, int *control);

//TOKENIZATION
int			tokenization(char *input, t_input **struct_input);

//PIPEX_UTILS
int		ft_verify_cmd(char **paths, t_var_parsed_table *cmd, t_input **env);
int		ft_close_pipes(int fd[2]);
int		relative_path(t_var_parsed_table *cmd, t_input **env);
int		ft_here_doc(char *end, int fd);
void	free_here_doc(char *delimiter, char *output, char *line, int *outfile);

//BUILT_IN
void	ft_echo(char **args, int fd);
int		ft_pwd(t_input **env);
int		get_path_utils(char **path, char **route, char *tmp, char *args);
int		get_path(char *args, t_input **env);
int		ft_cd(char **args, t_input **env);

char				*ft_get_path_line(char **env);
void				ft_son_process(t_var_parsed_table *arg, t_input **struct_input, t_step *step);
t_var_parsed_table	*father_process(t_var_parsed_table *cmd, int fd[2]);
int					ft_is_built_in(t_var_parsed_table	*cmd_list);
void				ft_make_process(t_var_parsed_table *cmd, int fd[2], t_input **struct_input, t_step *step);
void				file_permissions(char *name, int type);
int					pipex(t_input **struct_input, t_step *step);
char				*ft_getenv(t_var_list **list, char *name);
int					ft_strcmp(const char *s1, const char *s2);

//BUILT_IN_UTILS
void	ft_empty_export_utils(t_var_list *current, t_var_list **env, t_var_list	*name, int *size);
void	ft_empty_export(t_var_list **env);
int		ft_export(char	*var, t_input **struct_input);
void	ft_eexit(char **arg, t_input **struct_input, t_step *step);
void	ft_unset(char *name, t_input **struct_input);

//BUILT_IN_UTILS2
void	add_var_utils(char *name, char *content, t_var_list	*current, t_var_list *new);
void 	add_var(char *name, t_var_list **env, char *content);
int		ft_built_in2(t_var_parsed_table	*cmd_list, t_input **struct_input, int (*control)[2], t_step *step);
int		ft_built_in1(t_var_parsed_table	*cmd_list, t_input **struct_input, int (*control)[2], t_step *step);
int		ft_is_built_in(t_var_parsed_table	*cmd_list);

//FREE
void		free_all(t_input *struct_input, char *history);
void		free_steps(t_step *steps);
void		free_double(char **double_ptr);
void		free_parsed_table(t_var_parsed_table **table);

//ERROR
void		print_error(int id, char *args, t_input **struct_input);

//CMD_HANDLE
int			cmd_handle(t_var_parsed_table **cmd_list, t_input **env, t_step *step);
static char **cmd_handle_1(t_var_parsed_table *cmd, t_input **env, char **path_env);
static int 	cmd_handle2(t_var_parsed_table *cmd, t_input **env, int *control);
static int 	cmd_handle3(t_var_parsed_table *cmd, char *path_env, t_input **env, char **posible_paths);



#endif