/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/08 17:03:52 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/ioctl.h>
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
# define RES 2

# define START 0
# define END 1
# define CUR 2
# define SIZE 3
# define QUOTES 4
//READ_TREE
# define FIRST 0		//first flag
# define RTF 1			//redirection to flag
# define RFF 2			//redirection from flag
# define HDF 3			//here doc flag
# define APPF 4			//append flag
# define EF 5			//error flag
# define FD 6			//file descriptor
//05_LOOK_FOR_DOLARS_2
# define AFTER 0		//index for the after of the dolar sign
# define BEFORE 1		//index for the before of the dolar sign
//READ_TABLE
# define F_D 0			//index of the array for the fd value
# define OPTION_INDEX 1	//index of the array for option index
# define STATE 2		//index of the array for the state value
# define T_TYPE 3		//index pf the array with the token type value
# define ACTION 4		//index for the action, (shift, go or reduce)
# define NEXT_STATE 5	//index for the next state value
# define NBR_RED 6		//idex for the number of reduced tokens value
# define STATE_LIST 0	//index for all the states values
# define C_STATE 1		//index for the current state value
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
//14_BASH_SPLIT
# define I 0
# define J 1
# define START_ 2
# define END_ 3

# define FALSE 0
# define TRUE 1
# define ERROR -1

# define SPACE_M 32			//space code in ascii
# define REDUCE -1			//reduce action value
# define WORD 0				//simple token, any token thats not an operator
# define RED_TO 1			//simple token, operator '<'
# define RED_FROM 2			//simple token, operator '>'
# define DLESS 3			//simple token, operator '<<'
# define DGREAT 4			//simple token, operator '>>'
# define PIPE 5				//simple token, operator '|'
# define PIPE_SEQUENCE 100	//compound token, made with simple_cmd + pipe
# define SIMPLE_CMD 101		//compound token, cmd_prefix + cmd_name + cmd_suffix
# define CMD_NAME 102		//compound token, the cmd name
# define CMD_WORD 103		//compound token, 
# define CMD_PREFIX 104		//compound token, usually made with redirections
# define CMD_SUFFIX 105		//options or arguments of the cmd and redireccions
# define IO_REDIRECT 106	//made with the redirection operator + filename
# define IO_FILE 107		//compound token,
# define FILENAME 108		//compound token, the file of the redirections
# define IO_HERE 109		//compound token,
# define HERE_END 110		//compound token, limiter of the here_doc
# define READ 0				//standard input
# define WRITE 1			//standard output
# define ALLOW_WRITE 0

//Options of a state
typedef struct s_options
{
	int					index;
	int					state;
	int					t_type;
	int					action;
	int					next_state;
	int					nbr_red;
	struct s_options	*next;
}				t_options;

