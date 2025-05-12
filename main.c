#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void print_permissions(mode_t mode) 
{
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

void list_directory(const char *path, int long_format) 
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir) 
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_name[0] == '.') continue; // skip hidden files

        if (long_format) 
        {
            char full_path[1024];
            struct stat file_stat;

            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            if (stat(full_path, &file_stat) == -1) 
            {
                perror("stat");
                continue;
            }

            print_permissions(file_stat.st_mode);
            printf(" %ld", file_stat.st_nlink);

            struct passwd *pw = getpwuid(file_stat.st_uid);
            struct group *gr = getgrgid(file_stat.st_gid);

            printf(" %s %s", pw->pw_name, gr->gr_name);
            printf(" %5ld", file_stat.st_size);

            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
            printf(" %s", timebuf);

            printf(" %s\n", entry->d_name);
        } 
        else 
        {
            printf("%s  ", entry->d_name);
        }
    }

    if (!long_format)
        printf("\n");

    closedir(dir);
}

int main(int argc, char *argv[])  
{
    int long_format = 0;
    const char *path = "."; // default path is current directory

    // parse arguments
    if (argc == 2) 
    {
        if (strcmp(argv[1], "-l") == 0) 
        {
            long_format = 1;
        } 
        else 
        {
            path = argv[1];
        }
    } 
    else if (argc == 3 && strcmp(argv[1], "-l") == 0) 
    {
        long_format = 1;
        path = argv[2];
    }

    list_directory(path, long_format);
    return 0;
}
