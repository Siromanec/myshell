// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "internal_commands.hpp"

//TODO main-like implementations of internal commands

int merrno(int argc, char *argv[]){
    command_line_options_t command_line_options{argc, argv};
    int status, pid;
    pid = waitpid(-1, &status, 0);
    if (pid == -1){
        if (errno == ECHILD){
            return 0;
        }
        else {
            return -1;
        }
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

}
