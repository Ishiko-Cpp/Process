/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CHILDPROCESS_H_
#define _ISHIKO_PROCESS_CHILDPROCESS_H_

#include "Environment.h"
#include <Ishiko/Errors.h>
#if defined(__linux__)
#include <sys/types.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#endif

namespace Ishiko
{
namespace Process
{

class ChildProcess
{
public:
    static ChildProcess Spawn(const std::string& commandLine);
    static ChildProcess Spawn(const std::string& commandLine, Error& error) noexcept;
    static ChildProcess Spawn(const std::string& commandLine, const Environment& environment);
    static ChildProcess Spawn(const std::string& commandLine, const Environment& environment, Error& error) noexcept;

    ChildProcess();
#if defined(__linux__)
    ChildProcess(pid_t pid);
#elif defined(_WIN32)
    ChildProcess(HANDLE nativeHandle);
#endif
    ChildProcess(const ChildProcess& other) = delete;
    ChildProcess(ChildProcess&& other) noexcept;
    ~ChildProcess();

    ChildProcess& operator=(const ChildProcess& other) = delete;
    ChildProcess& operator=(ChildProcess&& other) noexcept;

#if defined(__linux__)
    void assign(pid_t pid);
#elif defined(_WIN32)
    void assign(HANDLE nativeHandle);
#endif

    void waitForExit();
    void kill(int exitCode) const;
    int exitCode() const;

private:
#if defined(__linux__)
    pid_t m_pid;
    int m_status;
#elif defined(_WIN32)
    HANDLE m_handle;
#endif
};

}
}

#include "linkoptions.h"

#endif
