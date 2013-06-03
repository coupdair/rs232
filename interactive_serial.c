//interactive dialog with serial device
//http://en.wikibooks.org/wiki/Serial_Programming/Serial_Linux#termios

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
 
int main(int argc,char** argv)
{
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;
 
        printf("usage: %s /dev/ttyUSB0\n",argv[0]);
        printf("Interactive prompt with device:\n- use 'q' to quit,\n- type command then press 'enter' to send command.\n\n");
        std::cout<<std::flush;

        tcgetattr(STDOUT_FILENO,&old_stdio);
 
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;

//set stdout
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
//set stdin
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
 
        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;
 
        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud
 
//set serial device
        tcsetattr(tty_fd,TCSANOW,&tio);

//interactive loop
int i=0;
        unsigned char c='D';
        while (c!='q')
        {
                if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
                if (read(STDIN_FILENO,&c,1)>0)  {write(tty_fd,&c,1);std::cout<<c<<std::flush;}// if new data is available on the console, send it to both the serial port and the standard output
if (i==123)  {write(tty_fd,"*VER\r\n",5);}
++i;
        }
 
        close(tty_fd);
        tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
 
        return EXIT_SUCCESS;
}

