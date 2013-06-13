#ifndef SERIAL_COMMUNICATION_TERMIOS
#define SERIAL_COMMUNICATION_TERMIOS

#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "serial.h"

#define SERIAL_OPEN_ERROR  -1
#define SERIAL_CLOSED      -2

class Cserial_termios: public Cserial
{
public:
  //!File descriptor for the port
  int fd;
//! \todo [high] . \c last_message_written, \c last_message_readed (remove \c message).
//! \todo [medium] _ error handling: init fd to SERIAL_CLOSED (i.e. constructor), return code error in all functions but opens() (i.e. if(fd!=SERIAL_CLOSED) closes(); ).
//! \todo [next]   _ call closes in destructor (e.g. add also if(fd!=SERIAL_CLOSED) in closes).
//! \todo [low] move opens, writes, reads and closes to .cpp (i.e. need Makefile changes)
  Cserial_termios()
  {
#if cimg_debug>1
    class_name="Cserial_termios";
#endif
  }//constructor

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens()
  {
    fd=open((const char*)port_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == SERIAL_OPEN_ERROR)
    {
      std::cerr<<"open_port: Unable to open "<<port_path<<" port.\n";//e.g. /dev/ttyUSB0
      return false;
    }
    fcntl(fd, F_SETFL, 0);
#if cimg_debug>1
    std::cerr <<class_name<<"::information: ";
#endif
    std::cerr << "port is open"<<std::endl;
    return true;
  }//opens

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens(const std::string& port_path_name)
  {
    return Cserial::opens(port_path_name);
  }//opens
  
  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
#endif
    last_message_written=value;
    value.append("\r\n");
    int  tries=0;        /* Number of tries so far */
    while(write(fd,(const char*)value.c_str(),value.size()) <value.size())
      {
	tries++;
	if (tries > number_of_try)
	  {
	    std::cerr<<"error: write KO :( (with "<<--tries<<" tries)\n"<<std::flush;
	    return false;
	  }
	std::cerr<<"warning: rs232 not ready, retry\n"<<std::flush;
        cimg_library::cimg::wait(try_wait_time);
      }//try loop
    std::cerr << "write OK\n" << std::flush;
    return true;
  }//writes

  //! read on serial port
  /** 
   *
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  bool reads(std::string& value)
  {
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(get \""<<value<<"\")\n"<<std::flush;
#endif
    char buffer[255];  /* Input buffer */
    char *bufptr;      /* Current char in buffer */
    int  nbytes;       /* Number of bytes read */
    //std::string value;
//std::cerr<<__func__<<"/sizeof(buffer)="<<sizeof(buffer)<<"\n"<<std::flush;
    //initialisation
//    std::memset(buffer,0,255);
    //read loop
    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
      {
	std::cerr << "reading buffer" << std::endl;
std::cerr<<"nbytes="<<nbytes<<"\n"<<std::flush;
	bufptr += nbytes;
	if (bufptr[-1] == '\n' )// || bufptr[-1] == '\r')
	  break;
      }
std::cerr <<"nbytes="<<nbytes<<"\n"<< std::flush;
if (bufptr[-1] == '\n' ) std::cerr << "last is \\n\n" << std::flush;
if (bufptr[-1] == '\r' ) {std::cerr << "last is \\r\n" << std::flush;read(fd,bufptr,1);std::cerr << "  clear last \\n\n" << std::flush;}
    std::cerr << "read OK\n" << std::flush;
    buffer[bufptr-buffer-1]='\0';
//std::cerr<<__func__<<"/lenght(buffer)="<<strlen(buffer)<<"\n"<<std::flush;
    value=buffer;
    last_message_readed=value;//for information
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(set \""<<value<<"\")\n"<<std::flush;
#endif
    return true;
  }//reads

  //! get a value from device on serial port (i.e. write then read; e.g. ask for a value)
  /** 
   *
   * @param[in]  ask=ask for a variable value (writes: string to send to serial port) 
   * @param[out] value=returned value (reads: value returned by serial port)
   *
   * @return 
   */
  bool gets(std::string ask,std::string &value,const int number_of_try=3,const int try_wait_time=20)
  {
    #if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(\""<<ask<<"\", value, number_of_try="<<number_of_try<<", wait_time="<<try_wait_time<<")\n"<<std::flush;
    #endif
// WRITE 
    if(!this->writes(ask,number_of_try,try_wait_time)) return false;
// READ
    if(!this->reads(value)) return false;
    return true;
  }//gets

  //! Close serial port
  /** 
   *
   * @return 
   */
  bool closes()
  {
    close(fd);
    fd=SERIAL_CLOSED;
    return true;
  }//closes

};//Cserial_termios class

class Cserial_termios_8n1: public Cserial_termios
{
public:
  Cserial_termios_8n1()
  {
#if cimg_debug>1
    class_name="Cserial_termios_8n1";
#endif
  }//constructor

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens()
  {
/*
    struct termios tio;
    //set serial structure
    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;//cfg.: 8n1 (see termios.h for more information)
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;
    //open  serial device
#if cimg_debug>1
    std::cerr <<class_name<<"::information: ";
#endif
    fd=open((const char*)port_path.c_str(), O_RDWR | O_NONBLOCK);
    ///check
    if (fd == SERIAL_OPEN_ERROR)
    {
      std::cerr<<"open_port: Unable to open "<<port_path<<" port.\n";//e.g. /dev/ttyUSB0
      return false;
    }
    //setup serial device
    cfsetospeed(&tio,B115200);// 115200 baud
    cfsetispeed(&tio,B115200);// 115200 baud
    tcsetattr(fd,TCSANOW,&tio);
    std::cerr << "port is open"<<std::endl;
{//test: get version
unsigned char c;
//ask     version
const char* message="*VER\r\n";
std::cerr<<message<<std::endl;
write(fd,message,5);
write(fd,message,5);
//receive version
std::cerr<<"read='"<<std::flush;
while(read(fd,&c,1)>0) std::cerr<<c;
std::cerr<<"'."<<std::endl;
}
*/
        struct termios tio;
        int tty_fd;

        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;
 
        tty_fd=open((const char*)port_path.c_str(), O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud
 
//set serial device
        tcsetattr(tty_fd,TCSANOW,&tio);

write(tty_fd,"*VER\r\n",6);

//message
std::string txt;txt.resize(1024);
int t=0;
//time out
int tries=1234;
int count=0;
    //get single message
    unsigned char c='D';
    while (c!='\r')
    {//get message until line break character
      if(read(tty_fd,&c,1)>0) txt[t++]=c;// if new data is available on the serial 
      cimg_library::cimg::wait(1);
      ++count;
      if(count>tries) break;//time out
    }

//        close(tty_fd);
fd=tty_fd;

std::cerr<<"time"<<std::string((count<tries)?" count=":"  out=")<<count<<".\n";//time out
for(int i=0;i<txt.size();++i) {if(txt[i]=='\r') txt[i]='_';if(txt[i]=='\n') txt[i]='!';}
if(t>0) txt.resize(t-1);
std::cerr<<"text["<<t<<","<<txt.length()<<"]|"<<txt<<"|\n"; 

    return true;
  }//opens

};//Cserial_termios_8n1 class
#endif //SERIAL_COMMUNICATION_TERMIOS

