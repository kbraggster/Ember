#pragma once

#ifdef EM_ENABLE_ASSERTS
#define EM_ASSERT(x, ...)                                                                                              \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            EM_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                            \
            __debugbreak();                                                                                            \
        }                                                                                                              \
    }
#define EM_CORE_ASSERT(x, ...)                                                                                         \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            EM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                       \
            __debugbreak();                                                                                            \
        }                                                                                                              \
    }
#else
#define EM_ASSERT(x, ...)
#define EM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)