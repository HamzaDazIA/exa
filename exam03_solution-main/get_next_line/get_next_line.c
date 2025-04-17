#include "get_next_line.h"

size_t ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    char *tmp = malloc(sizeof(char) * (len + 1));

    while(str[i])
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return tmp;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *join;
    int i = 0;
    int j = 0;

    join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    while(s1[i])
    {
        join[i] = s1[i];
        i++;
    }
    while(s2[j])
        join[i++] = s2[j++];
    join[i] = '\0';
    free(s1);
    free(s2);
    return join; 
}

char *ft_strchr(char *str, char c)
{
    int i = 0;

    while(str[i])
    {
        if(str[i] == c)
            return (&str[i]);
        i++;
    }
    return NULL;
}

char *substr(char *str, int *len)
{
    char *tmp;
    int i = 0;
    int k = 0;

    if (!str)
        return NULL;
    while(str[i] != '\n' && str[i])
        i++;

    if (str[i] == '\n')
        i++;
    
    tmp = malloc(sizeof(char) * (i + 1));
    if(!tmp)
        return NULL;

    while(k < i)
    {
        tmp[k] = str[k];
        k++;
    }
    tmp[k] = '\0';
    *len = i;
    return (tmp);
}

char *get_next_line(int fd)
{
    static char *str;
    char *line;
    int buf_readed;
    char *tmp;
    int cut;

    if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
        return(free(str), str = NULL, NULL);

    if (!str)
        str = ft_strdup("");
    
    buf_readed = 1;
    while(buf_readed > 0)
    {
        tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if(!tmp)
            return(free(str), str = NULL, NULL);
        buf_readed = read(fd, tmp, BUFFER_SIZE);
	if (buf_readed < 0)
		return(free(str), str = NULL, NULL);
	if (buf_readed == 0)
	{
		free(tmp);
		break;
	}
        tmp[buf_readed] = '\0';
        str = ft_strjoin(str, tmp);
        if(ft_strchr(str, '\n'))
            break;
    }
    if (!str || *str == '\0')
		return (free(str), str = NULL, NULL);
    line = substr(str, &cut);
    tmp = ft_strdup(str + cut);
    free(str);
    str = tmp;
    return line;
}

// int main()
// {
//     int file = open("file.txt", O_RDONLY);
//     char *str = get_next_line(file);


//     while(str)
//     {
//         printf("%s", str);
//         free(str);
//         str = get_next_line(file);
//     }
//     printf("[%s]\n", str);
//     free(str);
//     close(file);
// }
