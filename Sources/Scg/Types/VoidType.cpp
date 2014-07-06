/**
 * @file Scg/Types/VoidType.cpp
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
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

// Scg header files
#include <Types/VoidType.h>
#include <LlvmContainer.h>

namespace Scg
{
  VoidType *VoidType::s_singleton = nullptr;

  //----------------------------------------------------------------------------

  VoidType::VoidType() : typeSpec("string")
  {
    this->llvmType = llvm::Type::getVoidTy(LlvmContainer::GetContext());
    if (s_singleton == nullptr)
      s_singleton = this;
  }
}