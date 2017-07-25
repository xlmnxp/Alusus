/**
 * @file Core/Data/ConstTerm.h
 * Contains the header of class Core::Data::ConstTerm.
 *
 * @copyright Copyright (C) 2015 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef CORE_DATA_CONSTTERM_H
#define CORE_DATA_CONSTTERM_H

namespace Core { namespace Data
{

/**
 * @brief Handles constant grammar terms.
 * @ingroup data_terms
 *
 * This class handles constant terms in grammar formulas. Constant terms
 * are used to check for exact matches of strings.
 */
class ConstTerm : public Term
{
  //============================================================================
  // Type Info

  TYPE_INFO(ConstTerm, Term, "Core.Data", "Core", "alusus.net");


  //============================================================================
  // Member Variables

  /// A pointer to the string constant to be matched with input characters.
  private: WStr matchString;


  //============================================================================
  // Constructor / Destructor

  public: ConstTerm(SharedPtr<Node> const &f=SharedPtr<Node>(), Char const *str=0) : Term(f), matchString(str)
  {
  }

  public: ConstTerm(Word f, Char const *str=0) : Term(f), matchString(str)
  {
  }

  public: virtual ~ConstTerm()
  {
  }

  public: static SharedPtr<ConstTerm> create(SharedPtr<Node> const &f=SharedPtr<Node>(), Char const *str=0)
  {
    return std::make_shared<ConstTerm>(f, str);
  }

  public: static SharedPtr<ConstTerm> create(Word f, Char const *str=0)
  {
    return std::make_shared<ConstTerm>(f, str);
  }


  //============================================================================
  // Member Functions

  /**
   * @brief Set the match string.
   *
   * Once a match string is set, modifying (or setting) this value is not
   * allowed. This is to prevent accidentally modifying it while being in use
   * by some state.
   */
  public: void setMatchString(Char const *str)
  {
    if (str == 0) {
      throw EXCEPTION(InvalidArgumentException, STR("str"), STR("Argument should not be null."), str);
    }
    if (this->matchString.size() > 0) {
      throw EXCEPTION(GenericException, STR("Modifying an already set match string is not allowed."));
    }
    this->matchString= str;
  }

  /// Get the match string.
  public: WStr const& getMatchString() const
  {
    return this->matchString;
  }

}; // class

} } // namespace

#endif
