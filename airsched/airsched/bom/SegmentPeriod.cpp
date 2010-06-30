// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomSource.hpp>
// AIRSCHED
#include <airsched/bom/SegmentPeriod.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::SegmentPeriod (const Key_T& iKey,
                                Structure_T& ioSegmentPeriodStructure)
    : stdair::SegmentPeriod (iKey, ioSegmentPeriodStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::~SegmentPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriod::fill (stdair::SegmentPeriod& ioSegmentPeriod,
                            const LegStructList_T& iLegList) {

    const stdair::AirportCode_T& lBoardingPoint =
      ioSegmentPeriod.getBoardingPoint ();
    const stdair::AirportCode_T& lOffPoint = ioSegmentPeriod.getOffPoint();
    stdair::Duration_T lElapsedTime;

    // Find the leg which has the same boarding point.
    LegStructList_T::const_iterator itLeg = iLegList.begin ();
    while (itLeg != iLegList.end()) {
      const LegStruct_T& lLeg = *itLeg;
      if (lLeg._boardingPoint == lBoardingPoint) {
        break;
      } else {
        ++itLeg;
      }
    }
    assert (itLeg != iLegList.end());
    const LegStruct_T& lFirstLeg = *itLeg;
    stdair::AirportCode_T lCurrentOffPoint = lFirstLeg._offPoint;
    stdair::Duration_T lCurrentOffTime = lFirstLeg._offTime;
    
    // Update the elapsed time.
    lElapsedTime += lFirstLeg._elapsed;

    // Find the last used leg.
    while (lCurrentOffPoint != lOffPoint) {
      ++itLeg;
      assert (itLeg != iLegList.end());
      
      const LegStruct_T& lCurrentLeg = *itLeg;
      assert (lCurrentOffPoint == lCurrentLeg._boardingPoint);
      // As the boarding point of the current leg is the same as the off point
      // of the previous leg (by construction), there is no time difference.
      const stdair::Duration_T lStopOverTime =
        lCurrentLeg._boardingTime - lCurrentOffTime;
      lElapsedTime += lStopOverTime;

      // Add the elapsed time of the current leg
      lElapsedTime += lCurrentLeg._elapsed;

      lCurrentOffTime = lCurrentLeg._offTime;
      lCurrentOffPoint = lCurrentLeg._offPoint;
    }
    const LegStruct_T& lLastLeg = *itLeg;

    // Update the attributes of the segment-period.
    ioSegmentPeriod.setBoardingTime (lFirstLeg._boardingTime);
    ioSegmentPeriod.setOffTime (lLastLeg._offTime);
    ioSegmentPeriod.setBoardingDateOffset (lFirstLeg._boardingDateOffset);
    ioSegmentPeriod.setOffDateOffset (lLastLeg._offDateOffset);
    ioSegmentPeriod.setElapsedTime (lElapsedTime);
  }

}