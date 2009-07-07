#ifndef __STDAIR_FAC_FACBOMSTRUCTURE_HPP
#define __STDAIR_FAC_FACBOMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <string>
#include <vector>
// MPL
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
// STDAIR
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {

  // Forward declarations
  class BomStructure;
  class BomContent;

  /** Base class for Factory layer. */
  class FacBomStructure {
    friend class FacBomContent;
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomStructure*> BomStructurePool_T;

    /** Destructor. */
    virtual ~FacBomStructure();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is structure. */
    FacBomStructure() {}

  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomStructure& */
    static FacBomStructure& instance();
    
    /** Create a structure object with the given key. */
    template <typename BOM_KEY>
    typename BOM_KEY::BomStructure_T& create (const BOM_KEY& iKey) {
      // Type for the BOM structure.
      typedef typename BOM_KEY::BomStructure_T BOM_STRUCTURE_T;
      
      BOM_STRUCTURE_T* aBomStructure_ptr = NULL;
      
      aBomStructure_ptr = new BOM_STRUCTURE_T (iKey);
      assert (aBomStructure_ptr != NULL);

      // Initialise the children list of the BOM structure.
      initChildrenList<BOM_STRUCTURE_T> (*aBomStructure_ptr);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomStructure_ptr);
      
      return *aBomStructure_ptr;
    }

    /** Link a child structure object with its parent.
        <br>For instance, link a SegmentDate structure object with its parent
        FlightDate structure object.
        <br>The child structure object is added to the dedicated list within
        the parent structure object.       .
        @return bool Whether or not the operation succeeded. */
    template <typename BOM_STRUCTURE_CHILD,
              typename BOM_CHILDREN_TYPE_LIST>
    static bool linkBomParentWithBomChild (typename BOM_STRUCTURE_CHILD::ParentBomStructure_T& ioBomParent,
                                           BOM_STRUCTURE_CHILD& ioBomChild) {

      // Set the parent of the child structure object
      ioBomChild._parent = &ioBomParent;

      // Find the position of the BOM_STRUCTURE_CHILD type in the
      // BOM_CHILDREN_TYPE_LIST.
      const unsigned int pos = boost::mpl::find<BOM_CHILDREN_TYPE_LIST, BOM_STRUCTURE_CHILD>::type::pos::value;

      // Retrive the bom children holder corresponding the the children type.
      typedef BomChildrenHolder<BOM_STRUCTURE_CHILD> BOM_CHILDREN_HOLDER_T;
      BOM_CHILDREN_HOLDER_T* lBomChildrenHolder_ptr =
        dynamic_cast<BOM_CHILDREN_HOLDER_T*>(ioBomParent._childrenList.at (pos));
      assert (lBomChildrenHolder_ptr != NULL);
      
      // Retrieve the short key
      const typename BOM_STRUCTURE_CHILD::BomKey_T& lBomChildKey =
        ioBomChild.getKey();
      const std::string& lBomChildKeyStr = lBomChildKey.toString();
      
      // Insert the child structure object in the dedicated lists
      typedef typename BOM_CHILDREN_HOLDER_T::BomChildrenList_T BOM_CHILDREN_LIST_T;
      const bool hasInsertBeenSuccessful =
        lBomChildrenHolder_ptr->_bomChildrenList.
        insert (typename BOM_CHILDREN_LIST_T::value_type (lBomChildKeyStr,
                                                          &ioBomChild)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }

      lBomChildrenHolder_ptr->_bomChildrenOrderedList.push_back (&ioBomChild);
      
      return true;
    }

  private:
    /** Create a bom children holder object with the given children type. */
    template <typename BOM_CHILD>
    BomChildrenHolder<BOM_CHILD>& create () {
      
      BomChildrenHolder<BOM_CHILD>* aBomChildrenHolder_ptr = NULL;
      
      aBomChildrenHolder_ptr = new BomChildrenHolder<BOM_CHILD> ();
      assert (aBomChildrenHolder_ptr != NULL);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomChildrenHolder_ptr);
      
      return *aBomChildrenHolder_ptr;
    }

    /** Initialise the list of children for a given BOM structure.
        <br>Create the BomChildrenHolder objects corresponding to the
        list of children types of the given BOM structure. */
    template <typename BOM_STRUCTURE>
    static void initChildrenList (BOM_STRUCTURE& ioBomStructure) {
      // Type for the childrend type list.
      typedef typename BOM_STRUCTURE::ChildrenBomTypeList_T CHILDREN_TYPE_LIST_T;

      // Get the number of children types and create necessary number of
      // bom children holders.
      const int lNbOfTypes = boost::mpl::size<CHILDREN_TYPE_LIST_T>::type::value;

      if (lNbOfTypes > 0) {
        typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,0>::type FIRST_CHILDREN_TYPE_T;
        BomChildrenHolder<FIRST_CHILDREN_TYPE_T>& lFirstBomChildrenHolder =
          instance().create<FIRST_CHILDREN_TYPE_T>();
        ioBomStructure._childrenList.push_back (&lFirstBomChildrenHolder);
      }
      
      if (lNbOfTypes > 1) {
        typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,1>::type SECOND_CHILDREN_TYPE_T;
        BomChildrenHolder<SECOND_CHILDREN_TYPE_T>& lSecondBomChildrenHolder =
          instance().create<SECOND_CHILDREN_TYPE_T>();
        ioBomStructure._childrenList.push_back (&lSecondBomChildrenHolder);
      }
    }
    
  private:
    /** The unique instance.*/
    static FacBomStructure* _instance;
    
  private:
    /** List of instantiated Business Objects*/
    BomStructurePool_T _structurePool;
  };
}
#endif // __STDAIR_FAC_FACBOMSTRUCTURE_HPP
