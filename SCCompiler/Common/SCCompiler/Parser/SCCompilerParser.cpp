
// Generated from ./Common/SCCompiler/Parser/SCCompiler.g4 by ANTLR 4.7.1


#include "SCCompilerListener.h"
#include "SCCompilerVisitor.h"

#include "SCCompilerParser.h"


using namespace antlrcpp;
using namespace antlr4;

SCCompilerParser::SCCompilerParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SCCompilerParser::~SCCompilerParser() {
  delete _interpreter;
}

std::string SCCompilerParser::getGrammarFileName() const {
  return "SCCompiler.g4";
}

const std::vector<std::string>& SCCompilerParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SCCompilerParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

SCCompilerParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SCCompilerParser::ProgramContext::EOF() {
  return getToken(SCCompilerParser::EOF, 0);
}

std::vector<SCCompilerParser::VarDeclContext *> SCCompilerParser::ProgramContext::varDecl() {
  return getRuleContexts<SCCompilerParser::VarDeclContext>();
}

SCCompilerParser::VarDeclContext* SCCompilerParser::ProgramContext::varDecl(size_t i) {
  return getRuleContext<SCCompilerParser::VarDeclContext>(i);
}

std::vector<SCCompilerParser::FunctionDeclContext *> SCCompilerParser::ProgramContext::functionDecl() {
  return getRuleContexts<SCCompilerParser::FunctionDeclContext>();
}

SCCompilerParser::FunctionDeclContext* SCCompilerParser::ProgramContext::functionDecl(size_t i) {
  return getRuleContext<SCCompilerParser::FunctionDeclContext>(i);
}


size_t SCCompilerParser::ProgramContext::getRuleIndex() const {
  return SCCompilerParser::RuleProgram;
}

void SCCompilerParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void SCCompilerParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any SCCompilerParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ProgramContext* SCCompilerParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, SCCompilerParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(38);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(34);
        varDecl();
        setState(35);
        match(SCCompilerParser::T__0);
        break;
      }

      case 2: {
        setState(37);
        functionDecl();
        break;
      }

      }
      setState(40); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0));
    setState(42);
    match(SCCompilerParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

SCCompilerParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SCCompilerParser::TypeContext* SCCompilerParser::VarDeclContext::type() {
  return getRuleContext<SCCompilerParser::TypeContext>(0);
}

std::vector<SCCompilerParser::VarInitContext *> SCCompilerParser::VarDeclContext::varInit() {
  return getRuleContexts<SCCompilerParser::VarInitContext>();
}

SCCompilerParser::VarInitContext* SCCompilerParser::VarDeclContext::varInit(size_t i) {
  return getRuleContext<SCCompilerParser::VarInitContext>(i);
}


size_t SCCompilerParser::VarDeclContext::getRuleIndex() const {
  return SCCompilerParser::RuleVarDecl;
}

void SCCompilerParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void SCCompilerParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


antlrcpp::Any SCCompilerParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::VarDeclContext* SCCompilerParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SCCompilerParser::RuleVarDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    type();
    setState(45);
    varInit();
    setState(50);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(46);
      match(SCCompilerParser::T__1);
      setState(47);
      varInit();
      setState(52);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarInitContext ------------------------------------------------------------------

SCCompilerParser::VarInitContext::VarInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SCCompilerParser::VarInitContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

SCCompilerParser::ExprContext* SCCompilerParser::VarInitContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}


size_t SCCompilerParser::VarInitContext::getRuleIndex() const {
  return SCCompilerParser::RuleVarInit;
}

void SCCompilerParser::VarInitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarInit(this);
}

void SCCompilerParser::VarInitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarInit(this);
}


