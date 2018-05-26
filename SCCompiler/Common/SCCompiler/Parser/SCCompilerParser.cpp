
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
    setState(26); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(26);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(22);
        varDecl();
        setState(23);
        match(SCCompilerParser::T__0);
        break;
      }

      case 2: {
        setState(25);
        functionDecl();
        break;
      }

      }
      setState(28); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0));
    setState(30);
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
    setState(32);
    type();
    setState(33);
    varInit();
    setState(38);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(34);
      match(SCCompilerParser::T__1);
      setState(35);
      varInit();
      setState(40);
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
    setState(41);
    match(SCCompilerParser::ID);
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SCCompilerParser::T__2) {
      setState(42);
      match(SCCompilerParser::T__2);
      setState(43);
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
    setState(46);
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
    setState(48);
    type();
    setState(49);
    match(SCCompilerParser::ID);
    setState(50);
    match(SCCompilerParser::T__7);
    setState(52);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
      | (1ULL << SCCompilerParser::T__4)
      | (1ULL << SCCompilerParser::T__5)
      | (1ULL << SCCompilerParser::T__6))) != 0)) {
      setState(51);
      formalParameters();
    }
    setState(54);
    match(SCCompilerParser::T__8);
    setState(55);
    match(SCCompilerParser::T__9);
    setState(59);
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
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(56);
      stat();
      setState(61);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(62);
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
    setState(64);
    formalParameter();
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(65);
      match(SCCompilerParser::T__1);
      setState(66);
      formalParameter();
      setState(71);
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
    setState(72);
    type();
    setState(73);
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
    setState(75);
    match(SCCompilerParser::T__9);
    setState(79);
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
      | (1ULL << SCCompilerParser::BOOL)
      | (1ULL << SCCompilerParser::INT)
      | (1ULL << SCCompilerParser::FLOAT)
      | (1ULL << SCCompilerParser::ID))) != 0)) {
      setState(76);
      stat();
      setState(81);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(82);
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
//----------------- AssignmentStatementContext ------------------------------------------------------------------

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::AssignmentStatementContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::AssignmentStatementContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}

SCCompilerParser::AssignmentStatementContext::AssignmentStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::AssignmentStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentStatement(this);
}
void SCCompilerParser::AssignmentStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentStatement(this);
}

