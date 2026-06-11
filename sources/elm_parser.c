/* ************************************************************************** */
/*                                                                            */
/*                                             dP"Yb  88""Yb 8888b.  oP"Yb.   */
/*   elm_parser.c                             dP   Yb 88__dP  8I  Yb "' dP'   */
/*                                            Yb   dP 88""Yb  8I  dY   dP'    */
/*   By: momadafun <marvin@42.fr>              YbodP  88oodP 8888Y"  .d8888   */
/*                                                                            */
/*   Created: 2026/05/16 22:21:23 by momadafun                                */
/*   Updated: 2026/06/11 02:28:34 by momadafun                                */
/*                                                                            */
/* ************************************************************************** */

#include "elm.h"

char	*elm_normalize_response(char *response)
{
	(void)response;
	return (NULL);
}
/*
t_elm_response_type	elm_detect(char const *reponse)
{

}

int	elm_extract_payload(char *dest, char const *src)
{

}
*/
int	elm_parser(t_elm_response *response)
{
	response->lines = split_response(response->raw, "\n\r");
	for (int i = 0; response->lines[i]; i++) {
		printf("lines %d: %s\n", i, response->lines[i]);
	}
	return (0);
}
