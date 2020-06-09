//
// Created by tao on 18-10-8.
//

#ifndef UNIXSTUDY_FILE_DIR_MAIN_H
#define UNIXSTUDY_FILE_DIR_MAIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "stat_study.h"

int file_dir_main() {
  stat_std();
  char buff[200];
  while (true) {
    printf("curr : %s\n", getcwd(buff, sizeof(buff)));
    printf("input file name:");
    scanf("%s", buff);
    printf("\n");
    if (strcmp(buff, "0") == 0) {
      break;
    }
    access_std(buff);
  }
}

#endif  // UNIXSTUDY_FILE_DIR_MAIN_H
