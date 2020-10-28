/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "Environment.h"
#include <string>
#include <cstring>

namespace Ishiko
{
namespace Process
{

Environment::Environment()
{
    m_variables.push_back(nullptr);
}

Environment::Environment(const CurrentEnvironment& env)
{
    std::map<std::string, std::string> variables = env.ToMap();
    m_variables.reserve(variables.size());
    for (const auto& variable : variables)
    {
        char* entry = new char[variable.first.size() + variable.second.size() + 2];
        memcpy(entry, variable.first.c_str(), variable.first.size());
        entry[variable.first.size()] = '=';
        memcpy(entry + variable.first.size() + 1, variable.second.c_str(), variable.second.size() + 1);
        m_variables.push_back(entry);
    }
}

Environment::Environment(const Environment& other)
{
    m_variables.reserve(other.m_variables.size());
    for (size_t i = 0; i < other.m_variables.size() - 1; ++i)
    {
        m_variables.push_back(strdup(other.m_variables[i]));
    }
    m_variables.push_back(nullptr);
}

Environment::~Environment()
{
    for (const char* entry : m_variables)
    {
        delete[] entry;
    }
}

bool Environment::find(const std::string& name, std::string& value) const
{
    for (const char* entry : m_variables)
    {
        if ((entry != nullptr) && (memcmp(entry, name.c_str(), name.size()) == 0))
        {
            if (entry[name.size()] == '=')
            {
                value = entry + name.size() + 1;
                return true;
            }
        }
    }
    return false;
}

void Environment::set(const char* name, const char* value)
{
    std::string entry = name;
    entry += "=";
    entry += value;
    m_variables.insert(m_variables.end() - 1, strdup(entry.c_str()));
}

char** Environment::toEnvironmentArray()
{
    return m_variables.data();
}

std::vector<char> Environment::toEnvironmentBlock() const
{
    std::vector<char> result;

    if (m_variables.size() == 1)
    {
        result.push_back('\0');
    }
    else
    {
        for (size_t i = 0; i < (m_variables.size() - 1); ++i)
        {
            const char* entry = m_variables[i];
            result.insert(result.end(), entry, entry + strlen(entry) + 1);
        }
    }

    result.push_back('\0');

    return result;
}

}
}
