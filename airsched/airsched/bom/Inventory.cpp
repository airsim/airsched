// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/BomIterator.hpp>
// AIRSCHED 
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (BomStructure_T& ioInventoryStructure)
    : _inventoryStructure (ioInventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;

    _inventoryStructure.describeFull (oStr);
      
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _inventoryStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeShortKey() const {
    return _inventoryStructure.describeShortKey();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Inventory::flightDateListBegin () const {
    _inventoryStructure.flightDateListBegin ();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Inventory::flightDateListIterate () const {
    _inventoryStructure.flightDateListIterate ();
  }

  // //////////////////////////////////////////////////////////////////////
  const bool Inventory::flightDateListHasNotReachedEnd () const {
    return _inventoryStructure.flightDateListHasNotReachedEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate& Inventory::getCurrentFlightDate () const {
    return _inventoryStructure.getCurrentFlightDate ();
  }
  

}

