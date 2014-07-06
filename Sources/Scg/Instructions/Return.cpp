/**
 * @file Scg/Instructions/Return.cpp
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include <prerequisites.h>

// STL header files
#include <iostream>

// LLVM header files
#include <llvm/IR/IRBuilder.h>

// Scg files
#include <Containers/Block.h>
#include <Instructions/Return.h>
#include <LlvmContainer.h>

using namespace llvm;

namespace Scg
{
  CodeGenerationResult Return::GenerateCode()
  {
    auto result = GetExpression()->GenerateCode();
    if (result.exprValue == 0)
      THROW_EXCEPTION(EvaluationException,
          "Expression doesn't evaluate to a value: " + GetExpression()->ToString());

    IRBuilder<> *irBuilder = GetBlock()->GetIRBuilder();
    irBuilder->CreateRet(result.exprValue);
    // Return keyword doesn't evaluate to a value.
    return CodeGenerationResult(0, true);
  }

  //----------------------------------------------------------------------------

  Expression::CodeGenerationStage Return::PostGenerateCode()
  {
    SAFE_DELETE_LLVM_INST(this->retInst);
    return CodeGenerationStage::None;
  }

  //----------------------------------------------------------------------------

  std::string Return::ToString()
  {
    return "return " + GetExpression()->ToString() + ";";
  }
}