#include "lsr.h"


void print_depth(int depth)
{
    int i = 0;
    for(; i < depth; i++)
        printf("----");
}

void print_permission(struct stat mystat, char *file_path, int depth)
{
    struct tm *tm;
    char file_modified_time[100];
    
    tm = localtime(&mystat.st_mtime);
    sprintf(file_modified_time, "%s %d %d:%d", month(tm->tm_mon + 1), tm->tm_mday, tm->tm_hour, tm->tm_min);
    
    print_depth(depth);
    
    //
    printf("%s%s%s%s%s%s%s%s%s%s %d %s %s %d %s %s\n",
           (S_ISDIR(mystat.st_mode)) ? "d" : "-",
           (mystat.st_mode & S_IRUSR) ? "r" : "-",
           (mystat.st_mode & S_IWUSR) ? "w" : "-",
           (mystat.st_mode & S_IXUSR) ? "x" : "-",
           (mystat.st_mode & S_IRGRP) ? "r" : "-",
           (mystat.st_mode & S_IWGRP) ? "w" : "-",
           (mystat.st_mode & S_IXGRP) ? "x" : "-",
           (mystat.st_mode & S_IROTH) ? "r" : "-",
           (mystat.st_mode & S_IWOTH) ? "w" : "-",
           (mystat.st_mode & S_IXOTH) ? "x" : "-",
           mystat.st_nlink,
           getUserName(mystat.st_uid),
           getGroupName(mystat.st_gid),
           mystat.st_size,
           file_modified_time,
           file_path);//these are one line
}

void ls_file(char *fileName)
{
    struct stat mystat;
    if(stat(fileName, &mystat) != -1)
        print_permission(mystat, fileName, 0);
    exit(0);
}

int do_ls(char *dirName, int depth)
{
    
    char path[100] = "";
    DIR *dirp;
    struct dirent *direntp;
    struct stat mystat;
    
    strcpy(path, dirName);
    
    if (!(dirp  = opendir(path)))
        ls_file(path);
    
    while ((direntp = readdir(dirp)))
    {
        if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0) continue;
        
        char file_path[100] = "";
        sprintf(file_path, "%s/%s", path, direntp->d_name);
        
        if(stat(file_path, &mystat) != -1)
        {
            print_permission(mystat, file_path, depth);
            if(S_ISDIR(mystat.st_mode))
                do_ls(file_path, depth+1);
        }
    }
    closedir(dirp);
}


char *getUserName(uid_t uid) /* how to convert a user ID to a user name */
{
    struct passwd *pw = getpwuid(uid);
    return pw->pw_name ? pw->pw_name : "";
}

char *getGroupName(gid_t gid)
{
    struct group* gr = getgrgid(gid);
    return gr->gr_name ? gr->gr_name : "";
}

char *month(int m)
{
    switch (m) {
        case 1:
            return "Jan";
            break;
            
        case 2:
            return "Feb";
            break;
            
        case 3:
            return "Mar";
            break;
            
        case 4:
            return "Apr";
            break;
            
        case 5:
            return "May";
            break;
            
        case 6:
            return "Jun";
            break;
            
        case 7:
            return "Jul";
            break;
            
        case 8:
            return "Aug";
            break;
            
        case 9:
            return "Sep";
            break;
            
        case 10:
            return "Oct";
            break;
            
        case 11:
            return "Nov";
            break;
            
        case 12:
            return "Dec";
            break;
            

        default:
            break;
    }
}
