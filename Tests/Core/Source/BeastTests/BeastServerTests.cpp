/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "BeastServerTests.h"
#include "../Helpers/TestRoutes.h"
#include "../Helpers/TestServerObserver.h"
#include "Beast/BeastServer.h"
#include "Ishiko/HTTP/HTTPClient.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::TestFramework;

void BeastServerTests::AddTests(TestSequence& testSequence)
{
    TestSequence* beastServerTestSequence = new TestSequence("BeastServer tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *beastServerTestSequence);

    new HeapAllocationErrorsTest("start test 1", StartTest1, *beastServerTestSequence);

    new FileComparisonTest("Request test 1", RequestTest1, *beastServerTestSequence);
}

TestResult::EOutcome BeastServerTests::CreationTest1()
{
    Nemu::Routes routes;
    std::shared_ptr<Nemu::Server::Observer> observer;
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, observer, error);
    if (!error)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome BeastServerTests::StartTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    TestRoutes routes;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, observer, error);
    if (!error)
    {
        server.start();
        server.stop();
        server.join();

        if ((routes.visitedRoutes().size() == 0) && (observer->connectionEvents().size() == 0))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome BeastServerTests::RequestTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BeastTests/BeastServerTests_RequestTest1.txt");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BeastTests/BeastServerTests_RequestTest1.txt");

    TestRoutes routes;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, observer, error);
    if (!error)
    {
        server.start();

        Ishiko::HTTP::HTTPClient client;
        std::ofstream responseFile(outputPath.string());
        client.get("127.0.0.1", 8088, "/", responseFile, error);
        responseFile.close();

        server.stop();
        server.join();

        if (!error)
        {
            const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
                observer->connectionEvents();
            if ((events.size() == 2) && (std::get<0>(events[0]) == TestServerObserver::eConnectionOpened) &&
                (std::get<1>(events[0]) == &server) && (std::get<2>(events[0]).substr(0, 10) == "127.0.0.1:") &&
                (std::get<0>(events[1]) == TestServerObserver::eConnectionClosed) &&
                (std::get<1>(events[1]) == &server) && (std::get<2>(events[0]) == std::get<2>(events[1])))
            {
                if ((routes.visitedRoutes().size() == 1) && (routes.visitedRoutes()[0] == "/"))
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}
