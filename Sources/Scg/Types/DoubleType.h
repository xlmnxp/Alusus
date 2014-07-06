/**
 * @file Scg/Types/DoubleType.h
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef __DoubleType_h__
#define __DoubleType_h__

// Scg header files
#include <Types/ValueType.h>
#include <Types/ValueTypeSpec.h>

// LLVM forward declarations
#include <llvm_fwd.h>

namespace Scg
{
  //! Represents the double type.
  class DoubleType : public ValueType
  {
    friend class LlvmContainer;
    static DoubleType *s_singleton;
    ValueTypeSpecByName typeSpec;

  public:
    //! Constructs a double type.
    DoubleType();

    //! Destructor.
    virtual ~DoubleType() {}

    /**
     * Gets a constant value of double type.
     * @param[in] value The value of the constant.
     */
    llvm::Constant *GetLlvmConstant(double value) const;

    //! @copydoc ValueType::GetDefaultLLVMValue()
    virtual llvm::Constant *GetDefaultLLVMValue() const
    {
      return GetLlvmConstant(0.0);
    }

    //! @copydoc ValueType::GetName()
    virtual const std::string GetName() const { return "double"; }

    //! @copydoc ValueType::GetValueTypeSpec()
    virtual const ValueTypeSpec *GetValueTypeSpec() const
    {
      return &typeSpec;
    }

    //! @copydoc ValueType::GetImplicitCastingTargets()
    const ValueTypeArray &GetImplicitCastingTargets() const;

    //! @copydoc ValueType::GetExplicitCastingTargets()
    const ValueTypeArray &GetExplicitCastingTargets() const;

    //! @copydoc ValueType::GetImplicitCastingOperator()
    virtual CastingOperator *GetImplicitCastingOperator(
        const ValueType *targetType, Expression *expr) const;

    //! @copydoc ValueType::GetExplicitCastingOperator()
    virtual CastingOperator *GetExplicitCastingOperator(
        const ValueType *targetType, Expression *expr) const;

    static DoubleType *GetSingleton() { return s_singleton; }
  };
}

#endif // __DoubleType_h__