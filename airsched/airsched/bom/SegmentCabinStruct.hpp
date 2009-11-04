#ifndef __AIRSCHED_BOM_SEGMENTCABINSTRUCT_HPP
#define __AIRSCHED_BOM_SEGMENTCABINSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/StructAbstract.hpp>
// AIRSCHED
#include <airsched/bom/FareFamilyStruct.hpp>

// Forward declarations
namespace stdair {
  class SegmentCabin;
}

namespace AIRSCHED {
  
  /** Utility Structure for the parsing of SegmentCabin details. */
  struct SegmentCabinStruct_T : public stdair::StructAbstract {
    // Attributes
    stdair::CabinCode_T _cabinCode;
    stdair::ClassList_String_T _classes;
    stdair::FamilyCode_T _itFamilyCode;
    FareFamilyStructList_T _fareFamilies;

    /** Fill the SegmentCabin objects with the attributes of the
        SegmentCabinStruct. */
    void fill (stdair::SegmentCabin&) const;
      
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

  };

  /** List of SegmentCabin-Detail strucutres. */
  typedef std::vector<SegmentCabinStruct_T> SegmentCabinStructList_T;

}
#endif // __AIRSCHED_BOM_SEGMENTCABINSTRUCT_HPP