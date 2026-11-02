#ifndef INCLUDE_OVERLOADS_HPP
#define INCLUDE_OVERLOADS_HPP

template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };

// deduction guide required for C++17, but not for C++20 and later
// C++20 can create an aggregate deduction candidate
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

#endif // INCLUDE_OVERLOADS_HPP
