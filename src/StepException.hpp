#pragma once

#include <exception>


class StepException : public std::exception
{
public:
    int code;
    const char *message;

    StepException(int code, const char* message)
        : code(code), message(message) {}

};
