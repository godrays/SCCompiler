
// Generated from ./Targets/SCCompilerLib/Parser/SCCompiler.g4 by ANTLR 4.13.1


#include "SCCompilerLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct SCCompilerLexerStaticData final {
  SCCompilerLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SCCompilerLexerStaticData(const SCCompilerLexerStaticData&) = delete;
  SCCompilerLexerStaticData(SCCompilerLexerStaticData&&) = delete;
  SCCompilerLexerStaticData& operator=(const SCCompilerLexerStaticData&) = delete;
  SCCompilerLexerStaticData& operator=(SCCompilerLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sccompilerlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
SCCompilerLexerStaticData *sccompilerlexerLexerStaticData = nullptr;

void sccompilerlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sccompilerlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(sccompilerlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SCCompilerLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "T__32", 
      "T__33", "BOOL", "DIGIT", "LETTER", "INT", "FLOAT", "ID", "WS", "LINECOMMENT", 
      "BLOCKCOMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,41,284,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,
  	1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,
  	1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,
  	1,18,1,19,1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,
  	1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,28,1,28,1,28,1,29,1,29,1,29,1,30,
  	1,30,1,30,1,31,1,31,1,31,1,32,1,32,1,32,1,33,1,33,1,33,1,33,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,1,34,1,34,3,34,212,8,34,1,35,1,35,1,36,1,36,
  	1,37,4,37,219,8,37,11,37,12,37,220,1,38,4,38,224,8,38,11,38,12,38,225,
  	1,38,1,38,4,38,230,8,38,11,38,12,38,231,1,38,1,38,4,38,236,8,38,11,38,
  	12,38,237,1,38,3,38,241,8,38,3,38,243,8,38,1,39,1,39,1,39,5,39,248,8,
  	39,10,39,12,39,251,9,39,1,40,4,40,254,8,40,11,40,12,40,255,1,40,1,40,
  	1,41,1,41,1,41,1,41,5,41,264,8,41,10,41,12,41,267,9,41,1,41,1,41,1,42,
  	1,42,1,42,1,42,5,42,275,8,42,10,42,12,42,278,9,42,1,42,1,42,1,42,1,42,
  	1,42,1,276,0,43,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,
  	12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,
  	47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,
  	35,71,0,73,0,75,36,77,37,79,38,81,39,83,40,85,41,1,0,4,1,0,48,57,2,0,
  	65,90,97,122,3,0,9,10,13,13,32,32,2,0,10,10,13,13,293,0,1,1,0,0,0,0,3,
  	1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,
  	0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,
  	1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,
  	0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,
  	0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,
  	1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,
  	0,0,0,69,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,
  	0,83,1,0,0,0,0,85,1,0,0,0,1,87,1,0,0,0,3,89,1,0,0,0,5,91,1,0,0,0,7,93,
  	1,0,0,0,9,99,1,0,0,0,11,103,1,0,0,0,13,108,1,0,0,0,15,113,1,0,0,0,17,
  	115,1,0,0,0,19,117,1,0,0,0,21,119,1,0,0,0,23,121,1,0,0,0,25,124,1,0,0,
  	0,27,129,1,0,0,0,29,135,1,0,0,0,31,138,1,0,0,0,33,145,1,0,0,0,35,154,
  	1,0,0,0,37,160,1,0,0,0,39,163,1,0,0,0,41,166,1,0,0,0,43,168,1,0,0,0,45,
  	170,1,0,0,0,47,172,1,0,0,0,49,174,1,0,0,0,51,176,1,0,0,0,53,178,1,0,0,
  	0,55,181,1,0,0,0,57,183,1,0,0,0,59,186,1,0,0,0,61,189,1,0,0,0,63,192,
  	1,0,0,0,65,195,1,0,0,0,67,198,1,0,0,0,69,211,1,0,0,0,71,213,1,0,0,0,73,
  	215,1,0,0,0,75,218,1,0,0,0,77,242,1,0,0,0,79,244,1,0,0,0,81,253,1,0,0,
  	0,83,259,1,0,0,0,85,270,1,0,0,0,87,88,5,59,0,0,88,2,1,0,0,0,89,90,5,44,
  	0,0,90,4,1,0,0,0,91,92,5,61,0,0,92,6,1,0,0,0,93,94,5,102,0,0,94,95,5,
  	108,0,0,95,96,5,111,0,0,96,97,5,97,0,0,97,98,5,116,0,0,98,8,1,0,0,0,99,
  	100,5,105,0,0,100,101,5,110,0,0,101,102,5,116,0,0,102,10,1,0,0,0,103,
  	104,5,118,0,0,104,105,5,111,0,0,105,106,5,105,0,0,106,107,5,100,0,0,107,
  	12,1,0,0,0,108,109,5,98,0,0,109,110,5,111,0,0,110,111,5,111,0,0,111,112,
  	5,108,0,0,112,14,1,0,0,0,113,114,5,40,0,0,114,16,1,0,0,0,115,116,5,41,
  	0,0,116,18,1,0,0,0,117,118,5,123,0,0,118,20,1,0,0,0,119,120,5,125,0,0,
  	120,22,1,0,0,0,121,122,5,105,0,0,122,123,5,102,0,0,123,24,1,0,0,0,124,
  	125,5,101,0,0,125,126,5,108,0,0,126,127,5,115,0,0,127,128,5,101,0,0,128,
  	26,1,0,0,0,129,130,5,119,0,0,130,131,5,104,0,0,131,132,5,105,0,0,132,
  	133,5,108,0,0,133,134,5,101,0,0,134,28,1,0,0,0,135,136,5,100,0,0,136,
  	137,5,111,0,0,137,30,1,0,0,0,138,139,5,114,0,0,139,140,5,101,0,0,140,
  	141,5,116,0,0,141,142,5,117,0,0,142,143,5,114,0,0,143,144,5,110,0,0,144,
  	32,1,0,0,0,145,146,5,99,0,0,146,147,5,111,0,0,147,148,5,110,0,0,148,149,
  	5,116,0,0,149,150,5,105,0,0,150,151,5,110,0,0,151,152,5,117,0,0,152,153,
  	5,101,0,0,153,34,1,0,0,0,154,155,5,98,0,0,155,156,5,114,0,0,156,157,5,
  	101,0,0,157,158,5,97,0,0,158,159,5,107,0,0,159,36,1,0,0,0,160,161,5,43,
  	0,0,161,162,5,43,0,0,162,38,1,0,0,0,163,164,5,45,0,0,164,165,5,45,0,0,
  	165,40,1,0,0,0,166,167,5,45,0,0,167,42,1,0,0,0,168,169,5,43,0,0,169,44,
  	1,0,0,0,170,171,5,33,0,0,171,46,1,0,0,0,172,173,5,42,0,0,173,48,1,0,0,
  	0,174,175,5,47,0,0,175,50,1,0,0,0,176,177,5,60,0,0,177,52,1,0,0,0,178,
  	179,5,60,0,0,179,180,5,61,0,0,180,54,1,0,0,0,181,182,5,62,0,0,182,56,
  	1,0,0,0,183,184,5,62,0,0,184,185,5,61,0,0,185,58,1,0,0,0,186,187,5,61,
  	0,0,187,188,5,61,0,0,188,60,1,0,0,0,189,190,5,33,0,0,190,191,5,61,0,0,
  	191,62,1,0,0,0,192,193,5,38,0,0,193,194,5,38,0,0,194,64,1,0,0,0,195,196,
  	5,124,0,0,196,197,5,124,0,0,197,66,1,0,0,0,198,199,5,102,0,0,199,200,
  	5,111,0,0,200,201,5,114,0,0,201,68,1,0,0,0,202,203,5,116,0,0,203,204,
  	5,114,0,0,204,205,5,117,0,0,205,212,5,101,0,0,206,207,5,102,0,0,207,208,
  	5,97,0,0,208,209,5,108,0,0,209,210,5,115,0,0,210,212,5,101,0,0,211,202,
  	1,0,0,0,211,206,1,0,0,0,212,70,1,0,0,0,213,214,7,0,0,0,214,72,1,0,0,0,
  	215,216,7,1,0,0,216,74,1,0,0,0,217,219,3,71,35,0,218,217,1,0,0,0,219,
  	220,1,0,0,0,220,218,1,0,0,0,220,221,1,0,0,0,221,76,1,0,0,0,222,224,3,
  	71,35,0,223,222,1,0,0,0,224,225,1,0,0,0,225,223,1,0,0,0,225,226,1,0,0,
  	0,226,227,1,0,0,0,227,229,5,46,0,0,228,230,3,71,35,0,229,228,1,0,0,0,
  	230,231,1,0,0,0,231,229,1,0,0,0,231,232,1,0,0,0,232,243,1,0,0,0,233,235,
  	5,46,0,0,234,236,3,71,35,0,235,234,1,0,0,0,236,237,1,0,0,0,237,235,1,
  	0,0,0,237,238,1,0,0,0,238,240,1,0,0,0,239,241,5,102,0,0,240,239,1,0,0,
  	0,240,241,1,0,0,0,241,243,1,0,0,0,242,223,1,0,0,0,242,233,1,0,0,0,243,
  	78,1,0,0,0,244,249,3,73,36,0,245,248,3,73,36,0,246,248,7,0,0,0,247,245,
  	1,0,0,0,247,246,1,0,0,0,248,251,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,
  	0,250,80,1,0,0,0,251,249,1,0,0,0,252,254,7,2,0,0,253,252,1,0,0,0,254,
  	255,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,257,1,0,0,0,257,258,6,
  	40,0,0,258,82,1,0,0,0,259,260,5,47,0,0,260,261,5,47,0,0,261,265,1,0,0,
  	0,262,264,8,3,0,0,263,262,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,
  	266,1,0,0,0,266,268,1,0,0,0,267,265,1,0,0,0,268,269,6,41,0,0,269,84,1,
  	0,0,0,270,271,5,47,0,0,271,272,5,42,0,0,272,276,1,0,0,0,273,275,9,0,0,
  	0,274,273,1,0,0,0,275,278,1,0,0,0,276,277,1,0,0,0,276,274,1,0,0,0,277,
  	279,1,0,0,0,278,276,1,0,0,0,279,280,5,42,0,0,280,281,5,47,0,0,281,282,
  	1,0,0,0,282,283,6,42,0,0,283,86,1,0,0,0,13,0,211,220,225,231,237,240,
  	242,247,249,255,265,276,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sccompilerlexerLexerStaticData = staticData.release();
}

}

SCCompilerLexer::SCCompilerLexer(CharStream *input) : Lexer(input) {
  SCCompilerLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *sccompilerlexerLexerStaticData->atn, sccompilerlexerLexerStaticData->decisionToDFA, sccompilerlexerLexerStaticData->sharedContextCache);
}

SCCompilerLexer::~SCCompilerLexer() {
  delete _interpreter;
}

std::string SCCompilerLexer::getGrammarFileName() const {
  return "SCCompiler.g4";
}

const std::vector<std::string>& SCCompilerLexer::getRuleNames() const {
  return sccompilerlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& SCCompilerLexer::getChannelNames() const {
  return sccompilerlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& SCCompilerLexer::getModeNames() const {
  return sccompilerlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& SCCompilerLexer::getVocabulary() const {
  return sccompilerlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SCCompilerLexer::getSerializedATN() const {
  return sccompilerlexerLexerStaticData->serializedATN;
}

const atn::ATN& SCCompilerLexer::getATN() const {
  return *sccompilerlexerLexerStaticData->atn;
}




void SCCompilerLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sccompilerlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(sccompilerlexerLexerOnceFlag, sccompilerlexerLexerInitialize);
#endif
}