antlrcpp::Any SCCompilerParser::VarInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarInit(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::VarInitContext* SCCompilerParser::varInit() {
  VarInitContext *_localctx = _tracker.createInstance<VarInitContext>(_ctx, getState());
  enterRule(_localctx, 4, SCCompilerParser::RuleVarInit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    match(SCCompilerParser::ID);
    setState(56);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SCCompilerParser::T__2) {
      setState(54);
      match(SCCompilerParser::T__2);
      setState(55);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

SCCompilerParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SCCompilerParser::TypeContext::getRuleIndex() const {
  return SCCompilerParser::RuleType;
}

void SCCompilerParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void SCCompilerParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


antlrcpp::Any SCCompilerParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::TypeContext* SCCompilerParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SCCompilerParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

SCCompilerParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SCCompilerParser::FunctionDeclContext::getRuleIndex() const {
  return SCCompilerParser::RuleFunctionDecl;
}

void SCCompilerParser::FunctionDeclContext::copyFrom(FunctionDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncDeclarationContext ------------------------------------------------------------------

SCCompilerParser::TypeContext* SCCompilerParser::FuncDeclarationContext::type() {
  return getRuleContext<SCCompilerParser::TypeContext>(0);
}

tree::TerminalNode* SCCompilerParser::FuncDeclarationContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

SCCompilerParser::FormalParametersContext* SCCompilerParser::FuncDeclarationContext::formalParameters() {
  return getRuleContext<SCCompilerParser::FormalParametersContext>(0);
}

std::vector<SCCompilerParser::StatContext *> SCCompilerParser::FuncDeclarationContext::stat() {
  return getRuleContexts<SCCompilerParser::StatContext>();
}

SCCompilerParser::StatContext* SCCompilerParser::FuncDeclarationContext::stat(size_t i) {
  return getRuleContext<SCCompilerParser::StatContext>(i);
}

SCCompilerParser::FuncDeclarationContext::FuncDeclarationContext(FunctionDeclContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::FuncDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDeclaration(this);
}
void SCCompilerParser::FuncDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDeclaration(this);
}

antlrcpp::Any SCCompilerParser::FuncDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncDeclaration(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::FunctionDeclContext* SCCompilerParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, SCCompilerParser::RuleFunctionDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<FunctionDeclContext *>(_tracker.createInstance<SCCompilerParser::FuncDeclarationContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(60);
    type();
    setState(61);
    match(SCCompilerParser::ID);
    setState(62);
    match(SCCompilerParser::T__7);
    setState(64);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0)) {
      setState(63);
      formalParameters();
    }
    setState(66);
    match(SCCompilerParser::T__8);
    setState(67);
    match(SCCompilerParser::T__9);
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6)
      | (1ULL << SCCompilerParser::T__7)
      | (1ULL << SCCompilerParser::T__9)
      | (1ULL << SCCompilerParser::T__11)
      | (1ULL << SCCompilerParser::T__13)
      | (1ULL << SCCompilerParser::T__14)
      | (1ULL << SCCompilerParser::T__15)
      | (1ULL << SCCompilerParser::T__16)
      | (1ULL << SCCompilerParser::T__17)
      | (1ULL << SCCompilerParser::T__18)
      | (1ULL << SCCompilerParser::T__19)
      | (1ULL << SCCompilerParser::T__28)
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(68);
      stat();
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(74);
    match(SCCompilerParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParametersContext ------------------------------------------------------------------

SCCompilerParser::FormalParametersContext::FormalParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SCCompilerParser::FormalParameterContext *> SCCompilerParser::FormalParametersContext::formalParameter() {
  return getRuleContexts<SCCompilerParser::FormalParameterContext>();
}

SCCompilerParser::FormalParameterContext* SCCompilerParser::FormalParametersContext::formalParameter(size_t i) {
  return getRuleContext<SCCompilerParser::FormalParameterContext>(i);
}


size_t SCCompilerParser::FormalParametersContext::getRuleIndex() const {
  return SCCompilerParser::RuleFormalParameters;
}

void SCCompilerParser::FormalParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameters(this);
}

void SCCompilerParser::FormalParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameters(this);
}


antlrcpp::Any SCCompilerParser::FormalParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFormalParameters(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::FormalParametersContext* SCCompilerParser::formalParameters() {
  FormalParametersContext *_localctx = _tracker.createInstance<FormalParametersContext>(_ctx, getState());
  enterRule(_localctx, 10, SCCompilerParser::RuleFormalParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    formalParameter();
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(77);
      match(SCCompilerParser::T__1);
      setState(78);
      formalParameter();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterContext ------------------------------------------------------------------

SCCompilerParser::FormalParameterContext::FormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SCCompilerParser::FormalParameterContext::getRuleIndex() const {
  return SCCompilerParser::RuleFormalParameter;
}

void SCCompilerParser::FormalParameterContext::copyFrom(FormalParameterContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncArgDeclarationContext ------------------------------------------------------------------

SCCompilerParser::TypeContext* SCCompilerParser::FuncArgDeclarationContext::type() {
  return getRuleContext<SCCompilerParser::TypeContext>(0);
}

tree::TerminalNode* SCCompilerParser::FuncArgDeclarationContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

SCCompilerParser::FuncArgDeclarationContext::FuncArgDeclarationContext(FormalParameterContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::FuncArgDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncArgDeclaration(this);
}
void SCCompilerParser::FuncArgDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncArgDeclaration(this);
}

antlrcpp::Any SCCompilerParser::FuncArgDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncArgDeclaration(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::FormalParameterContext* SCCompilerParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 12, SCCompilerParser::RuleFormalParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<FormalParameterContext *>(_tracker.createInstance<SCCompilerParser::FuncArgDeclarationContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(84);
    type();
    setState(85);
    match(SCCompilerParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SCCompilerParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SCCompilerParser::StatContext *> SCCompilerParser::BlockContext::stat() {
  return getRuleContexts<SCCompilerParser::StatContext>();
}

SCCompilerParser::StatContext* SCCompilerParser::BlockContext::stat(size_t i) {
  return getRuleContext<SCCompilerParser::StatContext>(i);
}


size_t SCCompilerParser::BlockContext::getRuleIndex() const {
  return SCCompilerParser::RuleBlock;
}

void SCCompilerParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void SCCompilerParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any SCCompilerParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::BlockContext* SCCompilerParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 14, SCCompilerParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(SCCompilerParser::T__9);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6)
      | (1ULL << SCCompilerParser::T__7)
      | (1ULL << SCCompilerParser::T__9)
      | (1ULL << SCCompilerParser::T__11)
      | (1ULL << SCCompilerParser::T__13)
      | (1ULL << SCCompilerParser::T__14)
      | (1ULL << SCCompilerParser::T__15)
      | (1ULL << SCCompilerParser::T__16)
      | (1ULL << SCCompilerParser::T__17)
      | (1ULL << SCCompilerParser::T__18)
      | (1ULL << SCCompilerParser::T__19)
      | (1ULL << SCCompilerParser::T__28)
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(88);
      stat();
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
    match(SCCompilerParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

SCCompilerParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SCCompilerParser::StatContext::getRuleIndex() const {
  return SCCompilerParser::RuleStat;
}

void SCCompilerParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfStatementContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::IfStatementContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

std::vector<SCCompilerParser::StatContext *> SCCompilerParser::IfStatementContext::stat() {
  return getRuleContexts<SCCompilerParser::StatContext>();
}

SCCompilerParser::StatContext* SCCompilerParser::IfStatementContext::stat(size_t i) {
  return getRuleContext<SCCompilerParser::StatContext>(i);
}

SCCompilerParser::IfStatementContext::IfStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}
void SCCompilerParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}

antlrcpp::Any SCCompilerParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IgnoreContext ------------------------------------------------------------------

SCCompilerParser::ForStatementContext* SCCompilerParser::IgnoreContext::forStatement() {
  return getRuleContext<SCCompilerParser::ForStatementContext>(0);
}

SCCompilerParser::AssignmentContext* SCCompilerParser::IgnoreContext::assignment() {
  return getRuleContext<SCCompilerParser::AssignmentContext>(0);
}

SCCompilerParser::IgnoreContext::IgnoreContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::IgnoreContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIgnore(this);
}
void SCCompilerParser::IgnoreContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIgnore(this);
}

antlrcpp::Any SCCompilerParser::IgnoreContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitIgnore(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::ReturnStatementContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::ReturnStatementContext::ReturnStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}
void SCCompilerParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

antlrcpp::Any SCCompilerParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakContext ------------------------------------------------------------------

SCCompilerParser::BreakContext::BreakContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::BreakContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreak(this);
}
void SCCompilerParser::BreakContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreak(this);
}

antlrcpp::Any SCCompilerParser::BreakContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitBreak(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallStatementContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::FuncCallStatementContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::FuncCallStatementContext::FuncCallStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::FuncCallStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallStatement(this);
}
void SCCompilerParser::FuncCallStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallStatement(this);
}

