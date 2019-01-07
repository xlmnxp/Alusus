/**
 * @file Spp/GrammarFactory.cpp
 *
 * @copyright Copyright (C) 2018 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include "core.h"
#include "spp.h"

namespace Spp
{

using namespace Core;
using namespace Core::Data::Grammar;
using namespace Core::Processing;
using namespace Core::Processing::Handlers;

//==============================================================================
// Overloaded Abstract Functions

void GrammarFactory::createGrammar(
  Core::Data::Ast::Scope *rootScope, Main::RootManager *manager, Ast::Helper *astHelper,
  CodeGen::MacroProcessor *macroProcessor, CodeGen::Generator *generator,
  LlvmCodeGen::TargetGenerator *targetGenerator
) {
  this->setRootScope(rootScope);

  // Create leading commands.

  auto leadingCmdList = this->getLeadingCommandsList();
  auto innerCmdList = this->getInnerCommandsList();
  auto tildeCmdList = this->getTildeCommandsList();

  //// DumpIr = "dump_ir" + Subject
  this->set(S("root.Main.DumpLlvmIr"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("dump_llvm_ir"), 0 }, { S("أدرج_ت_و"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::CodeGenParsingHandler>(
      manager, astHelper, macroProcessor, generator, targetGenerator, false
    )}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.DumpLlvmIr")));

  //// run = "run" + Subject
  this->set(S("root.Main.Run"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("run"), 0 }, { S("نفّذ"), 0 }, { S("نفذ"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::CodeGenParsingHandler>(
      manager, astHelper, macroProcessor, generator, targetGenerator, true
    )}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.Run")));

  //// if = "if" + Expression + Statement + ("else" + Statement)*(0, 1)
  this->set(S("root.Main.If"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.MultiCmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("sections"), List::create({}, {
        Map::create(false, {}, {
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)},
          {S("kwd"), Map::create(false, {}, { { S("if"), 0 }, { S("إذا"), 0 } })},
          {S("args"), List::create({}, {
            Map::create(false, {}, {
              {S("min"), std::make_shared<TiInt>(1)},
              {S("max"), std::make_shared<TiInt>(1)},
              {S("pty"), std::make_shared<TiInt>(1)},
              {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)},
              {S("prd"), PARSE_REF(S("module.Expression"))}
            }),
            Map::create(false, {}, {
              {S("min"), std::make_shared<TiInt>(1)},
              {S("max"), std::make_shared<TiInt>(1)},
              {S("pty"), std::make_shared<TiInt>(1)},
              {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)},
              {S("prd"), PARSE_REF(S("module.BlockStatements.Stmt"))}
            })
          })}
        }),
        Map::create(false, {}, {
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(TermFlags::ONE_ROUTE_TERM|ParsingFlags::PASS_ITEMS_UP)},
          {S("kwd"), Map::create(false, {}, { { S("else"), 0 }, { S("وإلا"), 0 } })},
          {S("args"), List::create({}, {
            Map::create(false, {}, {
              {S("min"), std::make_shared<TiInt>(1)},
              {S("max"), std::make_shared<TiInt>(1)},
              {S("pty"), std::make_shared<TiInt>(1)},
              {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)},
              {S("prd"), PARSE_REF(S("module.BlockStatements.Stmt"))}
            })
          })}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::IfParsingHandler>()}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.If")));

  //// while = "while" + Expression + Statement
  this->set(S("root.Main.While"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("while"), 0 }, { S("بينما"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        }),
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.BlockStatements.Stmt"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::WhileParsingHandler>()}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.While")));

  //// for = "for" + Exp + Statement
  this->set(S("root.Main.For"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("for"), 0 }, { S("لكل"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        }),
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.BlockStatements.Stmt"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::ForParsingHandler>()}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.For")));

  //// continue = "continue" + Subject.Literal
  this->set(S("root.Main.Continue"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("continue"), 0 }, { S("أكمل"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Subject.Parameter"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<CustomParsingHandler>([](Parser *parser, ParserState *state) {
      auto metadata = state->getData().ti_cast_get<Data::Ast::MetaHaving>();
      auto currentList = state->getData().ti_cast_get<Containing<TiObject>>();
      auto continueStatement = Ast::ContinueStatement::create({
        { S("prodId"), metadata->getProdId() },
        { S("sourceLocation"), metadata->findSourceLocation() }
      });
      if (currentList != 0) {
        auto intLiteral = ti_cast<Core::Data::Ast::IntegerLiteral>(currentList->getElement(1));
        if (currentList->getElement(1) != 0 && intLiteral == 0) {
          state->addNotice(
            std::make_shared<Spp::Notices::InvalidContinueStatementNotice>(metadata->findSourceLocation())
          );
          state->setData(SharedPtr<TiObject>(0));
          return;
        }
        continueStatement->setSteps(getSharedPtr(intLiteral));
      }
      state->setData(continueStatement);
    })}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.Continue")));

  //// break = "break" + Subject.Literal
  this->set(S("root.Main.Break"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("break"), 0 }, { S("اقطع"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Subject.Parameter"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<CustomParsingHandler>([](Parser *parser, ParserState *state) {
      auto metadata = state->getData().ti_cast_get<Data::Ast::MetaHaving>();
      auto currentList = state->getData().ti_cast_get<Containing<TiObject>>();
      auto breakStatement = Ast::BreakStatement::create({
        { "prodId", metadata->getProdId() },
        { "sourceLocation", metadata->findSourceLocation() }
      });
      if (currentList != 0) {
        auto intLiteral = ti_cast<Core::Data::Ast::IntegerLiteral>(currentList->getElement(1));
        if (currentList->getElement(1) != 0 && intLiteral == 0) {
          state->addNotice(std::make_shared<Spp::Notices::InvalidBreakStatementNotice>(metadata->findSourceLocation()));
          state->setData(SharedPtr<TiObject>(0));
          return;
        }
        breakStatement->setSteps(getSharedPtr(intLiteral));
      }
      state->setData(breakStatement);
    })}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.Break")));

  //// return = "return" + Expression
  this->set(S("root.Main.Return"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("return"), 0 }, { S("أرجع"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<CustomParsingHandler>([](Parser *parser, ParserState *state) {
      auto metadata = state->getData().ti_cast_get<Data::Ast::MetaHaving>();
      auto currentList = state->getData().ti_cast_get<Containing<TiObject>>();
      auto returnStatement = Ast::ReturnStatement::create({
        { "prodId", metadata->getProdId() },
        { "sourceLocation", metadata->findSourceLocation() }
      });
      if (currentList != 0) {
        returnStatement->setOperand(getSharedPtr(currentList->getElement(1)));
      }
      state->setData(returnStatement);
    })}
  }).get());
  leadingCmdList->add(PARSE_REF(S("module.Return")));

  // Create inner commands.

  //// module = "module" + Set
  this->set(S("root.Main.Module"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("module"), 0 }, { S("حزمة"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.ModuleBody"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<CustomParsingHandler>([](Parser *parser, ParserState *state) {
      auto currentList = state->getData().ti_cast_get<Containing<TiObject>>();
      // We'll use the source location of the "module" keyword, rather than of the first statement.
      auto metaHaving = ti_cast<Core::Data::Ast::MetaHaving>(currentList->getElement(1));
      metaHaving->setSourceLocation(Core::Data::Ast::findSourceLocation(currentList->getElement(0)));
      state->setData(getSharedPtr(currentList->getElement(1)));
    })}
  }).get());
  innerCmdList->add(PARSE_REF(S("module.Module")));
  this->set(S("root.Main.ModuleBody"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("root.Set"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("stmt"), PARSE_REF(S("module.ModuleStatements.StmtList"))}
    })}
  }).get());
  this->set(S("root.Main.ModuleStatements"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Statements"))}
  }, {}));
  this->set(S("root.Main.ModuleStatements.StmtList"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.StmtList"))},
  }, {
    {S("handler"), ScopeParsingHandler<Spp::Ast::Module>::create(-1)}
  }).get());

  //// type = "type" + Set
  this->set(S("root.Main.Type"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("type"), 0 }, { S("صنف"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.BlockSet"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<CustomParsingHandler>([](Parser *parser, ParserState *state) {
      auto currentList = state->getData().ti_cast_get<Containing<TiObject>>();
      auto metadata = ti_cast<Data::Ast::MetaHaving>(currentList);
      auto type = Ast::UserType::create({
        { "prodId", metadata->getProdId()},
        { "sourceLocation", metadata->findSourceLocation() }
      }, {
        { "body", currentList->getElement(1) }
      });
      state->setData(type);
    })}
  }).get());
  innerCmdList->add(PARSE_REF(S("module.Type")));

  // Function
  this->set(S("root.Main.Function"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("function"), 0 }, { S("دالّة"), 0 }, { S("دالة"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.FuncSigExpression"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP|TermFlags::ONE_ROUTE_TERM)}
        }),
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.BlockSet"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("modifierTranslations"), Map::create({}, {
      {S("تصدير"), TiStr::create(S("expname"))}
    })},
    {S("handler"), std::make_shared<Handlers::FunctionParsingHandler>() }
  }).get());
  innerCmdList->add(PARSE_REF(S("module.Function")));

  // FuncSigExpression
  this->set(S("root.Main.FuncSigExpression"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Expression")) },
    {S("startRef"), PARSE_REF(S("module.LowLinkExp"))}
  }, {
    {S("subject"), PARSE_REF(S("module.owner.FuncSigSubject"))}
  }).get());
  this->set(S("root.Main.FuncSigExpression.LowLinkExp"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.LowLinkExp"))},
  }, {
    {S("vars"), Map::create(false, {}, {{S("enable"), std::make_shared<TiInt>(1)}})},
  }).get());
  this->set(S("root.Main.FuncSigExpression.AddExp"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.AddExp"))},
  }, {
    {S("vars"), Map::create(false, {}, {{S("enable"), std::make_shared<TiInt>(0)}})},
  }).get());
  this->set(S("root.Main.FuncSigExpression.MulExp"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.MulExp"))},
  }, {
    {S("vars"), Map::create(false, {}, {{S("enable"), std::make_shared<TiInt>(0)}})},
  }).get());
  this->set(S("root.Main.FuncSigExpression.BitwiseExp"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.BitwiseExp"))},
  }, {
    {S("vars"), Map::create(false, {}, {{S("enable"), std::make_shared<TiInt>(0)}})},
  }).get());
  this->set(S("root.Main.FuncSigExpression.UnaryExp"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.UnaryExp"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("enable1"), std::make_shared<TiInt>(0)},
      {S("enable2"), std::make_shared<TiInt>(0)}
    })},
  }).get());

  this->set(S("root.Main.FuncSigSubject"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Subject")) }
  }).get());
  this->set(S("root.Main.FuncSigSubject.Sbj"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.Sbj"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("sbj1"), PARSE_REF(S("module.Parameter"))},
      {S("sbj2"), PARSE_REF(S("module.expression"))},
      {S("sbj3"), PARSE_REF(S("module.expression"))},
      {S("frc2"), 0},
      {S("frc3"), 0},
      {S("fltr"), 0}
    })}
  }).get());

  // Macro
  this->set(S("root.Main.Macro"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("macro"), 0 }, { S("ماكرو"), 0 } })},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.MacroSignature"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP|TermFlags::ONE_ROUTE_TERM)}
        }),
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.Expression"))},
          {S("min"), std::make_shared<TiInt>(0)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), std::make_shared<Handlers::MacroParsingHandler>() }
  }).get());
  innerCmdList->add(PARSE_REF(S("module.Macro")));
  // Macro Signature
  this->set(S("root.Main.MacroSignature"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Subject")) }
  }).get());
  this->set(S("root.Main.MacroSignature.Sbj"), SymbolDefinition::create({
   {S("baseRef"), PARSE_REF(S("bmodule.Sbj"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("sbj1"), PARSE_REF(S("module.expression"))},
      {S("sbj2"), PARSE_REF(S("module.expression"))},
      {S("sbj3"), PARSE_REF(S("module.expression"))},
      {S("frc2"), std::make_shared<TiInt>(1)},
      {S("frc3"), std::make_shared<TiInt>(1)},
      {S("fltr"), std::make_shared<TiInt>(2)}
    })}
  }).get());

  // BlockSet
  this->set(S("root.Main.BlockSet"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("root.Set"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("stmt"), PARSE_REF(S("module.BlockStatements.StmtList"))}
    })}
  }).get());
  // BlockStatements
  this->set(S("root.Main.BlockStatements"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Statements"))}
  }, {
    {S("expression"), PARSE_REF(S("module.owner.BlockExpression"))}
  }));
  this->set(S("root.Main.BlockStatements.StmtList"), SymbolDefinition::create({
    {S("baseRef"), PARSE_REF(S("bmodule.StmtList"))},
  }, {
    {S("handler"), ScopeParsingHandler<Spp::Ast::Block>::create(-1) }
  }));
  // BlockSubject
  this->set(S("root.Main.BlockSubject"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Subject")) }
  }, {
    {S("set"), PARSE_REF(S("module.owner.BlockSet"))}
  }).get());
  // BlockExpression
  this->set(S("root.Main.BlockExpression"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Expression")) }
  }, {
    {S("subject"), PARSE_REF(S("module.owner.BlockSubject"))}
  }).get());

  // Create tilde commands.

  // ~ptr
  this->set(S("root.Main.PointerTilde"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("ptr"), 0 }, { S("مؤشر"), 0 } })},
      {S("prms"), List::create() }
    })},
    {S("handler"), Spp::Handlers::TildeOpParsingHandler<Spp::Ast::PointerOp>::create() }
  }).get());
  tildeCmdList->add(PARSE_REF(S("module.PointerTilde")));
  // ~cnt
  this->set(S("root.Main.ContentTilde"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("cnt"), 0 }, { S("محتوى"), 0 } })},
      {S("prms"), List::create() }
    })},
    {S("handler"), Spp::Handlers::TildeOpParsingHandler<Spp::Ast::ContentOp>::create() }
  }).get());
  tildeCmdList->add(PARSE_REF(S("module.ContentTilde")));
  // ~cast
  this->set(S("root.Main.CastTilde"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, {{S("cast"), 0}, {S("مثّل"), 0}, {S("مثل"), 0}})},
      {S("prms"), List::create({}, {
        Map::create(false, {}, {
          {S("prd"), PARSE_REF(S("module.CastSubject"))},
          {S("min"), std::make_shared<TiInt>(1)},
          {S("max"), std::make_shared<TiInt>(1)},
          {S("pty"), std::make_shared<TiInt>(1)},
          {S("flags"), TiInt::create(ParsingFlags::PASS_ITEMS_UP)}
        })
      })}
    })},
    {S("handler"), Spp::Handlers::TildeOpParsingHandler<Spp::Ast::CastOp>::create() }
  }).get());
  tildeCmdList->add(PARSE_REF(S("module.CastTilde")));
  this->set(S("root.Main.CastSubject"), Module::create({
    {S("baseRef"), PARSE_REF(S("module.Subject")) }
  }).get());
  this->set(S("root.Main.CastSubject.Sbj"), SymbolDefinition::create({
   {S("baseRef"), PARSE_REF(S("bmodule.Sbj"))},
  }, {
    {S("vars"), Map::create(false, {}, {
      {S("sbj1"), PARSE_REF(S("module.expression"))},
      {S("sbj2"), PARSE_REF(S("module.expression"))},
      {S("sbj3"), PARSE_REF(S("module.expression"))},
      {S("frc2"), std::make_shared<TiInt>(1)},
      {S("frc3"), std::make_shared<TiInt>(1)},
      {S("fltr"), std::make_shared<TiInt>(2)}
    })}
  }).get());
  // ~size
  this->set(S("root.Main.SizeTilde"), SymbolDefinition::create({}, {
    {S("term"), PARSE_REF(S("root.Cmd"))},
    {S("vars"), Map::create(false, {}, {
      {S("kwd"), Map::create(false, {}, { { S("size"), 0 }, { S("حجم"), 0 } })},
      {S("prms"), List::create() }
    })},
    {S("handler"), Spp::Handlers::TildeOpParsingHandler<Spp::Ast::SizeOp>::create() }
  }).get());
  tildeCmdList->add(PARSE_REF(S("module.SizeTilde")));
}


void GrammarFactory::cleanGrammar(Core::Data::Ast::Scope *rootScope)
{
  this->setRootScope(rootScope);

  auto leadingCmdList = this->getLeadingCommandsList();
  auto innerCmdList = this->getInnerCommandsList();
  auto tildeCmdList = this->getTildeCommandsList();

  // Remove commands from tilde commands list.
  this->removeReferenceFromCommandList(tildeCmdList, S("module.SizeTilde"));
  this->removeReferenceFromCommandList(tildeCmdList, S("module.CastTilde"));
  this->removeReferenceFromCommandList(tildeCmdList, S("module.ContentTilde"));
  this->removeReferenceFromCommandList(tildeCmdList, S("module.PointerTilde"));

  // Remove commands from leading commands list.
  this->removeReferenceFromCommandList(leadingCmdList, S("module.DumpLlvmIr"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.Run"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.If"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.While"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.For"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.Continue"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.Break"));
  this->removeReferenceFromCommandList(leadingCmdList, S("module.Return"));

  // Remove command from inner commands list.
  this->removeReferenceFromCommandList(innerCmdList, S("module.Module"));
  this->removeReferenceFromCommandList(innerCmdList, S("module.Type"));
  this->removeReferenceFromCommandList(innerCmdList, S("module.Function"));
  this->removeReferenceFromCommandList(innerCmdList, S("module.Macro"));

  // Delete tilde command definitions.
  this->tryRemove(S("root.Main.PointerTilde"));
  this->tryRemove(S("root.Main.ContentTilde"));
  this->tryRemove(S("root.Main.CastTilde"));
  this->tryRemove(S("root.Main.CastSubject"));
  this->tryRemove(S("root.Main.SizeTilde"));

  // Delete leading command definitions.
  this->tryRemove(S("root.Main.DumpLlvmIr"));
  this->tryRemove(S("root.Main.Run"));
  this->tryRemove(S("root.Main.If"));
  this->tryRemove(S("root.Main.While"));
  this->tryRemove(S("root.Main.For"));
  this->tryRemove(S("root.Main.Continue"));
  this->tryRemove(S("root.Main.Break"));
  this->tryRemove(S("root.Main.Return"));

  // Delete inner command definitions.
  this->tryRemove(S("root.Main.Module"));
  this->tryRemove(S("root.Main.ModuleBody"));
  this->tryRemove(S("root.Main.ModuleStatements"));
  this->tryRemove(S("root.Main.Type"));
  this->tryRemove(S("root.Main.Function"));
  this->tryRemove(S("root.Main.FuncSigExpression"));
  this->tryRemove(S("root.Main.FuncSigSubject"));
  this->tryRemove(S("root.Main.Macro"));
  this->tryRemove(S("root.Main.MacroSignature"));

  // Delete block definitions.
  this->tryRemove(S("root.Main.BlockSet"));
  this->tryRemove(S("root.Main.BlockStatements"));
  this->tryRemove(S("root.Main.BlockSubject"));
  this->tryRemove(S("root.Main.BlockExpression"));
}


List* GrammarFactory::getLeadingCommandsList()
{
  TiObject *obj;
  Core::Data::Grammar::Module *module;
  if (!this->tryGet(S("root.Main.LeadingCmdGrp"), obj, &module)) {
    throw EXCEPTION(GenericException, S("Could not find leading command group."));
  }
  SymbolDefinition *def = ti_cast<SymbolDefinition>(obj);
  if (def == 0) {
    throw EXCEPTION(GenericException, S("Could not find leading command group."));
  }

  Map *vars = this->context.getSymbolVars(def, module);
  List *cmd_list = ti_cast<List>(vars->getElement(S("prods")));
  if (cmd_list == 0) {
    throw EXCEPTION(GenericException, S("Could not find leading command group's command list."));
  }

  return cmd_list;
}


List* GrammarFactory::getInnerCommandsList()
{
  TiObject *obj;
  Core::Data::Grammar::Module *module;
  if (!this->tryGet(S("root.Main.SubjectCmdGrp"), obj, &module)) {
    throw EXCEPTION(GenericException, S("Could not find inner command group."));
  }
  SymbolDefinition *def = ti_cast<SymbolDefinition>(obj);
  if (def == 0) {
    throw EXCEPTION(GenericException, S("Could not find inner command group."));
  }

  Map *vars = this->context.getSymbolVars(def, module);
  List *cmd_list = ti_cast<List>(vars->getElement(S("prods")));
  if (cmd_list == 0) {
    throw EXCEPTION(GenericException, S("Could not find inner command group's command list."));
  }

  return cmd_list;
}


List* GrammarFactory::getTildeCommandsList()
{
  TiObject *obj;
  Core::Data::Grammar::Module *module;
  if (!this->tryGet(S("root.Main.PostfixTildeCmdGrp"), obj, &module)) {
    throw EXCEPTION(GenericException, S("Could not find tilde command group."));
  }
  SymbolDefinition *def = ti_cast<SymbolDefinition>(obj);
  if (def == 0) {
    throw EXCEPTION(GenericException, S("Could not find tilde command group."));
  }

  Map *vars = this->context.getSymbolVars(def, module);
  List *cmd_list = ti_cast<List>(vars->getElement(S("prods")));
  if (cmd_list == 0) {
    throw EXCEPTION(GenericException, S("Could not find inner command group's command list."));
  }

  return cmd_list;
}


void GrammarFactory::removeReferenceFromCommandList(List *cmdList, Char const *qualifier)
{
  auto ref = Core::Data::Grammar::createReference(qualifier, &this->referenceCache);
  for (Int i = 0; i < cmdList->getCount(); ++i) {
    auto reference = ti_cast<Core::Data::Grammar::Reference>(cmdList->getElement(i));
    if (ref->isEqual(reference)) {
      cmdList->remove(i);
      return;
    }
  }
}

} // namespace