/**
 * @file Core/Data/Ast/GenericCommand.h
 * Contains the header of class Core::Data::Ast::GenericCommand.
 *
 * @copyright Copyright (C) 2020 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/license.html>.
 */
//==============================================================================

#ifndef CORE_DATA_AST_GENERICCOMMAND_H
#define CORE_DATA_AST_GENERICCOMMAND_H

namespace Core::Data::Ast
{

class GenericCommand : public Node,
                       public Binding, public MapContaining<TiObject>, public MetaHaving, public Printable
{
  //============================================================================
  // Type Info

  TYPE_INFO(GenericCommand, Node, "Core.Data.Ast", "Core", "alusus.org");
  IMPLEMENT_INTERFACES(Node, Binding, MapContaining<TiObject>, MetaHaving, Printable);
  OBJECT_FACTORY(GenericCommand);


  //============================================================================
  // Member Variables

  protected: TiStr type;
  protected: SharedPtr<List> args;
  protected: SharedPtr<List> modifiers;


  //============================================================================
  // Implementations

  IMPLEMENT_METAHAVING(GenericCommand);

  IMPLEMENT_BINDING(Binding,
    (type, TiStr, VALUE, setType(value), &type),
    (prodId, TiWord, VALUE, setProdId(value), &prodId),
    (sourceLocation, SourceLocation, SHARED_REF, setSourceLocation(value), sourceLocation.get())
  );

  IMPLEMENT_MAP_CONTAINING(MapContaining<TiObject>,
    (args, List, SHARED_REF, setArgs(value), args.get()),
    (modifiers, List, SHARED_REF, setModifiers(value), modifiers.get())
  );

  IMPLEMENT_AST_MAP_PRINTABLE(GenericCommand, << this->type.get());


  //============================================================================
  // Constructors & Destructor

  IMPLEMENT_EMPTY_CONSTRUCTOR(GenericCommand);

  IMPLEMENT_ATTR_CONSTRUCTOR(GenericCommand);

  IMPLEMENT_ATTR_MAP_CONSTRUCTOR(GenericCommand);

  public: virtual ~GenericCommand()
  {
    DISOWN_SHAREDPTR(this->args);
    DISOWN_SHAREDPTR(this->modifiers);
  }


  //============================================================================
  // Member Functions

  public: void setType(Char const *t)
  {
    this->type = t;
  }
  public: void setType(TiStr const *t)
  {
    this->type = t == 0 ? "" : t->get();
  }

  public: TiStr const& getType() const
  {
    return this->type;
  }

  public: void setArgs(SharedPtr<List> const &a)
  {
    UPDATE_OWNED_SHAREDPTR(this->args, a);
  }
  private: void setArgs(List *a)
  {
    this->setArgs(getSharedPtr(a));
  }

  public: void addArg(TioSharedPtr const &arg)
  {
    if (this->args == 0) {
      this->args = List::create({}, { arg });
    } else {
      this->args->add(arg);
    }
  }

  public: SharedPtr<List> const& getArgs() const
  {
    return this->args;
  }

  public: void setModifiers(SharedPtr<List> const &m)
  {
    UPDATE_OWNED_SHAREDPTR(this->modifiers, m);
  }
  private: void setModifiers(List *m)
  {
    this->setModifiers(getSharedPtr(m));
  }

  public: void addModifier(TioSharedPtr const &modifier)
  {
    if (this->modifiers == 0) {
      this->modifiers = List::create({}, { modifier });
    } else {
      this->modifiers->add(modifier);
    }
  }

  public: SharedPtr<List> const& getModifiers() const
  {
    return this->modifiers;
  }

}; // class

} // namespace

#endif
