#include "elm.h"

int	elm_send(int fd, char const *cmd)
{
	size_t	bsz, off;
	ssize_t	nw;

	bsz = strlen(cmd);
	for (off = 0; off < bsz; off += nw) {
		nw = write(fd, cmd + off, bsz - off);
		if (nw == 0 || nw == -1) {
			perror("write");
			return (-1);
		}
	}
	return (0);
}

int	elm_read_response(int fd)
{
	int	total;
	time_t	start;
	char	buffer[1024];

	total = 0;
	start = time(NULL);
	bzero(buffer, 1024);
	bzero(elm_response.raw, 1024); /**/
	while (time(NULL) - start <= 4) {
		ssize_t	rd_bytes;

		rd_bytes = read(fd, buffer + total, 256);
		if (rd_bytes == -1) {
			perror("read");
			return (-1);
		}
		if (rd_bytes == 0) {
			continue ;
		}
		total += rd_bytes;
		buffer[total] = '\0';
		if (memchr(buffer, '>', total)) {
			break ;
		}
	}
	memcpy(elm_response.raw, buffer, total + 1); /**/
	return (0);
}