antlrcpp::Any SCCompilerParser::FuncCallStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncCallStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

SCCompilerParser::BlockContext* SCCompilerParser::BlockStatementContext::block() {
  return getRuleContext<SCCompilerParser::BlockContext>(0);
}

SCCompilerParser::BlockStatementContext::BlockStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::BlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStatement(this);
}
void SCCompilerParser::BlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStatement(this);
}

antlrcpp::Any SCCompilerParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStatementContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::WhileStatementContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::StatContext* SCCompilerParser::WhileStatementContext::stat() {
  return getRuleContext<SCCompilerParser::StatContext>(0);
}

SCCompilerParser::WhileStatementContext::WhileStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}
void SCCompilerParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}

antlrcpp::Any SCCompilerParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueContext ------------------------------------------------------------------

SCCompilerParser::ContinueContext::ContinueContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::ContinueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinue(this);
}
void SCCompilerParser::ContinueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinue(this);
}

antlrcpp::Any SCCompilerParser::ContinueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitContinue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclStatementContext ------------------------------------------------------------------

SCCompilerParser::VarDeclContext* SCCompilerParser::VarDeclStatementContext::varDecl() {
  return getRuleContext<SCCompilerParser::VarDeclContext>(0);
}

SCCompilerParser::VarDeclStatementContext::VarDeclStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::VarDeclStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDeclStatement(this);
}
void SCCompilerParser::VarDeclStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDeclStatement(this);
}

antlrcpp::Any SCCompilerParser::VarDeclStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarDeclStatement(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::StatContext* SCCompilerParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 16, SCCompilerParser::RuleStat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::BlockStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(96);
      block();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::VarDeclStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(97);
      varDecl();
      setState(98);
      match(SCCompilerParser::T__0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::IfStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(100);
      match(SCCompilerParser::T__11);
      setState(101);
      match(SCCompilerParser::T__7);
      setState(102);
      expr(0);
      setState(103);
      match(SCCompilerParser::T__8);
      setState(104);
      stat();
      setState(107);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
      case 1: {
        setState(105);
        match(SCCompilerParser::T__12);
        setState(106);
        stat();
        break;
      }

      }
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::IgnoreContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(109);
      forStatement();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::WhileStatementContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(110);
      match(SCCompilerParser::T__13);
      setState(111);
      match(SCCompilerParser::T__7);
      setState(112);
      expr(0);
      setState(113);
      match(SCCompilerParser::T__8);
      setState(114);
      stat();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::ReturnStatementContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(116);
      match(SCCompilerParser::T__14);
      setState(118);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
        | (1ULL << SCCompilerParser::T__4)
        | (1ULL << SCCompilerParser::T__6)
        | (1ULL << SCCompilerParser::T__7)
        | (1ULL << SCCompilerParser::T__17)
        | (1ULL << SCCompilerParser::T__18)
        | (1ULL << SCCompilerParser::T__19)
        | (1ULL << SCCompilerParser::BOOL)
        | (1ULL << SCCompilerParser::INT)
        | (1ULL << SCCompilerParser::FLOAT)
        | (1ULL << SCCompilerParser::ID))) != 0)) {
        setState(117);
        expr(0);
      }
      setState(120);
      match(SCCompilerParser::T__0);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::ContinueContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(121);
      match(SCCompilerParser::T__15);
      setState(122);
      match(SCCompilerParser::T__0);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::BreakContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(123);
      match(SCCompilerParser::T__16);
      setState(124);
      match(SCCompilerParser::T__0);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::IgnoreContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(125);
      assignment();
      setState(126);
      match(SCCompilerParser::T__0);
      break;
    }

    case 10: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::FuncCallStatementContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(128);
      expr(0);
      setState(129);
      match(SCCompilerParser::T__0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

SCCompilerParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SCCompilerParser::ExprContext::getRuleIndex() const {
  return SCCompilerParser::RuleExpr;
}

void SCCompilerParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExplicitTypeConversionContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::ExplicitTypeConversionContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::ExplicitTypeConversionContext::ExplicitTypeConversionContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::ExplicitTypeConversionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplicitTypeConversion(this);
}
void SCCompilerParser::ExplicitTypeConversionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplicitTypeConversion(this);
}

