#ifndef __STDAIR_BOM_BOMSTRUCTUREROOT_HPP
#define __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStructureRootKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
// MPL
#include <boost/mpl/vector.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM_CONTENT> class Inventory;
  class BomStructureDummy;
  class BomContentDummy;

  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename BOM_CONTENT>
  class BomStructureRoot : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the first children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::FirstContentChild_T FirstContentChild_T;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomStructureRootKey<BOM_CONTENT> BomKey_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<Inventory<FirstContentChild_T>, BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;
    
    /** Definition allowing to retrive the first children bom holder type. */
    typedef BomChildrenHolderImp<FirstContentChild_T> FirstChildrenBomHolder_T;

  public:

    // /////////// Getters /////////////
    /** Get the BomStructureRoot key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the list of inventories. */
    const FirstChildrenBomHolder_T& getFirstChildrenList() const {
      return *_firstChildrenList;
    }

    /** Get the list of inventories. */
    void getChildrenList (FirstChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _firstChildrenList;
    }

  private: 
    /////////////// Setters ////////////////
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
    /** Set the first children list. */
    void setChildrenList (FirstChildrenBomHolder_T& ioChildrenList) {
      _firstChildrenList = &ioChildrenList;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString() << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return _key.toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }


  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomStructureRoot ();
    BomStructureRoot (const BomStructureRoot&);
    BomStructureRoot (const BomKey_T& iKey) { _key = iKey; }

    /** Destructor. */
    ~BomStructureRoot () { }

  private:
    // Attributes
    /** The key of both the structure and content objects. */
    BomKey_T _key; 

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** List of inventories. */
    FirstChildrenBomHolder_T* _firstChildrenList;
  };

}
#endif // __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

