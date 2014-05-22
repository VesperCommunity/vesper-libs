/** \file
 * \author Max Mertens <max.mail@dameweb.de>
 * \section LICENSE
 * Copyright (c) 2014, Max Mertens.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code. */

#include "Console.hpp"

using namespace SphereSim;

std::mutex Console::mutex = {};

Console::Console()
    :color(white), font(light), stream()
{
}

Console::~Console()
{
    flush();
}

void Console::beginFormatting()
{
    stream<<"\x1b[3";
    stream<<color;
    if (font == bold)
    {
        stream<<";1";
    }
    stream<<"m";
}

void Console::endFormatting()
{
    stream<<"\x1b[0m";
}

Console& Console::operator<<(Format f)
{
    if (f != font)
    {
        font = f;
        endFormatting();
        beginFormatting();
    }
    return *this;
}

Console& Console::operator<<(Color c)
{
    if (c > white)
    {
        c = white;
    }
    if (c != color)
    {
        color = c;
        endFormatting();
        beginFormatting();
    }
    return *this;
}

void Console::flush()
{
    std::unique_lock<std::mutex> lock(mutex);
    endFormatting();
    std::string str = stream.str();
    stream.str(std::string());
    beginFormatting();
    std::cout<<std::flush<<str<<std::flush;
}
