
// Generated from ./Common/Parser/DemoCompiler.g4 by ANTLR 4.7.1


#include "DemoCompilerListener.h"
#include "DemoCompilerVisitor.h"

#include "DemoCompilerParser.h"


using namespace antlrcpp;
using namespace antlr4;

DemoCompilerParser::DemoCompilerParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

DemoCompilerParser::~DemoCompilerParser() {
  delete _interpreter;
}

std::string DemoCompilerParser::getGrammarFileName() const {
  return "DemoCompiler.g4";
}

const std::vector<std::string>& DemoCompilerParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& DemoCompilerParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

DemoCompilerParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DemoCompilerParser::ProgramContext::EOF() {
  return getToken(DemoCompilerParser::EOF, 0);
}

std::vector<DemoCompilerParser::LineContext *> DemoCompilerParser::ProgramContext::line() {
  return getRuleContexts<DemoCompilerParser::LineContext>();
}

DemoCompilerParser::LineContext* DemoCompilerParser::ProgramContext::line(size_t i) {
  return getRuleContext<DemoCompilerParser::LineContext>(i);
}


size_t DemoCompilerParser::ProgramContext::getRuleIndex() const {
  return DemoCompilerParser::RuleProgram;
}

void DemoCompilerParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void DemoCompilerParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any DemoCompilerParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DemoCompilerVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

DemoCompilerParser::ProgramContext* DemoCompilerParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, DemoCompilerParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(7); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(6);
      line();
      setState(9); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == DemoCompilerParser::WORD);
    setState(11);
    match(DemoCompilerParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

DemoCompilerParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DemoCompilerParser::LineContext::NEWLINE() {
  return getToken(DemoCompilerParser::NEWLINE, 0);
}

std::vector<DemoCompilerParser::NameContext *> DemoCompilerParser::LineContext::name() {
  return getRuleContexts<DemoCompilerParser::NameContext>();
}

DemoCompilerParser::NameContext* DemoCompilerParser::LineContext::name(size_t i) {
  return getRuleContext<DemoCompilerParser::NameContext>(i);
}


size_t DemoCompilerParser::LineContext::getRuleIndex() const {
  return DemoCompilerParser::RuleLine;
}

void DemoCompilerParser::LineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLine(this);
}

void DemoCompilerParser::LineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLine(this);
}


antlrcpp::Any DemoCompilerParser::LineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DemoCompilerVisitor*>(visitor))
    return parserVisitor->visitLine(this);
  else
    return visitor->visitChildren(this);
}

DemoCompilerParser::LineContext* DemoCompilerParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 2, DemoCompilerParser::RuleLine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(14); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(13);
      name();
      setState(16); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == DemoCompilerParser::WORD);
    setState(18);
    match(DemoCompilerParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

DemoCompilerParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DemoCompilerParser::NameContext::WORD() {
  return getToken(DemoCompilerParser::WORD, 0);
}


size_t DemoCompilerParser::NameContext::getRuleIndex() const {
  return DemoCompilerParser::RuleName;
}

void DemoCompilerParser::NameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName(this);
}

void DemoCompilerParser::NameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DemoCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName(this);
}


antlrcpp::Any DemoCompilerParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DemoCompilerVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

DemoCompilerParser::NameContext* DemoCompilerParser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 4, DemoCompilerParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(DemoCompilerParser::WORD);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> DemoCompilerParser::_decisionToDFA;
atn::PredictionContextCache DemoCompilerParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DemoCompilerParser::_atn;
std::vector<uint16_t> DemoCompilerParser::_serializedATN;

std::vector<std::string> DemoCompilerParser::_ruleNames = {
  "program", "line", "name"
};

std::vector<std::string> DemoCompilerParser::_literalNames = {
};

std::vector<std::string> DemoCompilerParser::_symbolicNames = {
  "", "WORD", "WHITESPACE", "NEWLINE"
};

dfa::Vocabulary DemoCompilerParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> DemoCompilerParser::_tokenNames;

DemoCompilerParser::Initializer::Initializer() {
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
    0x3, 0x5, 0x19, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x3, 0x2, 0x6, 0x2, 0xa, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0xb, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0x11, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0x12, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x2, 0x2, 0x5, 
    0x2, 0x4, 0x6, 0x2, 0x2, 0x2, 0x17, 0x2, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x10, 0x3, 0x2, 0x2, 0x2, 0x6, 0x16, 0x3, 0x2, 0x2, 0x2, 0x8, 0xa, 0x5, 
    0x4, 0x3, 0x2, 0x9, 0x8, 0x3, 0x2, 0x2, 0x2, 0xa, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0xb, 0x9, 0x3, 0x2, 0x2, 0x2, 0xb, 0xc, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0xd, 0xe, 0x7, 0x2, 0x2, 0x3, 0xe, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0xf, 0x11, 0x5, 0x6, 0x4, 0x2, 0x10, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x11, 0x12, 0x3, 0x2, 0x2, 0x2, 0x12, 0x10, 0x3, 0x2, 0x2, 0x2, 
    0x12, 0x13, 0x3, 0x2, 0x2, 0x2, 0x13, 0x14, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x15, 0x7, 0x5, 0x2, 0x2, 0x15, 0x5, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 
    0x7, 0x3, 0x2, 0x2, 0x17, 0x7, 0x3, 0x2, 0x2, 0x2, 0x4, 0xb, 0x12, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

DemoCompilerParser::Initializer DemoCompilerParser::_init;
