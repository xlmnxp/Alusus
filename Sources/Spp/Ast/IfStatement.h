/**
 * @file Spp/Ast/IfStatement.h
 * Contains the header of class Spp::Ast::IfStatement.
 *
 * @copyright Copyright (C) 2018 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef SPP_AST_IFSTATEMENT_H
#define SPP_AST_IFSTATEMENT_H

namespace Spp::Ast
{

class IfStatement : public Core::Data::Node,
                    public virtual Core::Basic::Bindings, public virtual Core::Basic::MapContainer<TiObject>,
                    public virtual Core::Data::Ast::Metadata, public virtual Core::Data::Clonable,
                    public virtual Core::Data::Printable
{
  //============================================================================
  // Type Info

  TYPE_INFO(IfStatement, Core::Data::Node, "Spp.Ast", "Spp", "alusus.net");
  IMPLEMENT_INTERFACES(Core::Data::Node, Core::Basic::Bindings, Core::Basic::MapContainer<TiObject>,
                                         Core::Data::Ast::Metadata, Core::Data::Clonable,
                                         Core::Data::Printable);


  //============================================================================
  // Member Variables

  private: Core::Basic::TioSharedPtr condition;
  private: Core::Basic::TioSharedPtr ifBody;
  private: Core::Basic::TioSharedPtr elseBody;


  //============================================================================
  // Implementations

  IMPLEMENT_METADATA(IfStatement);

  IMPLEMENT_BINDINGS(Bindings,
    (prodId, Core::Basic::TiWord, VALUE, setProdId(value), &prodId),
    (sourceLocation, Core::Data::SourceLocation, SHARED_REF, setSourceLocation(value), sourceLocation.get())
  );

  IMPLEMENT_MAP_CONTAINING(MapContainer<TiObject>,
    (condition, Core::Basic::TiObject, setCondition(value), condition.get()),
    (ifBody, Core::Basic::TiObject, setIfBody(value), ifBody.get()),
    (elseBody, Core::Basic::TiObject, setElseBody(value), elseBody.get())
  );

  IMPLEMENT_AST_CLONABLE(IfStatement);

  IMPLEMENT_AST_MAP_PRINTABLE(IfStatement);


  //============================================================================
  // Constructors & Destructor

  IMPLEMENT_EMPTY_CONSTRUCTOR(IfStatement);

  IMPLEMENT_ATTR_CONSTRUCTOR(IfStatement);

  IMPLEMENT_ATTR_MAP_CONSTRUCTOR(IfStatement);

  public: virtual ~IfStatement()
  {
    DISOWN_SHAREDPTR(this->condition);
    DISOWN_SHAREDPTR(this->ifBody);
    DISOWN_SHAREDPTR(this->elseBody);
  }


  //============================================================================
  // Member Functions

  public: void setCondition(Core::Basic::TioSharedPtr const &cond)
  {
    UPDATE_OWNED_SHAREDPTR(this->condition, cond);
  }
  private: void setCondition(TiObject *cond)
  {
    this->setCondition(getSharedPtr(cond));
  }

  public: Core::Basic::TioSharedPtr const& getCondition() const
  {
    return this->condition;
  }

  public: void setIfBody(Core::Basic::TioSharedPtr const &body)
  {
    UPDATE_OWNED_SHAREDPTR(this->ifBody, body);
  }
  private: void setIfBody(TiObject *body)
  {
    this->setIfBody(getSharedPtr(body));
  }

  public: Core::Basic::TioSharedPtr const& getIfBody() const
  {
    return this->ifBody;
  }

  public: void setElseBody(Core::Basic::TioSharedPtr const &body)
  {
    UPDATE_OWNED_SHAREDPTR(this->elseBody, body);
  }
  private: void setElseBody(TiObject *body)
  {
    this->setElseBody(getSharedPtr(body));
  }

  public: Core::Basic::TioSharedPtr const& getElseBody() const
  {
    return this->elseBody;
  }

}; // class

} // namespace

#endif