antlrcpp::Any SCCompilerParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitAssignmentStatement(this);
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
    setState(110);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::BlockStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(84);
      block();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::VarDeclStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(85);
      varDecl();
      setState(86);
      match(SCCompilerParser::T__0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::IfStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(88);
      match(SCCompilerParser::T__11);
      setState(89);
      match(SCCompilerParser::T__7);
      setState(90);
      expr(0);
      setState(91);
      match(SCCompilerParser::T__8);
      setState(92);
      stat();
      setState(95);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
      case 1: {
        setState(93);
        match(SCCompilerParser::T__12);
        setState(94);
        stat();
        break;
      }

      }
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::ReturnStatementContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(97);
      match(SCCompilerParser::T__13);
      setState(99);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
        | (1ULL << SCCompilerParser::T__4)
        | (1ULL << SCCompilerParser::T__6)
        | (1ULL << SCCompilerParser::T__7)
        | (1ULL << SCCompilerParser::T__14)
        | (1ULL << SCCompilerParser::T__15)
        | (1ULL << SCCompilerParser::T__16)
        | (1ULL << SCCompilerParser::BOOL)
        | (1ULL << SCCompilerParser::INT)
        | (1ULL << SCCompilerParser::FLOAT)
        | (1ULL << SCCompilerParser::ID))) != 0)) {
        setState(98);
        expr(0);
      }
      setState(101);
      match(SCCompilerParser::T__0);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::AssignmentStatementContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(102);
      expr(0);
      setState(103);
      match(SCCompilerParser::T__2);
      setState(104);
      expr(0);
      setState(105);
      match(SCCompilerParser::T__0);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<SCCompilerParser::FuncCallStatementContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(107);
      expr(0);
      setState(108);
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
  enterRule(_localctx, 18, SCCompilerParser::RuleExprList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    expr(0);
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(113);
      match(SCCompilerParser::T__1);
      setState(114);
      expr(0);
      setState(119);
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
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, SCCompilerParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(121);
      match(SCCompilerParser::ID);
      setState(122);
      match(SCCompilerParser::T__7);
      setState(124);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SCCompilerParser::T__3)
        | (1ULL << SCCompilerParser::T__4)
        | (1ULL << SCCompilerParser::T__6)
        | (1ULL << SCCompilerParser::T__7)
        | (1ULL << SCCompilerParser::T__14)
        | (1ULL << SCCompilerParser::T__15)
        | (1ULL << SCCompilerParser::T__16)
        | (1ULL << SCCompilerParser::BOOL)
        | (1ULL << SCCompilerParser::INT)
        | (1ULL << SCCompilerParser::FLOAT)
        | (1ULL << SCCompilerParser::ID))) != 0)) {
        setState(123);
        exprList();
      }
      setState(126);
      match(SCCompilerParser::T__8);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ExplicitTypeConversionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(127);
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
      setState(128);
      match(SCCompilerParser::T__7);
      setState(129);
      expr(0);
      setState(130);
      match(SCCompilerParser::T__8);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(132);
      _la = _input->LA(1);
      if (!(_la == SCCompilerParser::T__14

      || _la == SCCompilerParser::T__15)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(133);
      expr(7);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LogicalNotExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(134);
      match(SCCompilerParser::T__16);
      setState(135);
      expr(6);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(136);
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
      setState(137);
      match(SCCompilerParser::T__7);
      setState(138);
      expr(0);
      setState(139);
      match(SCCompilerParser::T__8);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(154);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(152);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(143);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(144);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__17

          || _la == SCCompilerParser::T__18)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(145);
          expr(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(146);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(147);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__14

          || _la == SCCompilerParser::T__15)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(148);
          expr(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CompExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(149);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(150);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SCCompilerParser::T__19)
            | (1ULL << SCCompilerParser::T__20)
            | (1ULL << SCCompilerParser::T__21)
            | (1ULL << SCCompilerParser::T__22)
            | (1ULL << SCCompilerParser::T__23)
            | (1ULL << SCCompilerParser::T__24))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(151);
          expr(4);
          break;
        }

        } 
      }
      setState(156);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
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
    case 10: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

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
  "formalParameter", "block", "stat", "exprList", "expr"
};

std::vector<std::string> SCCompilerParser::_literalNames = {
  "", "';'", "','", "'='", "'float'", "'int'", "'void'", "'bool'", "'('", 
  "')'", "'{'", "'}'", "'if'", "'else'", "'return'", "'-'", "'+'", "'!'", 
  "'*'", "'/'", "'=='", "'!='", "'<='", "'>='", "'<'", "'>'"
};

