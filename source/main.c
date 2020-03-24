#include <stdio.h>
#include <dirent.h>
#include <string.h>

int listdir(const char *path)
{
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL)
    {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dp)))
    {
        if (strstr(entry->d_name, ".c") == entry->d_name + entry->d_namlen - 2)
        {
            printf("%s/%s\n", path, entry->d_name);
        }
        if (entry->d_type == DT_DIR && (strchr(entry->d_name, '.') != entry->d_name))
        {
            char fullPath[FILENAME_MAX] = {};
            sprintf(fullPath, "%s/%s", path, entry->d_name);
            listdir(fullPath);
        }
    }
    
    closedir(dp);
    return 0;
}

int main(int argc, char **argv)
{
    int counter = 1;

    if (argc == 1)
        listdir(".");

    while (++counter <= argc)
    {
        printf("\nListing %s...\n", argv[counter - 1]);
        listdir(argv[counter - 1]);
    }
    getchar();
    return 0;
}