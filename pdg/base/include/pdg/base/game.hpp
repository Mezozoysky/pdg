#pragma once


namespace pdg::base
{


class Game
{
public:
    Game();
    Game(Game const & other) = delete;
    Game(Game && other) noexcept = default;
    ~Game() = default;

    Game & operator=(Game const & other) = delete;
    Game & operator=(Game && other) = default;
};


// template/inline members


} // namspace pdg::base
