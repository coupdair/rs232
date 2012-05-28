//serial put
/*-----------------------------------------------------------------------
  File        : serial_put.cpp
  Description : Particle Image Velocimetry program of the Laboratory of Mechanics in Lille (LML)
  Authors     : Caroline BRAUD, Sebastien COUDERT
-----------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxygen)*/
/** \mainpage
 *
 *  index:
 *  \li \ref sectionCommandLine
 *  \li \ref sectionSerialDocumentation
 *  \li \ref sectionDoxygenSyntax
 *
 *  \section sectionCommandLine command line options
 *  Mainly 2 test programs may be built:
 *  \li get: to get a value from RS232 device,
 *  \li put: to set a value to RS232 device.
 *
 *  \li get: return value as text on standard output
 *  \verbinclude "serial_get.help.output"
 *  
 *  \li put: set value
 *  \verbinclude "serial_put.help.output"
 *
 *  \section sectionSerialDocumentation documentation outline
 *  This is the reference documentation of <a href="http://www.meol.cnrs.fr/">serial</a>, from the <a href="http://www.univ-lille1.fr/lml/">LML</a>.\n\n
 *  serial RS232 software. The basis class is in <a href="serialCOM_8h.html">serialCOM.h</a> source file.\n\n
 *  This documentation has been automatically generated from the sources, 
 *  using the tool <a href="http://www.doxygen.org">doxygen</a>. It should be readed as HTML, LaTex and man page.\n
 *  It contains both
 *  \li a detailed description of all classes and functions
 *  \li TODO: a user guide (cf. \ref pages.html "related pages")
 *
 *  that as been documented in the sources.
 *
 *  \par Additional needed libraries:
 *
 *  \li <a href="http://cimg.sourceforge.net">the CImg Library</a> (v1.?.?) for command line options, only.
 *
 *  \section sectionDoxygenSyntax make documentation using Doxygen syntax
 *  Each function in the source code should be commented using \b doxygen \b syntax in the same file.
 *  The documentation need to be written before the function.
 *  The basic syntax is presented in this part.
 *  \verbinclude "doxygen.example1.txt"
 *
 *  Two kind of comments are needed for \b declaration and \b explanation \b parts of the function:
 *  Standart documentation should the following (\b sample of code documentation):
 *  \verbinclude "doxygen.example2.txt"
 *
 *  In both declaration and explanation part, \b writting and \b highlithing syntax can be the following:\n\n
 *  \li \c \\code to get\n
 *
 *  \li \c \\n    a new line
 *  \li \c \\li   a list (dot list)
 *
 *  \li \c \\b    bold style
 *  \li \c \\c    code style
 *  \li \c \\e    enhanced style (italic)
 *
 *  For making \b shortcut please use:\n
 *  \li \c \\see to make a shortcut to a related function or variable
 *  \li \c \\link to make a shortcut to a file or a function
 *  \note this keyword needs to be closed using \c \\end*
 *
 *  \li \c \\todo to add a thing to do in the list of <a href="todo.html">ToDo</a> for the whole program
 *
 *  In explanation part, \b paragraph style can be the following:\n
 *  \li \c \\code for an example of the function use
 *  \li \c \\note to add a few notes
 *  \li \c \\attention for SOMETHING NOT FULLY DEFINED YET
 *  \li \c \\warning to give a few warning on the function
 *  \note these keywords need to be closed using \c \\end*
 *
 *  \verbinclude "doxygen.example3.txt"
 *
 *  Many other keywords are defined, so please read the documentation of <a href="http://www.doxygen.org/commands.html">doxygen</a>.
 *
**/

//! \todo serial_put doxygen user page

//standard library
#include <iostream>
//CImg Library
#include "../CImg/CImg.h"
//RS232 library
#include "serialCOM.h"
#include "serial.h"

int main(int argc, char *argv[])
{ 
//commmand line options
 ///usage
  cimg_usage(std::string("serial_put a RS232 program of the Laboratory of Mechanics in Lille (LML), it is intended to send a message through the serial cable to a RS232 device, \
it uses different GNU libraries (see --info option)\n\n \
usage: ./get --message \"*IDN?\"\n \
       ./put --message \"CONF:GAIN 5\"\n \
       ./get --message \"READ:GAIN?\"\n \
version: "+std::string(VERSION)+"\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///serial related variable
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const std::string Message =  cimg_option("--message","CONF:GAIN 1","Message to write to serial port (the example set the IFA300 gain to 1");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}
//serial object
//  serialCOM serial;
  serial serial;
// OPEN 
  if(!serial.opens(SerialPath)) return 1;
// WRITE 
  std::cerr << "write:" << Message <<std::endl;
  if(!serial.writes(Message))   return 1;
//CLOSE
  serial.closes();
  return 0;
}//main

