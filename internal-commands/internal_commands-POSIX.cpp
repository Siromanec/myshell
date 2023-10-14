// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "internal_commands-POSIX.hpp"
#include "options_parser.h"
#include "iostream"
#include "unistd.h"
//TODO main-like implementations of internal commands

int merrno(int argc, char *argv[]){
    command_line_options_t command_line_options{argc, argv};
    int status, pid;
    pid = waitpid(-1, &status, 0);
    if (pid == -1){
        if (errno == ECHILD){
            errno = 0;
            return 0;
        }
        else {
            errno = -1;
            return -1;
        }
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

int mpwd(int argc, char *argv[]) {
    command_line_options_t commandLineOptions{argc, argv};
    std::string buff;
    buff.resize(100);
    while(getcwd(buff.data(), buff.size()) == NULL) {
        if (errno == ERANGE) {
            buff.resize(buff.size() * 2);
        } else {
            std::cerr << "mpwd: cannot get current directory" << std::endl;
            errno = -1;
            return -1;
        }
    }
    std::cout << buff << std::endl;
    return 0;
}

int mcd(int argc, char *argv[]) {
    command_line_options_t commandLineOptions{argc, argv};
    if (argc != 2) {
        std::cerr << "mcd: too many arguments" << std::endl;
        errno = -1;
        return -1;
    }
    if(chdir(argv[1]) < 0){
        if (errno == ENOTDIR) {
            std::cerr << "mcd: " << argv[1] << ": Not a directory" << std::endl;
            errno = -1;
            return -1;
        }
        else {
            std::cerr << "mcd: " << argv[1] << ": No such file or directory" << std::endl;
            errno = -1;
            return - 1;
        }
    }
    return 0;
}

int mexit(int argc, char *argv[]) {
    command_line_options_t commandLineOptions(argc, argv);
    if (argc == 1){
        exit(EXIT_SUCCESS);
    }
    for(size_t i = 0; i < strlen(argv[1]); ++i) {
        if(!isdigit(argv[1][i])) {
            std::cerr << "mexit: " << argv[1]<< ": numeric argument required" << std::endl;
            errno = -1;
            exit(EXIT_FAILURE);
        }
    }
    exit(atoi(argv[1]));
}

int mecho(int argc, char *argv[]) {
    command_line_options_t commandLineOptions(argc, argv);
    for (size_t i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
