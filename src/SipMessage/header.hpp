#ifndef CPP_PRACTICE_HEADER_HPP
#define CPP_PRACTICE_HEADER_HPP

#include <type_traits>
#include "fields.h"
#include "verb.h"
#include "status.h"

namespace sip {

    template<bool isRequest>
    class Header;

    template<>
    class Header<true> : public Fields {
    public:
        using is_request = std::true_type;

        void Method(Verb verb);

        void Target(std::string target);

    private:
        Verb m_verb;
        unsigned m_version = 20;
        std::string m_target;
    };

    void Header<true>::Method(Verb verb) {
        m_verb = verb;
    }

    void Header<true>::Target(std::string target) {
        m_target = target;
    }

    template<>
    class Header<false> : public Fields {
    private:
        Status m_status;
        unsigned m_version = 20;
    };

}
#endif //CPP_PRACTICE_HEADER_HPP
