# ce_utils

You need to use the githubusercontent Url for this to work.

```c++
#include <https://raw.githubusercontent.com/schuhr/ce_utils/master/include/format.hpp>
```

## format.hpp

- range formatting support for C++20

## lifetime.hpp

- `Lifetime` helper type that logs construction, copy/move, assignment, and destruction.
- useful for move-semantics demos and object lifetime tracing in examples.
- `CE_UTILS_DISABLE_NOEXCEPT` can be defined to remove `noexcept` from move operations.


## overloaded.hpp

- `Overloaded` utility to combine multiple callables into one overload set.
- intended for visitor patterns (for example with `std::visit`).


