// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYSHELL_INTERNAL_COMMANDS_POSIX_HPP
#define MYSHELL_INTERNAL_COMMANDS_POSIX_HPP

#include "options_parser.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "boost/program_options.hpp"
namespace po = boost::program_options;

//"merrno",
//"mpwd",
//"mcd",
//"mexit",
//"mecho",
//"mexport",
//"." - mdot_command,



int merrno(int argc, char *argv[]);

int mpwd(int argc, char *argv[]);

int mcd(int argc, char *argv[]);

int mexit(int argc, char *argv[]);

int mecho(int argc, char *argv[]);

int mexport(int argc, char *argv[]);

int mdot_command(int argc, char *argv[]);

int mdummy_command(int argc, char*argv[]);

static bool is_valid_name(std::string name);

std::tuple<po::variables_map, po::options_description> get_variables_map(int argc, char *argv[]);
#endif //MYSHELL_INTERNAL_COMMANDS_POSIX_HPP

