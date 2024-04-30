
// Generated from ./Targets/SCCompilerLib/Parser/SCCompiler.g4 by ANTLR 4.13.1


#include "SCCompilerListener.h"
#include "SCCompilerVisitor.h"

#include "SCCompilerParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SCCompilerParserStaticData final {
  SCCompilerParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SCCompilerParserStaticData(const SCCompilerParserStaticData&) = delete;
  SCCompilerParserStaticData(SCCompilerParserStaticData&&) = delete;
  SCCompilerParserStaticData& operator=(const SCCompilerParserStaticData&) = delete;
  SCCompilerParserStaticData& operator=(SCCompilerParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sccompilerParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
SCCompilerParserStaticData *sccompilerParserStaticData = nullptr;

void sccompilerParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sccompilerParserStaticData != nullptr) {
    return;
  }
#else
  assert(sccompilerParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SCCompilerParserStaticData>(
    std::vector<std::string>{
      "program", "varDecl", "varInit", "type", "functionDecl", "formalParameters", 
      "formalParameter", "block", "stat", "expr", "exprList", "assignment", 
      "forStatement", "forVarDecl", "forCondition", "forIncrements", "forInc"
    },
    std::vector<std::string>{
      "", "';'", "','", "'='", "'float'", "'int'", "'void'", "'bool'", "'('", 
      "')'", "'{'", "'}'", "'if'", "'else'", "'while'", "'do'", "'return'", 
      "'continue'", "'break'", "'++'", "'--'", "'-'", "'+'", "'!'", "'*'", 
      "'/'", "'<'", "'<='", "'>'", "'>='", "'=='", "'!='", "'&&'", "'||'", 
      "'for'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "BOOL", "INT", "FLOAT", "ID", "WS", "LINECOMMENT", "BLOCKCOMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,41,232,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,1,0,1,0,4,0,39,8,0,11,0,12,0,40,1,0,1,
  	0,1,1,1,1,1,1,1,1,5,1,49,8,1,10,1,12,1,52,9,1,1,2,1,2,1,2,3,2,57,8,2,
  	1,3,1,3,1,4,1,4,1,4,1,4,3,4,65,8,4,1,4,1,4,1,4,5,4,70,8,4,10,4,12,4,73,
  	9,4,1,4,1,4,1,5,1,5,1,5,5,5,80,8,5,10,5,12,5,83,9,5,1,6,1,6,1,6,1,7,1,
  	7,5,7,90,8,7,10,7,12,7,93,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,3,8,108,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,3,8,127,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,3,8,140,8,8,1,9,1,9,1,9,1,9,3,9,146,8,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,165,8,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,185,8,
  	9,10,9,12,9,188,9,9,1,10,1,10,1,10,5,10,193,8,10,10,10,12,10,196,9,10,
  	1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,13,3,13,213,8,13,1,14,3,14,216,8,14,1,15,1,15,1,15,5,15,221,8,15,10,
  	15,12,15,224,9,15,3,15,226,8,15,1,16,1,16,3,16,230,8,16,1,16,0,1,18,17,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,8,1,0,4,7,2,0,4,5,7,7,
  	1,0,19,20,1,0,21,22,1,0,35,38,1,0,24,25,1,0,26,29,1,0,30,31,253,0,38,
  	1,0,0,0,2,44,1,0,0,0,4,53,1,0,0,0,6,58,1,0,0,0,8,60,1,0,0,0,10,76,1,0,
  	0,0,12,84,1,0,0,0,14,87,1,0,0,0,16,139,1,0,0,0,18,164,1,0,0,0,20,189,
  	1,0,0,0,22,197,1,0,0,0,24,201,1,0,0,0,26,212,1,0,0,0,28,215,1,0,0,0,30,
  	225,1,0,0,0,32,229,1,0,0,0,34,35,3,2,1,0,35,36,5,1,0,0,36,39,1,0,0,0,
  	37,39,3,8,4,0,38,34,1,0,0,0,38,37,1,0,0,0,39,40,1,0,0,0,40,38,1,0,0,0,
  	40,41,1,0,0,0,41,42,1,0,0,0,42,43,5,0,0,1,43,1,1,0,0,0,44,45,3,6,3,0,
  	45,50,3,4,2,0,46,47,5,2,0,0,47,49,3,4,2,0,48,46,1,0,0,0,49,52,1,0,0,0,
  	50,48,1,0,0,0,50,51,1,0,0,0,51,3,1,0,0,0,52,50,1,0,0,0,53,56,5,38,0,0,
  	54,55,5,3,0,0,55,57,3,18,9,0,56,54,1,0,0,0,56,57,1,0,0,0,57,5,1,0,0,0,
  	58,59,7,0,0,0,59,7,1,0,0,0,60,61,3,6,3,0,61,62,5,38,0,0,62,64,5,8,0,0,
  	63,65,3,10,5,0,64,63,1,0,0,0,64,65,1,0,0,0,65,66,1,0,0,0,66,67,5,9,0,
  	0,67,71,5,10,0,0,68,70,3,16,8,0,69,68,1,0,0,0,70,73,1,0,0,0,71,69,1,0,
  	0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,71,1,0,0,0,74,75,5,11,0,0,75,9,1,0,
  	0,0,76,81,3,12,6,0,77,78,5,2,0,0,78,80,3,12,6,0,79,77,1,0,0,0,80,83,1,
  	0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,11,1,0,0,0,83,81,1,0,0,0,84,85,3,
  	6,3,0,85,86,5,38,0,0,86,13,1,0,0,0,87,91,5,10,0,0,88,90,3,16,8,0,89,88,
  	1,0,0,0,90,93,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,94,1,0,0,0,93,91,
  	1,0,0,0,94,95,5,11,0,0,95,15,1,0,0,0,96,140,3,14,7,0,97,98,3,2,1,0,98,
  	99,5,1,0,0,99,140,1,0,0,0,100,101,5,12,0,0,101,102,5,8,0,0,102,103,3,
  	18,9,0,103,104,5,9,0,0,104,107,3,16,8,0,105,106,5,13,0,0,106,108,3,16,
  	8,0,107,105,1,0,0,0,107,108,1,0,0,0,108,140,1,0,0,0,109,140,3,24,12,0,
  	110,111,5,14,0,0,111,112,5,8,0,0,112,113,3,18,9,0,113,114,5,9,0,0,114,
  	115,3,16,8,0,115,140,1,0,0,0,116,117,5,15,0,0,117,118,3,16,8,0,118,119,
  	5,14,0,0,119,120,5,8,0,0,120,121,3,18,9,0,121,122,5,9,0,0,122,123,5,1,
  	0,0,123,140,1,0,0,0,124,126,5,16,0,0,125,127,3,18,9,0,126,125,1,0,0,0,
  	126,127,1,0,0,0,127,128,1,0,0,0,128,140,5,1,0,0,129,130,5,17,0,0,130,
  	140,5,1,0,0,131,132,5,18,0,0,132,140,5,1,0,0,133,134,3,22,11,0,134,135,
  	5,1,0,0,135,140,1,0,0,0,136,137,3,18,9,0,137,138,5,1,0,0,138,140,1,0,
  	0,0,139,96,1,0,0,0,139,97,1,0,0,0,139,100,1,0,0,0,139,109,1,0,0,0,139,
  	110,1,0,0,0,139,116,1,0,0,0,139,124,1,0,0,0,139,129,1,0,0,0,139,131,1,
  	0,0,0,139,133,1,0,0,0,139,136,1,0,0,0,140,17,1,0,0,0,141,142,6,9,-1,0,
  	142,143,5,38,0,0,143,145,5,8,0,0,144,146,3,20,10,0,145,144,1,0,0,0,145,
  	146,1,0,0,0,146,147,1,0,0,0,147,165,5,9,0,0,148,149,7,1,0,0,149,150,5,
  	8,0,0,150,151,3,18,9,0,151,152,5,9,0,0,152,165,1,0,0,0,153,154,7,2,0,
  	0,154,165,5,38,0,0,155,156,7,3,0,0,156,165,3,18,9,10,157,158,5,23,0,0,
  	158,165,3,18,9,9,159,165,7,4,0,0,160,161,5,8,0,0,161,162,3,18,9,0,162,
  	163,5,9,0,0,163,165,1,0,0,0,164,141,1,0,0,0,164,148,1,0,0,0,164,153,1,
  	0,0,0,164,155,1,0,0,0,164,157,1,0,0,0,164,159,1,0,0,0,164,160,1,0,0,0,
  	165,186,1,0,0,0,166,167,10,8,0,0,167,168,7,5,0,0,168,185,3,18,9,9,169,
  	170,10,7,0,0,170,171,7,3,0,0,171,185,3,18,9,8,172,173,10,6,0,0,173,174,
  	7,6,0,0,174,185,3,18,9,7,175,176,10,5,0,0,176,177,7,7,0,0,177,185,3,18,
  	9,6,178,179,10,4,0,0,179,180,5,32,0,0,180,185,3,18,9,5,181,182,10,3,0,
  	0,182,183,5,33,0,0,183,185,3,18,9,4,184,166,1,0,0,0,184,169,1,0,0,0,184,
  	172,1,0,0,0,184,175,1,0,0,0,184,178,1,0,0,0,184,181,1,0,0,0,185,188,1,
  	0,0,0,186,184,1,0,0,0,186,187,1,0,0,0,187,19,1,0,0,0,188,186,1,0,0,0,
  	189,194,3,18,9,0,190,191,5,2,0,0,191,193,3,18,9,0,192,190,1,0,0,0,193,
  	196,1,0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,21,1,0,0,0,196,194,1,
  	0,0,0,197,198,3,18,9,0,198,199,5,3,0,0,199,200,3,18,9,0,200,23,1,0,0,
  	0,201,202,5,34,0,0,202,203,5,8,0,0,203,204,3,26,13,0,204,205,5,1,0,0,
  	205,206,3,28,14,0,206,207,5,1,0,0,207,208,3,30,15,0,208,209,5,9,0,0,209,
  	210,3,16,8,0,210,25,1,0,0,0,211,213,3,2,1,0,212,211,1,0,0,0,212,213,1,
  	0,0,0,213,27,1,0,0,0,214,216,3,18,9,0,215,214,1,0,0,0,215,216,1,0,0,0,
  	216,29,1,0,0,0,217,222,3,32,16,0,218,219,5,2,0,0,219,221,3,32,16,0,220,
  	218,1,0,0,0,221,224,1,0,0,0,222,220,1,0,0,0,222,223,1,0,0,0,223,226,1,
  	0,0,0,224,222,1,0,0,0,225,217,1,0,0,0,225,226,1,0,0,0,226,31,1,0,0,0,
  	227,230,3,18,9,0,228,230,3,22,11,0,229,227,1,0,0,0,229,228,1,0,0,0,230,
  	33,1,0,0,0,21,38,40,50,56,64,71,81,91,107,126,139,145,164,184,186,194,
  	212,215,222,225,229
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sccompilerParserStaticData = staticData.release();
}

}

SCCompilerParser::SCCompilerParser(TokenStream *input) : SCCompilerParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SCCompilerParser::SCCompilerParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SCCompilerParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sccompilerParserStaticData->atn, sccompilerParserStaticData->decisionToDFA, sccompilerParserStaticData->sharedContextCache, options);
}

