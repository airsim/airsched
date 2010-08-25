// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
// StdAir
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightPeriod.hpp>
#include <stdair/bom/SegmentPeriod.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/service/Logger.hpp>
// AIRSCHED
#include <airsched/bom/ReachableUniverse.hpp>
#include <airsched/bom/OriginDestinationSet.hpp>
#include <airsched/bom/SegmentPathPeriod.hpp>
#include <airsched/command/TravelSolutionProvider.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::BomRoot& iBomRoot,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve the origin-destination set objet correponding to the
    // booking request.
    std::ostringstream ostr;
    ostr << iBookingRequest.getOrigin() << ", "
         << iBookingRequest.getDestination();;
    const OriginDestinationSet* lOriginDestinationSet_ptr =
      stdair::BomManager::getChildPtr<OriginDestinationSet> (iBomRoot,
                                                             ostr.str());
    if (lOriginDestinationSet_ptr != NULL) {
      getTravelSolutions (ioTravelSolutionList, *lOriginDestinationSet_ptr,
                          iBookingRequest);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const OriginDestinationSet& iOriginDestinationSet,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve the departure date of the booking request.
    const stdair::Date_T& lPreferedDepartureDate =
      iBookingRequest.getPreferedDepartureDate ();

    // Browse the list of segment path periods and find those which content
    // the prefered departure date.
    const SegmentPathPeriodList_T& lSegmentPathPeriodList =
      stdair::BomManager::getList<SegmentPathPeriod> (iOriginDestinationSet);
    for (SegmentPathPeriodList_T::const_iterator itSegmentPath =
           lSegmentPathPeriodList.begin ();
         itSegmentPath != lSegmentPathPeriodList.end (); ++itSegmentPath) {
      const SegmentPathPeriod* lCurrentSegmentPath_ptr = *itSegmentPath;
      assert (lCurrentSegmentPath_ptr != NULL);
      if (lCurrentSegmentPath_ptr->isDepartureDateValid(lPreferedDepartureDate)){
        getTravelSolutions (ioTravelSolutionList, *lCurrentSegmentPath_ptr,
                            iBookingRequest);
      }
    }
  } 

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const SegmentPathPeriod& iSegmentPathPeriod,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Create a new travel solution.
    stdair::TravelSolutionStruct lTravelSolution;
    
    // Browse the detailed list of segments and retrieve the necessary
    // informations for identifying the corresponding segment-date.
    const stdair::Date_T& lPreferedDepartureDate =
      iBookingRequest.getPreferedDepartureDate ();
    const stdair::SegmentPeriodDetailedList_T& lSegmentPeriodDetailedList =
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (iSegmentPathPeriod);
    const DateOffsetList_T& lBoardingDateOffsetList =
      iSegmentPathPeriod.getBoardingDateOffsetList ();
    assert (lSegmentPeriodDetailedList.size() == lBoardingDateOffsetList.size());
    DateOffsetList_T::const_iterator itOffset = lBoardingDateOffsetList.begin();
    for (stdair::SegmentPeriodDetailedList_T::const_iterator itSegment =
           lSegmentPeriodDetailedList.begin();
         itSegment != lSegmentPeriodDetailedList.end(); ++itSegment) {
      const stdair::SegmentPeriod* lSegmentPeriod_ptr = itSegment->second;
      assert (lSegmentPeriod_ptr != NULL);
      const stdair::DateOffset_T& lBoardingDateOffset = *itOffset;

      // Find the corresponding segment-date within the segment period.
      const stdair::DateOffset_T& lSegmentBoardingDateOffset =
        lSegmentPeriod_ptr->getBoardingDateOffset();
      const stdair::Date_T& lReferenceFlightDate = lPreferedDepartureDate 
        + lBoardingDateOffset - lSegmentBoardingDateOffset;

      // Build the whole segment-date key string.
      std::ostringstream oStr;
      oStr << itSegment->first
           << ", " << lReferenceFlightDate;

      lTravelSolution.addSegmentDateKey (oStr.str());

      // Retrieve a class code within the segment-date.
      const stdair::CabinBookingClassMap_T& lCabinBookingClassMap =
        lSegmentPeriod_ptr->getCabinBookingClassMap ();
      stdair::CabinBookingClassMap_T::const_reverse_iterator
        itCabinBookingClassList = lCabinBookingClassMap.rbegin();
      if (itCabinBookingClassList != lCabinBookingClassMap.rend()) {
        const stdair::ClassList_String_T& lClassList =
          itCabinBookingClassList->second;
        const unsigned int lNbOfClasses = lClassList.size();
        if (lNbOfClasses > 0) {
          const char lClassCode = lClassList.at (lNbOfClasses-1);
          lTravelSolution.addBookingClassKey (lClassCode);
        }
      }
      ++itOffset;
    }
    ioTravelSolutionList.push_back (lTravelSolution);
  }

}
