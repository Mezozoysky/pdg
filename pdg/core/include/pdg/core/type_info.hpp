#pragma once

#include <pdg/core/macros.hpp>

#include <string>

namespace pdg::core
{

class TypeInfo
{
public:
    TypeInfo() noexcept;
    explicit TypeInfo(char const * const typeName, TypeInfo const * const baseTypeInfo = nullptr) noexcept;
    virtual ~TypeInfo() noexcept = default;

    bool isValid() const noexcept
    {
        return mTypeName != nullptr;
    }

    inline operator bool() const noexcept
    {
        return isValid();
    }

    inline char const * const getTypeName() const noexcept
    {
        return mTypeName;
    }

    inline TypeInfo const * const baseTypeInfo() const noexcept
    {
        return mBaseInfo;
    }

private:
    char const * const mTypeName;
    TypeInfo const * const mBaseInfo;
};


#define PDG_BASE_CLASS_TYPE_INFO_DECL                              \
public:                                                            \
    inline static core::TypeInfo const * const getTypeInfoStatic() \
    {                                                              \
        return &mTypeInfo;                                         \
    }                                                              \
                                                                   \
    inline static char const * const getTypeNameStatic()           \
    {                                                              \
        return mTypeInfo.getTypeName();                            \
    }                                                              \
                                                                   \
    virtual core::TypeInfo const * const getTypeInfo() const       \
    {                                                              \
        return &mTypeInfo;                                         \
    }                                                              \
                                                                   \
    virtual char const * const getTypeName() const                 \
    {                                                              \
        return mTypeInfo.getTypeName();                            \
    }                                                              \
                                                                   \
private:                                                           \
    static core::TypeInfo mTypeInfo


#define PDG_CLASS_TYPE_INFO_DECL                                      \
public:                                                               \
    inline static core::TypeInfo const * const getTypeInfoStatic()    \
    {                                                                 \
        return &mTypeInfo;                                            \
    }                                                                 \
                                                                      \
    inline static char const * const getTypeNameStatic()              \
    {                                                                 \
        return mTypeInfo.getTypeName();                               \
    }                                                                 \
                                                                      \
    virtual core::TypeInfo const * const getTypeInfo() const override \
    {                                                                 \
        return &mTypeInfo;                                            \
    }                                                                 \
                                                                      \
    virtual char const * const getTypeName() const override           \
    {                                                                 \
        return mTypeInfo.getTypeName();                               \
    }                                                                 \
                                                                      \
private:                                                              \
    static core::TypeInfo mTypeInfo


#define PDG_BASE_CLASS_TYPE_INFO_DEF(type) \
    core::TypeInfo type::mTypeInfo(PDG_STRINGIFY_EXPR(type))

#define PDG_BASE_CLASS_TYPE_INFO_NAME_DEF(type, name) \
    core::TypeInfo type::mTypeInfo(name)


#define PDG_CLASS_TYPE_INFO_DEF(type, baseType) \
    core::TypeInfo type::mTypeInfo(PDG_STRINGIFY_EXPR(type), baseType::getTypeInfoStatic())


#define PDG_CLASS_TYPE_INFO_NAME_DEF(type, baseType, name) \
    core::TypeInfo type::mTypeInfo(name, baseType::getTypeInfoStatic())


} // namespace pdg::core
