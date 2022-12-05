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

//template<typename Type, typename... Tail, typename Base>
//     requires std::is_polymorphic_v<Base>
//inline std::unique_ptr<std::common_type_t<Type, Tail...>> find_cast(std::unique_ptr<Base>&& ptr)
//{
//    if(auto* casted = cast_to<Type>(std::move(ptr)); casted)
//    {
//        return std::make_unique<Type>(casted);
//    }

//    return find_cast<Tail...>(std::move(ptr));
//}

//template<typename Type, typename Base>
//     requires std::is_polymorphic_v<Base>
//inline std::unique_ptr<Type> find_cast(std::unique_ptr<Base>&& ptr)
//{
//    return cast_to<Type>(std::move(ptr));
//}

//template<typename Type, typename... Tail, typename Base>
//     requires std::is_polymorphic_v<Base>
//inline std::common_type_t<Type, Tail...> find_cast(const Base& ref)
//{
//    if(const auto& casted = dynamic_cast<Type&>(ref); casted)
//    {
//        return casted;
//    }

//    return find_cast<Tail...>(ref);
//}

//template<typename Base>
//     requires std::is_polymorphic_v<Base>
//inline auto find_cast(const Base&)
//{
//    throw std::bad_cast();
//}

#endif // CASTING_H
