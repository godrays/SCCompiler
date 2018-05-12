//
//  main.cpp
//  SCCTestApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <map>
#include <docopt/docopt.h>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestSuccessListener.h>
#include <cppunit/Portability.h>

const int EXIT_CODE_OK = 0;
const int EXIT_CODE_ERROR = -1;

// List the given test heirarchy.
void ListTests(CppUnit::Test * test)
{
    if (test == nullptr)
    {
        return;
    }
    
    std::cout << test->getName() << std::endl;
    
    for (int i=0; i < test->getChildTestCount(); ++i)
    {
        ListTests(test->getChildTestAt(i));
    }
}


// Returns true if source string matches with the given pattern, returns false otherwise.
bool IsMatch(const std::string & source, const std::string & pattern)
{
    const char * star = nullptr;
    const char * str = source.c_str();
    const char * sstr= str;
    const char * pstr = pattern.c_str();
    
    while (*str)
    {
        if ((*pstr == '?') || (*pstr == *str)) { str++; pstr++; continue; }
        if (*pstr == '*') { star = pstr++; sstr = str; continue; }
        if (star) { pstr = star + 1; str = ++sstr; continue; }
        
        return false;
    }
    
    while (*pstr == '*') { pstr++; }
    
    return !*pstr;
}


// Runs all matching test with the given name, otherwise returns nullptr.
void RunMatchingTests(CppUnit::Test * test, const std::string & pattern, CppUnit::TestResult & result, size_t repeat)
{
    if (test == nullptr)
    {
        return;
    }
    
    // Run matching test.
    if (IsMatch(test->getName(), pattern) == true)
    {
        CppUnit::TestRunner runner;
        runner.addTest(test);
        
        for (int i = 0; i < repeat; ++i)
        {
            runner.run(result);
        }
        return;
    }
    
    // Iterate childrens.
    for (int i=0; i < test->getChildTestCount(); ++i)
    {
        RunMatchingTests(test->getChildTestAt(i), pattern, result, repeat);
    }
}


int main(int argc, char * const argv[])
{
    // NOTE: USAGE text context and indentations is very sensitive. Must have only 2 chars indent.
    static const char USAGE[] =
    R"(SCC Test Application.

    Usage:
      SCCompilerTestApp  [--output-style=<style>] [--progress=<progress>] [--test=<test>] [--repeat=<count>]
      SCCompilerTestApp  --list-all
      SCCompilerTestApp  (-h | --help)

    Options:

      --output-style   Output style (compiler | text | xml | none ). [default: compiler]
      --progress       Progress style (dots | brief | none ). [Default: dots]
      --test           Runs all matching test with the given search pattern. [default: "*"]
      --repeat         Repeat count. [default: 1]
      --list-all       List all available tests.
      -h, --help       Show this screen.

    Return values: Zero=Success, Negative=Errors and failures.
    )";
    
    std::map<std::string, docopt::value> args;
    
    try
    {
        args = docopt::docopt(USAGE,
                              { argv + 1, argv + argc },
                              true,                                     // Show help if requested
                              "SCC Test Application 1.0");     // Version string
    }
    catch (...)
    {
        std::cerr << "Invalid command line parameter usage. Please use '--help' parameter for more info." << std::endl;
        return EXIT_CODE_ERROR;
    }
    
    using OutputterMap = std::map<std::string, CppUnit::Outputter *>;
    using ListenerMap = std::map<std::string, CppUnit::TestListener *>;
    
    CppUnit::TestResult result;
    CppUnit::TestResultCollector collector;
    
    result.addListener(&collector);
    
    OutputterMap allOutputters;
    allOutputters.insert(std::make_pair("compiler", new CppUnit::CompilerOutputter(&collector, std::cout)));
    allOutputters.insert(std::make_pair("text", new CppUnit::TextOutputter(&collector, std::cout)));
    allOutputters.insert(std::make_pair("xml", new CppUnit::XmlOutputter(&collector, std::cout)));
    allOutputters.insert(std::make_pair("none", nullptr));
    
    ListenerMap  allListeners;
    allListeners.insert(std::make_pair("dots", new CppUnit::TextTestProgressListener()));
    allListeners.insert(std::make_pair("brief", new CppUnit::BriefTestProgressListener()));
    allListeners.insert(std::make_pair("none", nullptr));
    
    // Set default options.
    CppUnit::Outputter * outputter = allOutputters.find("compiler")->second;
    CppUnit::TestListener * listener = allListeners.find("dots")->second;
    
    std::string testMatchPattern = "*";
    
    if (args["--list-all"].asBool() == true)
    {
        auto testList = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
        ListTests(testList);
        return EXIT_CODE_OK;
    }
    
    size_t repeat = args["--repeat"] ? args["--repeat"].asLong() : 1;
    
    if (args["--output-style"])
    {
        auto paramValue = args["--output-style"].asString();
        auto it = allOutputters.find(paramValue);
        if (it == allOutputters.end())
        {
            std::cerr << "Unknown output-style: " << paramValue << std::endl;
            return EXIT_CODE_ERROR;
        }
        outputter = it->second;
    }
    
    if (args["--progress"])
    {
        std::string progress = args["--progress"].asString();
        auto  it = allListeners.find(progress);
        if (it == allListeners.end())
        {
            std::cerr << "Unknown listener: " << progress << std::endl;
            return EXIT_CODE_ERROR;
        }
        listener = it->second;
    }
    
    if (args["--test"])
    {
        testMatchPattern = args["--test"].asString();
    }
    
    if (listener != nullptr)
    {
        result.addListener(listener);
    }
    
    // Run all matching tests.
    RunMatchingTests(CppUnit::TestFactoryRegistry::getRegistry().makeTest(), testMatchPattern, result, repeat);
    
    if (outputter != nullptr)
    {
        outputter->write();
    }
    
    return collector.testErrors() + collector.testFailures();
}

