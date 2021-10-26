#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"

#include <log.h>
#include <argtable3.h>

#define DEFAULT_TIME_LIMIT ((double)600.0)

enum {
    MAX_NUMBER_OF_ERRORS_TO_DISPLAY = 16,
};

static void print_brief_description(const char *progname);
static void print_version(void);
static void print_use_help_for_more_information(const char *progname);

static int main2(const char *instance_filepath, const char *solver, double timelimit,
                 const char **defines, int32_t num_defines) {
    (void)instance_filepath;
    (void)solver;
    (void)timelimit;
    (void)defines;
    (void)num_defines;
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    const char *progname = argv[0];
    FILE *log_file_handle = NULL;

    if (argc == 1) {
        print_brief_description(progname);
        print_version();
        printf("\n");
        print_use_help_for_more_information(progname);
        return EXIT_FAILURE;
    }

    struct arg_dbl *timelimit = arg_dbl0(
        "t", "timelimit", NULL, "define the maximum timelimit in seconds (default 10 minutes)");
    struct arg_str *defines =
        arg_strn("D", "define", "KEY=VALUE", 0, argc + 2, "define parameters");
    struct arg_str *solver = arg_str0("S", "solver", "SOLVER", "solver to use (default \"mip\")");
    struct arg_lit *verbose = arg_lit0("v", "verbose", "verbose messages");
    struct arg_file *logfile =
        arg_file0("l", "log", NULL,
                  "specify an additional file where log informations would be "
                  "stored (default none)");
    struct arg_lit *help = arg_lit0(NULL, "help", "print this help and exit");
    struct arg_lit *version = arg_lit0(NULL, "version", "print version information and exit");
    struct arg_file *instance = arg_file1("i", "instance", NULL, "input instance file");
    struct arg_end *end = arg_end(MAX_NUMBER_OF_ERRORS_TO_DISPLAY);

    void *argtable[] = {help, version, verbose, logfile, timelimit, defines, instance, solver, end};

    int nerrors;
    int exitcode = 0;

    /* verify the argtable[] entries were allocated sucessfully */
    if (arg_nullcheck(argtable) != 0) {
        printf("%s: insufficient memory\n", progname);
        exitcode = 1;
        goto exit;
    }

    // Default time limit
    timelimit->dval[0] = DEFAULT_TIME_LIMIT;
    // Default solver
    solver->sval[0] = "mip";
    // No logging file by default
    logfile->filename[0] = NULL;

    nerrors = arg_parse(argc, argv, argtable);

    /* special case: '--help' takes precedence over error reporting */
    if (help->count > 0) {
        print_brief_description(progname);
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        arg_print_glossary(stdout, argtable, "  %-32s %s\n");
        exitcode = 0;
        goto exit;
    }

    /* special case: '--version' takes precedence error reporting */
    if (version->count > 0) {
        print_version();
        exitcode = 0;
        goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0) {
        arg_print_errors(stdout, end, progname);
        print_use_help_for_more_information(progname);
        exitcode = 1;
        goto exit;
    }

    if (verbose->count > 0) {
        log_set_level(LOG_INFO);
    } else {
        log_set_level(LOG_WARN);
    }

    if (logfile->count > 0) {
        log_file_handle = fopen(logfile->filename[0], "w");
        if (log_file_handle) {
            log_add_fp(log_file_handle, LOG_INFO);
        } else {
            fprintf(stderr, "%s: Failed to open for logging\n", logfile->filename[0]);
        }
    }

    exitcode = main2(instance->filename[0], solver->sval[0], timelimit->dval[0], defines->sval,
                     defines->count);

exit:
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

    if (log_file_handle) {
        fclose(log_file_handle);
        log_file_handle = NULL;
    }

    return exitcode;
}

static void print_brief_description(const char *progname) {
    (void)progname;
    printf("My program's short brief description\n");
}

static void print_version(void) {
    printf("%s (revision: %s)\n", GIT_DATE, GIT_SHA1);
    printf("Compiled with %s v%s (%s), %s build\n", C_COMPILER_ID, C_COMPILER_VERSION,
           C_COMPILER_ABI, BUILD_TYPE);
}

static void print_use_help_for_more_information(const char *progname) {
    printf("Try '%s --help' for more information.\n", progname);
}
