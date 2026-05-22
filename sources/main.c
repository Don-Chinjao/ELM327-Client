/* ************************************************************************** */
/*                                                                            */
/*                                             dP"Yb  88""Yb 8888b.  oP"Yb.   */
/*   main.c                                   dP   Yb 88__dP  8I  Yb "' dP'   */
/*                                            Yb   dP 88""Yb  8I  dY   dP'    */
/*   By: momadafun <marvin@42.fr>              YbodP  88oodP 8888Y"  .d8888   */
/*                                                                            */
/*   Created: 2026/05/16 17:25:41 by momadafun                                */
/*   Updated: 2026/05/21 23:06:09 by momadafun                                */
/*                                                                            */
/* ************************************************************************** */

#include "elm.h"

//char	elm_response[1024];

int	setup(char const *tty_path, int *fd, struct termios *tty)
{
	/* -------------------tty-opening------------------ */

	*fd = open(tty_path, O_RDWR | O_NOCTTY);
	if (*fd == -1) {
		perror(tty_path);
		return (-1);
	}

	/* ---------------init-tty-struct------------------ */

	if (tcgetattr(*fd, tty) == -1) {
		perror("tcgetattr");
		return (-1);
	}
	cfmakeraw(tty);
	if (cfsetispeed(tty, B38400)) {  /* input baud rate */
		perror("cfsetispeed");
		return (-1);
	}
	if (cfsetospeed(tty, B38400)) {  /* output baud rate */
		perror("cfsetospeed");
		return (-1);
	}
	tty->c_cc[VMIN] = 0;  	   /* min chars to read 	  */
	tty->c_cc[VTIME] = 3; 	   /* timeout delay (in 1/10 sec) */

	/* ----------------set-tty-attribute--------------- */
	if (tcsetattr(*fd, TCSANOW, tty) == -1) {
	    perror("tcsetattr");
	    return (-1);
	}

	return (0);
}

void	print_raw(int fd, char const *msg)
{
	dprintf(fd, "Raw Response:\n");
	for (int i = 0; msg[i] != '\0'; i++) {
		dprintf(fd, "%02x ", (unsigned char)msg[i]);
	}
	dprintf(fd, "\nAscii Response:\n%s\n", msg);
}

int	loop(int fd)
{
	char	input_buffer[1024];

	while (1) {
		ssize_t	rd_bytes = 0;

		bzero(input_buffer, 1024);
		write(2, ">", 1);
		rd_bytes = read(STDIN_FILENO, input_buffer, 256);
		if (rd_bytes <= 0) {
			return (-1);
		}
		if (input_buffer[rd_bytes - 1] == '\n')
			rd_bytes--;
		input_buffer[rd_bytes++] = '\r';
		input_buffer[rd_bytes] = '\0';
		if (elm_send(fd, input_buffer) == -1) {
			return (-1);
		}
		if (elm_read_response(fd) == -1) {
			return (-1);
		}
		print_raw(STDOUT_FILENO, elm_response.raw); /**/
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	struct termios	tty;

	if (ac != 2) {
		dprintf(STDERR_FILENO, "Usage: ./elm <tty path>\n");
		return (1);
	}

	if (setup(av[1], &fd, &tty) == -1) {
		return (2);
	}
/*
	elm_send(fd, "ATI\r");
	elm_read_response(fd);
	print_raw(STDOUT_FILENO);
*/
	elm_send(fd, "ATE0\r");
	elm_read_response(fd);
	print_raw(STDOUT_FILENO, elm_response);
	loop(fd);
	close(fd);

	return (0);
}
