/**
 * @file Scg/Operators/Content.cpp
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
#include <llvm/IR/IRBuilder.h>
// Scg files
#include <Containers/Block.h>
#include <Operators/Content.h>
#include <Types/PointerType.h>

namespace Scg
{
const ValueType *Content::GetValueType() const
{
  // TODO: Don't use dynamic_cast.
  auto pointerType = dynamic_cast<PointerType*>(this->expression->GetValueType());
  if (pointerType == nullptr)
    THROW_EXCEPTION(InvalidOperationException, "Trying to find the content "
        "of a non-pointer type.");
  // TODO: Change the return type to a reference or change GetContentType().
  return pointerType->GetContentType();
}

//------------------------------------------------------------------------------

CodeGenerationResult Content::GenerateCode()
{
  BLOCK_CHECK;

  this->pointer = this->expression->GenerateCode().exprValue;
  this->loadInst = GetBlock()->GetIRBuilder()->CreateLoad(this->pointer);
  return CodeGenerationResult(this->loadInst);
}

//----------------------------------------------------------------------------

Expression::CodeGenerationStage Content::PostGenerateCode()
{
  if (this->loadInst == nullptr)
    return CodeGenerationStage::None;
  if (!this->loadInst->hasNUses(0))
    // Cannot delete the instruction yet; stay in PostCodeGeneration stage.
    return CodeGenerationStage::PostCodeGeneration;
  this->loadInst->eraseFromParent();
  this->loadInst = nullptr;
  return Expression::PostGenerateCode();
}

//----------------------------------------------------------------------------

std::string Content::ToString()
{
  // TODO: Implement this function.
  return "";
}
}