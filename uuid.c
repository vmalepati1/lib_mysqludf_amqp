#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UUID_BUF_LEN 40

/*
 * simple implementation of version 4 UUID generation
 */
char *uuidgen(void) {

    char *buffer = malloc(UUID_BUF_LEN);
    if (buffer == NULL) {
        return NULL;
    }

    memset(buffer, '\0', UUID_BUF_LEN);
    for (int i = 0, pos = 0; i < 16 && pos < UUID_BUF_LEN - 1; i++) {

        uint8_t r = (uint8_t) arc4random();

        /* set some special bits */
        if (i == 6) {
            r = (uint8_t) ((r & 0x0F) | 0x40); /* set version number */
        } else if (i == 8) {
            r = (uint8_t) ((r & 0x3F) | 0x80); /* set reserved to b01 */
        }

        /* insert '-' where needed */
        if (pos == 8 || pos == 13 || pos == 18 || pos == 23) {
            pos += snprintf(buffer + pos, UUID_BUF_LEN - pos, "-");
        }

        /* print hex characters */
        pos += snprintf(buffer + pos, UUID_BUF_LEN - pos, "%2.2x", r);
    }

    return buffer;
}