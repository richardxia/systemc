/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/
//=====================================================================
///  @file report.cpp
//
///  @Details
///   
//
//=====================================================================
//  Original Authors:
//    Jack Donovan, ESLX
//=====================================================================

#include "reporting.h"                                // Reporting convenience macros

//static const char *filename = "report.cpp"; ///< filename for reporting

namespace report {
std::string print(const tlm::tlm_phase phase) 
{ 
  std::string os;
  switch (phase)
  {
    case tlm::BEGIN_REQ:        
      { 
        os =  "BEGIN_REQ";
        break;
      }
    case tlm::END_REQ:        
      { 
        os = "END_REQ";
        break;
      }  
    case tlm::BEGIN_RESP:
      { 
        os = "BEGIN_RESP";
        break;
      }
    case tlm::END_RESP:
      { 
        os = "END_RESP";
        break;
      }
    default:
      {     
//        char buffer[8];
//        snprintf(buffer,8," %d",int(phase));
//        os += buffer;
        os += "UNKNOWN: " + phase;        
        break;
      }
  }//end switch
  return os;
}

std::string print(const tlm::tlm_sync_enum status) 
{ //
  std::string os ( "TLM_" );
  switch (status)
  {
    case tlm::TLM_COMPLETED:        
      { 
        os = "COMPLETED";
        break;
      }
    case tlm::TLM_UPDATED:        
      { 
        os = "UPDATED";
        break;
      }  
    case tlm::TLM_ACCEPTED:
      { 
        os = "ACCEPTED";
        break;
      }
    default:
      { 
//        char buffer[8];
//        snprintf(buffer,8," %d",int(status));
//        os += buffer;
        os += "UNKNOWN: " + os;
        break;
      }
  }//end switch
  return os;
}
//=====================================================================
//  
///  @brief helper function for printing memory transactions
//   
//=====================================================================
void
print
( const int                 &ID              ///< Target ID/Initiator/?ID
, tlm::tlm_generic_payload  &gp          ///< transaction to be printed
, const char*               calling_filename
)
{
   std::ostringstream     msg;
   msg.str("");
   
   sc_dt::uint64 print_address  = gp.get_address();      // memory address
   unsigned char *print_data    = gp.get_data_ptr();    // data pointer
   unsigned int  print_length   = gp.get_data_length(); // data length
   tlm::tlm_command print_command = gp.get_command();     // memory command
     
   msg << "ID: "<< ID << " COMMAND: ";
       
   if (print_command == tlm::TLM_WRITE_COMMAND) msg << "WRITE";
   else msg << "READ";
       
   msg << " Length: " << internal << setw( 2 ) << setfill( '0' ) 
       << dec << print_length << endl;
   msg << "      Addr: 0x" << internal << setw( sizeof(print_address) * 2 ) 
       << setfill( '0' ) << uppercase << hex << print_address;  
   
   msg << " Data: 0x";
 /// @todo Fix endian issues for int longer than 4 bytes 
   //for (unsigned int i = 0; i < print_length; i++)
   //{
   // msg << internal << setw( 2 ) << setfill( '0' ) 
   //     << uppercase << hex << (int)print_data[i];
   //}
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[3];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[2];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[1];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[0];


   REPORT_INFO(calling_filename, __FUNCTION__, msg.str());
}
//=====================================================================
//  
///  @brief helper function for printing memory transactions
//   
//=====================================================================
void
print_full
( const int                 &ID              ///< Target ID/Initiator/?ID
, tlm::tlm_generic_payload  &gp          ///< transaction to be printed
, const char*               caller_filename
)
{
   std::ostringstream     msg;
   msg.str("");
   
   msg << "gp_ptr = " << &gp << endl << "      ";
   
   sc_dt::uint64 print_address  = gp.get_address();      // memory address
   unsigned char *print_data    = gp.get_data_ptr();    // data pointer
   unsigned int  print_length   = gp.get_data_length(); // data length
   tlm::tlm_command print_command = gp.get_command();     // memory command
     
   msg << "ID: "<< ID << " COMMAND: ";
       
   if (print_command == tlm::TLM_WRITE_COMMAND) msg << "WRITE";
   else msg << "READ";
       
   msg << " Length: " << internal << setw( 2 ) << setfill( '0' ) 
       << dec << print_length << endl;
   msg << "      Addr: 0x" << internal << setw( sizeof(print_address) * 2 ) 
       << setfill( '0' ) << uppercase << hex << print_address;  
   
   msg << " Data: 0x";
// @todo only prints 4 bytes at this time.
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[3];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[2];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[1];
    msg << internal << setw( 2 ) << setfill( '0' ) 
        << uppercase << hex << (int)print_data[0];
    
    msg << endl << "      "
        << "RSP STATUS = " << gp.get_response_string()
        << " STREAMING WIDTH = " << gp.get_streaming_width()
        << endl << "      "
        << "DMI ALLOWED = " << gp.is_dmi_allowed()
        << endl << "      "
 //       << "BYTE ENABLE PTR = " << gp.get_byte_enable_ptr()
        << "BYTE ENABLE LNGTH = " << gp.get_byte_enable_length();


   REPORT_INFO(caller_filename, __FUNCTION__, msg.str());
   
}
void  
print
( const int                 &ID              ///< Target ID/Initiator/?ID
, tlm::tlm_dmi              &dmi_properties     ///< dmi transaction to be printed
, const char*               calling_filename
)       
{  
   std::ostringstream     msg;
   msg.str("");
   msg << "Initiator: " << ID 
       << " &dmi_properties = " << &dmi_properties 
       << endl << "      ";
   msg << "start addr = " << dmi_properties.get_start_address()
       << " end addr = " << dmi_properties.get_end_address() 
       << endl << "      ";
   msg << "read latency = " << dmi_properties.get_read_latency()
       << " write latency = " << dmi_properties.get_write_latency() 
       << endl << "      ";
   msg << "granted access = " << dmi_properties.get_granted_access()
       << endl << "      ";
   
//   unsigned char*    temp_dmi_ptr = dmi_properties.get_dmi_ptr();
//   msg << "dmi_ptr = " << temp_dmi_ptr; 
   
   REPORT_INFO(calling_filename, __FUNCTION__, msg.str());
   
}     
    
}//end namespace
