/**
 * @file Scg/Types/ValueType.cpp
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================
#include <prerequisites.h>

// LLVM header files
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>

// Scg files
#include <LlvmContainer.h>
#include <Types/DoubleType.h>
#include <Types/FloatType.h>
#include <Types/IntegerType.h>
#include <Types/StringType.h>
#include <Types/ValueType.h>
#include <Types/VoidType.h>
#include <Values/Variable.h>
#include <Memory/AutoDeleteAllocator.h>

namespace Scg
{
ValueType *ValueType::GetPrimitiveType(const std::string &typeName)
{
  if (typeName == "int") {
    return IntegerType::GetSingleton();
  } else if (typeName == "float") {
    return FloatType::GetSingleton();
  } else if (typeName == "double") {
    return DoubleType::GetSingleton();
  } else if (typeName == "string") {
    return StringType::GetSingleton();
  } else if (typeName == "void" || typeName == "") {
    return VoidType::GetSingleton();
  }
  return nullptr;
}

//----------------------------------------------------------------------------

Variable *ValueType::NewVariable(const std::string &name,
    llvm::Argument *llvmArgument) const
{
  this->varCount++;
  return new Variable(name, const_cast<ValueType*>(this), llvmArgument);
}

//----------------------------------------------------------------------------

void ValueType::DeleteVariable(Variable *var) const
{
  this->varCount--;
  delete var;
}

//------------------------------------------------------------------------------

void *ValueType::operator new(size_t size)
{
  return AutoDeleteAllocator::GetSingleton().Allocate(size);
}

//------------------------------------------------------------------------------

void ValueType::operator delete(void *ptr)
{
  AutoDeleteAllocator::GetSingleton().Free(ptr);
}
}