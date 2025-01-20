#pragma once

#include <string>
#include <set>

namespace pdg::log
{


class Category
{
public:
    explicit Category(std::string_view name);
    ~Category() noexcept = default;

    friend bool operator<(Category const &, Category const &);
    friend bool operator==(Category const &, Category const &);
    friend bool operator!=(Category const &, Category const &);

    inline std::string const & getName() const noexcept;

private:
    std::string mName;
};


static Category const DEFAULT{"default"};


// inline members

inline bool operator<(Category const & a, Category const & b)
{
    return (a.mName < b.mName);
}


inline bool operator==(Category const & a, Category const & b)
{
    return (a.mName == b.mName);
}


inline bool operator!=(Category const & a, Category const & b)
{
    return !(a == b);
}


inline std::string const & Category::getName() const noexcept
{
    return mName;
}


} // namespace pdg::log

