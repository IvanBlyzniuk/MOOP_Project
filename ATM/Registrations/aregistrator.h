#ifndef IREGISTRATOR_H
#define IREGISTRATOR_H

template<typename AbstractProduct>
class ARegistrator
{
public:
    using product_abstract_type = AbstractProduct;
    using product_key_type = typename product_abstract_type::key_type;
    using product_login_info = typename product_abstract_type::login_info_type;
    using product_common_info = typename product_abstract_type::common_info_type;
public:
    virtual ~ARegistrator() = default;
public:
    void make_registration(const product_abstract_type&) const;
    void remove_registration(const product_key_type&) const;
    bool can_be_registered(const product_key_type&) const noexcept;
private:
    virtual void do_make_registration(const product_abstract_type&) const          = 0;
    virtual void do_remove_registration(const product_key_type&)    const          = 0;
    virtual bool do_can_be_registered(const product_key_type&)      const noexcept = 0;
};

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
make_registration(const product_abstract_type& info) const -> void
{
    return do_make_registration(info);
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
remove_registration(const product_key_type& info) const -> void
{
    return do_remove_registration(info);
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
can_be_registered(const product_key_type& info) const noexcept -> bool
{
    return do_can_be_registered(info);
}

#endif // IREGISTRATOR_H
