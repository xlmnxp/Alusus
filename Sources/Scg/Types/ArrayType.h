/**
 * @file Scg/Types/ArrayType.h
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef __ArrayType_h__
#define __ArrayType_h__

// Scg header files
#include <Types/ValueType.h>
#include <Types/ValueTypeSpec.h>

// LLVM forward declarations
#include <llvm_fwd.h>

namespace Scg
{
  /**
   * Represents a structure type with custom fields.
   */
  class ArrayType : public ValueType
  {
    //! The name of the type, for example arr[int, 10].
    std::string name;
    ArrayValueTypeSpec typeSpec;
    ValueType *elementsType;
    unsigned int arraySize;

  public:
    /**
     * Constructs a new array type.
     * @param[in] elementsType  The type of the elements of the array.
     * @param[in] arraySize     The number of elements in the array.
     */
    ArrayType(ValueType *elementsType, unsigned int arraySize);

    //! @copydoc ValueType::GetName()
    virtual const std::string GetName() const { return name; }

    /**
     * Retrieves the type of the elements of the array.
     * @return A pointer to the type of the elements of the array.
     */
    virtual const ValueType *GetElementsType () const { return elementsType; }

    /**
     * Retrieves the number of the elements of the array.
     * @return The number of the elements of the array.
     */
    unsigned int GetArraySize() const { return arraySize; }

    //! @copydoc ValueType::GetValueTypeSpec()
    virtual const ValueTypeSpec *GetValueTypeSpec() const
    {
      return &typeSpec;
    }

    //! @copydoc ValueType::GetDefaultLLVMValue()
    virtual llvm::Constant *GetDefaultLLVMValue() const
    {
      THROW_EXCEPTION(NotImplementedException, "Not implemented yet!");
    }

    //! @copydoc ValueType::GetImplicitCastingOperator()
    virtual const ValueTypeArray &GetImplicitCastingTargets() const
    {
      THROW_EXCEPTION(NotImplementedException, "Not implemented yet for arrays.");
    }

    //! @copydoc ValueType::GetExplicitCastingTargets()
    virtual const ValueTypeArray &GetExplicitCastingTargets() const
    {
      THROW_EXCEPTION(NotImplementedException, "Not implemented yet for arrays.");
    }

    //! @copydoc ValueType::GetImplicitCastingOperator()
    virtual CastingOperator *GetImplicitCastingOperator(const ValueType *targetType, Expression *expr) const
    {
      THROW_EXCEPTION(NotImplementedException, "Not implemented yet for arrays.");
    }

    //! @copydoc ValueType::GetExplicitCastingOperator()
    virtual CastingOperator *GetExplicitCastingOperator(const ValueType *targetType, Expression *expr) const
    {
      THROW_EXCEPTION(NotImplementedException, "Not implemented yet for arrays.");
    }
  };
}

#endif // __ArrayType_h__