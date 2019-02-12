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

#include "Application.h"
#include "HTTPServer.h"
#ifdef _WIN32
#include "ControlHandlerRegistration.h"
#endif
#include <algorithm>

namespace Nemu
{

std::mutex Application::sm_applicationsMutex;
std::set<Application*> Application::sm_applications;

void Application::Observer::onApplicationStarting(const Application& source)
{
}

void Application::Observer::onApplicationStarted(const Application& source)
{
}

void Application::Observer::onApplicationStopping(const Application& source)
{
}

void Application::Observer::onApplicationStopped(const Application& source)
{
}

void Application::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

void Application::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

void Application::Observers::notifyApplicationStarting(const Application& source)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onApplicationStarting(source);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Application::Observers::notifyApplicationStarted(const Application& source)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onApplicationStarted(source);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Application::Observers::notifyApplicationStopping(const Application& source)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onApplicationStopping(source);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Application::Observers::notifyApplicationStopped(const Application& source)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onApplicationStopped(source);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Application::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return o.first.expired();
        }
    );
    m_observers.erase(it, m_observers.end());
}

Application::Application(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error)
{
    m_observers.add(observer);

    m_servers.emplace_back(std::make_shared<HTTPServer>(configuration.numberOfThreads(), configuration.address(),
        configuration.port(), observer, error));

    std::lock_guard<std::mutex> guard(sm_applicationsMutex);
    sm_applications.insert(this);
}

Application::~Application()
{
    std::lock_guard<std::mutex> guard(sm_applicationsMutex);
    sm_applications.erase(this);
}

void Application::start()
{
    m_observers.notifyApplicationStarting(*this);

#ifdef _WIN32
    m_controlHandlerRegistration = std::make_unique<ControlHandlerRegistration>();
#endif

    // First we start all the servers, note that the Server::start()
    // function does not block
    for (std::shared_ptr<Server>& server : m_servers)
    {
        server->start();
    }

    m_observers.notifyApplicationStarted(*this);

    // By default we want the Application::start() function to block
    // so we call Server::join() on all the servers
    for (std::shared_ptr<Server>& server : m_servers)
    {
        server->join();
    }

    m_observers.notifyApplicationStopped(*this);
}

void Application::stop()
{
    m_observers.notifyApplicationStopping(*this);

    for (std::shared_ptr<Server>& server : m_servers)
    {
        server->stop();
    }

#ifdef _WIN32
    m_controlHandlerRegistration.reset();
#endif
}

void Application::StopAllApplications()
{
    std::lock_guard<std::mutex> guard(sm_applicationsMutex);
    for (Application* app : Application::sm_applications)
    {
        app->stop();
    }
}

Application::Observers& Application::observers()
{
    return m_observers;
}

}