#ifndef INCLUDE_LIFETIME_HPP
#define INCLUDE_LIFETIME_HPP

#if defined(CE_UTILS_DISABLE_NOEXCEPT)
#define CE_UTILS_LIFETIME_NOEXCEPT
#else
#define CE_UTILS_LIFETIME_NOEXCEPT noexcept
#endif

#include <iostream>
#include <string>
#include <utility>

namespace ce_utils
{
    struct Lifetime
    {
        std::size_t id;
        std::string label;

        Lifetime()
            : id(next_id_ref()++)
            , label("obj-" + std::to_string(id))
        {
            log("default-construct");
        }

        explicit Lifetime(std::string name)
            : id(next_id_ref()++)
            , label(std::move(name))
        {
            log("construct");
        }

        Lifetime(const Lifetime& other)
            : id(next_id_ref()++)
            , label(other.label + "(copy)")
        {
            log("copy-construct", &other);
        }

        Lifetime(Lifetime&& other) CE_UTILS_LIFETIME_NOEXCEPT
            : id(next_id_ref()++)
            , label(std::move(other.label))
        {
            log("move-construct", &other);
            other.label = "moved-from";
        }

        Lifetime& operator=(const Lifetime& other)
        {
            if (this != &other)
            {
                label = other.label + "(copy-assigned)";
                log("copy-assign", &other);
            }
            return *this;
        }

        Lifetime& operator=(Lifetime&& other) CE_UTILS_LIFETIME_NOEXCEPT
        {
            if (this != &other)
            {
                label = std::move(other.label);
                log("move-assign", &other);
                other.label = "moved-from";
            }
            return *this;
        }

        ~Lifetime()
        {
            log("destruct");
        }

    private:
        static std::size_t& next_id_ref()
        {
            static std::size_t next_id = 0;
            return next_id;
        }

        void log(const char* event, const Lifetime* other = nullptr) const
        {
            std::cout << "[Lifetime] " << event << " id=" << id << " label='" << label << "'";
            if (other != nullptr)
            {
                std::cout << " from id=" << other->id;
            }
            std::cout << '\n';
        }
    };
}

#undef CE_UTILS_LIFETIME_NOEXCEPT

#endif // INCLUDE_LIFETIME_HPP
