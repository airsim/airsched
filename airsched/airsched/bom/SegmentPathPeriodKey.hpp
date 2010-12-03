#ifndef __AIRSCHED_BOM_SEGMENTPATHPERIODKEY_HPP
#define __AIRSCHED_BOM_SEGMENTPATHPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/bom/PeriodStruct.hpp>
// AirSched
#include <airsched/bom/SegmentPathPeriodTypes.hpp>

namespace AIRSCHED {

  /** Key of SegmentPathPeriod. */
  struct SegmentPathPeriodKey : public stdair::KeyAbstract {
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    SegmentPathPeriodKey ();
    SegmentPathPeriodKey (const stdair::PeriodStruct&,
                          const stdair::Duration_T&,  const stdair::Duration_T&,
                          const DateOffsetList_T&, 
                          const stdair::NbOfAirlines_T&);
    
    /** Destructor. */
    ~SegmentPathPeriodKey ();
    
    // /////////// Getters //////////
    /** Get the active days-of-week. */
    const stdair::PeriodStruct& getPeriod () const {
      return _period;
    }

    const DateOffsetList_T& getBoardingDateOffsetList () const {
      return _boardingDateOffsetList;
    }
    
    /** Get the number of segments. */
    const stdair::NbOfSegments_T getNbOfSegments() const {
      return _boardingDateOffsetList.size();
    }
    
    /** Get the number of airlines. */
    const stdair::NbOfAirlines_T& getNbOfAirlines() const {
      return _nbOfAirlines;
    }

    /** Get the elapsed time. */
    const stdair::Duration_T& getElapsedTime() const {
      return _elapsed;
    }

    /** Get the boarding time. */
    const stdair::Duration_T& getBoardingTime () const {
      return _boardingTime;
    }

    // /////////// Setters //////////
    /** Set the active days-of-week. */
    void setPeriod (const stdair::PeriodStruct& iPeriod) {
      _period = iPeriod;
    }

    void setBoardingDateOffsetList (const DateOffsetList_T& iList) {
      _boardingDateOffsetList = iList;
    }
    
    /** Set the number of airlines. */
    void setNbOfAirlines (const stdair::NbOfAirlines_T& iNbOfAirlines) {
      _nbOfAirlines = iNbOfAirlines;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const stdair::Duration_T& iElapsed) {
      _elapsed = iElapsed;
    }

    /** Set the boarding time. */
    void setBoardingTime (const stdair::Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-cabin. */
    const std::string toString() const;

    // /////////// Business methods ////////////
    /** Check if the key is valid (i.e. the departure period is valid). */
    const bool isValid () const {
      return _period.isValid ();
    }
    
  private:
    // Attributes
    /** Departure peiod. */
    stdair::PeriodStruct _period;
    
    /** The boarding time. */
    stdair::Duration_T _boardingTime;

    /** The elapsed time of the path. */
    stdair::Duration_T _elapsed;

    /** The list of boarding date offsets of the segments compare to
        the first one. */
    DateOffsetList_T _boardingDateOffsetList;

    /** Number of airlines included in the path. */
    stdair::NbOfAirlines_T _nbOfAirlines;
  };

}
#endif // __AIRSCHED_BOM_SEGMENTPATHPERIODKEY_HPP
