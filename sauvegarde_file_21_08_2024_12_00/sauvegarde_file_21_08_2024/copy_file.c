#include "main.h"

/**
 * copy_file - Copies a file from a source path to a destination path.
 * @src: The path to the source file that needs to be copied.
 * @dest: The path to the destination file where the source file will be copied.
 *
 * This function opens the source file for reading and the destination file
 * for writing (creating it if necessary). It reads the source file in chunks
 * and writes those chunks to the destination file. The destination file is
 * created with permissions set to 0755 (rwxr-xr-x).
 *
 * Return:
 * 0 on success.
 * -1 on failure, with errno set to indicate the error.
 */
int copy_file(const char *src, const char *dest)
{
	int src_fd, dest_fd;
	char buffer[4096];
	ssize_t bytes_read, bytes_written;

	src_fd = open(src, O_RDONLY);
	if (src_fd < 0)
	{
		perror("open src");
		return -1;
	}

	dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0755); // 0755 = rwxr-xr-x
	if (dest_fd < 0)
	{
		perror("open dest");
		close(src_fd);
		return -1;
	}

	while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			perror("write");
			close(src_fd);
			close(dest_fd);
			return -1;
		}
	}

	if (bytes_read < 0)
	{
		perror("read");
	}

	close(src_fd);
	close(dest_fd);
	return (bytes_read < 0) ? -1 : 0;
}
