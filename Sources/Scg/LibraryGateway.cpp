/**
 * @file Scg/LibraryGateway.cpp
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include <map>
#include <core.h>
#include <LibraryGateway.h>

namespace Scg
{

using namespace Core;
using namespace Core::Data;

//==============================================================================
// Overloaded Abstract Functions

void LibraryGateway::initialize(Standard::RootManager *manager)
{
    this->moduleHandler = std::make_shared<ModuleParsingHandler>(manager);
    this->buildHandler = std::make_shared<BuildParsingHandler>(manager);
    this->runHandler = std::make_shared<RunParsingHandler>(manager);
    this->dumpHandler = std::make_shared<DumpParsingHandler>(manager);
    this->defHandler = std::make_shared<DefParsingHandler>(manager);
    this->handler = std::make_shared<Core::Standard::GenericParsingHandler>();

    DataStore *grammarStore = manager->getGrammarStore();

    // Create leading commands.

    //// run = "run" + Subject
    grammarStore->setSharedValue(STR("Main.Run"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("run"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Subject"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->runHandler}
        }));

    //// build = "build" + Subject
    grammarStore->setSharedValue(STR("Main.Build"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("build"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Subject"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->buildHandler}
        }));

    //// dump = "dump" + Subject
    grammarStore->setSharedValue(STR("Main.Dump"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("dump"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Subject"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->dumpHandler}
        }));

    //// def = "def" + Subject
    grammarStore->setSharedValue(STR("Main.Def"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("def"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->defHandler}
        }));

    //// return = "return" + Subject
    grammarStore->setSharedValue(STR("Main.Return"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("return"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(0)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// if = "if" + Exp + Statement
    grammarStore->setSharedValue(STR("Main.If"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("if"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    }),
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("module.Statement"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// for = "for" + Exp + Statement
    grammarStore->setSharedValue(STR("Main.For"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("for"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    }),
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("module.Statement"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// while = "while" + Exp + Statement
    grammarStore->setSharedValue(STR("Main.While"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("while"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    }),
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("module.Statement"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// link = "link" + Set
    grammarStore->setSharedValue(STR("Main.Link"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("link"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("module.Statement"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// Add command to leading commands list.
    List *cmd_list = this->GetLeadingCommandsList(grammarStore);
    this->leadingCmdListPos = static_cast<Int>(cmd_list->getCount());
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Run")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Build")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Dump")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Def")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Return")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.If")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.For")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.While")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Link")));


    // Create inner command.

    //// module = "module" + Subject + Subject
    grammarStore->setSharedValue(STR("Subject.Module"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("module"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.SubSet"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->moduleHandler}
        }));

    //// function = "function" + Exp + Statement
    // TODO: Exp and Statement need to be optional, but at least one of them is
    // given.
    /*grammarStore->setSharedValue(STR("Subject.Function"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("function"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.SubSubject"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(2)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));*/

    grammarStore->setSharedValue(STR("Subject.Function"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("function"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.Expression"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    }),
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.SubSet"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// structure = "struct" + Statement
    grammarStore->setSharedValue(STR("Subject.Structure"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("struct"))},
            {STR("prms"), List::create({
                Map::create(false, {
                    {STR("prd"), ReferenceParser::parseQualifier(STR("root.SubSet"))},
                    {STR("min"), std::make_shared<Integer>(1)},
                    {STR("max"), std::make_shared<Integer>(1)},
                    {STR("pty"), std::make_shared<Integer>(1)}
                    })
                })}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// Add command to inner commands list.
    cmd_list = this->GetInnerCommandsList(grammarStore);
    this->innerCmdListPos = static_cast<Int>(cmd_list->getCount());
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Module")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Function")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Structure")));

    // Create tilde commands.

    // ~ptr
    grammarStore->setSharedValue(STR("Expression.Pointer_Tilde"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("ptr"))},
            {STR("prms"), List::create({})}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));
    // ~cnt
    grammarStore->setSharedValue(STR("Expression.Content_Tilde"), SymbolDefinition::create({
        {SymbolDefElement::TERM, ReferenceParser::parseQualifier(STR("root.Cmd"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("kwd"), std::make_shared<String>(STR("cnt"))},
            {STR("prms"), List::create({})}
            })},
        {SymbolDefElement::HANDLER, this->handler}
        }));
    //// Add command to tilde commands list.
    cmd_list = this->GetTildeCommandsList(grammarStore);
    this->tildeCmdListPos = static_cast<Int>(cmd_list->getCount());
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Pointer_Tilde")));
    cmd_list->add(ReferenceParser::parseQualifier(STR("module.Content_Tilde")));


    // Define sub statements.

    // Define a SubMain module.
    grammarStore->setSharedValue(STR("SubMain"), GrammarModule::create({
        {STR("@parent"), ReferenceParser::parseQualifier(STR("root.Main"))}}));

    //// def = "def" + Subject
    grammarStore->setSharedValue(STR("SubMain.Def"), SymbolDefinition::create({
        {SymbolDefElement::PARENT_REF, ReferenceParser::parseQualifier(STR("pmodule.Def"))},
        {SymbolDefElement::HANDLER, this->handler}
        }));

    //// Overloaded subject.
    grammarStore->setSharedValue(STR("SubSubject"), GrammarModule::create({
        {STR("@parent"), ReferenceParser::parseQualifier(STR("root.Subject"))}
        }));
    grammarStore->setSharedValue(STR("SubSubject.Subject1"), SymbolDefinition::create({
        {SymbolDefElement::PARENT_REF, ReferenceParser::parseQualifier(STR("pmodule.Subject1"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("sbj1"), List::create({
                ReferenceParser::parseQualifier(STR("module.SubjectCmdGrp")),
                ReferenceParser::parseQualifier(STR("module.Parameter")),
                ReferenceParser::parseQualifier(STR("root.SubSet"))
                })},
            {STR("sbj2"), List::create({ReferenceParser::parseQualifier(STR("root.Expression"))})},
            {STR("sbj3"), List::create({ReferenceParser::parseQualifier(STR("root.Expression"))})},
            {STR("frc2"), 0},
            {STR("frc3"), 0}
            })}
        }));

    //// Overloaded set.
    grammarStore->setSharedValue(STR("SubSet"), SymbolDefinition::create({
        {SymbolDefElement::PARENT_REF, ReferenceParser::parseQualifier(STR("root.Set"))},
        {SymbolDefElement::VARS, Map::create(false, {
            {STR("stmt"), ReferenceParser::parseQualifier(STR("root.SubMain.StatementList"))}
            })}
        }));
}


