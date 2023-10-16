// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "internal_commands-POSIX.hpp"
#include "options_parser.h"
#include <iostream>
#include "unistd.h"
#include "ScriptRunner.hpp"
#include <filesystem>
//TODO main-like implementations of internal commands

static bool isValidName(std::string name) {
    for(auto s: name) {
        if(!isdigit(s) || !isalpha(s) || s != '_') {
            return false;
        }
    }
    return true;
}

int merrno(int argc, char *argv[]) {
    command_line_options_t command_line_options{argc, argv};
    int status, pid;
    pid = waitpid(-1, &status, 0);
    if (pid == -1) {
        if (errno == ECHILD) {
            errno = 0;
            return 0;
        } else {
            errno = -1;
            return -1;
        }
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
}

int mpwd(int argc, char *argv[]) {
    command_line_options_t commandLineOptions{argc, argv};
    std::cout << boost::filesystem::current_path() << std::endl;
    return 0;
}

int mcd(int argc, char *argv[]) {
    command_line_options_t commandLineOptions{argc, argv};
    if (argc > 2) {
        std::cerr << "mcd: too many arguments" << std::endl;
        errno = -1;
        return -1;
    }
    try {
        boost::filesystem::current_path(argv[1]);
    }
    catch (std::exception) {
            std::cerr << "mcd: " << argv[1] << ": No such file or directory" << std::endl;
            errno = -1;
            return - 1;
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
    for (size_t i = 1; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}

int mexport(int argc, char *argv[]) {
    command_line_options_t commandLineOptions(argc, argv);
    std::string name, value;
    char * token;
    for (size_t i = 1; i < argc; ++i) {
        auto location = strchr(argv[i], '=');
        bool found = location != nullptr;
        if (found && (isalpha(argv[i][0]) || argv[i][0] == '_')) {
            token = strtok(argv[i], "=");
            name = token;
            token = strtok(NULL, "=");
            if (token == NULL) {
                value = " ";
            }
            else {
                value = token;
            }
            if (isValidName(name)) {
                setenv(name.c_str(), value.c_str(), true);
            }
            else {
                std::cerr << "mexport: '" << name << "': not a valid identifier";
                errno = -1;
                return -1;
            }
        }
        else {
            std::cerr << "mexport: '" << argv[i] << "': not a valid identifier";
            errno = -1;
            return -1;
        }
    }
    return 0;
}

int mdot_command(int argc, char *argv[]) {
    ScriptRunner(argc - 1, argv + 1).run();
}
