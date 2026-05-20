/******************************************************************************/
/*                              elm.h                                         */
/******************************************************************************/

#ifndef ELM_H
# define ELM_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <time.h>
# include <sys/select.h>
# include <stdint.h>

extern char	elm_response[1024];

typedef	enum e_obd_error
{
    OBD_OK,
    OBD_TIMEOUT,
    OBD_NO_DATA,
    OBD_BAD_RESPONSE,
    OBD_PARSE_ERROR,
}		t_obd_error;

enum elm_type {
    ELM_HEX,
    ELM_NO_DATA,
    ELM_ERROR,
    ELM_TEXT,
};

typedef	struct s_obd_response
{
	uint8_t	mode;
	uint8_t	pid;
	uint8_t	data[256];
	size_t	len;
}		t_obd_response;

char	**split_response(char *response, char *charset);

int	elm_send(int fd, char const *cmd);
int	elm_read_response(int fd);

#endif
