/*
int	elm_read_response(int fd)
{
	fd_set		set;
	struct timeval	timeout;
	int		rv;
	char		buffer[1024];

	bzero(buffer, 1024);
	bzero(elm_response, 1024);
	while (1) {
		ssize_t	rd_bytes;

		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(fd, &set);
		rv = select(fd + 1, &set, NULL, NULL, &timeout);
		if (rv == -1) {
			perror("select");
			return (-1);
		}
		if (rv == 0) {
			dprintf(2, "timeout\n");
			break ;
			//return (-1);
		}
		rd_bytes = read(fd, buffer, 256);
		if (rd_bytes == -1) {
			perror("read");
			return (-1);
		}
		if (rd_bytes == 0) {
			dprintf(2, "again\n");
			continue ;
		}
		buffer[rd_bytes] = '\0';
		strcat(elm_response, buffer);
		if (strchr(elm_response, '>')) {
			break ;
		}
	}
	return (0);
}*//*
int elm_read_response(int fd)
{
    fd_set set;
    struct timeval timeout;

    char buffer[4096];
    size_t total = 0;

    int got_data = 0;

    while (1) {

        FD_ZERO(&set);
        FD_SET(fd, &set);

        if (!got_data) {
            timeout.tv_sec = 2;
            timeout.tv_usec = 0;
        } else {
            timeout.tv_sec = 1;
            timeout.tv_usec = 500000;
        }

        int rv = select(fd + 1, &set, NULL, NULL, &timeout);

        if (rv == -1) {
            perror("select");
            return (-1);
        }

        if (rv == 0) {
            if (got_data)
                break;

            dprintf(2, "timeout\n");
            return (-1);
        }

        ssize_t rd = read(
            fd,
            buffer + total,
            sizeof(buffer) - total - 1
        );

        if (rd <= 0) {
            perror("read");
            return (-1);
        }

        got_data = 1;

        total += rd;
        buffer[total] = '\0';

        if (total >= sizeof(buffer) - 1) {
            dprintf(2, "buffer full\n");
            return (-1);
        }
    }

    memcpy(elm_response, buffer, total + 1);
    return (0);
}*/
/*
int elm_read_response(int fd)
{
    fd_set         set;
    struct timeval timeout;

    char    buffer[4096];
    size_t  total = 0;

    while (1) {
        ssize_t rd;

        FD_ZERO(&set);
        FD_SET(fd, &set);

        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        int rv = select(fd + 1, &set, NULL, NULL, &timeout);
        if (rv == -1) {
            perror("select");
            return (-1);
        }

        if (rv == 0) {
            dprintf(2, "timeout\n");
            return (-1);
        }

        rd = read(fd, buffer + total, sizeof(buffer) - total - 1);
        if (rd == -1) {
            perror("read");
            return (-1);
        }

        total += rd;
        buffer[total] = '\0';

        if (memchr(buffer, '>', total))
            break;

        if (total >= sizeof(buffer) - 1) {
            dprintf(2, "buffer full\n");
            return (-1);
        }
    }

    memcpy(elm_response, buffer, total + 1);
    return (0);
}*/