SCCompilerParser::~SCCompilerParser() {
  delete _interpreter;
}

const atn::ATN& SCCompilerParser::getATN() const {
  return *sccompilerParserStaticData->atn;
}

std::string SCCompilerParser::getGrammarFileName() const {
  return "SCCompiler.g4";
}

const std::vector<std::string>& SCCompilerParser::getRuleNames() const {
  return sccompilerParserStaticData->ruleNames;
}

const dfa::Vocabulary& SCCompilerParser::getVocabulary() const {
  return sccompilerParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SCCompilerParser::getSerializedATN() const {
  return sccompilerParserStaticData->serializedATN;
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


std::any SCCompilerParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ProgramContext* SCCompilerParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, SCCompilerParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
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

      default:
        break;
      }
      setState(40); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240) != 0));
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


std::any SCCompilerParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::VarDeclContext* SCCompilerParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SCCompilerParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
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


std::any SCCompilerParser::VarInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarInit(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::VarInitContext* SCCompilerParser::varInit() {
  VarInitContext *_localctx = _tracker.createInstance<VarInitContext>(_ctx, getState());
  enterRule(_localctx, 4, SCCompilerParser::RuleVarInit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
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


std::any SCCompilerParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::TypeContext* SCCompilerParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SCCompilerParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240) != 0))) {
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

std::any SCCompilerParser::FuncDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncDeclaration(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::FunctionDeclContext* SCCompilerParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, SCCompilerParser::RuleFunctionDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SCCompilerParser::FuncDeclarationContext>(_localctx);
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
      ((1ULL << _la) & 240) != 0)) {
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
      ((1ULL << _la) & 532592711152) != 0)) {
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


std::any SCCompilerParser::FormalParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFormalParameters(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::FormalParametersContext* SCCompilerParser::formalParameters() {
  FormalParametersContext *_localctx = _tracker.createInstance<FormalParametersContext>(_ctx, getState());
  enterRule(_localctx, 10, SCCompilerParser::RuleFormalParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
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

std::any SCCompilerParser::FuncArgDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitFuncArgDeclaration(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::FormalParameterContext* SCCompilerParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 12, SCCompilerParser::RuleFormalParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SCCompilerParser::FuncArgDeclarationContext>(_localctx);
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


std::any SCCompilerParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::BlockContext* SCCompilerParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 14, SCCompilerParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
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
      ((1ULL << _la) & 532592711152) != 0)) {
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

std::any SCCompilerParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::IgnoreContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::BreakContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::FuncCallStatementContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::ContinueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitContinue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoWhileStatementContext ------------------------------------------------------------------

SCCompilerParser::StatContext* SCCompilerParser::DoWhileStatementContext::stat() {
  return getRuleContext<SCCompilerParser::StatContext>(0);
}

SCCompilerParser::ExprContext* SCCompilerParser::DoWhileStatementContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::DoWhileStatementContext::DoWhileStatementContext(StatContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::DoWhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhileStatement(this);
}
void SCCompilerParser::DoWhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhileStatement(this);
}

std::any SCCompilerParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
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

std::any SCCompilerParser::VarDeclStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitVarDeclStatement(this);
  else
    return visitor->visitChildren(this);
}
SCCompilerParser::StatContext* SCCompilerParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 16, SCCompilerParser::RuleStat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SCCompilerParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(96);
      block();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SCCompilerParser::VarDeclStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(97);
      varDecl();
      setState(98);
      match(SCCompilerParser::T__0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SCCompilerParser::IfStatementContext>(_localctx);
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

      default:
        break;
      }
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SCCompilerParser::IgnoreContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(109);
      forStatement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SCCompilerParser::WhileStatementContext>(_localctx);
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
      _localctx = _tracker.createInstance<SCCompilerParser::DoWhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(116);
      match(SCCompilerParser::T__14);
      setState(117);
      stat();
      setState(118);
      match(SCCompilerParser::T__13);
      setState(119);
      match(SCCompilerParser::T__7);
      setState(120);
      expr(0);
      setState(121);
      match(SCCompilerParser::T__8);
      setState(122);
      match(SCCompilerParser::T__0);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SCCompilerParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(124);
      match(SCCompilerParser::T__15);
      setState(126);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515412328880) != 0)) {
        setState(125);
        expr(0);
      }
      setState(128);
      match(SCCompilerParser::T__0);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SCCompilerParser::ContinueContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(129);
      match(SCCompilerParser::T__16);
      setState(130);
      match(SCCompilerParser::T__0);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<SCCompilerParser::BreakContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(131);
      match(SCCompilerParser::T__17);
      setState(132);
      match(SCCompilerParser::T__0);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<SCCompilerParser::IgnoreContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(133);
      assignment();
      setState(134);
      match(SCCompilerParser::T__0);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<SCCompilerParser::FuncCallStatementContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(136);
      expr(0);
      setState(137);
      match(SCCompilerParser::T__0);
      break;
    }

    default:
      break;
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