antlrcpp::Any SCCompilerParser::ExplicitTypeConversionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitExplicitTypeConversion(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesisExprContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::ParenthesisExprContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::ParenthesisExprContext::ParenthesisExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::ParenthesisExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesisExpr(this);
}
void SCCompilerParser::ParenthesisExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesisExpr(this);
}

antlrcpp::Any SCCompilerParser::ParenthesisExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitParenthesisExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalNotExprContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::LogicalNotExprContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::LogicalNotExprContext::LogicalNotExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::LogicalNotExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalNotExpr(this);
}
void SCCompilerParser::LogicalNotExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalNotExpr(this);
}

antlrcpp::Any SCCompilerParser::LogicalNotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitLogicalNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExprContext ------------------------------------------------------------------

tree::TerminalNode* SCCompilerParser::LiteralExprContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

tree::TerminalNode* SCCompilerParser::LiteralExprContext::FLOAT() {
  return getToken(SCCompilerParser::FLOAT, 0);
}

tree::TerminalNode* SCCompilerParser::LiteralExprContext::INT() {
  return getToken(SCCompilerParser::INT, 0);
}

tree::TerminalNode* SCCompilerParser::LiteralExprContext::BOOL() {
  return getToken(SCCompilerParser::BOOL, 0);
}

SCCompilerParser::LiteralExprContext::LiteralExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::LiteralExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpr(this);
}
void SCCompilerParser::LiteralExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpr(this);
}

antlrcpp::Any SCCompilerParser::LiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CompExprContext ------------------------------------------------------------------

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::CompExprContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::CompExprContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}

SCCompilerParser::CompExprContext::CompExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::CompExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompExpr(this);
}
void SCCompilerParser::CompExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompExpr(this);
}

antlrcpp::Any SCCompilerParser::CompExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitCompExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AOPExprContext ------------------------------------------------------------------

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::AOPExprContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::AOPExprContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}

SCCompilerParser::AOPExprContext::AOPExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::AOPExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAOPExpr(this);
}
void SCCompilerParser::AOPExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAOPExpr(this);
}

antlrcpp::Any SCCompilerParser::AOPExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitAOPExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::UnaryExprContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void SCCompilerParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

antlrcpp::Any SCCompilerParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallExprContext ------------------------------------------------------------------

tree::TerminalNode* SCCompilerParser::FuncCallExprContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

SCCompilerParser::ExprListContext* SCCompilerParser::FuncCallExprContext::exprList() {
  return getRuleContext<SCCompilerParser::ExprListContext>(0);
}

SCCompilerParser::FuncCallExprContext::FuncCallExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::FuncCallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallExpr(this);
}
void SCCompilerParser::FuncCallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallExpr(this);
}

antlrcpp::Any SCCompilerParser::FuncCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncCallExpr(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ExprContext* SCCompilerParser::expr() {
   return expr(0);
}

SCCompilerParser::ExprContext* SCCompilerParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SCCompilerParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  SCCompilerParser::ExprContext *previousContext = _localctx;
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, SCCompilerParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(154);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(134);
      match(SCCompilerParser::ID);
      setState(135);
      match(SCCompilerParser::T__7);
      setState(137);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
        | (1ULL << SCCompilerParser::T__4)
        | (1ULL << SCCompilerParser::T__6)
        | (1ULL << SCCompilerParser::T__7)
        | (1ULL << SCCompilerParser::T__17)
        | (1ULL << SCCompilerParser::T__18)
        | (1ULL << SCCompilerParser::T__19)
        | (1ULL << SCCompilerParser::BOOL)
        | (1ULL << SCCompilerParser::INT)
        | (1ULL << SCCompilerParser::FLOAT)
        | (1ULL << SCCompilerParser::ID))) != 0)) {
        setState(136);
        exprList();
      }
      setState(139);
      match(SCCompilerParser::T__8);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ExplicitTypeConversionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(140);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
        | (1ULL << SCCompilerParser::T__4)
        | (1ULL << SCCompilerParser::T__6))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(141);
      match(SCCompilerParser::T__7);
      setState(142);
      expr(0);
      setState(143);
      match(SCCompilerParser::T__8);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(145);
      _la = _input->LA(1);
      if (!(_la == SCCompilerParser::T__17

      || _la == SCCompilerParser::T__18)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(146);
      expr(7);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LogicalNotExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(147);
      match(SCCompilerParser::T__19);
      setState(148);
      expr(6);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(149);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::BOOL)
        | (1ULL << SCCompilerParser::INT)
        | (1ULL << SCCompilerParser::FLOAT)
        | (1ULL << SCCompilerParser::ID))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ParenthesisExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(150);
      match(SCCompilerParser::T__7);
      setState(151);
      expr(0);
      setState(152);
      match(SCCompilerParser::T__8);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(167);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(165);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(156);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(157);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__20

          || _la == SCCompilerParser::T__21)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(158);
          expr(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(159);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(160);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__17

          || _la == SCCompilerParser::T__18)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(161);
          expr(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CompExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(162);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(163);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SCCompilerParser::T__22)
            | (1ULL << SCCompilerParser::T__23)
            | (1ULL << SCCompilerParser::T__24)
            | (1ULL << SCCompilerParser::T__25)
            | (1ULL << SCCompilerParser::T__26)
            | (1ULL << SCCompilerParser::T__27))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(164);
          expr(4);
          break;
        }

        } 
      }
      setState(169);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprListContext ------------------------------------------------------------------

