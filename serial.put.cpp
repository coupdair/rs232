#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions*/
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

using namespace std;

#include "serialCOM.h"

//!todo: add CIMG library for command lines

int main(void)
{ 
  serialCOM::serialCOM serial;

  //string port;
  //string message;

  // OPEN 
  serial.port="/dev/ttyUSB0";
  int fd=serial.opens();
  // WRITE 
 serial.message="INST:CNUM?";
 cerr << "write:" << serial.message <<endl;
  serial.writes(fd);
}





