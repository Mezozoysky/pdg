#pragma once

#include <pdg/base/player.hpp>


namespace pdg::demo
{


class Player : public base::Player
{
public:
    Player(std::string_view appName);
    virtual ~Player() = default;
};


} // namspace pdg::demo
