/**
 * @file Tests/CoreTests/helpers.cpp
 * Contains the definition of different helper functions and classes that are
 * used by unit tests.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include "core_tests.h"

namespace Tests { namespace CoreTests
{

using namespace std;

/**
 * Search the given tree recursively for the data of the given production id.
 *
 * @param prodId The id of the production to search for.
 * @param ptr The root of the tree.
 * @param result A reference to an array to contain all found results.
 * @param index If ptr is a list object, this index will specify at what element
 *              of that list to search. If this is -1 the entire list will be
 *              searched.
 */
void findProdData(Word prodId, SharedPtr<IdentifiableObject> ptr,
                  vector<SharedPtr<IdentifiableObject> > &result, Int index)
{
  if (ptr == 0 || !ptr->isDerivedFrom<Standard::ParsedItem>()) return;

  if (ptr.s_cast_get<Standard::ParsedItem>()->getProdId() == prodId) {
    result.push_back(ptr);
  }

  // Print the data itself.
  if (ptr->isDerivedFrom<Standard::ParsedList>()) {
    if (index != -1) {
      findProdData(prodId, ptr.s_cast_get<Standard::ParsedList>()->getElement(index), result);
    } else {
      for (Word i = 0; i < ptr.s_cast_get<Standard::ParsedList>()->getElementCount(); ++i) {
        findProdData(prodId, ptr.s_cast_get<Standard::ParsedList>()->getElement(i), result);
      }
    }
  } else if (ptr->isDerivedFrom<Standard::ParsedRoute>()) {
    findProdData(prodId, ptr.s_cast_get<Standard::ParsedRoute>()->getData(), result);
  }
}


/**
 * Search the given tree recursively for the token with the given id and/or
 * text.
 *
 * @param tokenId The id of the token to search for, or UNKNOWN_ID to ignore
 *                 the token id.
 * @param text The text of the token, or 0 to ignore the token text.
 * @param ptr The root of the tree.
 * @param result A reference to an array to contain all found results.
 * @param index If ptr is a list object, this index will specify at what element
 *              of that list to search. If this is -1 the entire list will be
 *              searched.
 */
void findToken(Word tokenId, const Char *text, SharedPtr<IdentifiableObject> ptr,
               vector<SharedPtr<IdentifiableObject> > &result, Int index)
{
  if (ptr == 0 || !ptr->isDerivedFrom<Standard::ParsedItem>()) return;

  // Print the data itself.
  if (ptr->isDerivedFrom<Standard::ParsedList>()) {
    if (index != -1) {
      findToken(tokenId, text, ptr.s_cast_get<Standard::ParsedList>()->getElement(index), result);
    } else {
      for (Word i = 0; i < ptr.s_cast_get<Standard::ParsedList>()->getElementCount(); ++i) {
        findToken(tokenId, text, ptr.s_cast_get<Standard::ParsedList>()->getElement(i), result);
      }
    }
  } else if (ptr->isDerivedFrom<Standard::ParsedRoute>()) {
    findToken(tokenId, text, ptr.s_cast_get<Standard::ParsedRoute>()->getData(), result);
  } else if (ptr->isDerivedFrom<Standard::ParsedToken>()) {
    // Print the token type.
    SharedPtr<Standard::ParsedToken> token = ptr.s_cast<Standard::ParsedToken>();
    if ((tokenId == 0 || tokenId == token->getId()) &&
        (text == 0 || token->getText().compare(text) == 0)) {
      result.push_back(token);
    }
  }
}


/**
 * Check whether the provided pointer has empty data. Data is considered empty
 * if:<br>
 * - ptr is a list that has 0 elements.<br>
 * - ptr is a route that has no child data.<br>
 * or<br>
 * - ptr is a token that has UNKNOWN_ID.
 */
Bool isEmpty(SharedPtr<IdentifiableObject> ptr)
{
  if (ptr == 0) {
    return false;
  } else if (ptr->isDerivedFrom<Standard::ParsedList>()) {
    return ptr.s_cast_get<Standard::ParsedList>()->getElementCount() == 0;
  } else if (ptr->isDerivedFrom<Standard::ParsedRoute>()) {
    return ptr.s_cast_get<Standard::ParsedRoute>()->getData() == 0;
  } else if (ptr->isDerivedFrom<Standard::ParsedToken>()) {
    return ptr.s_cast_get<Standard::ParsedToken>()->getId() == UNKNOWN_ID;
  }
  return false;
}

} } // namespace