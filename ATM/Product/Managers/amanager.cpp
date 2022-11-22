#include "amanager.h"
#include "Exceptions\inputexception.h"

AManager::AManager(const text_type& login, const text_type& password) :
    _login(login),
    _password(password)
{
    if(!check_input())
    {
        throw InputException("Incorrect input to AManager.");
    }
}

auto AManager::login() const noexcept -> const text_type&
{
    return _login;
}

auto AManager::password() const noexcept -> const text_type&
{
    return _password;
}

auto AManager::set_login(const text_type& nval) -> void
{
    _login = nval;
}

auto AManager::set_password(const text_type& nval) -> void
{
    _password = nval;
}

auto AManager::check_input() const noexcept -> bool
{
    return false; //TODO provide a check
}
