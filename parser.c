#include "minishell.h"

int count_cmds(t_command *t_line)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while(t_line->tokens[++i])
    {
        if (t_line->tokens[i] == PIPE)
            count++;
    }
    return (++count);
}

int count_cmd_words(t_command *t_line, int start)
{
    int count;
    
    count = 0;
    while (t_line->tokens[start])
    {
        if (t_line->tokens[start] == PIPE)
            break;
        count++;
        start++;
    }
    return (count);
}

void    parser(t_command *t_line, t_minishell *main)
{
    int i;
    int cmd_index;
    int cmd_words;
    int j;

    main->cmds_count = count_cmds(t_line);
    i = -1;
    main->full_line = malloc(main->cmds_count * sizeof(t_command));
    cmd_index = -1;
    while(t_line->tokens[++i])
    {
        j = -1;
        cmd_words = count_cmd_words(t_line, i);
        main->full_line[++cmd_index].cmd = malloc((cmd_words + 1) * sizeof(char *));
        main->full_line[cmd_index].tokens = malloc((cmd_words + 1) * sizeof(char));
        while(++j < cmd_words)
        {
            main->full_line[cmd_index].cmd[j] = ft_strdup(t_line->cmd[i++]);
            main->full_line[cmd_index].tokens[j] = t_line->tokens[i - 1];
        }
        main->full_line[cmd_index].cmd[j] = NULL;
        main->full_line[cmd_index].tokens[j] = '\0';
        if (!t_line->tokens[i])
            break ;
    }
}
