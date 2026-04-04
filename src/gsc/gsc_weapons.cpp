/**************************************************************************/
/*  gsc_weapons.cpp                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             IW1X-Server-K                              */
/*              https://gitlab.com/kazam0180/iw1x-server-k/               */
/**************************************************************************/
/* See AUTHORS.md                                                         */
/*                                                                        */
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>. */
/**************************************************************************/

#include "gsc.h"

qboolean isValidWeaponId(int id)
{
    int weps = BG_GetNumWeapons();

    if (id > weps || id <= 0 || weps == 0)
        return qfalse;

    return qtrue;
}

// Get a weapon's string property
void gsc_weapons_getweaponstrproperty()
{
    int id;
    char* name;
    char* property;
    char* value;

    if (!stackGetParams("ss", &name, &property)) {
        stackError("gsc_weapons_getweaponstrproperty() one or more arguments is undefined or has a "
                   "wrong type");
        Scr_AddUndefined();
        return;
    }
    id = BG_GetWeaponIndexForName(name);
    if (!isValidWeaponId(id)) {
        Scr_AddUndefined();
        return;
    }

    weaponinfo_t* weapon = BG_GetInfoForWeapon(id);

    if (strcmp(property, "name") == 0) {
        value = weapon->name;
    }
    else if (strcmp(property, "displayName") == 0) {
        value = weapon->displayName;
    }
    else {
        stackError("gsc_weapons_getweaponstrproperty() property %s is either unsupported or invalid", property);
        Scr_AddUndefined();
        return;
    }

    Scr_AddString(value);
    return;
}

// Set a weapon's string property
void gsc_weapons_setweaponstrproperty()
{
    int id;
    char* name;
    char* property;
    char* value;

    if (!stackGetParams("sss", &name, &property, &value)) {
        stackError("gsc_weapons_setweaponstrproperty() one or more arguments is undefined or has a "
                   "wrong type");
        Scr_AddUndefined();
        return;
    }
    id = BG_GetWeaponIndexForName(name);
    if (!isValidWeaponId(id)) {
        Scr_AddUndefined();
        return;
    }

    weaponinfo_t* weapon = BG_GetInfoForWeapon(id);

    if (strcmp(property, "name") == 0) {
        weapon->name = value;
    }
    else if (strcmp(property, "displayName") == 0) {
        weapon->displayName = value;
    }
    else {
        stackError("gsc_weapons_getweaponstrproperty() property %s is either unsupported or invalid", property);
        Scr_AddUndefined();
        return;
    }

    Scr_AddBool(qtrue);
    return;
}

// Get a weapon's integer property
void gsc_weapons_getweaponintproperty()
{
    int id;
    char* name;
    char* property;
    int value = -1;

    if (!stackGetParams("ss", &name, &property)) {
        stackError("gsc_weapons_getweaponintproperty() one or more arguments is undefined or has a "
                   "wrong type");
        Scr_AddUndefined();
        return;
    }
    id = BG_GetWeaponIndexForName(name);
    if (!isValidWeaponId(id)) {
        Scr_AddUndefined();
        return;
    }

    weaponinfo_t* weapon = BG_GetInfoForWeapon(id);

    if (strcmp(property, "maxAmmo") == 0) {
        value = weapon->maxAmmo;
    }
    else if (strcmp(property, "fuseTime") == 0) {
        value = weapon->fuseTime;
    }
    else {
        stackError("gsc_weapons_getweaponintproperty() property %s is either unsupported or invalid", property);
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(value);
    return;
}

// Set a weapon's integer property
void gsc_weapons_setweaponintproperty()
{
    int id;
    char* name;
    char* property;
    int value = -1;

    if (!stackGetParams("ssi", &name, &property, &value)) {
        stackError("gsc_weapons_setweaponintproperty() one or more arguments is undefined or has a "
                   "wrong type");
        Scr_AddUndefined();
        return;
    }
    id = BG_GetWeaponIndexForName(name);
    if (!isValidWeaponId(id)) {
        Scr_AddUndefined();
        return;
    }

    weaponinfo_t* weapon = BG_GetInfoForWeapon(id);

    if (strcmp(property, "maxAmmo") == 0) {
        weapon->maxAmmo = value;
    }
    else if (strcmp(property, "fuseTime") == 0) {
        weapon->fuseTime = value;
    }
    else {
        stackError("gsc_weapons_setweaponintproperty() property %s is either unsupported or invalid", property);
        Scr_AddUndefined();
        return;
    }

    Scr_AddBool(qtrue);
    return;
}
