#include <dirent.h>
#include <stdio.h>


int main(const int argc, const char *argv[])
{
  if (argc < 2) {
    printf("null\n");
    return 1;
  }
  DIR *dir = opendir(argv[1]);
  if (dir == NULL) {
    printf("failed to open %s\n", argv[1]);
    return 1;
  }
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
  }

  closedir(dir);
  return 0;
}