SCCompilerParser::ExprListContext::ExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::ExprListContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::ExprListContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}


size_t SCCompilerParser::ExprListContext::getRuleIndex() const {
  return SCCompilerParser::RuleExprList;
}

void SCCompilerParser::ExprListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprList(this);
}

void SCCompilerParser::ExprListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprList(this);
}


antlrcpp::Any SCCompilerParser::ExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitExprList(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ExprListContext* SCCompilerParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 20, SCCompilerParser::RuleExprList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    expr(0);
    setState(175);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(171);
      match(SCCompilerParser::T__1);
      setState(172);
      expr(0);
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

SCCompilerParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::AssignmentContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::AssignmentContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}


size_t SCCompilerParser::AssignmentContext::getRuleIndex() const {
  return SCCompilerParser::RuleAssignment;
}

void SCCompilerParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void SCCompilerParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


antlrcpp::Any SCCompilerParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::AssignmentContext* SCCompilerParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 22, SCCompilerParser::RuleAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    expr(0);
    setState(179);
    match(SCCompilerParser::T__2);
    setState(180);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

SCCompilerParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SCCompilerParser::ForVarDeclContext* SCCompilerParser::ForStatementContext::forVarDecl() {
  return getRuleContext<SCCompilerParser::ForVarDeclContext>(0);
}

SCCompilerParser::ForConditionContext* SCCompilerParser::ForStatementContext::forCondition() {
  return getRuleContext<SCCompilerParser::ForConditionContext>(0);
}

SCCompilerParser::ForIncrementsContext* SCCompilerParser::ForStatementContext::forIncrements() {
  return getRuleContext<SCCompilerParser::ForIncrementsContext>(0);
}

SCCompilerParser::StatContext* SCCompilerParser::ForStatementContext::stat() {
  return getRuleContext<SCCompilerParser::StatContext>(0);
}


size_t SCCompilerParser::ForStatementContext::getRuleIndex() const {
  return SCCompilerParser::RuleForStatement;
}

void SCCompilerParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void SCCompilerParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}


antlrcpp::Any SCCompilerParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForStatementContext* SCCompilerParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, SCCompilerParser::RuleForStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    match(SCCompilerParser::T__28);
    setState(183);
    match(SCCompilerParser::T__7);
    setState(184);
    forVarDecl();
    setState(185);
    match(SCCompilerParser::T__0);
    setState(186);
    forCondition();
    setState(187);
    match(SCCompilerParser::T__0);
    setState(188);
    forIncrements();
    setState(189);
    match(SCCompilerParser::T__8);
    setState(190);
    stat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForVarDeclContext ------------------------------------------------------------------

SCCompilerParser::ForVarDeclContext::ForVarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SCCompilerParser::VarDeclContext* SCCompilerParser::ForVarDeclContext::varDecl() {
  return getRuleContext<SCCompilerParser::VarDeclContext>(0);
}


size_t SCCompilerParser::ForVarDeclContext::getRuleIndex() const {
  return SCCompilerParser::RuleForVarDecl;
}

void SCCompilerParser::ForVarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForVarDecl(this);
}

void SCCompilerParser::ForVarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForVarDecl(this);
}


antlrcpp::Any SCCompilerParser::ForVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForVarDeclContext* SCCompilerParser::forVarDecl() {
  ForVarDeclContext *_localctx = _tracker.createInstance<ForVarDeclContext>(_ctx, getState());
  enterRule(_localctx, 26, SCCompilerParser::RuleForVarDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0)) {
      setState(192);
      varDecl();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForConditionContext ------------------------------------------------------------------

SCCompilerParser::ForConditionContext::ForConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SCCompilerParser::ExprContext* SCCompilerParser::ForConditionContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}


size_t SCCompilerParser::ForConditionContext::getRuleIndex() const {
  return SCCompilerParser::RuleForCondition;
}

void SCCompilerParser::ForConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForCondition(this);
}

void SCCompilerParser::ForConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForCondition(this);
}


