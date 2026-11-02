#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <format>

#ifndef __cpp_lib_format_ranges

#include <ranges>

namespace compat
{
    struct range_formatter_options
    {
        char open  = '[';
        char close = ']';
        const char* separator = ", ";
    };
}

// Enable for ranges whose value type is already formattable.
template<std::ranges::input_range R, class CharT>
    requires (!std::same_as<R, std::basic_string<CharT>>)
class std::formatter<R, CharT>
{
    std::formatter<std::ranges::range_value_t<R>, CharT> value_formatter_;
    compat::range_formatter_options opts_;

public:
    constexpr auto parse(std::basic_format_parse_context<CharT>& ctx)
    {
        // Forward any format specifiers to the element formatter.
        return value_formatter_.parse(ctx);
    }

    template<class FormatContext>
    auto format(const R& range, FormatContext& ctx) const
    {
        auto out = ctx.out();

        *out++ = static_cast<CharT>(opts_.open);

        bool first = true;
        for (const auto& value : range)
        {
            if (!first)
            {
                for (const char* p = opts_.separator; *p; ++p)
                    *out++ = static_cast<CharT>(*p);
            }

            out = value_formatter_.format(value, ctx);
            first = false;
        }

        *out++ = static_cast<CharT>(opts_.close);

        return out;
    }
};

#endif

#endif // FORMAT_HPP
