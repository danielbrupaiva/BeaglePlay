#pragma once
#include <iostream>
#include <map>

namespace Core {
class User
{
public:
    enum class eSecurity_level{ADMIN,SUPERVISOR,USER};
private:
    uint32_t m_id;
    std::string m_name;
    std::string m_password;
    eSecurity_level m_security_level;
    bool m_is_logged;
public:
    explicit User(){};
    explicit User(const uint32_t _id,
                  const std::string_view _name,
                  const std::string_view _password,
                  const eSecurity_level _security_level = eSecurity_level::USER,
                  const bool _is_logged = false)
        : m_id{_id}, m_name{_name}, m_password{_password}, m_security_level{_security_level}, m_is_logged{_is_logged}
    {};
    ~User(){};

    void set_user(const int _id,
                  const std::string& _name,
                  const std::string& _password,
                  const eSecurity_level _security_level,
                  const bool _is_logged = false )
    {
        set_id(_id);
        set_name(_name);
        set_password(_password);
        set_security_level(_security_level);
        set_is_logged(_is_logged);
    };

    void set_user(const int _id,
                  const std::string& _name,
                  const std::string& _password,
                  const unsigned int _security_level,
                  const bool _is_logged = false )
    {
        set_id(_id);
        set_name(_name);
        set_password(_password);
        set_security_level(_security_level);
        set_is_logged(_is_logged);
    };

    void reset(){
        set_id(0);
        set_name("");
        set_password("");
        set_security_level(User::eSecurity_level::USER);
        set_is_logged(false);
    };
    /*Getters and setters*/
    inline int get_id() const { return m_id; };
    inline void set_id(int newId) { m_id = newId; };

    inline std::string get_name() const { return m_name; };
    inline void set_name(const std::string &_name) { m_name = _name; };

    inline std::string get_password() const { return m_password; };
    inline void set_password(const std::string &_password) { m_password = _password; };

    inline User::eSecurity_level get_security_level() const { return m_security_level; };
    inline void set_security_level(User::eSecurity_level _security_level) { m_security_level = _security_level; };
    inline void set_security_level(unsigned int _security_level)
    {
        std::map<int, User::eSecurity_level> security_level_map = {
            { 0, User::eSecurity_level::ADMIN     },
            { 1, User::eSecurity_level::SUPERVISOR},
            { 2, User::eSecurity_level::USER      }};

        m_security_level = security_level_map[_security_level];
    };

    inline bool get_is_logged() const { return m_is_logged; };
    inline void set_is_logged(bool newIs_logged) { m_is_logged = newIs_logged; };

};
};//namespace Core
