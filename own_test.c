#include "minishell.h"

void	add_cmd(t_cmd **head, t_cmd *newnode);
t_cmd *newcmd(char **cmd, t_redir *directions, int pipe);
void	add_redirr(t_redir **head, t_redir *newnode);
t_redir *new_redir(char *redir, char *file);
char **new_command(char *s, char *s2, char *s3);

void	testing(char **env)
{
	t_data data;
	data.env = env;
	my_envp(&data);
	find_path(&data, env);
	t_cmd *cmd_head = NULL;
	t_redir *dir_head = NULL;

	add_redirr(&dir_head, new_redir("<", "infile2"));
	//add_redir(&dir_head, new_redir("<", "infile2"));
	//add_redir(&dir_head, new_redir(">", "out2", 1));
//	add_redir(&dir_head, new_redir("<<", "test", 0));
	//add_redir(&dir_head, new_redir(">", "out3", 1));
	char **cmd1 = new_command("cat", "", NULL);
	add_cmd(&cmd_head, newcmd(cmd1, dir_head, 0));

//	t_redir *dir_head2 = NULL;
//	add_redir(&dir_head2, new_redir("<<", "infile3", 0));
//	add_redir(&dir_head2, new_redir("<<", "infile4", 1));
//	add_redir(&dir_head2, new_redir(">", "outfile"));
//	add_redir(&dir_head2, new_redir(">", "outfile2"));
//	add_redir(&dir_head2, new_redir(NULL, NULL));
//	char **cmd2 = new_command("cat", "-e", NULL);
//	add_cmd(&cmd_head, newcmd(cmd2, dir_head2, 1));

//	t_redir *dir_head3 = NULL;
//	add_redir(&dir_head3, new_redir(">", "out2"));
//	char **cmd3 = new_command("cat", "-e", NULL);
//	add_cmd(&cmd_head, newcmd(cmd3, dir_head3, 0));

/*	t_redir *dir_head4 = NULL;
	add_redir(&dir_head4, new_redir(NULL, NULL, 1));
	char **cmd4 = new_command("catt", "-e", NULL);
	add_cmd(&cmd_head, newcmd(cmd4, dir_head4));

	t_redir *dir_head5 = NULL;
	add_redir(&dir_head5, new_redir(">>", "outfile3", 0));
	char **cmd5 = new_command("catt", "-e", NULL);
	add_cmd(&cmd_head, newcmd(cmd5, dir_head5));
*/
	data.list = cmd_head;
	read_list(&data);
/*	char **menv = data.my_env;
	while(*menv)
	{
	
		printf("%s\n", *menv);
		menv++;
	}
*/	printf("check!\n");
	if(1)
	{
		write(2, "YES!\n", 5);
		free_all_exit("END OF TESTING\n", 1, &data, 1);
	}
	return;
}

void	add_cmd(t_cmd **head, t_cmd *newnode)
{
	t_cmd *cur;

	if(!(*head))
	{
		(*head) = newnode;
		return;
	}
	cur = (*head);
	while(cur->next)
		cur = cur->next;
	cur->next = newnode;
}

t_cmd *newcmd(char **cmd, t_redir *directions, int pipe)
{
	t_cmd *newnode;

	newnode = malloc(sizeof(t_cmd));
	if(!newnode)
		return(NULL); // EXIT AND ERROR MESSAGE IF FAILS!!!
	newnode->cmd = cmd;
	newnode->redirections = directions;
	newnode->pipe = pipe;
	newnode->next = NULL;
	return(newnode);
}

void	add_redirr(t_redir **head, t_redir *newnode)
{
	t_redir *cur;

	if(!(*head))
	{
		(*head) = newnode;
		return;
	}
	cur = (*head);
	while(cur->next)
		cur = cur->next;
	cur->next = newnode;
}

t_redir *new_redir(char *redir, char *file)
{
	t_redir *newnode;
	newnode = malloc(sizeof(t_redir));
	if(!newnode)
		return(NULL);			//EXIT AND ERROR MESSAGE IF FAILS!
	if(redir)
		newnode->redir = ft_strdup(redir);
	else
		newnode->redir = NULL;
	if(file)
		newnode->file = ft_strdup(file);
	else
		newnode->file = NULL;
	newnode->next = NULL;
	return(newnode);
}

char **new_command(char *s, char *s2, char *s3)
{
	char **cmd = malloc(sizeof(char *) * 4);
	
	if(s)
		cmd[0] = ft_strdup(s);
	else
		cmd[0] = NULL;
	if(s2)
		cmd[1] = ft_strdup(s2);
	else
		cmd[1] = NULL;
	if(s3)
		cmd[2] = ft_strdup(s3);
	else
		cmd[2] = NULL;
	cmd[3] = NULL;
	return(cmd);
}
