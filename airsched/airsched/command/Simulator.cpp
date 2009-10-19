// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <string>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/BomRootStructure.hpp>
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/FlightDateStructure.hpp>
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/SegmentCabinStructure.hpp>
#include <stdair/bom/BookingClassStructure.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/bom/BomRoot.hpp>
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/bom/SegmentCabin.hpp>
#include <airsched/bom/LegCabin.hpp>
#include <airsched/bom/BookingClass.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate () {
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomRoot object)
    BomRoot& lBomRoot =
      stdair::FacBomContent::instance().createBomRoot<BomRoot>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    const stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    Inventory& lInventory =
      stdair::FacBomContent::
      instance().create<Inventory> (lBomRoot, lInventoryKey);
    
    // Display the inventory
    AIRSCHED_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    const stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lFlightDate =
      stdair::FacBomContent::instance().create<FlightDate> (lInventory,
                                                            lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    stdair::LegDateKey_T lLegDateKey (lLHR);

    LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey_T (lBKK);

    LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) of the Segment LHR-BKK;
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey_T lYSegmentCabinKey (lY);

    SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBomContent::
      instance().create<SegmentCabin> (lLHRBKKSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<SegmentCabin> (lBKKSYDSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<SegmentCabin> (lLHRSYDSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    
    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) of the Leg LHR-BKK;
    stdair::LegCabinKey_T lYLegCabinKey (lY);

    LegCabin& lLHRLegYCabin =
      stdair::FacBomContent::
      instance().create<LegCabin> (lLHRLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) of the Leg BKK-SYD;
    LegCabin& lBKKLegYCabin =
      stdair::FacBomContent::
      instance().create<LegCabin> (lBKKLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) of the Segment LHR-BKK, cabin Y;
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey_T lQBookingClassKey (lQ);

    BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBomContent::
      instance().create<BookingClass> (lLHRBKKSegmentYCabin, 
                                               lQBookingClassKey);

    // Display the booking class
    AIRSCHED_LOG_DEBUG ("BookingClass: "
                        << lLHRBKKSegmentYCabinQClass.toString());

        
    // Step 0.8: Initialisation results
    // Display the full structure and content
    AIRSCHED_LOG_DEBUG ("Full Inventory: " << lInventory.toString());

  }
  
}
