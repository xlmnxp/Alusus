/**
 * @file Tests/CoreTests/helpers.h
 * Contains the declarations of different helper functions and classes that are
 * used by unit tests.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

namespace Tests { namespace CoreTests
{

using namespace std;
using namespace Core;

/// Search the given tree recursively for the data of the given production id.
void findProdData(Word prodId, SharedPtr<IdentifiableObject> ptr,
                  vector<SharedPtr<IdentifiableObject> > &result, Int index = -1);

/// Search the given tree recursively for a token.
void findToken(Word tokenId, const Char *text, SharedPtr<IdentifiableObject> ptr,
               vector<SharedPtr<IdentifiableObject> > &result, Int index = -1);

/// Check whether the provided pointer has empty data.
Bool isEmpty(SharedPtr<IdentifiableObject> ptr);

/**
 * @brief A class used to validate the tokens generated from the lexer.
 *
 * It works by adding a list of tokens to it, then start the lexer. The class
 * will then make sure it receives the same sequence of tokens.
 */
class LexerTester : public SignalReceiver
{
  TYPE_INFO(LexerTester, SignalReceiver, "Core.Test", "Core", "alusus.net");

  private: vector<SharedPtr<Common::Token> > tokens;
  private: Int currentIndex;
  private: Str errorMsg;
  private: Lexer::StateMachine *lexer;

  public: LexerTester(Lexer::StateMachine *l) : currentIndex(0), lexer(l)
  {
    this->lexer->tokenGenerated.connect(this, &LexerTester::handleNewToken);
  }

  public: void handleNewToken(const Common::Token *token)
  {
    if (this->errorMsg.size() != 0) return;
    if (this->currentIndex >= static_cast<Int>(this->tokens.size())) {
      this->errorMsg = STR("Extra token received: id=");
      this->errorMsg += Data::IdGenerator::getSingleton()->getDesc(token->getId());
      this->errorMsg += STR(", text=");
      this->errorMsg += token->getText();
      return;
    }
    SharedPtr<Common::Token> expected = this->tokens[this->currentIndex];
    if ((expected->getId() != UNKNOWN_ID && expected->getId() != token->getId()) ||
        expected->getText().compare(token->getText()) != 0) {
      this->errorMsg = STR("Unexpected token received at ");
      stringstream ss; ss << this->currentIndex;
      this->errorMsg += ss.str();
      this->errorMsg += STR(": id=");
      this->errorMsg += Data::IdGenerator::getSingleton()->getDesc(token->getId());
      this->errorMsg += STR(", text=");
      this->errorMsg += token->getText();
      return;
    }
    this->currentIndex++;
  }

  public: void reset()
  {
    this->tokens.clear();
    this->currentIndex = 0;
    this->errorMsg.clear();
  }

  public: void addToken(Word id, const Char *text)
  {
    SharedPtr<Common::Token> token(new Common::Token);
    token->setId(id);
    token->setText(text);
    this->tokens.push_back(token);
  }

  public: void test(const Char *text)
  {
    Int line = 1;
    Int column = 1;
    this->lexer->handleNewString(text, line, column);
    this->lexer->handleNewChar(FILE_TERMINATOR, line, column);
    if (this->errorMsg.size() == 0) {
      if (this->currentIndex == static_cast<Int>(this->tokens.size())) {
        REQUIRE(true);
      } else {
        stringstream ss; ss << this->currentIndex;
        this->errorMsg = STR("Didn't receive all the expected tokens. Current index=");
        this->errorMsg += ss.str();
        FAIL(this->errorMsg.c_str());
      }
    } else {
      FAIL(this->errorMsg.c_str());
    }
  }
};


/// A class that receives and stores build messages.
class BuildMsgReceiver : public SignalReceiver
{
  TYPE_INFO(BuildMsgReceiver, SignalReceiver, "Core.Test", "Core", "alusus.net");

  private: vector<SharedPtr<Common::BuildMsg> > msgs;

  public: BuildMsgReceiver(Main::Processor *processor)
  {
    processor->buildMsgNotifier.connect(this, &BuildMsgReceiver::receiveBuildMsg);
  }

  public: void receiveBuildMsg(const SharedPtr<Common::BuildMsg> &msg)
  {
    this->msgs.push_back(msg);
  }

  public: Int getMsgCount()
  {
    return this->msgs.size();
  }

  public: const SharedPtr<Common::BuildMsg>& getMsg(Int i)
  {
    return this->msgs[i];
  }

  public: void clear()
  {
    this->msgs.clear();
  }
};

} } // namespace

#endif