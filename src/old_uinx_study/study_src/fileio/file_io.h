//
// Created by tao on 18-10-5.
//

#ifndef UNIXSTUDY_FILE_IO_HP
#define UNIXSTUDY_FILE_IO_HP

#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <unistd.h>

#define G 1024 * 1024 * 1024

void test_seek(const char *file) {
  const char *hello = "hello";
  int fd;
  off_t res;
  char buff[100];

  int seek = 1 * G;
  if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC)) < 0) {
    fprintf(stderr, "err in creat file\n");
    return;
  }

  if ((res = write(fd, hello, strlen(hello))) != strlen(hello)) {
    fprintf(stderr, "err in write except %d , return %ld\n", (int)strlen(hello),
            res);
    return;
  }

  printf("input anything thing to continue seek!\n");
  scanf("%s", buff);

  if ((res = lseek(fd, seek, SEEK_SET)) != seek) {
    fprintf(stderr, "lseek err except %d, return %ld", seek, res);
    return;
  }

  printf("input anything to write in end");
  scanf("%s", buff);

  if ((res = write(fd, "\0", 1)) != 1) {
    fprintf(stderr, "fputc err except %d, return %ld", 1, res);
    return;
  }
  close(fd);
}

#endif  // UNIXSTUDY_FILE_IO_HP
