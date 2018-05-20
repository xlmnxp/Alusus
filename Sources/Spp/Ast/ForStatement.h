/**
 * @file Spp/Ast/ForStatement.h
 * Contains the header of class Spp::Ast::ForStatement.
 *
 * @copyright Copyright (C) 2018 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef SPP_AST_FORSTATEMENT_H
#define SPP_AST_FORSTATEMENT_H

namespace Spp::Ast
{

using namespace Core;

class ForStatement : public Core::Data::Node,
                     public virtual Core::Basic::Bindings, public virtual Core::Basic::MapContainer<TiObject>,
                     public virtual Core::Data::Ast::Metadata, public virtual Core::Data::Clonable,
                     public virtual Core::Data::Printable
{
  //============================================================================
  // Type Info

  TYPE_INFO(ForStatement, Core::Data::Node, "Spp.Ast", "Spp", "alusus.net");
  IMPLEMENT_INTERFACES(Core::Data::Node, Core::Basic::Bindings, Core::Basic::MapContainer<TiObject>,
                                         Core::Data::Ast::Metadata, Core::Data::Clonable,
                                         Core::Data::Printable);


  //============================================================================
  // Member Variables

  private: TioSharedPtr initializer;
  private: TioSharedPtr condition;
  private: TioSharedPtr updater;
  private: TioSharedPtr body;


  //============================================================================
  // Implementations

  IMPLEMENT_METADATA(ForStatement);

  IMPLEMENT_BINDINGS(Bindings,
    (prodId, TiWord, VALUE, setProdId(value), &prodId),
    (sourceLocation, Core::Data::SourceLocation, SHARED_REF, setSourceLocation(value), sourceLocation.get())
  );

  IMPLEMENT_MAP_CONTAINING(MapContainer<TiObject>,
    (initializer, TiObject, setInitializer(value), initializer.get()),
    (condition, TiObject, setCondition(value), condition.get()),
    (updater, TiObject, setUpdater(value), updater.get()),
    (body, TiObject, setBody(value), body.get())
  );

  IMPLEMENT_AST_CLONABLE(ForStatement);

  IMPLEMENT_AST_MAP_PRINTABLE(ForStatement);


  //============================================================================
  // Constructors & Destructor

  IMPLEMENT_EMPTY_CONSTRUCTOR(ForStatement);

  IMPLEMENT_ATTR_CONSTRUCTOR(ForStatement);

  IMPLEMENT_ATTR_MAP_CONSTRUCTOR(ForStatement);

  public: virtual ~ForStatement()
  {
    DISOWN_SHAREDPTR(this->initializer);
    DISOWN_SHAREDPTR(this->condition);
    DISOWN_SHAREDPTR(this->updater);
    DISOWN_SHAREDPTR(this->body);
  }


  //============================================================================
  // Member Functions

  public: void setInitializer(TioSharedPtr const &init)
  {
    UPDATE_OWNED_SHAREDPTR(this->initializer, init);
  }
  private: void setInitializer(TiObject *init)
  {
    this->setInitializer(getSharedPtr(init));
  }

  public: TioSharedPtr const& getInitializer() const
  {
    return this->initializer;
  }

  public: void setCondition(TioSharedPtr const &cond)
  {
    UPDATE_OWNED_SHAREDPTR(this->condition, cond);
  }
  private: void setCondition(TiObject *cond)
  {
    this->setCondition(getSharedPtr(cond));
  }

  public: TioSharedPtr const& getCondition() const
  {
    return this->condition;
  }

  public: void setUpdater(TioSharedPtr const &updtr)
  {
    UPDATE_OWNED_SHAREDPTR(this->updater, updtr);
  }
  private: void setUpdater(TiObject *updtr)
  {
    this->setUpdater(getSharedPtr(updtr));
  }

  public: TioSharedPtr const& getUpdater() const
  {
    return this->updater;
  }

  public: void setBody(TioSharedPtr const &b)
  {
    UPDATE_OWNED_SHAREDPTR(this->body, b);
  }
  private: void setBody(TiObject *b)
  {
    this->setBody(getSharedPtr(b));
  }

  public: TioSharedPtr const& getBody() const
  {
    return this->body;
  }

}; // class

} // namespace

#endif
