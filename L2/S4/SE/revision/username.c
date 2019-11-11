#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

int main(int argc, char **argv){
    struct stat s;
    struct passwd *p;

    stat(argv[1], &s);
    p = getpwuid(s.st_uid);
    printf("%s\n", p->pw_name);
    return 0;
}