std::vector<std::string> SCCompilerParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "BOOL", "INT", "FLOAT", "ID", "WS", "LINECOMMENT", 
  "BLOCKCOMMENT"
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
    0x3, 0x22, 0xa0, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x6, 
    0x2, 0x1d, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1e, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x27, 0xa, 0x3, 0xc, 0x3, 
    0xe, 0x3, 0x2a, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x2f, 
    0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x5, 0x6, 0x37, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x3c, 
    0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x3f, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x46, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 
    0x49, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x7, 
    0x9, 0x50, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x53, 0xb, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x62, 0xa, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x66, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 
    0xa, 0x71, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x76, 0xa, 
    0xb, 0xc, 0xb, 0xe, 0xb, 0x79, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x5, 0xc, 0x7f, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x90, 0xa, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x9b, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x9e, 
    0xb, 0xc, 0x3, 0xc, 0x2, 0x3, 0x16, 0xd, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x8, 0x3, 0x2, 0x6, 0x9, 0x4, 0x2, 
    0x6, 0x7, 0x9, 0x9, 0x3, 0x2, 0x11, 0x12, 0x3, 0x2, 0x1c, 0x1f, 0x3, 
    0x2, 0x14, 0x15, 0x3, 0x2, 0x16, 0x1b, 0x2, 0xad, 0x2, 0x1c, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x22, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x30, 0x3, 0x2, 0x2, 0x2, 0xa, 0x32, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x70, 0x3, 0x2, 0x2, 0x2, 0x14, 0x72, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x5, 0x4, 0x3, 
    0x2, 0x19, 0x1a, 0x7, 0x3, 0x2, 0x2, 0x1a, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x1b, 0x1d, 0x5, 0xa, 0x6, 0x2, 0x1c, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1c, 
    0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 
    0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x2, 0x2, 0x3, 0x21, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x23, 0x5, 0x8, 0x5, 0x2, 0x23, 0x28, 0x5, 0x6, 0x4, 
    0x2, 0x24, 0x25, 0x7, 0x4, 0x2, 0x2, 0x25, 0x27, 0x5, 0x6, 0x4, 0x2, 
    0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x27, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 0x2, 0x2, 0x2, 0x29, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2e, 0x7, 
    0x1f, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x5, 0x2, 0x2, 0x2d, 0x2f, 0x5, 0x16, 
    0xc, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x2f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x9, 0x2, 0x2, 0x2, 
    0x31, 0x9, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x5, 0x8, 0x5, 0x2, 0x33, 
    0x34, 0x7, 0x1f, 0x2, 0x2, 0x34, 0x36, 0x7, 0xa, 0x2, 0x2, 0x35, 0x37, 
    0x5, 0xc, 0x7, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0xb, 
    0x2, 0x2, 0x39, 0x3d, 0x7, 0xc, 0x2, 0x2, 0x3a, 0x3c, 0x5, 0x12, 0xa, 
    0x2, 0x3b, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x3, 0x2, 0x2, 0x2, 
    0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x40, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 
    0x7, 0xd, 0x2, 0x2, 0x41, 0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x47, 0x5, 
    0xe, 0x8, 0x2, 0x43, 0x44, 0x7, 0x4, 0x2, 0x2, 0x44, 0x46, 0x5, 0xe, 
    0x8, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0xd, 0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4a, 
    0x4b, 0x5, 0x8, 0x5, 0x2, 0x4b, 0x4c, 0x7, 0x1f, 0x2, 0x2, 0x4c, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x4d, 0x51, 0x7, 0xc, 0x2, 0x2, 0x4e, 0x50, 0x5, 
    0x12, 0xa, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x53, 0x3, 0x2, 
    0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 
    0x2, 0x52, 0x54, 0x3, 0x2, 0x2, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x55, 0x7, 0xd, 0x2, 0x2, 0x55, 0x11, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x71, 0x5, 0x10, 0x9, 0x2, 0x57, 0x58, 0x5, 0x4, 0x3, 0x2, 0x58, 0x59, 
    0x7, 0x3, 0x2, 0x2, 0x59, 0x71, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 
    0xe, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0xa, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0x16, 
    0xc, 0x2, 0x5d, 0x5e, 0x7, 0xb, 0x2, 0x2, 0x5e, 0x61, 0x5, 0x12, 0xa, 
    0x2, 0x5f, 0x60, 0x7, 0xf, 0x2, 0x2, 0x60, 0x62, 0x5, 0x12, 0xa, 0x2, 
    0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x71, 0x3, 0x2, 0x2, 0x2, 0x63, 0x65, 0x7, 0x10, 0x2, 0x2, 0x64, 0x66, 
    0x5, 0x16, 0xc, 0x2, 0x65, 0x64, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x3, 
    0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 0x71, 0x7, 0x3, 
    0x2, 0x2, 0x68, 0x69, 0x5, 0x16, 0xc, 0x2, 0x69, 0x6a, 0x7, 0x5, 0x2, 
    0x2, 0x6a, 0x6b, 0x5, 0x16, 0xc, 0x2, 0x6b, 0x6c, 0x7, 0x3, 0x2, 0x2, 
    0x6c, 0x71, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x5, 0x16, 0xc, 0x2, 0x6e, 
    0x6f, 0x7, 0x3, 0x2, 0x2, 0x6f, 0x71, 0x3, 0x2, 0x2, 0x2, 0x70, 0x56, 
    0x3, 0x2, 0x2, 0x2, 0x70, 0x57, 0x3, 0x2, 0x2, 0x2, 0x70, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x70, 0x63, 0x3, 0x2, 0x2, 0x2, 0x70, 0x68, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x71, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x72, 0x77, 0x5, 0x16, 0xc, 0x2, 0x73, 0x74, 0x7, 0x4, 0x2, 0x2, 
    0x74, 0x76, 0x5, 0x16, 0xc, 0x2, 0x75, 0x73, 0x3, 0x2, 0x2, 0x2, 0x76, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x15, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x7a, 0x7b, 0x8, 0xc, 0x1, 0x2, 0x7b, 0x7c, 0x7, 0x1f, 
    0x2, 0x2, 0x7c, 0x7e, 0x7, 0xa, 0x2, 0x2, 0x7d, 0x7f, 0x5, 0x14, 0xb, 
    0x2, 0x7e, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x3, 0x2, 0x2, 0x2, 0x80, 0x90, 0x7, 0xb, 0x2, 0x2, 0x81, 
    0x82, 0x9, 0x3, 0x2, 0x2, 0x82, 0x83, 0x7, 0xa, 0x2, 0x2, 0x83, 0x84, 
    0x5, 0x16, 0xc, 0x2, 0x84, 0x85, 0x7, 0xb, 0x2, 0x2, 0x85, 0x90, 0x3, 
    0x2, 0x2, 0x2, 0x86, 0x87, 0x9, 0x4, 0x2, 0x2, 0x87, 0x90, 0x5, 0x16, 
    0xc, 0x9, 0x88, 0x89, 0x7, 0x13, 0x2, 0x2, 0x89, 0x90, 0x5, 0x16, 0xc, 
    0x8, 0x8a, 0x90, 0x9, 0x5, 0x2, 0x2, 0x8b, 0x8c, 0x7, 0xa, 0x2, 0x2, 
    0x8c, 0x8d, 0x5, 0x16, 0xc, 0x2, 0x8d, 0x8e, 0x7, 0xb, 0x2, 0x2, 0x8e, 
    0x90, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x81, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x86, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x8f, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x90, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0xc, 0x7, 0x2, 
    0x2, 0x92, 0x93, 0x9, 0x6, 0x2, 0x2, 0x93, 0x9b, 0x5, 0x16, 0xc, 0x8, 
    0x94, 0x95, 0xc, 0x6, 0x2, 0x2, 0x95, 0x96, 0x9, 0x4, 0x2, 0x2, 0x96, 
    0x9b, 0x5, 0x16, 0xc, 0x7, 0x97, 0x98, 0xc, 0x5, 0x2, 0x2, 0x98, 0x99, 
    0x9, 0x7, 0x2, 0x2, 0x99, 0x9b, 0x5, 0x16, 0xc, 0x6, 0x9a, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x9a, 0x94, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x97, 0x3, 0x2, 
    0x2, 0x2, 0x9b, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x9c, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x9e, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x12, 0x1c, 0x1e, 0x28, 0x2e, 0x36, 
    0x3d, 0x47, 0x51, 0x61, 0x65, 0x70, 0x77, 0x7e, 0x8f, 0x9a, 0x9c, 
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