std::any SCCompilerParser::ExplicitTypeConversionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitExplicitTypeConversion(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrefixAOPExprContext ------------------------------------------------------------------

tree::TerminalNode* SCCompilerParser::PrefixAOPExprContext::ID() {
  return getToken(SCCompilerParser::ID, 0);
}

SCCompilerParser::PrefixAOPExprContext::PrefixAOPExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::PrefixAOPExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrefixAOPExpr(this);
}
void SCCompilerParser::PrefixAOPExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrefixAOPExpr(this);
}

std::any SCCompilerParser::PrefixAOPExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitPrefixAOPExpr(this);
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

std::any SCCompilerParser::ParenthesisExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitParenthesisExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalNotOPExprContext ------------------------------------------------------------------

SCCompilerParser::ExprContext* SCCompilerParser::LogicalNotOPExprContext::expr() {
  return getRuleContext<SCCompilerParser::ExprContext>(0);
}

SCCompilerParser::LogicalNotOPExprContext::LogicalNotOPExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::LogicalNotOPExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalNotOPExpr(this);
}
void SCCompilerParser::LogicalNotOPExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalNotOPExpr(this);
}

std::any SCCompilerParser::LogicalNotOPExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitLogicalNotOPExpr(this);
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

std::any SCCompilerParser::LiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::CompExprContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::AOPExprContext::accept(tree::ParseTreeVisitor *visitor) {
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

std::any SCCompilerParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOPExprContext ------------------------------------------------------------------

std::vector<SCCompilerParser::ExprContext *> SCCompilerParser::LogicalOPExprContext::expr() {
  return getRuleContexts<SCCompilerParser::ExprContext>();
}

SCCompilerParser::ExprContext* SCCompilerParser::LogicalOPExprContext::expr(size_t i) {
  return getRuleContext<SCCompilerParser::ExprContext>(i);
}

SCCompilerParser::LogicalOPExprContext::LogicalOPExprContext(ExprContext *ctx) { copyFrom(ctx); }

void SCCompilerParser::LogicalOPExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOPExpr(this);
}
void SCCompilerParser::LogicalOPExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SCCompilerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOPExpr(this);
}

