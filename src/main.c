#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <log.h>
#include <argtable3.h>

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    log_info("Test from log_info");
    return 0;
}
