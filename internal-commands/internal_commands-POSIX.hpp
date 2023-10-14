//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_INTERNAL_COMMANDS_POSIX_HPP
#define MYSHELL_INTERNAL_COMMANDS_POSIX_HPP

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


#endif //MYSHELL_INTERNAL_COMMANDS_POSIX_HPP
