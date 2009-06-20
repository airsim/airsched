// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/SegmentDateKey.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void SegmentDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentDateKey: " << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDateKey::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SegmentDateKey::toString() const {
    std::ostringstream oStr;
    oStr << _boardPoint << "-" << _offPoint;
    return oStr.str();
  }
  
}