antlrcpp::Any SCCompilerParser::ForConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForCondition(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForConditionContext* SCCompilerParser::forCondition() {
  ForConditionContext *_localctx = _tracker.createInstance<ForConditionContext>(_ctx, getState());
  enterRule(_localctx, 28, SCCompilerParser::RuleForCondition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__6)
      | (1ULL << SCCompilerParser::T__7)
      | (1ULL << SCCompilerParser::T__17)
      | (1ULL << SCCompilerParser::T__18)
      | (1ULL << SCCompilerParser::T__19)
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(195);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForIncrementsContext ------------------------------------------------------------------

SCCompilerParser::ForIncrementsContext::ForIncrementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SCCompilerParser::ForIncContext *> SCCompilerParser::ForIncrementsContext::forInc() {
  return getRuleContexts<SCCompilerParser::ForIncContext>();
}

SCCompilerParser::ForIncContext* SCCompilerParser::ForIncrementsContext::forInc(size_t i) {
  return getRuleContext<SCCompilerParser::ForIncContext>(i);
}


size_t SCCompilerParser::ForIncrementsContext::getRuleIndex() const {
  return SCCompilerParser::RuleForIncrements;
}

void SCCompilerParser::ForIncrementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForIncrements(this);
}

void SCCompilerParser::ForIncrementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForIncrements(this);
}


antlrcpp::Any SCCompilerParser::ForIncrementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForIncrements(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForIncrementsContext* SCCompilerParser::forIncrements() {
  ForIncrementsContext *_localctx = _tracker.createInstance<ForIncrementsContext>(_ctx, getState());
  enterRule(_localctx, 30, SCCompilerParser::RuleForIncrements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__6)
      | (1ULL << SCCompilerParser::T__7)
      | (1ULL << SCCompilerParser::T__17)
      | (1ULL << SCCompilerParser::T__18)
      | (1ULL << SCCompilerParser::T__19)
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(198);
      forInc();
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SCCompilerParser::T__1) {
        setState(199);
        match(SCCompilerParser::T__1);
        setState(200);
        forInc();
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForIncContext ------------------------------------------------------------------

SCCompilerParser::ForIncContext::ForIncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SCCompilerParser::ExprContext* SCCompilerParser::ForIncContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::AssignmentContext* SCCompilerParser::ForIncContext::assignment() {
  return getRuleContext<SCCompilerParser::AssignmentContext>(0);
}


size_t SCCompilerParser::ForIncContext::getRuleIndex() const {
  return SCCompilerParser::RuleForInc;
}

void SCCompilerParser::ForIncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForInc(this);
}

void SCCompilerParser::ForIncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForInc(this);
}


