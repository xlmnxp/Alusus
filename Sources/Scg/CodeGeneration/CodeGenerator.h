/**
 * @file Scg/CodeGeneration/CodeGenerator.h
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef __CodeGenerator_h__
#define __CodeGenerator_h__

// Alusus Core header files
#include <core.h>

// Scg CodeGeneration type definitions.
#include <typedefs.h>
#include <Types/ValueTypeSpec.h>

namespace Scg
{
  class BinaryOperator;
  class Block;
  class CallFunction;
  class DeclareExtFunction;
  class DefineFunction;
  class DefineStruct;
  class DefineVariable;
  class Expression;
  class ForStatement;
  class IfStatement;
  class List;
  class Module;
  class Return;
  class ValueTypeSpec;
  class WhileStatement;

  class CodeGenerator
  {
  public:
    Word GetStatementListId() { return statementListId; }
    Word GetExpressionId() { return expressionId; }
    Word GetListExpId() { return listExpId; }
    Word GetLowLinkExpId() { return lowLinkExpId; }
    Word GetLowerLinkExpId() { return lowerLinkExpId; }
    Word GetLowestLinkExpId() { return lowestLinkExpId; }
    Word GetFunctionalExpId() { return functionalExpId; }
    Word GetSubjectId() { return subjectId; }
    Word GetSubSubjectId() { return subSubjectId; }
    Word GetParameterId() { return parameterId; }
    Word GetLiteralId() { return literalId; }
    Word GetComparisonExpId() { return comparisonExpId; }
    Word GetAssignmentExpId() { return assignmentExpId; }
    Word GetAddExpId() { return addExpId; }
    Word GetMulExpId() { return mulExpId; }
    Word GetParamPassId() { return paramPassId; }
    Word GetLinkExpId() { return linkExpId; }
    Word GetPostfixTildeExpId() { return postfixTildeExpId; }
    Word GetIdentifierTokenId() { return identifierTokenId; }

    Word GetDefId() { return defId; }
    Word GetReturnId() { return returnId; }
    Word GetIfId() { return ifId; }
    Word GetForId() { return forId; }
    Word GetWhileId() { return whileId; }
    Word GetFunctionId() { return functionId; }
    Word GetStructureId() { return structureId; }
    Word GetLinkId() { return linkId; }
    Word GetPointerTildeId() { return pointerTildeId; }
    Word GetContentTildeId() { return contentTildeId; }

  private:
    Word statementListId;
    Word expressionId;
    Word listExpId;
    Word lowLinkExpId;
    Word lowerLinkExpId;
    Word lowestLinkExpId;
    Word functionalExpId;
    Word subjectId;
    Word subSubjectId;
    Word parameterId;
    Word literalId;
    Word comparisonExpId;
    Word assignmentExpId;
    Word addExpId;
    Word mulExpId;
    Word paramPassId;
    Word linkExpId;
    Word postfixTildeExpId;
    Word identifierTokenId;

    Word defId;
    Word returnId;
    Word ifId;
    Word forId;
    Word whileId;
    Word functionId;
    Word structureId;
    Word linkId;
    Word pointerTildeId;
    Word contentTildeId;

  public:
    CodeGenerator()
    {
      InitializeIds();
    }
    ~CodeGenerator() {}

  public:
    Module *GenerateModule(const SharedPtr<Core::Data::Module> &srcModule);
    Block *GenerateSet(const Core::Basic::SharedPtr<Core::Standard::ParsedList> &list);
    Block *GenerateInnerSet(const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &item);
    Expression *GenerateStatement(const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &item);
    Expression *GenerateDefine(const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &item);
    DefineVariable *GenerateDefineVariable(const std::string &name, const SharedPtr<Core::Standard::ParsedItem> &item);
    DefineFunction *GenerateDefineFunction(const std::string &name, const SharedPtr<Core::Standard::ParsedItem> &expr);
    DefineStruct *GenerateDefineStructure(const std::string &name, const SharedPtr<Core::Standard::ParsedItem> &expr);

    Expression *GenerateExpression(const SharedPtr<Core::Standard::ParsedItem> &item);
    CallFunction *GeneratePrint(const Core::Basic::SharedPtr<IdentifiableObject> &ptr);
    Return *GenerateReturn(const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &ptr);

  private:
    void InitializeIds();
    Expression *GenerateVariableRef(const SharedPtr<Core::Standard::ParsedItem> &param);
    //Expression *GenerateMemberAccess(const SharedPtr<IdentifiableObject> &param);
    Expression *GenerateConst(const SharedPtr<Core::Standard::ParsedToken> &literal);
    List *GenerateList(const SharedPtr<Core::Standard::ParsedList> &listExpr);
    Expression *GenerateBinaryOperator(const SharedPtr<Core::Standard::ParsedList> &cmpExpr);
    //CallFunction *GenerateFunctionCall(const SharedPtr<Core::Standard::ParsedList> &functionalExpr);
    List *GenerateOperand(const SharedPtr<IdentifiableObject> &functionalExpr);
    IfStatement *GenerateIfStatement(const SharedPtr<Core::Standard::ParsedItem> &command);
    ForStatement *GenerateForStatement(const SharedPtr<Core::Standard::ParsedItem> &command);
    WhileStatement *GenerateWhileStatement(const SharedPtr<Core::Standard::ParsedItem> &command);
    Expression *GenerateLinkStatement(const SharedPtr<Core::Standard::ParsedItem> &command);

  public:
    /**
     * Parses an AST block that represents a token, e.g. variable name,
     * number, etc.
     *
     * @param[in] item  A pointer to the root of the AST block.
     */
    std::string ParseToken(const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &item);

    /**
     * Parses an AST block that is generated for a variable type, e.g. int,
     * float, ptr[int], ptr[ptr[double]], etc.
     *
     * @param[in] item      A pointer to the root of the AST block.
     *
     * @return A pointer to ValueTypeSpec specifying the parsed type. The
     * content of the pointer is allocated in the heap and should be freed by
     * the caller.
     */
    ValueTypeSpec *ParseVariableType(
        const Core::Basic::SharedPtr<Core::Standard::ParsedItem> &item);

    /**
     * Parses a colon-separated variable definition where the name of the
     * variable is specified before the colon and the type of the variable is
     * after the colon.
     *
     * @param[in] astBlockRoot  A pointer to the root of the AST block to be parsed.
     *
     * @return A VariableDefinition value specifying the name and type of the
     * variable.
     */
    VariableDefinition ParseVariableDefinition(
        const SharedPtr<Core::Standard::ParsedItem> &astBlockRoot);

    /**
     * Parses a comma-separated list of variable definitions which is used
     * to specify the arguments of a function, where each argument is a
     * variable definition.
     *
     * @param[in] astBlockRoot  A pointer to the root of the AST block to be parsed.
     *
     * @return A VariableDefinitionArray containing the variable definitions.
     */
    VariableDefinitionArray ParseFunctionArguments(
        const SharedPtr<Core::Standard::ParsedItem> &astBlockRoot);

  }; // CodeGenerator
} // Scg

#endif // __CodeGenerator_h__