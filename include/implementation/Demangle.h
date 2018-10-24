#ifndef METAXXA_IMPLEMENTATION_DEMANGLE_H
#define METAXXA_IMPLEMENTATION_DEMANGLE_H

#include <string>

// TODO: check for abi include

namespace metaxxa::implementation
{
    template <typename T>
    class CVRSaver
    {};

    template <typename T>
    std::string demangle()
    {
        static const char cvr_saver_name[] = "metaxxa::implementation::CVRSaver<";
        static constexpr std::string::size_type cvr_saver_name_length = sizeof(cvr_saver_name) - 1;

        #ifdef _MSC_VER
        // Nothing to do, already demangled
        const char *begin = typeid(CVRSaver<T>).name();
        #else
        // TODO: demangle
        #endif

        const std::string::size_type length = std::strlen(begin);
        const char *end = begin + length;

        if(length > cvr_saver_name_length)
        {
            const char *b = std::strstr(begin, cvr_saver_name);
            if(b)
            {
                b += cvr_saver_name_length;

                while(*b == ' ')
                    ++b;

                const char *e = end - 1;
                while(e > b && *e != '>')
                    --e;

                while(e > b && *(e - 1) == ' ')
                    --e;

                if(b < e)
                {
                    begin = b;
                    end = e;
                }
            }
        }

        return std::string(begin, end);
    }
}

#endif // METAXXA_IMPLEMENTATION_DEMANGLE_H