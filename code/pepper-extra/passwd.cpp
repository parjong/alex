#include "pepper/passwd.hpp"

#include <iostream>

namespace {

  #include <termios.h>
  #include <unistd.h>

  // NOTE These functions are platform-dependent
  bool get_echo_mode()
  {
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);

    return tty.c_lflag & ECHO;
  }

  void set_echo_mode(bool flag)
  {
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);

    if ( !flag )
      tty.c_lflag &= ~ECHO;
    else
      tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
  }
  
}

namespace pepper { namespace passwd {

  std::string unix_reader::read(const std::string &prompt)
  {
    std::string s;

    std::cout << prompt;

    bool echo_mode = ::get_echo_mode();

    ::set_echo_mode(false);
    std::cin >> s;
    ::set_echo_mode(echo_mode);

    std::cout << std::endl;

    return s;
  }

} }