std::any SCCompilerParser::LogicalOPExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitLogicalOPExpr(this);
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

std::any SCCompilerParser::FuncCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, SCCompilerParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(164);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(142);
      match(SCCompilerParser::ID);
      setState(143);
      match(SCCompilerParser::T__7);
      setState(145);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515412328880) != 0)) {
        setState(144);
        exprList();
      }
      setState(147);
      match(SCCompilerParser::T__8);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ExplicitTypeConversionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(148);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 176) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(149);
      match(SCCompilerParser::T__7);
      setState(150);
      expr(0);
      setState(151);
      match(SCCompilerParser::T__8);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrefixAOPExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(153);
      _la = _input->LA(1);
      if (!(_la == SCCompilerParser::T__18

      || _la == SCCompilerParser::T__19)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(154);
      match(SCCompilerParser::ID);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(155);
      _la = _input->LA(1);
      if (!(_la == SCCompilerParser::T__20

      || _la == SCCompilerParser::T__21)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(156);
      expr(10);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<LogicalNotOPExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(157);
      match(SCCompilerParser::T__22);
      setState(158);
      expr(9);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(159);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515396075520) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ParenthesisExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(160);
      match(SCCompilerParser::T__7);
      setState(161);
      expr(0);
      setState(162);
      match(SCCompilerParser::T__8);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(186);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(184);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(166);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(167);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__23

          || _la == SCCompilerParser::T__24)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(168);
          expr(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(169);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(170);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__20

          || _la == SCCompilerParser::T__21)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(171);
          expr(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CompExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(172);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(173);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1006632960) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(174);
          expr(7);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<CompExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(175);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(176);
          _la = _input->LA(1);
          if (!(_la == SCCompilerParser::T__29

          || _la == SCCompilerParser::T__30)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(177);
          expr(6);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<LogicalOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(178);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(179);
          match(SCCompilerParser::T__31);
          setState(180);
          expr(5);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<LogicalOPExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(181);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(182);
          match(SCCompilerParser::T__32);
          setState(183);
          expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(188);
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


std::any SCCompilerParser::ExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitExprList(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ExprListContext* SCCompilerParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 20, SCCompilerParser::RuleExprList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    expr(0);
    setState(194);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SCCompilerParser::T__1) {
      setState(190);
      match(SCCompilerParser::T__1);
      setState(191);
      expr(0);
      setState(196);
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


std::any SCCompilerParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::AssignmentContext* SCCompilerParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 22, SCCompilerParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    expr(0);
    setState(198);
    match(SCCompilerParser::T__2);
    setState(199);
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


std::any SCCompilerParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForStatementContext* SCCompilerParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, SCCompilerParser::RuleForStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(SCCompilerParser::T__33);
    setState(202);
    match(SCCompilerParser::T__7);
    setState(203);
    forVarDecl();
    setState(204);
    match(SCCompilerParser::T__0);
    setState(205);
    forCondition();
    setState(206);
    match(SCCompilerParser::T__0);
    setState(207);
    forIncrements();
    setState(208);
    match(SCCompilerParser::T__8);
    setState(209);
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


std::any SCCompilerParser::ForVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForVarDeclContext* SCCompilerParser::forVarDecl() {
  ForVarDeclContext *_localctx = _tracker.createInstance<ForVarDeclContext>(_ctx, getState());
  enterRule(_localctx, 26, SCCompilerParser::RuleForVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240) != 0)) {
      setState(211);
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


std::any SCCompilerParser::ForConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForCondition(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForConditionContext* SCCompilerParser::forCondition() {
  ForConditionContext *_localctx = _tracker.createInstance<ForConditionContext>(_ctx, getState());
  enterRule(_localctx, 28, SCCompilerParser::RuleForCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 515412328880) != 0)) {
      setState(214);
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


std::any SCCompilerParser::ForIncrementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForIncrements(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForIncrementsContext* SCCompilerParser::forIncrements() {
  ForIncrementsContext *_localctx = _tracker.createInstance<ForIncrementsContext>(_ctx, getState());
  enterRule(_localctx, 30, SCCompilerParser::RuleForIncrements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 515412328880) != 0)) {
      setState(217);
      forInc();
      setState(222);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SCCompilerParser::T__1) {
        setState(218);
        match(SCCompilerParser::T__1);
        setState(219);
        forInc();
        setState(224);
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


std::any SCCompilerParser::ForIncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SCCompilerVisitor*>(visitor))
    return parserVisitor->visitForInc(this);
  else
    return visitor->visitChildren(this);
}

SCCompilerParser::ForIncContext* SCCompilerParser::forInc() {
  ForIncContext *_localctx = _tracker.createInstance<ForIncContext>(_ctx, getState());
  enterRule(_localctx, 32, SCCompilerParser::RuleForInc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(229);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(227);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(228);
      assignment();
      break;
    }

    default:
      break;
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
    case 9: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SCCompilerParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);
    case 4: return precpred(_ctx, 4);
    case 5: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void SCCompilerParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sccompilerParserInitialize();
#else
  ::antlr4::internal::call_once(sccompilerParserOnceFlag, sccompilerParserInitialize);
#endif
}
