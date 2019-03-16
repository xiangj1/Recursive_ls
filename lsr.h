#ifndef MY_LS_H
#define MY_LS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_depth(int depth);

void print_permission(struct stat mystat, char *file_path, int depth);

void ls_file(char *fileName);

int do_ls(char *dirName, int depth);

char *getUserName(uid_t uid);

char *getGroupName(gid_t gid);

char *month(int m);

#endif
