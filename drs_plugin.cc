#include "drs_plugin.h"

#include <daq_device_drs.h>
//#include <daq_device_tspmparams.h>

#include <strings.h>

int drs_plugin::create_device(deviceblock *db)
{

  //  std::cout << __LINE__ << "  " << __FILE__ << "  " << db->argv0 << "  " << db->npar << std::endl;

  int eventtype;
  int subid;

  if ( strcasecmp(db->argv0,"device_drs") == 0 ) 
    {
      // we need at least 3 params
      if ( db->npar <3 ) return 1; // indicate wrong params
      
      eventtype  = atoi ( db->argv1); // event type
      subid = atoi ( db->argv2); // subevent id

      if ( db->npar == 3)
	{

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 4)
	{
	  int trigger = atoi ( db->argv3);

	  std::cout << __FILE__ << "  " << __LINE__ 
		    << trigger << " "  
		    << std::endl;

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid,
					      trigger ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 5)
	{
	  int trigger = atoi ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  std::cout << __FILE__ << "  " << __LINE__ 
		    << trigger << " "  
		    << th << "  "
		    << std::endl;

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid,
					      trigger, th ));
	  return 0;  // say "we handled this request" 
	}
      else if ( db->npar == 6)
	{
	  int trigger = atoi ( db->argv3);
	  float th = strtof ( db->argv4, 0);
	  
	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = atoi ( db->argv5);
	    }
	  std::cout << __LINE__ << "  " << db->argv5 << "  " << slope << std::endl;

	  std::cout << __FILE__ << "  " << __LINE__ 
		    << trigger << " "  
		    << th << "  "
		    << slope << "  "
		    << std::endl;

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid,
					      trigger, th, slope ));
	  return 0;  // say "we handled this request" 
	}


      else if ( db->npar == 7)
	{
	  int trigger = atoi ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = atoi ( db->argv5);
	    }
	  std::cout << __LINE__ << "  " << db->argv5 << "  " << slope << std::endl;

	  int delay = atoi ( db->argv6);

	  std::cout << __FILE__ << "  " << __LINE__ << "  " 
		    << trigger << " "  
		    << th << "  "
		    << slope << "  "
		    << delay << "  "
		    << std::endl;

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid,
					      trigger, th, slope, delay ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 8)
	{
	  int trigger = atoi ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = atoi ( db->argv5);
	    }
	  std::cout << __LINE__ << "  " << db->argv5 << "  " << slope << std::endl;

	  int delay = atoi ( db->argv6);
	  int speed = atoi ( db->argv7);

	  std::cout << __FILE__ << "  " << __LINE__ << "  " 
		    << trigger << " "  
		    << th << "  "
		    << slope << "  "
		    << delay << "  "
		    << speed 
		    << std::endl;

	  add_readoutdevice ( new daq_device_drs( eventtype,
					      subid,
					      trigger, th, slope, delay, speed ));
	  return 0;  // say "we handled this request" 
	}

      else
	{
	  return 1; // say it is our device but the parameters are wrong 
	}
    }  

  return -1; // say " this is not our device"
}

void drs_plugin::identify(std::ostream& os, const int flag) const
{
      os << " flag is " << flag  << std::endl;
  if ( flag <=2 )
    {
      os << " - DRS Plugin" << std::endl;
    }
  else
    {
      os << " - DRS Plugin, provides - " << std::endl;
      os << " -     device_drs (evttype, subid, triggerchannel, triggerthreshold[mV], slope[n/p], delay[ns]) - DRS4 Eval Board " << std::endl;
      //      os << " -     device_tspmparams (evttype, subid, IP addr) - readback of TSPM configuration" << std::endl;
    }
      
}


drs_plugin _dp;