//State
typedef struct s_states
{
	int					state;
	struct s_options	*options;
	struct s_states		*next;
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
typedef struct s_step
{
	int				step_nbr;			//nbr of the current step
	int				state_nbr;			//nbr of the current state
	struct s_states	*state;				//ptr to the current state
	int				option_nbr;			//nbr of the current option of the state
	struct s_token	*tree_stack;		//ptr to the tree/ stack
	struct s_token	*input;				//ptr to the input
	struct s_step	*next;				//ptr to the next step
	struct s_step	*prev;				//ptr to the prev step
}				t_step;

//main struct for the input
typedef struct s_input
{
	char						**token_raw;
	struct s_var_list			*ent_var;
	struct s_states				*parsing_table;
	struct s_var_parsed_table	*parsed_table;
	int							allow_input;
	char						*input;
}				t_input;

//linked list for the enviroment variables
typedef struct s_var_list
{
	char				*name;
	int					is_printed;
	char				*content;
	struct s_var_list	*next;
	int					is_env;
}				t_var_list;

typedef struct s_var_parsed_table
{
	char						**env;
	char						**cmd_splited;
	char						*cmd;
	char						*path;
	int							fd_in;
	int							fd_out;
	int							fd_error;
	pid_t						pid;
	struct s_var_parsed_table	*next;
	struct s_var_parsed_table	*prev;
}				t_var_parsed_table;

//MAIN
int							main(int argc, char **argv, char **envp);

//MAIN UTILS
void						beyond_pipe(char *input, size_t *control);
char						*join_line(char *input, size_t *ctrl, \
							t_input **s_input);
int							add_space(char **input, char c, t_input **s_input);
int							open_quotes(char *input);

//HISTORY
void						load_history(void);
void						save_history(char	*input);

//SIGNAL
void						exec_signal_receiver(int mode);
void						signal_receiver(void);

//VARIABLES
void						save_env(char	**env, t_input **struct_input);

//LOOK FOR EQUALS
void						ft_print_var(t_input *input);
int							ft_var_found(t_var_list **list, char *name, \
							char *content);
void						ft_trim_var_equal(char *token, int e_pos, \
							t_var_list **v_list, int id);
int							ft_look_4_equal(char const *token, \
							t_var_list **variable_list, int id);

//LOOK FOR DOLLARS 1
void						del_char(char **cadena, int position);
int							ft_find_variable(char *var_name, \
							t_var_list **v_list, char **content);
void						expand_var_ent(t_var_parsed_table **table, \
							t_input **struct_input);

//LOOK FOR DOLLARS 2
int							ft_look_4_dollar(t_var_list **v_list, \
							char **content);

//READ TABLE
void						read_table(t_input **struct_input);

//ANALYZER
void						print_token_list(t_token *tokens);
void						create_tokens_analyzer(t_input **struct_input);

//STEPS
int							start_anaylizer(t_input **s_input, \
							t_token *input_token);

//REMOVE QUOTES
void						remove_quotes(t_var_parsed_table **head);
void						remove_quotes_aux(char **cmd_ptr, int mode);

//STEPS UTILS 1
int							find_state(t_states *states_list, int state_number, \
							t_states **state);
int							stack_size(t_token *tokens);
t_options					*find_option(t_states *state, int token_type);
void						add_step(t_input *s_input, t_options *option, \
							t_step **c_step);
t_token						*last_node_stack(t_token *stack);

//STEPS UTILS 2
void						ret_to_prev(t_step **c_step);
void						config_parsed_table(t_var_parsed_table **current);
t_step						*init_first_step(t_input **struct_input, \
t_token *input_token);
int							special_case(char *s);

//ACTIONS
void						ft_reduce(t_options *options, t_step **c_step);
void						ft_shift(t_token **stack, t_token **input);

//ACTIONS UTILS
void						apply_action(t_options *opts, t_step **c_step, \
							int *end);

//BUILT IN
void						ft_echo(char **args, int fd);
int							ft_pwd(t_input **env);
int							get_path_utils(char **path, char **route, \
							char *tmp, char *args);
int							get_path(char *args, t_input **env);
int							ft_cd(char **args, t_input **env);

//BUILT IN UTILS 1
int							ft_export(char *var, t_input **struct_input);
void						ft_eexit(char **arg, t_input **struct_input, \
							t_step *step);
void						ft_unset(char *name, t_input **struct_input);

//BUILT IN UTILS 2
void						add_var(char *name, t_var_list **env, \
							char *content);
int							ft_built_in1(t_var_parsed_table	*cmd_list, \
							t_input **struct_input, int (*control)[2], \
							t_step *step);
int							ft_is_built_in(t_var_parsed_table *cmd_list);

//READ TREE
void						free_parsed_table(t_var_parsed_table **table);
t_var_parsed_table			*init_parsed_table(t_var_parsed_table *prev_table);
void						walk_tree(t_var_parsed_table **parsed_table, \
							t_token *tree);
void						read_tree(t_token *tree, \
							t_var_parsed_table **table_node, int mode);

//READ TREE UTILS
int							reset_statics(int mode, int (*array)[7], \
							t_var_parsed_table **table_node);
void						init_append_tree(t_token *tree, int *first_time, \
							t_var_parsed_table **table_node);
void						set_fds(int (*array)[7], \
							t_var_parsed_table **table_node);
void						create_table(t_token *tree, \
							t_var_parsed_table **table_node);
void						set_flags(t_token *tree, int (*array)[7]);

//PIPEX
char						*ft_getenv(t_var_list **list, char *name);
int							ft_strcmp(const char *s1, const char *s2);
int							pipex(t_input **struct_input, t_step *step);

//PIPEX UTILS
int							ft_verify_cmd(char **paths, t_var_parsed_table *\
							cmd, t_input **env);
int							ft_close_pipes(int fd[2]);
int							relative_path(t_var_parsed_table *cmd, \
							t_input **env);
int							ft_here_doc(char **end, int fd);

//PROCESS
void						ft_make_process(t_var_parsed_table *cmd_list, \
							int fd[2], t_input **struct_input, t_step *step);

//BASH SPLIT
char						**ft_bash_split(char const *s, char cr, int *c);

//FREE
void						free_token_tree(t_token *head);
void						free_options(t_options *options);

//FREE 2
void						free_double(char **double_ptr);
void						free_steps(t_step *steps, int mode);
void						free_all(t_input *struct_input, char *history);

//TOKENIZATION
int							tokenization(char *input, t_input **struct_input);

//CMD HANDLE
int							cmd_handle(t_var_parsed_table **cmd_list, \
							t_input **env);

//ERROR
void						print_error(int id, char *args, t_input **input);

//PRINT
void						print_step_list(t_step *step);
void						print_cmd_contents(t_var_parsed_table **head);
void						display_structure_tree(t_token *root, int depth);

#endif