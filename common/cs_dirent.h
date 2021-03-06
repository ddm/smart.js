/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_CS_DIRENT_H_
#define CS_COMMON_CS_DIRENT_H_

#include "common/platform.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CS_ENABLE_SPIFFS
#define CS_ENABLE_SPIFFS 0
#endif

#if CS_ENABLE_SPIFFS

#include <spiffs.h>

typedef struct {
  spiffs_DIR dh;
  struct spiffs_dirent de;
} DIR;

#define d_name name
#define dirent spiffs_dirent

int rmdir(const char *path);
int mkdir(const char *path, mode_t mode);

#endif

#if defined(_WIN32)
struct dirent {
  char d_name[MAX_PATH];
};

typedef struct DIR {
  HANDLE handle;
  WIN32_FIND_DATAW info;
  struct dirent result;
} DIR;
#endif

#if CS_ENABLE_SPIFFS
extern spiffs *cs_spiffs_get_fs(void);
#endif

#if defined(_WIN32) || CS_ENABLE_SPIFFS
DIR *opendir(const char *dir_name);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_DIRENT_H_ */
