// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::LegDateKey_T (const AirportCode_T& iBoardPoint) 
    : _boardPoint (iBoardPoint) {
  }
  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::LegDateKey_T (const LegDateKey_T& iKey)
    : _parentKey (iKey._parentKey), _boardPoint (iKey._boardPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::~LegDateKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDateKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "LegDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDateKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegDateKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _boardPoint;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegDateKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }

}
