/**
 * @file Core/Data/PlainRepository.cpp
 * Contains the implementation of class Core::Data::Logger.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include "core.h"

namespace Core { namespace Data
{

//==============================================================================
// Data Functions

void PlainRepository::popLevel()
{
  if (this->stack.getCount() > 0) {
    this->stack.remove(this->stack.getCount()-1);
  } else {
    if (this->trunkIndex >= 0) {
      this->trunkIndex--;
    } else {
      // This should never be reached.
      throw GeneralException(STR("Stack is empty."), STR("Core::Data::PlainRepository::pop"));
    }
  }
}


void PlainRepository::setLevel(IdentifiableObject *obj, Int index)
{
  if (this->getLevelCount() == 0) {
    throw GeneralException(STR("Stack is empty."), STR("Core::Data::PlainRepository::set"));
  }
  if (index >= 0) {
    if (index >= this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::set"),
                                     STR("Index is out of range."), index);
    }
  } else {
    if ((-index) > this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::set"),
                                     STR("Index is out of range."), index);
    }
    index = this->getLevelCount() + index;
  }

  if (this->trunkIndex >= 0) {
    ASSERT(this->trunkRepo != 0);
    if (index <= this->trunkIndex) {
      this->trunkRepo->setLevel(obj, index);
    } else {
      this->stack.set(index-(this->trunkIndex+1), obj);
    }
  } else {
    this->stack.set(index, obj);
  }
}


void PlainRepository::setLevel(Char const *scope, IdentifiableObject *obj, Int index)
{
  if (this->getLevelCount() == 0) {
    throw GeneralException(STR("Stack is empty."), STR("Core::Data::PlainRepository::set"));
  }
  if (index >= 0) {
    if (index >= this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::set"),
                                     STR("Index is out of range."), index);
    }
  } else {
    if ((-index) > this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::set"),
                                     STR("Index is out of range."), index);
    }
    index = this->getLevelCount() + index;
  }

  if (this->trunkIndex >= 0) {
    ASSERT(this->trunkRepo != 0);
    if (index <= this->trunkIndex) {
      this->trunkRepo->setLevel(scope, obj, index);
    } else {
      this->stack.set(index-(this->trunkIndex+1), scope, obj);
    }
  } else {
    this->stack.set(index, scope, obj);
  }
}


IdentifiableObject* PlainRepository::getLevelData(Int index) const
{
  if (this->getLevelCount() == 0) {
    throw GeneralException(STR("Stack is empty."), STR("Core::Data::PlainRepository::get"));
  }
  if (index >= 0) {
    if (index >= this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::get"),
                                     STR("Index is out of range."), index);
    }
  } else {
    if ((-index) > this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::get"),
                                     STR("Index is out of range."), index);
    }
    index = this->getLevelCount() + index;
  }

  if (this->trunkIndex >= 0) {
    ASSERT(this->trunkRepo != 0);
    if (index <= this->trunkIndex) {
      return this->trunkRepo->getLevelData(index);
    } else {
      return this->stack.get(index-(this->trunkIndex+1));
    }
  } else {
    return this->stack.get(index);
  }
  // Dummy return statement to avoid compilation error. This won't be reached.
  return this->stack.get(index);
}


const SbStr& PlainRepository::getLevelScope(Int index) const
{
  if (this->getLevelCount() == 0) {
    throw GeneralException(STR("Stack is empty."), STR("Core::Data::PlainRepository::get"));
  }
  if (index >= 0) {
    if (index >= this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::get"),
                                     STR("Index is out of range."), index);
    }
  } else {
    if ((-index) > this->getLevelCount()) {
      throw InvalidArgumentException(STR("index"), STR("Core::Data::PlainRepository::get"),
                                     STR("Index is out of range."), index);
    }
    index = this->getLevelCount() + index;
  }

  if (this->trunkIndex >= 0) {
    ASSERT(this->trunkRepo != 0);
    if (index <= this->trunkIndex) {
      return this->trunkRepo->getLevelScope(index);
    } else {
      return this->stack.getName(index-(this->trunkIndex+1));
    }
  } else {
    return this->stack.getName(index);
  }
  // Dummy return statement to avoid compilation error. This won't be reached.
  return this->stack.getName(index);
}


void PlainRepository::copyFrom(PlainRepository const *src)
{
  if (src == 0) {
    throw InvalidArgumentException(STR("src"), STR("Core::Data::PlainRepository::copyFrom"),
                                   STR("Argument cannot be null."));
  }
  this->clear();
  for (Int i = 0; i < src->getLevelCount(); ++i) {
    this->pushLevel(src->getLevelScope(i).c_str(), src->getLevelData(i));
  }
}


//==============================================================================
// Branching Functions

void PlainRepository::setBranchingInfo(PlainRepository *ds, Int ti)
{
  if (ds == 0) ti = -1;
  else if (ti < -1 || ti >= static_cast<Int>(ds->getLevelCount())) {
    throw InvalidArgumentException(STR("ti"), STR("Core::Data::PlainRepository::setBranchingInfo"),
                                   STR("Must be between -1 and ds->getLevelCount()-1 when ds is not null."));
  }
  this->clear();
  this->trunkRepo = ds;
  this->trunkIndex = ti;
}


void PlainRepository::ownTopLevel()
{
  ASSERT(this->getLevelCount() > 0);
  if (this->stack.getCount() > 0) return;
  ASSERT(this->trunkRepo != 0);
  ASSERT(this->trunkIndex > -1);
  if (static_cast<Int>(this->trunkRepo->getLevelCount()) <= this->trunkIndex) {
    throw GeneralException(STR("Trunk stack has been modified."),
                           STR("Core::Data::PlainRepository::ownTopLevel"));
  }
  auto srcData = this->trunkRepo->getLevelData(this->trunkIndex);
  Str scope = this->trunkRepo->getLevelScope(this->trunkIndex);
  this->trunkIndex--;
  this->stack.add(scope.c_str(), srcData);
}


//==============================================================================
// Provider Implementation

void PlainRepository::set(Reference const *ref, IdentifiableObject *val)
{
  // Set the value first.
  if (ref->isA<ScopeReference>()) {
    this->referenceSeeker.set(ref, &this->stack, val);
  } else {
    Bool ret = false;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      ret = this->referenceSeeker.trySet(ref, parent, val);
      if (ret) break;
    }
    if (!ret) {
      throw GeneralException(STR("Couldn't set value. Reference doesn't point to an existing element."),
                             STR("Core::Data::PlainRepository::set"));
    }
  }

  // TODO: We can remove this part if/when we start handling IDs in definition signals.
  // Set the id for the new object.
  if (this->owner) {
    Str qualifierStr;
    if (ref->isA<ScopeReference>()) qualifierStr = ReferenceParser::getQualifier(ref->getNext().get());
    else qualifierStr = ReferenceParser::getQualifier(ref);
    Char const *qualifier = qualifierStr.c_str();
    setTreeIds(val, qualifier);
  }
}


void PlainRepository::set(Char const *qualifier, IdentifiableObject *val)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  // Set the value first.
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    Bool ret = false;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) {
        throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::set"),
                                       STR("Invalid scope value."), qualifier);
      }
      ret = this->qualifierSeeker.trySet(qualifier2, parent, val);
      if (ret) break;
    }
    if (!ret) {
      throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::set"),
                                     STR("Qualifier doesn't point to an existing element."), qualifier);
    }
  } else {
    qualifier2 = qualifier;
    Bool ret = false;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      ret = this->qualifierSeeker.trySet(qualifier2, parent, val);
      if (ret) break;
    }
    if (!ret) {
      throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::set"),
                                     STR("Qualifier doesn't point to an existing element."), qualifier);
    }
  }

  // TODO: We can remove this part if/when we start handling IDs in definition signals.
  // Set the id for the new object.
  if (this->owner) {
    setTreeIds(val, qualifier2);
  }
}


Bool PlainRepository::trySet(Reference const *ref, IdentifiableObject *val)
{
  // Set the value first.
  if (ref->isA<ScopeReference>()) {
    if (!this->referenceSeeker.trySet(ref, &this->stack, val)) return false;
  } else {
    Bool ret = false;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      ret = this->referenceSeeker.trySet(ref, parent, val);
      if (ret) break;
    }
    if (!ret) return false;
  }

  // TODO: We can remove this part if/when we start handling IDs in definition signals.
  // Set the id for the new object.
  if (this->owner) {
    Str qualifierStr;
    if (ref->isA<ScopeReference>()) qualifierStr = ReferenceParser::getQualifier(ref->getNext().get());
    else qualifierStr = ReferenceParser::getQualifier(ref);
    Char const *qualifier = qualifierStr.c_str();
    setTreeIds(val, qualifier);
  }

  return true;
}


Bool PlainRepository::trySet(Char const *qualifier, IdentifiableObject *val)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  // Set the value first.
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    Bool ret = false;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) return false;
      ret = this->qualifierSeeker.trySet(qualifier2, parent, val);
      if (ret) break;
    }
    if (!ret) return false;
  } else {
    qualifier2 = qualifier;
    Bool ret = false;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      ret = this->qualifierSeeker.trySet(qualifier2, parent, val);
      if (ret) break;
    }
    if (!ret) return false;
  }

  // TODO: We can remove this part if/when we start handling IDs in definition signals.
  // Set the id for the new object.
  if (this->owner) {
    setTreeIds(val, qualifier2);
  }

  return true;
}


void PlainRepository::remove(Reference const *ref)
{
  if (ref->isA<ScopeReference>()) {
    this->referenceSeeker.remove(ref, &this->stack);
  } else {
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryRemove(ref, parent)) return;
    }
    throw InvalidArgumentException(STR("ref"), STR("Core::Data::PlainRepository::remove"),
                                   STR("Doesn't refer to an existing element."), ReferenceParser::getQualifier(ref));
  }
}


void PlainRepository::remove(Char const *qualifier)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) {
        throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::remove"),
                                       STR("Invalid scope value."), qualifier);
      }
      if (this->qualifierSeeker.tryRemove(qualifier2, parent)) return;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryRemove(qualifier2, parent)) return;
    }
  }
  throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::remove"),
                                 STR("Qualifier doesn't refer to an existing element."), qualifier);
}


Bool PlainRepository::tryRemove(Reference const *ref)
{
  if (ref->isA<ScopeReference>()) {
    return this->referenceSeeker.tryRemove(ref, &this->stack);
  } else {
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryRemove(ref, parent)) return true;
    }
    return false;
  }
}


Bool PlainRepository::tryRemove(Char const *qualifier)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) break;
      if (this->qualifierSeeker.tryRemove(qualifier2, parent)) return true;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryRemove(qualifier2, parent)) return true;
    }
  }
  return false;
}


IdentifiableObject* PlainRepository::get(Reference const *ref)
{
  if (ref->isA<ScopeReference>()) {
    return this->referenceSeeker.get(ref, &this->stack);
  } else {
    // The default is to go downward through the stack.
    IdentifiableObject *obj;
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryGet(ref, parent, obj)) return obj;
    }
    throw GeneralException(STR("Couldn't set value. Reference doesn't point to an existing element."),
                           STR("Core::Data::PlainRepository::get"));
  }
}


void PlainRepository::get(Reference const *ref, PlainModulePairedPtr &retVal)
{
  if (ref->isA<ScopeReference>()) {
    this->referenceSeeker.get(ref, &this->stack, retVal);
  } else {
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryGet(ref, parent, retVal)) return;
    }
    throw GeneralException(STR("Couldn't set value. Reference doesn't point to an existing element."),
                           STR("Core::Data::PlainRepository::get"));
  }
}


IdentifiableObject* PlainRepository::get(Char const *qualifier)
{
  Char const *qualifier2 = qualifier;
  IdentifiableObject *obj;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) {
        throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::get"),
                                       STR("Invalid scope value."), qualifier);
      }
      if (this->qualifierSeeker.tryGet(qualifier2, parent, obj)) return obj;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, obj)) return obj;
    }
  }
  throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::getPlainValue"),
                                 STR("Qualifier doesn't point to an existing element."), qualifier);
}


void PlainRepository::get(Char const *qualifier, PlainModulePairedPtr &retVal)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) {
        throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::get"),
                                       STR("Invalid scope value."), qualifier);
      }
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return;
    }
  }
  throw InvalidArgumentException(STR("qualifier"), STR("Core::Data::PlainRepository::get"),
                                 STR("Qualifier doesn't point to an existing element."), qualifier);
}


Bool PlainRepository::tryGet(Reference const *ref, IdentifiableObject *&retVal)
{
  if (ref->isA<ScopeReference>()) {
    return this->referenceSeeker.tryGet(ref, &this->stack, retVal);
  } else {
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryGet(ref, parent, retVal)) return true;
    }
    return false;
  }
}


Bool PlainRepository::tryGet(Reference const *ref, PlainModulePairedPtr &retVal)
{
  if (ref->isA<ScopeReference>()) {
    return this->referenceSeeker.tryGet(ref, &this->stack, retVal);
  } else {
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->referenceSeeker.tryGet(ref, parent, retVal)) return true;
    }
    return false;
  }
}


Bool PlainRepository::tryGet(Char const *qualifier, IdentifiableObject *&retVal)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) break;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return true;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return true;
    }
  }
  return false;
}


Bool PlainRepository::tryGet(Char const *qualifier, PlainModulePairedPtr &retVal)
{
  Char const *qualifier2 = qualifier;
  ReferenceParser parser;
  Reference const *ref = &parser.parseQualifierSegment(qualifier2);
  if (ref->isA<ScopeReference>()) {
    ASSERT(*qualifier2 == CHR(':'));
    ++qualifier2;
    IdentifiableObject *parent;
    Int index = 0;
    while (index != -1) {
      if (!ref->getValue(0, &this->stack, parent, index)) break;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return true;
    }
  } else {
    qualifier2 = qualifier;
    // The default is to go downward through the stack.
    for (Int i = this->stack.getCount()-1; i>=0; --i) {
      IdentifiableObject *parent = this->stack.get(i);
      if (parent == 0) continue;
      if (this->qualifierSeeker.tryGet(qualifier2, parent, retVal)) return true;
    }
  }
  return false;
}

} } // namespace

