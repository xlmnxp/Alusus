/**
 * @file Scg/Operators/IdentifierReference.h
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

// TODO: Consider renaming the class to IdentifierReferenceByName.

#ifndef __IdentifierReference_h__
#define __IdentifierReference_h__

#include <Types/ValueTypeSpec.h>

using namespace Core;

namespace Scg
{
class Block;
class Value;
class ValueType;

/**
 * Represents a reference to a variable by name.
 */
class IdentifierReference : public Expression
{
protected:
  //! The name of the variable.
  std::string name;
  //! Storing the value type to avoid fetching it frequently.
  mutable ValueType *valueType = nullptr;

public:
  /**
   * Constructs pointer to the variable having the given name in the scope where
   * this expression is defined.
   * @param[in] name  The name of the variable to point to.
   */
  IdentifierReference(Char const *name) : name(name) {}

  /**
   * Gets the name of the variable pointed to by this instance.
   * @return The name of the variable.
   */
  const std::string &getName() const
  {
    return name;
  }

  //! @copydoc Pointer::getValueTypeSpec()
  virtual const ValueTypeSpec *getValueTypeSpec() const override;

  //! @copydoc Expression::generateCode()
  virtual CodeGenerationStage generateCode();

  //! @copydoc Expression::toString()
  virtual std::string toString();
};
}

#endif // __IdentifierReference_h__