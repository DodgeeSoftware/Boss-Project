#include "Boss.h"

void Boss::bind(lua_State* luaState)
{
    luabind::module(luaState)
    [
        luabind::class_<Boss>("Boss")
        .def(luabind::constructor<>())
        .def("getX", (float(Boss::*)())& Boss::getX)
        .def("getY", (float(Boss::*)())& Boss::getY)
        .def("getXVelocity", (float(Boss::*)())& Boss::getXVelocity)
        .def("getYVelocity", (float(Boss::*)())& Boss::getYVelocity)
        .def("getState", (std::string(Boss::*)())& Boss::getState)
        .def("getHealth", (int(Boss::*)())& Boss::getHealth)
        .def("getMaxHealth", (int(Boss::*)())& Boss::getMaxHealth)
        .def("setHealth", (void(Boss::*)(int))& Boss::setHealth)
        .def("setMaxHealth", (void(Boss::*)(int))& Boss::setMaxHealth)
        .def("setX", (void(Boss::*)(float))& Boss::setX)
        .def("setY", (void(Boss::*)(float))& Boss::setY)
        .def("setXVelocity", (void(Boss::*)(float))& Boss::setXVelocity)
        .def("setYVelocity", (void(Boss::*)(float))& Boss::setYVelocity)
        .def("setState", (void(Boss::*)(std::string))& Boss::setState)

        .def("setUnderAttack", (void(Boss::*)(bool))& Boss::setUnderAttack)
        .def("isUnderAttack", (bool(Boss::*)())& Boss::isUnderAttack)
        .def("setDead", (void(Boss::*)(bool))& Boss::setDead)
        .def("isDead", (bool(Boss::*)())& Boss::isDead)
        .def("setImmuneToDamage", (void(Boss::*)(bool))& Boss::setImmuneToDamage)
        .def("isImmuneToDamage", (bool(Boss::*)())& Boss::isImmuneToDamage)

    ];
}
