#include "amanager.h"
#include "Exceptions\inputexception.h"

AManager::AManager(const info_type& info) :
    _info(info)
{
    if(!check_input())
    {
        throw InputException("Incorrect input to AManager.");
    }
}

auto AManager::login() const noexcept -> const text_type&
{
    return _info.Login;
}

auto AManager::password() const noexcept -> const text_type&
{
    return _info.Password;
}

auto AManager::set_login(const text_type& nval) -> void
{
    _info.Login = nval;
}

auto AManager::set_password(const text_type& nval) -> void
{
    _info.Password = nval;
}

auto AManager::check_input() const noexcept -> bool
{
    return false; //TODO provide a check
}
