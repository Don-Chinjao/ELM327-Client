/* ************************************************************************** */
/*                                                                            */
/*                                             dP"Yb  88""Yb 8888b.  oP"Yb.   */
/*   split_response.c                         dP   Yb 88__dP  8I  Yb "' dP'   */
/*                                            Yb   dP 88""Yb  8I  dY   dP'    */
/*   By: momadafun <marvin@42.fr>              YbodP  88oodP 8888Y"  .d8888   */
/*                                                                            */
/*   Created: 2026/05/21 00:49:14 by momadafun                                */
/*   Updated: 2026/05/21 23:47:17 by momadafun                                */
/*                                                                            */
/* ************************************************************************** */

#include "elm.h"

char	*split_response(char *response, char *charset, char tokens[256][1024])
{
	int	i;
	char	*pos;

	i = 0;
	while (*response) {
		while (strchr(charset, *response))
			response++;
		if (!*response)
			break ;
		pos = response;
		while (!strchr(charset, *pos) && *pos)
			pos++;
		bzero(tokens[i], 1024);
		memcpy(tokens[i], response, pos - response);
		i++;
	}
	return (tokens);
}
