#include "minishell.h"

void	add_cmd(t_cmd **head, t_cmd *newnode);
t_cmd *newcmd(char **cmd, t_redir *directions);
void	add_redir(t_redir **head, t_redir *newnode);
t_redir *new_redir(char *redir, char *file, int pipe);
char **new_command(char *s, char *s2, char *s3);

void	testing(char **env)
{
	t_data data;
	data.env = env;
	my_envp(&data);
	find_path(&data, env);
	t_cmd *cmd_head = NULL;
	t_redir *dir_head = NULL;

	add_redir(&dir_head, new_redir("<", "infile", 0));
	add_redir(&dir_head, new_redir("<<", "infile2", 1));
	//add_redir(&dir_head, new_redir(">", "out2", 0));
//	add_redir(&dir_head, new_redir("<<", "test", 0));
	//add_redir(&dir_head, new_redir(">", "out3", 1));
	char **cmd1 = new_command("cat", NULL, NULL);
	add_cmd(&cmd_head, newcmd(cmd1, dir_head));

	t_redir *dir_head2 = NULL;
	add_redir(&dir_head2, new_redir(NULL, NULL, 1));
	/*add_redir(&dir_head2, new_redir("<", "infile2", 0));
	add_redir(&dir_head2, new_redir(">", "outfile2", 0));
	add_redir(&dir_head2, new_redir(">", "outfile2", 0));
	add_redir(&dir_head2, new_redir(NULL, NULL, 1));
*/	char **cmd2 = new_command("cat", "-e", NULL);
	add_cmd(&cmd_head, newcmd(cmd2, dir_head2));

	t_redir *dir_head3 = NULL;
	add_redir(&dir_head3, new_redir(">", "out2", 0));
	char **cmd3 = new_command("cat", "-e", NULL);
	add_cmd(&cmd_head, newcmd(cmd3, dir_head3));

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

/*	while(data.list)
	{
		for(int i = 0; data.list->cmd[i]; i++)
			printf("%s\n", data.list->cmd[i]);
		while(data.list->redirections)
		{
			printf("dir:%s	file:%s	pipe:%d\n", data.list->redirections->redir, data.list->redirections->file, data.list->redirections->pipe);
			data.list->redirections = data.list->redirections->next;
		}
		data.list = data.list->next;
	}
*/	
/*	char **menv = data.my_env;
	while(*menv)
	{
		printf("%s\n", *menv);
		menv++;
	}
	printf("check!\n");
*/	free_all_exit("END OF TESTING\n", -1, &data);
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

t_cmd *newcmd(char **cmd, t_redir *directions)
{
	t_cmd *newnode;

	newnode = malloc(sizeof(t_cmd));
	if(!newnode)
		return(NULL); // EXIT AND ERROR MESSAGE IF FAILS!!!
	newnode->cmd = cmd;
	newnode->redirections = directions;
	newnode->next = NULL;
	return(newnode);
}

void	add_redir(t_redir **head, t_redir *newnode)
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

t_redir *new_redir(char *redir, char *file, int pipe)
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
	newnode->pipe = pipe;
	newnode->next = NULL;
	return(newnode);
}

char **new_command(char *s, char *s2, char *s3)
{
	char **cmd = malloc(sizeof(char *) * 4);
	
	if(s)
		cmd[0] = ft_strdup(s);
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
