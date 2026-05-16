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

typedef	struct s_obd_response
{
	uint8_t	mode;
	uint8_t	pid;
	uint8_t	data[256];
	size_t	len;
}		t_obd_response;

#endif
