#ifndef CASTING_H
#define CASTING_H
#include <memory>
#include <type_traits>
#include <tuple>

template<typename Derived, typename Base>
    requires std::is_convertible_v<Derived&, Base&> &&
             std::is_polymorphic_v<Base>
inline std::unique_ptr<Derived> cast_to(std::unique_ptr<Base>&& ptr)
{
    Derived* d = dynamic_cast<Derived*>(ptr.get());
    if (d)
    {
        ptr.release();
        return std::unique_ptr<Derived>(d);
    }
    return nullptr;
}

#endif // CASTING_H
