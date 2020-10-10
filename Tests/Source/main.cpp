/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests.h"
#include "CommandLineTests.h"
#include "CurrentProcessTests.h"
#include "ProcessTests/ChildProcessTests.h"
#include "ProcessTests/ChildProcessBuilderTests.h"
#include "Ishiko/TestFramework/TestFrameworkCore.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoProcess");

    theTestHarness.environment().setTestDataDirectory("../../TestData");
    theTestHarness.environment().setTestOutputDirectory("../../TestOutput");
    boost::filesystem::create_directories("../../TestOutput");
    theTestHarness.environment().setReferenceDataDirectory("../../ReferenceData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<EnvironmentTests>();
    theTests.append<CommandLineTests>();
    theTests.append<CurrentProcessTests>();
    theTests.append<ChildProcessTests>();
    theTests.append<ChildProcessBuilderTests>();

    return theTestHarness.run();
}
