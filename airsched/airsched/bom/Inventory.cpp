// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// AIRSCHED
#include <airsched/bom/Inventory.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const BomKey_T& iKey,
                        BomStructure_T& ioInventoryStructure)
    : stdair::Inventory (iKey, ioInventoryStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

}
