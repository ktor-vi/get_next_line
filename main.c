#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int main(int argc, char **argv)
{
    int fd;
    if (argc != 2)
    {
        if (argc == 1)
            write(1, "File name missing.\n", 19);
        else if (argc > 2)
            write(1, "Too many arguments.\n", 20);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        write(1, "Cannot read file.\n", 18);
        return (1);
    }

    char *line;
    // line = get_next_line(fd);
    int i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        
        // printf("|%d line : %s",i, line);
        // get_next_line(fd);
        printf("%s", line);
        free(line);
        i++;
    }
    // system("leaks a.out");
    close(fd);
    return (0);
}
