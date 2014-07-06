/**
 * @file Core/Data/PlainProvider.h
 * Contains the header of interface Data::PlainProvider.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef DATA_PLAINPROVIDER_H
#define DATA_PLAINPROVIDER_H

namespace Core { namespace Data
{

// TODO: DOC

class Reference;

class PlainProvider : public Provider
{
  //============================================================================
  // Type Info

  INTERFACE_INFO(PlainProvider, Provider, "Core.Data", "Core", "alusus.net");


  //============================================================================
  // Abstract Functions

  /// @name Data Setting Functions
  /// @{

  public: virtual void setPlainValue(Reference *ref, IdentifiableObject *val) = 0;

  public: virtual void setPlainValue(const Char *qualifier, IdentifiableObject *val) = 0;

  public: virtual Bool trySetPlainValue(Reference *ref, IdentifiableObject *val) = 0;

  public: virtual Bool trySetPlainValue(const Char *qualifier, IdentifiableObject *val) = 0;

  /// @}

}; // class

} } // namespace

#endif