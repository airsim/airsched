#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>

// Forward declarations.
namespace stdair {
  class STDAIR_Service;
  struct BasLogParams;
}

namespace AIRSCHED {

  /** Forward declaration. */
  class AIRSCHED_ServiceContext;

  
  /** Interface for the AIRSCHED Services. */
  class AIRSCHED_Service {
  public:
    // ////////////////// Constructors and Destructors //////////////////    
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input schedule file. */
    AIRSCHED_Service (const stdair::BasLogParams&,
                      const stdair::Date_T& iStartAnalysisDate,
                      const stdair::Filename_T& iScheduleInputFilename);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the AIRSCHED_Service
        is itself being initialised by another library service such as
        SIMCRS_Service).
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input schedule file. */
    AIRSCHED_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                      const stdair::Date_T& iStartAnalysisDate,
                      const stdair::Filename_T& iScheduleInputFilename);
    
    /** Destructor. */
    ~AIRSCHED_Service();

    
  public:    
    // ////////////////// Business support methods //////////////////    
    /** Add a travel solution to the service context.
        <br>Currently, that method does nothing. */
    void addTravelSolution (const stdair::AirportCode_T& iDepartureAirport,
                            const stdair::AirportCode_T& iArrivalAirport,
                            const stdair::Date_T& iDepartureDate,
                            const stdair::Duration_T& iDepartureTime,
                            const stdair::Duration_T& iArrivalTime,
                            const stdair::Duration_T& iDuration,
                            const bool iRefundability,
                            const stdair::AirlineCode_T& iAirlineCode,
                            const stdair::CabinCode_T& iCabinCode,
                            const stdair::FlightNumber_T& iFlightNumber,
                            const stdair::Fare_T& iFare,
                            int iStopsNumber, bool iSNS, bool iChangeability);

    /** Calculate and return a list of travel solutions corresponding to a given
        product demand. */
    void getTravelSolutions (stdair::TravelSolutionList_T&,
                             const stdair::BookingRequestStruct&);

    /** Perform a small simulation, which uses the Customer Choice Model.
        <br>Currently, that method does nothing.*/
    void simulate();

    
  private:
    // ////////////////// Constructors and Destructors //////////////////    
    /** Default Constructors, which must not be used. */
    AIRSCHED_Service ();
    AIRSCHED_Service (const AIRSCHED_Service&);

    /** Initialise the (AIRSCHED) service context (i.e., the
        AIRSCHED_ServiceContext object). */
    void initServiceContext ();

    /** Initialise the STDAIR service (including the log service).
        <br>A reference on the root of the BOM tree, namely the BomRoot object,
        is stored within the service context for later use.
        @param const stdair::BasLogParams& Parameters for the output log
               stream. */
    void initStdAirService (const stdair::BasLogParams&);
    
    /** Initialise.
        <br>The CSV file, describing the airline schedules for the
        simulator, is parsed and the inventories are generated accordingly.
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input schedule file. */
    void init (const stdair::Date_T& iStartAnalysisDate,
               const stdair::Filename_T& iScheduleInputFilename);
    
    /** Finaliser. */
    void finalise ();

    
  private:
    // ////////////////// Service Context //////////////////
    /** Service Context. */
    AIRSCHED_ServiceContext* _airschedServiceContext;
  };
}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
