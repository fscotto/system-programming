#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <sys/stat.h>

char filetype(mode_t mode);
char *getpermissions(mode_t mode);

int main(int argc, char *argv[])
{
  char *dirname = ".";
  if (argc > 1)
    dirname = argv[1];

  DIR *dir = opendir(dirname);
  if (dir == NULL) {
    int errsv = errno;
    fprintf(stderr, "%s: cannot access %s: %s\n", argv[0], dirname, strerror(errsv));
    return EXIT_FAILURE;
  }

  struct stat statbuf;
  struct dirent *dirp;
  while ((dirp = readdir(dir)) != NULL) {
    // Skip current and previous directory symbols
    if (strcmp(dirp->d_name, ".") == 0 ||
	strcmp(dirp->d_name, "..") == 0)
      continue;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", dirname, dirp->d_name);
    if (stat(path, &statbuf) < 0) {
      int errsv = errno;
      fprintf(stderr, "%s: cannot stat %s: %s\n", argv[0], path, strerror(errsv));
      continue;
    }
    
    char type = filetype(statbuf.st_mode);
    char *permissions = getpermissions(statbuf.st_mode);
    
    /*
     * Format output:
     * TYPE: d (directory) | f (regular file) | l (symbolic link) | o (others)
     * PERMISSIONS (ex. rwxrwxrwx)
     * NR HARD LINKS
     * USER
     * GROUP
     * SIZE
     * NAME
     */
    printf("%c%s %lu %u %u %6lu %s\n",
	   type, permissions, statbuf.st_nlink,
	   statbuf.st_uid, statbuf.st_gid, statbuf.st_size,
	   dirp->d_name);

    if (permissions != NULL) {
      free(permissions);
      permissions = NULL;
    }
  }

  if (closedir(dir) == -1) {
    int errsv = errno;
    fprintf(stderr, "%s: cannot close %s: %s\n", argv[0], dirname, strerror(errsv));
    return EXIT_FAILURE;
  }
}

char filetype(mode_t mode)
{
  if (S_ISREG(mode)) return '-';
  if (S_ISDIR(mode)) return 'd';
  if (S_ISLNK(mode)) return 'l';
  if (S_ISCHR(mode)) return 'c';
  if (S_ISBLK(mode)) return 'b';
  if (S_ISFIFO(mode)) return 'p';
#ifdef S_ISSOCK
  if (S_ISSOCK(mode)) return 's';
#endif
  return '?';
}

char checkpermission(mode_t mode, int perm, char c)
{
  return (mode & perm) ? c : '-';
}

char *getpermissions(mode_t mode)
{
  char *permissions = malloc(9 + 1);

  /* User */
  permissions[0] = checkpermission(mode, S_IRUSR, 'r');
  permissions[1] = checkpermission(mode, S_IWUSR, 'w');
  permissions[2] = checkpermission(mode, S_IXUSR, 'x');

  /* Group */
  permissions[3] = checkpermission(mode, S_IRGRP, 'r');
  permissions[4] = checkpermission(mode, S_IWGRP, 'w');
  permissions[5] = checkpermission(mode, S_IXGRP, 'x');

  /* Other */
  permissions[6] = checkpermission(mode, S_IROTH, 'r');
  permissions[7] = checkpermission(mode, S_IWOTH, 'w');
  permissions[8] = checkpermission(mode, S_IXOTH, 'x');

  permissions[9] = '\0';
  return permissions;
}
