#ifndef CATCH_MESSAGE_INFO_HPP_INCLUDED
#define CATCH_MESSAGE_INFO_HPP_INCLUDED

#include <catch2/internal/catch_result_type.hpp>
#include <catch2/internal/catch_common.hpp>
#include <catch2/interfaces/catch_interfaces_capture.hpp>

#include <string>

namespace Catch {

    struct MessageInfo {
        MessageInfo(    StringRef const& _macroName,
                        SourceLineInfo const& _lineInfo,
                        ResultWas::OfType _type );

        StringRef macroName;
        std::string message;
        SourceLineInfo lineInfo;
        ResultWas::OfType type;
        unsigned int sequence;

        bool operator == (MessageInfo const& other) const {
            return sequence == other.sequence;
        }
        bool operator < (MessageInfo const& other) const {
            return sequence < other.sequence;
        }
    private:
        static unsigned int globalCount;
    };

} // end namespace Catch

#endif // CATCH_MESSAGE_INFO_HPP_INCLUDED