void LibraryGateway::uninitialize(Standard::RootManager *manager)
{
    DataStore *grammarStore = manager->getGrammarStore();

    // Remove commands from leading commands list.
    List *cmdList = this->GetLeadingCommandsList(grammarStore);
    for (int i = 0; i < 8; ++i) {
      cmdList->remove(this->leadingCmdListPos);
    }

    // Remove command from inner commands list.
    cmdList = this->GetInnerCommandsList(grammarStore);
    for (int i = 0; i < 3; ++i) {
        cmdList->remove(this->innerCmdListPos);
    }

    // Remove command from tilde commands list.
    cmdList = this->GetTildeCommandsList(grammarStore);
    for (int i = 0; i < 2; ++i) {
        cmdList->remove(this->tildeCmdListPos);
    }

    // Delete definitions.
    grammarStore->removeValue(STR("Main.Run"));
    grammarStore->removeValue(STR("Main.Build"));
    grammarStore->removeValue(STR("Main.Dump"));
    grammarStore->removeValue(STR("Main.Def"));
    grammarStore->removeValue(STR("Main.Return"));
    grammarStore->removeValue(STR("Main.If"));
    grammarStore->removeValue(STR("Main.For"));
    grammarStore->removeValue(STR("Main.While"));
    grammarStore->removeValue(STR("Main.Link"));
    grammarStore->removeValue(STR("Subject.Module"));
    grammarStore->removeValue(STR("Subject.Function"));
    grammarStore->removeValue(STR("Subject.Structure"));
    grammarStore->removeValue(STR("Expression.Pointer_Tilde"));
    grammarStore->removeValue(STR("Expression.Content_Tilde"));
    grammarStore->removeValue(STR("SubMain"));
    grammarStore->removeValue(STR("SubSubject"));
    grammarStore->removeValue(STR("SubSet"));
}


List* LibraryGateway::GetLeadingCommandsList(DataStore *grammarStore)
{
    IdentifiableObject *val;
    Core::Data::Module *module;
    grammarStore->getPlainValue(STR("root.Main.LeadingCmdGrp"), val, module);
    SymbolDefinition *def = io_cast<SymbolDefinition>(val);
    if (def == 0) {
        throw GeneralException(STR("Could not find leading command group."),
                                STR("Scg::LibraryGateway::GetLeadingCommandsList"));
    }
    GrammarHelper helper(grammarStore->getInterface<Provider>());
    Map *vars = helper.getSymbolVars(def, module);
    List *cmd_list = vars->get(STR("cmds")).io_cast_get<List>();
    if (cmd_list == 0) {
        throw GeneralException(STR("Could not find leading command group's command list."),
                                STR("Scg::LibraryGateway::GetLeadingCommandsList"));
    }
    return cmd_list;
}


List* LibraryGateway::GetInnerCommandsList(DataStore *grammarStore)
{
    IdentifiableObject *val;
    Core::Data::Module *module;
    grammarStore->getPlainValue(STR("root.Subject.SubjectCmdGrp"), val, module);
    SymbolDefinition *def = io_cast<SymbolDefinition>(val);
    if (def == 0) {
        throw GeneralException(STR("Could not find inner command group."),
                                STR("Scg::LibraryGateway::GetInnerCommandsList"));
    }
    GrammarHelper helper(grammarStore->getInterface<Provider>());
    Map *vars = helper.getSymbolVars(def, module);
    List *cmd_list = vars->get(STR("cmds")).io_cast_get<List>();
    if (cmd_list == 0) {
        throw GeneralException(STR("Could not find inner command group's command list."),
                                STR("Scg::LibraryGateway::GetInnerCommandsList"));
    }
    return cmd_list;
}


List* LibraryGateway::GetTildeCommandsList(DataStore *grammarStore)
{
    IdentifiableObject *val;
    Core::Data::Module *module;
    grammarStore->getPlainValue(STR("root.Expression.DefaultPostfixTildeCmd"), val, module);
    SymbolDefinition *def = io_cast<SymbolDefinition>(val);
    if (def == 0) {
        throw GeneralException(STR("Could not find tilde command group."),
                                STR("Scg::LibraryGateway::GetTildeCommandsList"));
    }
    GrammarHelper helper(grammarStore->getInterface<Provider>());
    Map *vars = helper.getSymbolVars(def, module);
    List *cmd_list = vars->get(STR("cmds")).io_cast_get<List>();
    if (cmd_list == 0) {
        throw GeneralException(STR("Could not find inner command group's command list."),
                                STR("Scg::LibraryGateway::GetTildeCommandsList"));
    }
    return cmd_list;
}

} // namespace
