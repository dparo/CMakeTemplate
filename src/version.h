#pragma once

#if __cplusplus
extern "C" {
#endif

extern const char *PROJECT_NAME;
extern const char *PROJECT_DESCRIPTION;
extern const char *PROJECT_VERSION;
extern const char *PROJECT_VERSION_MAJOR;
extern const char *PROJECT_VERSION_MINOR;
extern const char *PROJECT_VERSION_PATCH;

extern const char *BUILD_TYPE;
extern const char *C_COMPILER_ID;
extern const char *C_COMPILER_ABI;
extern const char *C_COMPILER_VERSION;
extern const char *GIT_SHA1;
extern const char *GIT_DATE;
extern const char *GIT_COMMIT_SUBJECT;

#if __cplusplus
}
#endif
