/**************************************************************************/
/*  gsc_entity.cpp                                                        */
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

void gsc_entity_setbounds(scr_entref_t ref)
{
    int id = ref.entnum;
    float width, height;

    if (!stackGetParams("ff", &width, &height)) {
        stackError("gsc_entity_setbounds() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    gentity_t* entity = &g_entities[id];

    vec3_t mins = {-height, -width, -width};
    vec3_t maxs = {width, width, height};

    VectorCopy(mins, entity->r.mins);
    VectorCopy(maxs, entity->r.maxs);

    Scr_AddBool(qtrue);
}

void gsc_entity_setclipmask(scr_entref_t ref)
{
    int id = ref.entnum;
    gentity_t* ent = &g_entities[id];

    ent->clipmask = Scr_GetInt(0);
    Scr_AddBool(qtrue);
}

void gsc_entity_getclipmask(scr_entref_t ref)
{
    int id = ref.entnum;
    gentity_t* ent = &g_entities[id];

    Scr_AddInt(ent->clipmask);
}

void gsc_entity_showtoplayer(scr_entref_t ref) // TODO: try like cod2rev instead
{
    int id = ref.entnum;
    gentity_t* clientEnt;
    gentity_t* pEnt;

    pEnt = &g_entities[id];
    if (Scr_GetType(0) == STACK_UNDEFINED) {
        pEnt->r.svFlags &= ~SVF_SINGLECLIENT;
        pEnt->r.singleClient = 0;
        Scr_AddBool(qtrue);
        return;
    }

    clientEnt = Scr_GetEntity(0);
    if (clientEnt->s.number >= MAX_CLIENTS) {
        stackError("gsc_entity_showtoplayer() param must be a client entity");
        return;
    }

    pEnt->r.svFlags |= SVF_SINGLECLIENT;
    pEnt->r.singleClient = clientEnt->s.number;

    Scr_AddBool(qtrue);
}
