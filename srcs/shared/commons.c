#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(char const *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
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

char		*ft_itoa(int n)
{
	int		nbrlen;
	char	*str;
	long	n2;

	n2 = (long int)n;
	nbrlen = ft_nbrlen_bonus(n2);
	if (n < 0)
	{
		n2 = -n2;
		nbrlen++;
	}
	if (!(str = (char*)malloc((nbrlen + 1) * sizeof(char))))
		return (0);
	str[0] = '-';
	str[nbrlen--] = '\0';
	if (n2 == 0)
		str[nbrlen--] = '0';
	while (n2)
	{
		str[nbrlen--] = n2 % 10 + '0';
		n2 = n2 / 10;
	}
	return (str);
}
