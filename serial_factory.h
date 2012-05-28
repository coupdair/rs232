#ifndef SERIAL_COMMUNICATION_FACTORY
#define SERIAL_COMMUNICATION_FACTORY

#include "serial.h"
#include "serialCOM.h"

class Cserial_factory
{
public:
  //! class name for debug only
#if cimg_debug>1
  std::string class_name;
#endif

  //! constructor
  /**
   *
  **/
  Cserial_factory()
  {
#if cimg_debug>1
    class_name="serial_factory";
#endif
  }//constructor

  //! create a serial port of a specific \c type
  /** 
   *
   * @param[in] type: type of port (e.g. type==1 <=> \c Cserial_system type)
   *
   * @return 
   */
  Cserial* create(int type)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"("<<type<<")\n"<<std::flush;
#endif
   switch(type)
    {
      //case 0: return new Cserial;  break;//virtual
      case 1: return new Cserial_system;  break;
      case 2: return new Cserial_termios; break;
      default:
      {
        std::cerr<<class_name<<"::"<<__func__<<": error: serial type="<<type<<" is unknown\n"<<std::flush;
        return NULL; break;
      }
    }
  }//create
  //! create a serial port of a specific \c type
  /** 
   *
   * @param[in] type: type of port (e.g. type=="serial_system" <=> \c Cserial_system type)
   *
   * @return 
   */
  Cserial* create(std::string type_name)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"("<<type_name<<")\n"<<std::flush;
#endif
    if(type_name=="serial_system") return create(1);
    else if(type_name=="serial_termios") return create(2);
    else
    {
      std::cerr<<class_name<<"::"<<__func__<<": error: serail type="<<type_name<<" not handled.\n"<<std::flush;
      return NULL;
    }
  }//create
//  Cserial* create(CNetCDFParameter &fp)

};//Cserial_factory class

#endif //SERIAL_COMMUNICATION_FACTORY

