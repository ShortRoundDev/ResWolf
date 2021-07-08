using System;
using System.Collections.Generic;

namespace Edward.Models
{
    unsafe struct UWallToken
    {
        UInt16 wallType;
        byte isDoor;
        byte lockType;
        fixed byte reserved[12];
        char* message;
    }

    unsafe struct UEntityToken
    {
        UInt16 entityId;
        UInt16 x;
        UInt16 y;
        fixed byte reserved[10];
        char* config;
    }

    unsafe struct ULevelToken
    {
        fixed byte waterMark[3];
        byte version;
        UInt16 width;
        UInt16 height;
        UInt64 totalEntities;
        UWallToken* walls;
        UEntityToken* entities;
        fixed byte reserved[24];
    }

    struct SWallToken
    {
        UInt16 wallType;
        byte isDoor;
        byte lockType;
        string message;

        // reserved filled at save-time
    }

    struct SEntityToken
    {
        UInt16 entityId;
        UInt16 x;
        UInt16 y;
        string config;
    }

    struct SLevelToken
    {
        byte version;
        UInt16 width;
        UInt16 height;
        UInt64 totalEntities;
        List<SWallToken> walls;
        List<SEntityToken> entities;
    }
}
