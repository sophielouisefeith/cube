/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:01:42 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/03 21:14:34 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ik wil dat hij dus in een keer heel de map leest dus hij moet gewoon lezen tot een /0 teken. dit moet hij mee geven als een string
// aan split dan geven dus heel de string mee aan split en het split character. 

static int		ft_wordcount(char const *s, char c)
{
	int		i;
	int		wcount;

	i = 0;
	wcount = 0;
	if (c == '\0' && s[i] != '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			wcount++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (wcount);
}

static int		ft_lettercount(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char		**ft_freenewstring(char **ns, int j)
{
	while (j >= 0)
	{
		j--;
		if (ns[j])
			free(ns[j]);
	}
	if (ns)
		free(ns);
	return (NULL);
}

static char		**ft_newstring(char const *s, char c, char **ns)
{
	int i;
	int lcount;
	int j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			lcount = ft_lettercount(s, c, i);
			ns[j] = ft_substr((char *)s, i, (size_t)lcount);
			if (ns[j] == 0)
				return (ft_freenewstring(ns, j));
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (ns);
}

static char			**ft_split(char const *s, char c)
{
	int		i;
	char	**words;
	int		wc;

	if (!s)
		return (NULL);
	i = 0;
	wc = ft_wordcount(s, c);
	words = ((char**)malloc((wc + 1) * sizeof(char *)));
	if (words == NULL)
		return (NULL);
	words = ft_newstring(s, c, words);
	words[wc] = NULL;
	return (words);
}






static char			*ft_cut(char *new)
{
	int		i;

	i = 0;
	while (new[i] != '\0')
		i++;
	new = ft_substr(new, 0, i);

	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	//if (new[i] == '\0')
	// temp = ft_substr(new, i + 1, ft_strlen(new) - i);
		// free(new);
	//printf("wat ben je new[%s]\n", new);
	return (new);

}

static char			*ft_treatment(char *new, int ret, int fd)
{
	char	*buf;

	while (ret > 0)
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buf == 0)
		{
			free(new);
			return (NULL);
		}
		ret = (read(fd, buf, BUFFER_SIZE));
		if (ret == -1)
		{
			free(buf);
			free(new);
			return (NULL);
		}
		buf[ret] = '\0';
		new = ft_strjoin(new, buf);
		if (new == NULL)
			return (NULL);
		// if (ft_strchr(new, '\n'))
		// 	break ;
	}
	return (new);
}

char				*get_next_line(const int fd)
{
	int			ret;
	static char *new;


	ret = 1;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (new == NULL)
		new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	new = ft_treatment(new, ret, fd);
	if (new == NULL)
		return (NULL);
	new = ft_cut(new);
	//printf("wat ben je new[%s]\n", new);
	if (new == NULL)
		//return (NULL);
	// if (r == 0)
	{
		free(new);
		new = NULL;
	}
//	printf("wat ben je new[%s]\n", new);
	return (new);
}

char	**ft_savemap(char const *s, const int fd)
{
	
	char **map;
	
	*map  = get_next_line(fd);
	if ( map == 0)
		return NULL;
	*map = *ft_split(*map, '\n');
	if (!map)
		return NULL;
	return(map);
}