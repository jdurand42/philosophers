#include "../includes/philo_three.h"

void ft_print(char *str, int timestamp, int n)
{
	char *s;
	char *s2;
	char ns[12];
	char ts[12];

	ft_itoa_buff(n, ns);
	ft_itoa_buff(timestamp, ts);
	if (!(s = ft_strjoin(ts, "ms: Philosopher ")))
		return ;
	if (!(s2 = ft_strjoin(s, ns)))
		return ;
	free(s);
	if (!(s = ft_strjoin(s2, str)))
		return ;
	free(s2);
	write(1, s, ft_strlen(s));
	free(s);
}

static int	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int			ft_atoi(char const *str)
{
	int	i;
	int	neg;
	int	resultat;

	resultat = 0;
	i = 0;
	neg = 1;
	while (str[i] != '\0' && (ft_iswhitespace(str[i])))
		i++;
	if ((str[i] != '\0' && str[i] == '-') || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		resultat = resultat * 10 + str[i] - '0';
		i++;
	}
	return (neg * resultat);
}

static int	ft_nbrlen_bonus(long int nbr)
{
	int	nbrlen;

	nbrlen = 1;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr >= 10)
	{
		nbr /= 10;
		nbrlen = nbrlen + 1;
	}
	return (nbrlen);
}

void		ft_itoa_buff(int n, char *str)
{
	int		nbrlen;
	long	n2;

	n2 = (long)n;
	nbrlen = ft_nbrlen_bonus(n2);
	if (n < 0)
	{
		n2 = -n2;
		nbrlen++;
	}
	str[0] = '-';
	str[nbrlen--] = '\0';
	if (n2 == 0)
		str[nbrlen--] = '0';
	while (n2)
	{
		str[nbrlen--] = n2 % 10 + '0';
		n2 = n2 / 10;
	}
}

static char	*ft_strcat_bonus(char *dest, char const *src, size_t len)
{
	unsigned int i;
	unsigned int j;

	i = len;
	j = 0;
	while (src[j] != '\0')
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t			megasize;
	char			*b;
	size_t			len_1;
	size_t			len_2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	megasize = len_1 + len_2;
	if (!(b = (char *)malloc((megasize + 1) * sizeof(char))))
		return (NULL);
	b[0] = 0;
	ft_strcat_bonus(b, s1, 0);
	ft_strcat_bonus(b, s2, len_1);
	return (b);
}

char	*ft_strdup(char const *src)
{
	unsigned int	len;
	unsigned int	i;
	char			*dest;

	i = 0;
	len = ft_strlen(src);
	if (!(dest = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	else
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}

size_t	ft_strlen(char const *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
