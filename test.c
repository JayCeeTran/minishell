#include "minishell.h"

int main(int argc, char **argv)
{
    char *cmd[3];
    
    printf("hellooo world\n");

    if (argc < 2) {
        cmd[0] = "a.out";
        cmd[1] = "run";
        cmd[2] = NULL;
        execve("a.out", cmd, NULL);
    }

    printf("execve failed or not called\n");
    return 0;
}
