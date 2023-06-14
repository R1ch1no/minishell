

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



void printOpenFileDescriptors() {
    int fd;
    int max_fd = sysconf(_SC_OPEN_MAX);  // Maximum number of file descriptors

    for (fd = 0; fd < max_fd; ++fd) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("File descriptor %d is open.\n", fd);
        }
    }
}

/*
//clsong a file will close all its fd's it seems; OK NO SEEMS I WAS RIGHT IDK so fd= doesnt create a new fd but dup does blabbla
int main()
{
    int fd[2];
    
    pipe(fd);
    //int cpy1 = fd[0]; 
    //int cpy2 = fd[0]; 
    
    int dup0 = dup(fd[0]);
    int dup1 = dup(fd[1]);
    //int dup2 = dup(fd[1]); 
    //code above creates 2 fds cpy doesnt create a fd
    //standard fds 3 and with pipe 2 more in total five
    
    //the following close calls will close the fds from pipe
    //close(cpy1);
    //close(cpy2);
    //close(dup0);
    //close(dup1);
    //close(fd[1]);

    //the following code shows that with clsong dup not all fds are closed 
    //u just have anothe 
    
    //pipe(fd);
    //int dup = fd[0];
    //close(dup);
    //close(fd[0]);
    //close(fd[1]);

    printOpenFileDescriptors();
}*/


//STDIN and STDOUT
int main()
{
    int dup0 = dup(STDIN_FILENO);
    int dup1 = dup(STDOUT_FILENO);
    
    close(dup0);
    close(dup1);

    //close(STDIN_FILENO);
    //close(STDOUT_FILENO);

    printf("HELLO\n");
    printOpenFileDescriptors();
}