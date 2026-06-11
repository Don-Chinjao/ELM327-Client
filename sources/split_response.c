/* ************************************************************************** */
/*                                                                            */
/*                                             dP"Yb  88""Yb 8888b.  oP"Yb.   */
/*   split_response.c                         dP   Yb 88__dP  8I  Yb "' dP'   */
/*                                            Yb   dP 88""Yb  8I  dY   dP'    */
/*   By: momadafun <marvin@42.fr>              YbodP  88oodP 8888Y"  .d8888   */
/*                                                                            */
/*   Created: 2026/05/21 00:49:14 by momadafun                                */
/*   Updated: 2026/06/10 23:48:30 by momadafun                                */
/*                                                                            */
/* ************************************************************************** */

#include "elm.h"

char	**split_response(char *response, char *charset)
{
	char	**lines;
	int	i;
	char	*pos;

	lines = malloc(sizeof(char *) * 256);
	bzero(lines, sizeof(char *) * 256);
	i = 0;
	while (*response) {
		while (strchr(charset, *response))
			response++;
		if (!*response)
			break ;
		pos = response;
		while (!strchr(charset, *pos) && *pos)
			pos++;
		lines[i] = malloc(sizeof(char) * (pos - response));
		bzero(lines[i], pos - response);
		memcpy(lines[i], response, pos - response);
		response += pos - response;
		i++;
	}
	return (lines);
}
