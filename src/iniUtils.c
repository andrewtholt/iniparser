#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int readLine(int fd, void *buffer, int n) {
    int numRead;                    /* # of bytes fetched by last read() */
    int totRead;                     /* Total bytes read so far */
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = buffer;                       /* No pointer arithmetic on "void *" */

    totRead = 0;
    while (true) {
#ifdef LINUX
        numRead = read(fd, &ch, 1);
#endif
#ifdef FREERTOS
        numRead = yaffs_read(fd, &ch, 1);
#endif

        if (numRead == -1) {
            if (errno == EINTR)         /* Interrupted --> restart read() */
                continue;
            else
                return -1;              /* Some other error */

        } else if (numRead == 0) {      /* EOF */
            if (totRead == 0)           /* No bytes read; return 0 */
                return 0;
            else                        /* Some bytes read; add '\0' */
                break;

        } else {                        /* 'numRead' must be 1 if we get here */
            if (totRead < n - 1) {      /* Discard > (n - 1) bytes */
                totRead++;
                *buf++ = ch;
            }

            if (ch == '\n')
                break;
        }
    }

    *buf = '\0';

    return totRead;
}
