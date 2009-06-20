// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// AIRSCHED
#include <airsched/command/FileMgr.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  void FileMgr::
  readAndProcessTravelSolutionInputFile (const std::string& iInputFileName) {

    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      AIRSCHED_LOG_ERROR ("Can not open input file \"" << iInputFileName
                           << "\"");
      throw new FileNotFoundException();
    }
    
    char buffer[80];
    double dval=0.0;
    std::string dvalStr;
    short i = 1;
    bool hasAllPArams = true;

    std::string dAirport;
    std::string aAirport;
    Date_T depDate;
    Duration_T depTime;
    Duration_T arTime;
    Duration_T dur;
    bool Ref;
    std::string airline;
    std::string cabin;
    int flightNum;
    double fare;
    int lagsNum;
    bool SNS;
    bool change;
    
    while (inputFile.getline (buffer, sizeof (buffer), ';')) {
      std::istringstream iStringStr (buffer);

      bool hasRead = false;

      if (i == 1) {
        hasAllPArams = true;
      }

      if (i>=1 && i<=14) {
        hasRead = (iStringStr >> dvalStr);
      }

      if (i == 15) {
        hasRead = (iStringStr >> dval);
      }

      if (hasRead) {
        if (i == 1) {
          dAirport = dvalStr;

        } else if (i == 2) {
          aAirport = dvalStr;
          // std::cout << "City Pair = '" << dAiport
          // << "-" << aAirport << "'" << std::endl;

        } else if (i == 3) {
          depDate = boost::gregorian::from_simple_string (dvalStr);
          // std::cout << "Date = '" << depDate << "'" << std::endl;

        } else if (i == 4) {
          depTime = boost::posix_time::duration_from_string (dvalStr);

        } else if (i == 5) {
          arTime = boost::posix_time::duration_from_string (dvalStr);

        } else if (i == 6) {
          dur = boost::posix_time::duration_from_string (dvalStr);

        } else if (i == 7) {
          if (dvalStr == "refundable fare")
            Ref = true;
          else Ref  = false;

        } else if (i == 8) {
          airline = dvalStr;

        } else if (i == 9) {
          cabin = dvalStr;

        } else if (i == 10) {
          flightNum = dval;

        } else if (i == 11) {
          fare = dval;

        } else if (i == 12) {
          lagsNum = dval;

        } else if (i == 13) {
          if (dvalStr == "Saturday Nigth Stay mandatory")
            SNS = true;
          else SNS = false;

        } else if (i == 14) {
          if (dvalStr == "changeable fare")
            change = true;
          else change = false;
          i = 0;
        }
        i++;
      } else {
        hasAllPArams = false;
      }

    }

    if (hasAllPArams && i == 1) {
      AIRSCHED_LOG_DEBUG ("Successfully read");
    }
    
    if (!inputFile.eof()) {
      AIRSCHED_LOG_ERROR ("Problem when reading input file \""
                          << iInputFileName << "\"");
    }

  }
}