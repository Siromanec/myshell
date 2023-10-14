//
// Created by ADMIN on 11-Oct-23.
//

#include "internal_commands-POSIX.hpp"
#include "options_parser.h"
#include "iostream"
#include "unistd.h"
//TODO main-like implementations of internal commands

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
