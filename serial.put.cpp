#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions*/
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#define cimg_debug         2

//CIMG Library
#include "../CImg/CImg.h"

using namespace std;

#include "serialCOM.h"

//!todo: add CIMG library for command lines

int main(int argc, char *argv[])
{ 
  const int         verbose    = (cimg_option("-v",(const char*)NULL,"verbose option")!=NULL);
  const bool        show_info  = (cimg_option("--info",(const char*)NULL,"information")!=NULL);
  const bool        show_help  = (cimg_option("-h",(const char*)NULL,"information")!=NULL);
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const std::string Message =  cimg_option("--message","CONF:GAIN 1","Message to write to serial port (the example set the IFA300 gain to 1");

  if (show_help|show_info)
    return 0; // program stops after printing the information

  serialCOM::serialCOM serial;

  //string port;
  //string message;

  // OPEN 
  serial.port=SerialPath;
  int fd=serial.opens();
  // WRITE 
 serial.message=Message;
 cerr << "write:" << serial.message <<endl;
  serial.writes(fd);
}





