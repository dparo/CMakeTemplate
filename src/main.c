#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <slog.h>

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    int32_t logged_levels =
        SLOG_ERROR | SLOG_FATAL | SLOG_WARN | SLOG_TRACE | SLOG_DEBUG | SLOG_INFO;

    slog_init("example", logged_levels, 0);
    slog_info("My dick is nice: %s!", "Hello world");

    return 0;
}
