// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR 
#include <stdair/bom/LegDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate (const BomKey_T& iKey)
    : _parent (NULL), _key (iKey) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegDate::~LegDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  LegDate::ParentBomStructure_T& LegDate::getFlightDate() const {
    assert (_parent != NULL);
    return *_parent;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void LegDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void LegDate::describeFull (std::ostringstream& ioOut) const {
    ioOut << describeShortKey() << std::endl;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void LegDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string LegDate::toString() const {
    return describeKey();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string LegDate::describeKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string LegDate::describeShortKey() const {
    return _key.toString();
  }

}

