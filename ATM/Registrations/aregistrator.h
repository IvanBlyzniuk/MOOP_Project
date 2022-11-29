#ifndef IREGISTRATOR_H
#define IREGISTRATOR_H

template<typename AbstractProduct>
class ARegistrator
{
public:
    using product_abstract_type = AbstractProduct;
public:
    virtual ~ARegistrator() = default;
public:
    void make_registration(const product_abstract_type&) const;
    void remove_registration(const product_abstract_type&) const;
    bool can_be_registered(const product_abstract_type&) const noexcept;
private:
    virtual void do_make_registration(const product_abstract_type&) const          = 0;
    virtual void do_remove_registration(const product_abstract_type&) const        = 0;
    virtual bool do_can_be_registered(const product_abstract_type&) const noexcept = 0;
};

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
make_registration(const product_abstract_type& info) const -> void
{
    return do_make_registration(info);
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
remove_registration(const product_abstract_type& info) const -> void
{
    return do_remove_registration(info);
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::
can_be_registered(const product_abstract_type& info) const noexcept -> bool
{
    return do_can_be_registered(info);
}

#endif // IREGISTRATOR_H