antlrcpp::Any SCCompilerParser::ForIncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForInc(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForIncContext* SCCompilerParser::forInc() {
  ForIncContext *_localctx = _tracker.createInstance<ForIncContext>(_ctx, getState());
  enterRule(_localctx, 32, SCCompilerParser::RuleForInc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(208);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(209);
      assignment();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SCCompilerParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 9: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SCCompilerParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);
    case 2: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> SCCompilerParser::_decisionToDFA;
atn::PredictionContextCache SCCompilerParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SCCompilerParser::_atn;
std::vector<uint16_t> SCCompilerParser::_serializedATN;

std::vector<std::string> SCCompilerParser::_ruleNames = {
  "program", "varDecl", "varInit", "type", "functionDecl", "formalParameters", 
  "formalParameter", "block", "stat", "expr", "exprList", "assignment", 
  "forStatement", "forVarDecl", "forCondition", "forIncrements", "forInc"
};

std::vector<std::string> SCCompilerParser::_literalNames = {
  "", "';'", "','", "'='", "'float'", "'int'", "'void'", "'bool'", "'('", 
  "')'", "'{'", "'}'", "'if'", "'else'", "'while'", "'return'", "'continue'", 
  "'break'", "'-'", "'+'", "'!'", "'*'", "'/'", "'=='", "'!='", "'<='", 
  "'>='", "'<'", "'>'", "'for'"
};

std::vector<std::string> SCCompilerParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "BOOL", "INT", "FLOAT", 
  "ID", "WS", "LINECOMMENT", "BLOCKCOMMENT"
};

dfa::Vocabulary SCCompilerParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SCCompilerParser::_tokenNames;

SCCompilerParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x26, 0xd7, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x29, 0xa, 
    0x2, 0xd, 0x2, 0xe, 0x2, 0x2a, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x33, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x36, 
    0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x3b, 0xa, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x43, 
    0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x48, 0xa, 0x6, 0xc, 
    0x6, 0xe, 0x6, 0x4b, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x7, 0x7, 0x52, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x55, 0xb, 0x7, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x5c, 0xa, 
    0x9, 0xc, 0x9, 0xe, 0x9, 0x5f, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x6e, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0x79, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x5, 0xa, 0x86, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 
    0xb, 0x8c, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x9d, 0xa, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x7, 0xb, 0xa8, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0xab, 0xb, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0xb0, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 
    0xb3, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xf, 0x5, 0xf, 0xc4, 0xa, 0xf, 0x3, 0x10, 0x5, 0x10, 
    0xc7, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0xcc, 0xa, 
    0x11, 0xc, 0x11, 0xe, 0x11, 0xcf, 0xb, 0x11, 0x5, 0x11, 0xd1, 0xa, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xd5, 0xa, 0x12, 0x3, 0x12, 0x2, 0x3, 
    0x14, 0x13, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x2, 0x8, 0x3, 0x2, 0x6, 0x9, 0x4, 
    0x2, 0x6, 0x7, 0x9, 0x9, 0x3, 0x2, 0x14, 0x15, 0x3, 0x2, 0x20, 0x23, 
    0x3, 0x2, 0x17, 0x18, 0x3, 0x2, 0x19, 0x1e, 0x2, 0xe7, 0x2, 0x28, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x3e, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x4e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x56, 0x3, 0x2, 0x2, 0x2, 0x10, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x85, 0x3, 0x2, 0x2, 0x2, 0x14, 0x9c, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0xac, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb4, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xc3, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0xc6, 0x3, 0x2, 0x2, 0x2, 0x20, 0xd0, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0xd4, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x5, 0x4, 0x3, 0x2, 0x25, 
    0x26, 0x7, 0x3, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 0x29, 
    0x5, 0xa, 0x6, 0x2, 0x28, 0x24, 0x3, 0x2, 0x2, 0x2, 0x28, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x2d, 0x7, 0x2, 0x2, 0x3, 0x2d, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x2f, 0x5, 0x8, 0x5, 0x2, 0x2f, 0x34, 0x5, 0x6, 0x4, 0x2, 0x30, 
    0x31, 0x7, 0x4, 0x2, 0x2, 0x31, 0x33, 0x5, 0x6, 0x4, 0x2, 0x32, 0x30, 
    0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x37, 0x3a, 0x7, 0x23, 0x2, 
    0x2, 0x38, 0x39, 0x7, 0x5, 0x2, 0x2, 0x39, 0x3b, 0x5, 0x14, 0xb, 0x2, 
    0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x9, 0x2, 0x2, 0x2, 0x3d, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0x8, 0x5, 0x2, 0x3f, 0x40, 0x7, 
    0x23, 0x2, 0x2, 0x40, 0x42, 0x7, 0xa, 0x2, 0x2, 0x41, 0x43, 0x5, 0xc, 
    0x7, 0x2, 0x42, 0x41, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x7, 0xb, 0x2, 0x2, 
    0x45, 0x49, 0x7, 0xc, 0x2, 0x2, 0x46, 0x48, 0x5, 0x12, 0xa, 0x2, 0x47, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 
    0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0xd, 
    0x2, 0x2, 0x4d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x53, 0x5, 0xe, 0x8, 
    0x2, 0x4f, 0x50, 0x7, 0x4, 0x2, 0x2, 0x50, 0x52, 0x5, 0xe, 0x8, 0x2, 
    0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x52, 0x55, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x3, 0x2, 0x2, 0x2, 0x54, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x5, 
    0x8, 0x5, 0x2, 0x57, 0x58, 0x7, 0x23, 0x2, 0x2, 0x58, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x59, 0x5d, 0x7, 0xc, 0x2, 0x2, 0x5a, 0x5c, 0x5, 0x12, 0xa, 
    0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 
    0x60, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 
    0x7, 0xd, 0x2, 0x2, 0x61, 0x11, 0x3, 0x2, 0x2, 0x2, 0x62, 0x86, 0x5, 
    0x10, 0x9, 0x2, 0x63, 0x64, 0x5, 0x4, 0x3, 0x2, 0x64, 0x65, 0x7, 0x3, 
    0x2, 0x2, 0x65, 0x86, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0xe, 0x2, 
    0x2, 0x67, 0x68, 0x7, 0xa, 0x2, 0x2, 0x68, 0x69, 0x5, 0x14, 0xb, 0x2, 
    0x69, 0x6a, 0x7, 0xb, 0x2, 0x2, 0x6a, 0x6d, 0x5, 0x12, 0xa, 0x2, 0x6b, 
    0x6c, 0x7, 0xf, 0x2, 0x2, 0x6c, 0x6e, 0x5, 0x12, 0xa, 0x2, 0x6d, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x86, 0x3, 
    0x2, 0x2, 0x2, 0x6f, 0x86, 0x5, 0x1a, 0xe, 0x2, 0x70, 0x71, 0x7, 0x10, 
    0x2, 0x2, 0x71, 0x72, 0x7, 0xa, 0x2, 0x2, 0x72, 0x73, 0x5, 0x14, 0xb, 
    0x2, 0x73, 0x74, 0x7, 0xb, 0x2, 0x2, 0x74, 0x75, 0x5, 0x12, 0xa, 0x2, 
    0x75, 0x86, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x7, 0x11, 0x2, 0x2, 0x77, 
    0x79, 0x5, 0x14, 0xb, 0x2, 0x78, 0x77, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 
    0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x86, 0x7, 
    0x3, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x12, 0x2, 0x2, 0x7c, 0x86, 0x7, 0x3, 
    0x2, 0x2, 0x7d, 0x7e, 0x7, 0x13, 0x2, 0x2, 0x7e, 0x86, 0x7, 0x3, 0x2, 
    0x2, 0x7f, 0x80, 0x5, 0x18, 0xd, 0x2, 0x80, 0x81, 0x7, 0x3, 0x2, 0x2, 
    0x81, 0x86, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x5, 0x14, 0xb, 0x2, 0x83, 
    0x84, 0x7, 0x3, 0x2, 0x2, 0x84, 0x86, 0x3, 0x2, 0x2, 0x2, 0x85, 0x62, 
    0x3, 0x2, 0x2, 0x2, 0x85, 0x63, 0x3, 0x2, 0x2, 0x2, 0x85, 0x66, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x85, 0x70, 0x3, 0x2, 
    0x2, 0x2, 0x85, 0x76, 0x3, 0x2, 0x2, 0x2, 0x85, 0x7b, 0x3, 0x2, 0x2, 
    0x2, 0x85, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x85, 0x7f, 0x3, 0x2, 0x2, 0x2, 
    0x85, 0x82, 0x3, 0x2, 0x2, 0x2, 0x86, 0x13, 0x3, 0x2, 0x2, 0x2, 0x87, 
    0x88, 0x8, 0xb, 0x1, 0x2, 0x88, 0x89, 0x7, 0x23, 0x2, 0x2, 0x89, 0x8b, 
    0x7, 0xa, 0x2, 0x2, 0x8a, 0x8c, 0x5, 0x16, 0xc, 0x2, 0x8b, 0x8a, 0x3, 
    0x2, 0x2, 0x2, 0x8b, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x3, 0x2, 
    0x2, 0x2, 0x8d, 0x9d, 0x7, 0xb, 0x2, 0x2, 0x8e, 0x8f, 0x9, 0x3, 0x2, 
    0x2, 0x8f, 0x90, 0x7, 0xa, 0x2, 0x2, 0x90, 0x91, 0x5, 0x14, 0xb, 0x2, 
    0x91, 0x92, 0x7, 0xb, 0x2, 0x2, 0x92, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x93, 
    0x94, 0x9, 0x4, 0x2, 0x2, 0x94, 0x9d, 0x5, 0x14, 0xb, 0x9, 0x95, 0x96, 
    0x7, 0x16, 0x2, 0x2, 0x96, 0x9d, 0x5, 0x14, 0xb, 0x8, 0x97, 0x9d, 0x9, 
    0x5, 0x2, 0x2, 0x98, 0x99, 0x7, 0xa, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x14, 
    0xb, 0x2, 0x9a, 0x9b, 0x7, 0xb, 0x2, 0x2, 0x9b, 0x9d, 0x3, 0x2, 0x2, 
    0x2, 0x9c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x8e, 0x3, 0x2, 0x2, 0x2, 
    0x9c, 0x93, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x95, 0x3, 0x2, 0x2, 0x2, 0x9c, 
    0x97, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9d, 0xa9, 
    0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0xc, 0x7, 0x2, 0x2, 0x9f, 0xa0, 0x9, 
    0x6, 0x2, 0x2, 0xa0, 0xa8, 0x5, 0x14, 0xb, 0x8, 0xa1, 0xa2, 0xc, 0x6, 
    0x2, 0x2, 0xa2, 0xa3, 0x9, 0x4, 0x2, 0x2, 0xa3, 0xa8, 0x5, 0x14, 0xb, 
    0x7, 0xa4, 0xa5, 0xc, 0x5, 0x2, 0x2, 0xa5, 0xa6, 0x9, 0x7, 0x2, 0x2, 
    0xa6, 0xa8, 0x5, 0x14, 0xb, 0x6, 0xa7, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa7, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xab, 
    0x3, 0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x3, 
    0x2, 0x2, 0x2, 0xaa, 0x15, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa9, 0x3, 0x2, 
    0x2, 0x2, 0xac, 0xb1, 0x5, 0x14, 0xb, 0x2, 0xad, 0xae, 0x7, 0x4, 0x2, 
    0x2, 0xae, 0xb0, 0x5, 0x14, 0xb, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xb0, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 
    0xb2, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x17, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0x14, 0xb, 0x2, 0xb5, 0xb6, 0x7, 
    0x5, 0x2, 0x2, 0xb6, 0xb7, 0x5, 0x14, 0xb, 0x2, 0xb7, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0xb8, 0xb9, 0x7, 0x1f, 0x2, 0x2, 0xb9, 0xba, 0x7, 0xa, 0x2, 
    0x2, 0xba, 0xbb, 0x5, 0x1c, 0xf, 0x2, 0xbb, 0xbc, 0x7, 0x3, 0x2, 0x2, 
    0xbc, 0xbd, 0x5, 0x1e, 0x10, 0x2, 0xbd, 0xbe, 0x7, 0x3, 0x2, 0x2, 0xbe, 
    0xbf, 0x5, 0x20, 0x11, 0x2, 0xbf, 0xc0, 0x7, 0xb, 0x2, 0x2, 0xc0, 0xc1, 
    0x5, 0x12, 0xa, 0x2, 0xc1, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc4, 0x5, 
    0x4, 0x3, 0x2, 0xc3, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x3, 0x2, 
    0x2, 0x2, 0xc4, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc7, 0x5, 0x14, 0xb, 
    0x2, 0xc6, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x3, 0x2, 0x2, 0x2, 
    0xc7, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xcd, 0x5, 0x22, 0x12, 0x2, 0xc9, 
    0xca, 0x7, 0x4, 0x2, 0x2, 0xca, 0xcc, 0x5, 0x22, 0x12, 0x2, 0xcb, 0xc9, 
    0x3, 0x2, 0x2, 0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 
    0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0xd1, 0x3, 0x2, 
    0x2, 0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc8, 0x3, 0x2, 0x2, 
    0x2, 0xd0, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd1, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0xd2, 0xd5, 0x5, 0x14, 0xb, 0x2, 0xd3, 0xd5, 0x5, 0x18, 0xd, 0x2, 0xd4, 
    0xd2, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd5, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0x17, 0x28, 0x2a, 0x34, 0x3a, 0x42, 0x49, 0x53, 
    0x5d, 0x6d, 0x78, 0x85, 0x8b, 0x9c, 0xa7, 0xa9, 0xb1, 0xc3, 0xc6, 0xcd, 
    0xd0, 0xd4, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SCCompilerParser::Initializer SCCompilerParser::_init;
