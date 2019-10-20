#include "Player.h"

void Player::bindToLua(lua_State* luaState)
{
    luabind::module(luaState)
    [
        luabind::class_<Player>("Player")
        .def(luabind::constructor<>())
        .def("getX", (float(Player::*)())& Player::getX)
        .def("getY", (float(Player::*)())& Player::getY)
        .def("getXVelocity", (float(Player::*)())& Player::getXVelocity)
        .def("getYVelocity", (float(Player::*)())& Player::getYVelocity)
        .def("getState", (std::string(Player::*)())& Player::getState)
        .def("setX", (void(Player::*)(float))& Player::setX)
        .def("setY", (void(Player::*)(float))& Player::setY)
        .def("setXVelocity", (void(Player::*)(float))& Player::setXVelocity)
        .def("setYVelocity", (void(Player::*)(float))& Player::setYVelocity)
        .def("setState", (void(Player::*)(std::string))& Player::setState)

//        .def("getHealth", (int(Player::*)())& Player::getHealth)
//        .def("getMaxHealth", (int(Player::*)())& Player::getMaxHealth)
//        .def("setHealth", (void(Player::*)(int))& Player::setHealth)
//        .def("setMaxHealth", (void(Player::*)(int))& Player::setMaxHealth)
//        .def("setUnderAttack", (void(Player::*)(bool))& Player::setUnderAttack)
//        .def("isUnderAttack", (bool(Player::*)())& Player::isUnderAttack)
//        .def("setDead", (void(Player::*)(bool))& Player::setDead)
//        .def("isDead", (bool(Player::*)())& Player::isDead)
//        .def("setImmuneToDamage", (void(Player::*)(bool))& Player::setImmuneToDamage)
//        .def("isImmuneToDamage", (bool(Player::*)())& Player::isImmuneToDamage)

    ];
}





