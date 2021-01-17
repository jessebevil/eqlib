/*
 * MacroQuest2: The extension platform for EverQuest
 * Copyright (C) 2002-2019 MacroQuest Authors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include "../common/Common.h"
#include "Common.h"
#include "Constants.h"
#include "Containers.h"
#include "Items.h"
#include "PlayerClient.h"
#include "SoeUtil.h"

namespace eqlib {

struct SClassInfo
{
	bool CanCast;
	bool PureCaster;
	bool PetClass;
	bool DruidType;
	bool NecroType;
	bool ClericType;
	bool ShamanType;
	bool MercType;
	char RaidColorOrder;
	char* Name;
	char* ShortName;
	char* UCShortName;
};

inline namespace deprecated {
	using CLASSINFO DEPRECATE("Use SClassInfo instead of CLASSINFO") = SClassInfo;
	using PCLASSINFO DEPRECATE("Use SClassInfo instead of CLASSINFO") = SClassInfo*;
}

static SClassInfo ClassInfo[] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0,  "",             "",    ""    }, // unk
	{ 0, 0, 0, 0, 0, 0, 0, 0, 13, "Warrior",      "war", "WAR" }, // war
	{ 1, 1, 0, 0, 0, 1, 0, 0, 2,  "Cleric",       "clr", "CLR" }, // clr
	{ 1, 0, 0, 0, 0, 1, 0, 0, 8,  "Paladin",      "pal", "PAL" }, // pal
	{ 1, 0, 0, 1, 0, 0, 0, 0, 9,  "Ranger",       "rng", "RNG" }, // rng
	{ 1, 0, 0, 0, 1, 0, 0, 0, 11, "Shadowknight", "shd", "SHD" }, // shd
	{ 1, 1, 0, 1, 0, 0, 0, 0, 3,  "Druid",        "dru", "DRU" }, // dru
	{ 0, 0, 0, 0, 0, 0, 0, 0, 6,  "Monk",         "mnk", "MNK" }, // mnk
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0,  "Bard",         "brd", "BRD" }, // brd
	{ 0, 0, 0, 0, 0, 0, 0, 0, 10, "Rogue",        "rog", "ROG" }, // rog
	{ 1, 1, 1, 0, 0, 0, 1, 0, 12, "Shaman",       "shm", "SHM" }, // shm
	{ 1, 1, 1, 0, 1, 0, 0, 0, 7,  "Necromancer",  "nec", "NEC" }, // nec
	{ 1, 1, 0, 0, 0, 0, 0, 0, 14, "Wizard",       "wiz", "WIZ" }, // wiz
	{ 1, 1, 1, 0, 0, 0, 0, 0, 5,  "Mage",         "mag", "MAG" }, // mag
	{ 1, 1, 0, 0, 0, 0, 0, 0, 4,  "Enchanter",    "enc", "ENC" }, // enc
	{ 1, 0, 1, 0, 0, 0, 1, 0, 1,  "Beastlord",    "bst", "BST" }, // bst
	{ 0, 0, 0, 0, 0, 0, 0, 0, 15, "Berserker",    "ber", "BER" }, // ber
	{ 1, 1, 0, 0, 0, 0, 0, 1, 16, "Mercenary",    "mer", "MER" }, // mer
};

enum MOUSE_DATA_TYPES
{
	MD_Unknown        = -1,
	MD_Button0Click   = 0,
	MD_Button1Click   = 1,
	MD_Button0        = 2,
	MD_Button1        = 3,
};

inline namespace deprecated {
	constexpr char* KeyRingWindowParent DEPRECATE("Use pKeyRingWnd instead of looking it up by name") = "KeyRingWnd";
	constexpr char* MountWindowList DEPRECATE("Use pKeyRingWnd instead of looking members up by name") = "KRW_Mounts_List";
	constexpr char* IllusionWindowList DEPRECATE("Use pKeyRingWnd instead of looking members up by name") = "KRW_Illusions_List";
	constexpr char* FamiliarWindowList DEPRECATE("Use pKeyRingWnd instead of looking members up by name") = "KRW_Familiars_list";
	constexpr char* HeroForgeWindowList DEPRECATE("Use pKeyRingWnd instead of looking members up by name") = "KRW_HeroForge_List";
	constexpr char* KeyRingTab DEPRECATE("Use pKeyRingWnd instead of looking members up by name") = "KRW_Subwindows";
}

template <typename T>
inline int EQHeading(T heading)
{
	return static_cast<int>((((heading + 16) % 256) / 32) * 2);
}

// ***************************************************************************
// Structures
// ***************************************************************************

class PopDialogHandler
{
public:
	virtual void DialogResponse(int, int, void*);
};

struct MOUSESPOOF
{
	MOUSE_DATA_TYPES   mdType;
	DWORD              dwData;
	MOUSESPOOF*        pNext;
};

struct MOUSECLICK {
	BYTE Confirm[8];         // DO NOT WRITE TO THIS BYTE
	BYTE Click[8];          // Left = 0, Right = 1, etc
};
using PMOUSECLICK = MOUSECLICK*;

struct [[offsetcomments]] LEADERABILITIES
{
	FORCE_SYMBOLS;

/*0x00*/ DWORD MarkNPC;
/*0x04*/ DWORD NPCHealth;
/*0x08*/ DWORD Unknown0x8;
/*0x0c*/ DWORD DelegateMA;
/*0x10*/ DWORD DelegateMarkNPC;
/*0x14*/ DWORD Unknown0x14;
/*0x18*/ DWORD InspectBuffs;
/*0x1c*/ DWORD Unknown0x1c;
/*0x20*/ DWORD SpellAwareness;
/*0x24*/ DWORD OffenseEnhancement;
/*0x28*/ DWORD ManaEnhancement;
/*0x2c*/ DWORD HealthEnhancement;
/*0x30*/ DWORD HealthRegen;
/*0x34*/ DWORD FindPathPC;
/*0x38*/ DWORD HoTT;
/*0x3c*/
};
using PLEADERABILITIES = LEADERABILITIES*;

struct [[offsetcomments]] USINGSKILL
{
/*0x00*/ int       Skill;
/*0x04*/ void*     Target;
/*0x08*/
};
using PUSINGSKILL = USINGSKILL*;

struct [[offsetcomments]] EQCAMERABASE
{
/*0x00*/ void* vftable;
/*0x04*/ float Y;
/*0x08*/ float X;
/*0x0c*/ float Z;
/*0x10*/ float Orientation_Y;                   // old name Heading
/*0x14*/ float Orientation_X;                   // old name LookAngle
/*0x18*/ float Orientation_Z;
/*0x1c*/ float OldPosition_Y;
/*0x20*/ float OldPosition_X;
/*0x24*/ float OldPosition_Z;
/*0x28*/ float Heading;
/*0x2c*/ float Height;
/*0x30*/ float Pitch;
/*0x34*/ float Distance;
/*0x38*/ float DirectionalHeading;
/*0x3c*/ float SideMovement;
/*0x40*/ float Zoom;                            // old name: ViewAngle
/*0x44*/ bool  bAutoPitch;
/*0x45*/ bool  bAutoHeading;
/*0x46*/ bool  bSkipFrame;
/*0x48*/
};
using PEQCAMERABASE = EQCAMERABASE*;

#define MODEL_LABEL                              0
#define MODEL_LABELINFO                          1
#define MODEL_NULL2                              2
#define MODEL_HELD_R                             3
#define MODEL_HELD_L                             4
#define MODEL_SHIELD                             5
#define MODEL_NULL6                              6

#if 0
// Work in progress...
#define MODEL_HEAD                               0x00
#define MODEL_HEAD_POINT                         0x01
#define MODEL_NULL_1                             0x02
#define MODEL_HELD_R                             0x03
#define MODEL_HELD_L                             0x04
#define MODEL_SHIELD                             0x05
#define MODEL_NULL_2                             0x06
#define MODEL_TUNIC                              0x07
#define MODEL_HAIR                               0x08
#define MODEL_BEARD                              0x09
#define MODEL_CHEST                              0x0a
#define MODEL_GLOVES                             0x0b
#define MODEL_GLOVES2                            0x0c
#endif

// This is the # of spell gems + 1 (zero-based)
constexpr int InnateETA = 12;

enum InvisibleTypes
{
	eAll,
	eUndead,
	eAnimal
};

#define STANDSTATE_STAND                         0x64
#define STANDSTATE_CASTING                       0x66
#define STANDSTATE_BIND                          0x69
#define STANDSTATE_SIT                           0x6E
#define STANDSTATE_DUCK                          0x6F
#define STANDSTATE_FEIGN                         0x73
#define STANDSTATE_DEAD                          0x78

#define MONITOR_SPAWN_X                          1
#define MONITOR_SPAWN_Y                          2
#define MONITOR_SPAWN_Z                          4
#define MONITOR_SPAWN_HEADING                    8
#define MONITOR_SPAWN_SPEEDRUN                   16
#define MONITOR_SPAWN_HPCURRENT                  32

struct SPAWNMONITORINFO
{
	WORD SpawnID;
	float Y;
	float X;
	float Z;
	float Heading;
	float SpeedRun;
	DWORD HPCurrent;
	DWORD MonitorMask;
};
using PSPAWNMONITORINFO = SPAWNMONITORINFO*;

// copy of D3DMATRIX by brainiac dec 16 2015
struct Matrix4x4
{
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

struct SWITCHCLICK
{
	float Y;
	float X;
	float Z;
	float Y1;
	float X1;
	float Z1;
};
using PSWITCHCLICK = SWITCHCLICK*;

enum eMemPoolType
{
	eGlobal,
	eOnDemand,
	eClearOnZone,
};

// this is actually a CActor Class
// actual size: 0x120 3-3-2009
// Size is 0x190 dec 13 2016 live - eqmule
// see Cactor::CActor in EQGraphicsDX9.dll
struct [[offsetcomments]] EQSWITCH
{
/*0x000*/ void*         vfTable;
/*0x004*/ eMemPoolType  MemType;
/*0x008*/ bool          bIsS3DCreated;
/*0x009*/ bool          bHasParentBone;
/*0x00a*/ bool          bUpdateScaledAmbient;
/*0x00c*/ float         ScaledAmbient;
/*0x010*/ float         ScaledAmbientTarget;
/*0x014*/ float         ParticleScaleFactor;
/*0x018*/ float         CollisionSphereScaleFactor;
/*0x01c*/ UINT          UpdateAmbientTick;
/*0x020*/ UINT          InterpolateAmbientTick;
/*0x024*/ void*         pParentActor;             // its a  CActor*
/*0x028*/ void*         pDPVSObject;
/*0x02c*/ float         Y;
/*0x030*/ float         X;
/*0x034*/ float         Z;
/*0x038*/ float         SurfaceNormalY;
/*0x03c*/ float         SurfaceNormalX;
/*0x040*/ float         SurfaceNormalZ;
/*0x044*/ UINT          VisibleIndex;
/*0x048*/ float         Alpha;
/*0x04c*/ bool          bCastShadow;
/*0x04d*/ bool          bNeverClip;
/*0x04e*/ bool          bClientCreated;
/*0x050*/ float         ZOffset;
/*0x054*/ float         EmitterScalingRadius;
/*0x058*/ void*         pDuplicateActor;          // its a  CActor*
/*0x05c*/ bool          bShowParticlesWhenInvisible;
/*0x060*/ void*         pAreaPortalVolumeList;    // CAreaPortalVolumeList*
/*0x064*/ void*         CleanupList;              // a TListNode<CActor*>? not sure
/*0x068*/ BYTE          CleanupListFiller[0xc];
/*0x074*/ void*         pActorApplicationData;    // CActorApplicationData* 74 for sure see 1003AE70
/*0x078*/ EActorType    ActorType;
/*0x07c*/ void*         pTerrainObject;           // CTerrainObject*
/*0x080*/ void*         HighlightData;            // HighlightData*
/*0x084*/ float         yAdjustment1;             // from this point on im not sure - 2013 dec 16
/*0x088*/ float         xAdjustment1;
/*0x08c*/ float         zAdjustment1;
/*0x090*/ float         headingAdjustment1;
/*0x094*/ float         yAdjustment2;
/*0x098*/ float         xAdjustment2;
/*0x09c*/ float         zAdjustment2;
/*0x0a0*/ float         headingAdjustment2;
/*0x0a4*/ float         yAdjustment3;
/*0x0a8*/ float         xAdjustment3;
/*0x0ac*/ float         zAdjustment3;
/*0x0b0*/ float         headingAdjustment3;
/*0x0b4*/ float         adjustments4[3];
/*0x0c0*/ float         adjustments5[4];
/*0x0d0*/ bool          bbHasAttachSRT;
/*0x0d1*/ bool          bDisableDesignOverride;
/*0x0d4*/ int           Unknown0xd4[4];
/*0x0e4*/ Matrix4x4     transformMatrix;          // used for new armor
/*0x124*/ float         Heading;
/*0x128*/ BYTE          Unknown0x12c[0x14];
/*0x13c*/ float         HeightAdjustment;         // this is most likely wrong dec 16 2013 eqmule
/*0x140*/ BYTE          Unknown0x144[0x4c];
/*0x18c*/
};
using PEQSWITCH = EQSWITCH*;


struct [[offsetcomments]] GUILDDATA
{
	FORCE_SYMBOLS;

/*0x00*/ char   Name[0x40];
/*0x40*/ DWORD  ID;
/*0x44*/
};
using PGUILDDATA = GUILDDATA*;

struct [[offsetcomments]] GUILD
{
/*0x00*/ char                Name[0x40];
/*0x40*/ DWORD               ID;                 // maybe this is just a int64 now, not sure needs more investigation.
/*0x44*/ DWORD               ID2;
/*0x48*/ GUILD*              pNext;
/*0x4c*/ GUILD*              pPrev;
/*0x50*/
};
using PGUILD = GUILD*;

// 11-15-11 - ieatacid
// aUnknownGuild the offset below is the guild vftable
// 2016 Oct 11 beta - eqmule (see AB50E4) not sure on size needs more investigation
struct [[offsetcomments]] GUILDS
{
/*0x0000*/ void*             pOneEntryVTable;
/*0x0004*/ BYTE              Unknown0x4[0x4];
/*0x0008*/ DWORD             GuildMemberCount;
/*0x000c*/ GuildMember*      pMember;
/*0x0010*/ BYTE              Unknown0x10[0x51];
/*0x0061*/ char              GuildMotD[0x200];
/*0x0261*/ char              GuildLeader[0x40];
/*0x02a1*/ BYTE              Unknown0x2a1[0x3];
/*0x02a4*/ DWORD             GuildTribute;
/*0x02a8*/ BYTE              Unknown0x2a8[0x8dc1];
/*0x9069*/ char              GuildUrl[0x200];
/*0x9269*/ char              GuildChannelName[0x80];
/*0x92e9*/ BYTE              Unknown0x9e9[0x2f];
/*0x9318*/ GUILD*            pFirst;
/*0x931c*/ GUILD*            pLast;
/*0x9320*/ UINT              GuildListCount;
/*0x9324*/ DWORD             Empty;
/*0x9328*/ GUILD*            GuildList;
/*0x932c*/ DWORD             HashValue;
/*0x9330*/
};
using PGUILDS = GUILDS*;

struct [[offsetcomments]] INTERACTGROUNDITEM
{
	FORCE_SYMBOLS;

/*0x00*/ DWORD DropID;
/*0x04*/ DWORD SpawnID;
/*0x08*/
};
using PINTERACTGROUNDITEM = INTERACTGROUNDITEM;

constexpr int MAX_SPELL_LOADOUT_NAME = 24;

struct [[offsetcomments]] SpellLoadout
{
/*0x00*/ int  SpellId[NUM_SPELL_GEMS];
/*0x38*/ char Name[MAX_SPELL_LOADOUT_NAME + 1];
/*0x51*/ bool inuse;
/*0x52*/ bool changed;
/*0x54*/
};

inline namespace deprecated {
	using SPELLFAVORITE DEPRECATE("Use SpellLoadout instead of SPELLFAVORITE") = SpellLoadout;
	using PSPELLFAVORITE DEPRECATE("Use SpellLoadout* instead of PSPELLFAVORITE") = SpellLoadout*;
}

struct [[offsetcomments]] CMDLIST
{
/*0x00*/ DWORD LocalizedStringID;
/*0x04*/ char* szName;
/*0x08*/ char* szLocalized;
/*0x0c*/ void  (*fAddress)(PSPAWNINFO, char*);
/*0x10*/ DWORD Restriction;
/*0x14*/ DWORD Category;
/*0x18*/ DWORD Flags;
/*0x1c*/
};
using PCMDLIST = CMDLIST*;

struct [[offsetcomments]] EQSOCIAL
{
/*0x000*/ char Name[0x10];
/*0x010*/ char Line[0x5][0x100];
/*0x510*/ BYTE Color;
/*0x514*/ UINT TimerBegin;
/*0x518*/ UINT TimerDuration;
/*0x51c*/
};
using PEQSOCIAL = EQSOCIAL*;

struct EQSOCIALCHANGED
{
	bool bChanged[10][12];
};
using PEQSOCIALCHANGED = EQSOCIALCHANGED*;

struct [[offsetcomments]] EQFRIENDSLIST
{
	FORCE_SYMBOLS;

/*0x0000*/ char Name[0x64][0x40];
/*0x1900*/
};
using PEQFRIENDSLIST = EQFRIENDSLIST*;

struct [[offsetcomments]] AAEFFECTDATA
{
	FORCE_SYMBOLS;

/*0x00*/ int EffectType;
/*0x04*/ int BaseEffect1;
/*0x08*/ int BaseEffect2;
/*0x0c*/ int Slot;
/*0x10*/
};
using PAAEFFECTDATA = AAEFFECTDATA*;

// Size 0xa4    11/15/2011 ieatacid in msg_send_alt_data
// Size 0xa8    06/11/2014 eqmule in msg_send_alt_data
// Size 0xa8    See 4EF12F (msg_send_alt_data) in 2015-09-24
class [[offsetcomments]] CAltAbilityData
{
public:
/*0x00*/ DWORD         Index;
/*0x04*/ bool          bShowInAbilityWindow;               // [0] = enabled flag? everything 1
/*0x05*/ BYTE          bShowInAbilityWindowdPadding[0x3];
/*0x08*/ DWORD         nShortName;
/*0x0c*/ DWORD         nShorterName;
/*0x10*/ DWORD         nName;                              // now a database number
/*0x14*/ DWORD         nDesc;                              // now a database number
/*0x18*/ DWORD         MinLevel;                           // LevelNeeded
/*0x1c*/ DWORD         Cost;                               // Initial Cost or cost the last time you bought a level of it
/*0x20*/ DWORD         ID;                                 // ID of the AA group (/alt activate id)
/*0x24*/ DWORD         CurrentRank;                        // GroupLevel the current rank of this AA first rank is 1 etc
/*0x28*/ DWORD*        RequiredGroups;                     // array of required groups
/*0x2c*/ DWORD*        RequiredGroupLevels;                // array of required group ID;
/*0x30*/ DWORD         Unknown0x30[2];                     // ArrayClass stuff
/*0x38*/ DWORD         prereq_count2;                      // count of next array, which contains rank required
/*0x3c*/ DWORD*        RequiresAbilityPoints;              // this is part of their ArrayClass
/*0x40*/ DWORD         Unknown0x40;                        // ArrayClass stuff
/*0x44*/ DWORD         pointer;                            // ArrayClass stuff
/*0x48*/ DWORD         Type;                               // 1 General 2 Archetype 3 Class 4 special 5 focus
/*0x4c*/ int           SpellID;                            // -1 for no Spell
/*0x50*/ DWORD         Unknown0x50;
/*0x54*/ DWORD         Unknown0x54;                        // this uses the same class as prereqs, so count?
/*0x58*/ DWORD*        reuse_id;
/*0x5c*/ bool          bRefund;
/*0x5d*/ BYTE          bRefundPadding[0x3];
/*0x60*/ DWORD*        TimerIds;                           // ArrayClass of timer ids starts here
/*0x64*/ DWORD         ReuseTimer;                         // in seconds
/*0x68*/ DWORD         Classes;                            // Classes/2 is the actual value we want.
/*0x6c*/ DWORD         MaxRank;                            // so like x/25, this is the 25
/*0x70*/ DWORD         TotalPoints;
/*0x74*/ DWORD         PreviousGroupAbilityId;             // -1 if none, although sometimes it can be -1 when there is ...
/*0x78*/ DWORD         NextGroupAbilityId;                 // ID of the next rank
/*0x7c*/ bool          QuestOnly;                          // vet AA, quest AA
/*0x7d*/ BYTE          QuestOnlypadding[0x3];
/*0x80*/ DWORD         max_charges;                        // charges on expendable AAs (limited use aa's)
/*0x84*/ BOOL          bIgnoreDeLevel;
/*0x88*/ DWORD         Expansion;
/*0x8c*/ DWORD         special_category;                   // 7 is expendable, -1 none
/*0x90*/ bool          bShroud;                            // shrouds are also called "templates"
/*0x91*/ bool          bBetaOnlyAbility;
/*0x92*/ bool          bResetOnDeath;                      // true for lay on hands for example.
/*0x93*/ bool          bAutogrant;                         // true if its an autogrant ability? or if auto grant is enabled? need to check cause this could be useful
/*0x94*/ DWORD         AutoGrantAssociationId;             // Usually the same as normal expansion if enabled
	// this is where a list of Ability Effect Data starts in the packet
/*0x98*/ DWORD         effects_count;                      // Count of spell effects for AA
/*0x9c*/ DWORD**       effects;                            // this is repeated a few times some times depending on list size
/*0xa0*/ BYTE          Unknown0xA0[0x8];                   // part of their internal list class, I need to re that at some point
/*0xa8*/

	EQLIB_OBJECT int GetMercCurrentRank(int);
	EQLIB_OBJECT int GetMercMaxRank(int);
	EQLIB_OBJECT int GetMaxRank();
};
using ALTABILITY = CAltAbilityData;
using PALTABILITY = CAltAbilityData*;

struct [[offsetcomments]] ALTABILITIESLISTMGR
{
	FORCE_SYMBOLS;

/*0x00*/ ALTABILITY* Ability;
/*0x04*/ DWORD Index;
/*0x08*/
};
using PALTABILITIESLISTMGR = ALTABILITIESLISTMGR*;

// NUM_ALT_ABILITIES is now defined before CHARINFO definition in this same header file.
struct [[offsetcomments]] ALTABILITIESLIST
{
	FORCE_SYMBOLS;

/*0x000*/ ALTABILITIESLISTMGR* Abilities[NUM_ALT_ABILITIES_ARRAY];
/*0x7dc*/
};
using PALTABILITIESLIST = ALTABILITIESLIST*;

struct [[offsetcomments]] NEWALTADVMGR
{
	FORCE_SYMBOLS;

/*0x00*/ ALTABILITIESLIST*   AltAbilityList;
/*0x04*/ DWORD               NumAltAbilities;    // NUM_ALT_ABILITIES
/*0x08*/ DWORD               Unknown0x08;        // data here
/*0x0c*/ DWORD               Unknown0x0c;        // data here
/*0x10*/ BYTE                Unknown0x10[0x8];
/*0x18*/
};
using PNEWALTADVMGR = NEWALTADVMGR*;

struct [[offsetcomments]] ALTADVMGR
{
	FORCE_SYMBOLS;

/*0x00*/ NEWALTADVMGR* AltAbilities;
/*0x04*/
};
using PALTADVMGR = ALTADVMGR*;

struct [[offsetcomments]] MERCAADATA
{
/*0x00*/ DWORD nName;                            // I would guess we can find aapoints spent on the ability in this struct as well
/*0x04*/
};
using PMERCAADATA = MERCAADATA*;

struct [[offsetcomments]] MERCAA
{
/*0x00*/ DWORD         Unknown0x00;
/*0x04*/ DWORD         Unknown0x04;
/*0x08*/ MERCAADATA*   Ptr;
/*0x0c*/ DWORD         Unknown0x00c;
/*0x10*/ DWORD         Max;                      // how many AA can be spent on this ability
/*0x14*/
};
using PMERCAA = MERCAA*;

// pinstMercAltAbilities_x
// MercAltAbilities__MercAltAbilities
// Actual Size: 0x478 in eqgame dated oct 04 2013 (see 4A96D4) - eqmule
struct [[offsetcomments]] EQMERCALTABILITIES
{
/*0x000*/ BYTE    Unknown0x000[0x408];
/*0x408*/ PMERCAA MercAAInfo[MERC_ALT_ABILITY_COUNT];  // 12 pointers since there are currently only 12 mercenary aa's
/*0x438*/ BYTE    Unknown0x438[0x40];
/*0x478*/
};
using PEQMERCALTABILITIES = EQMERCALTABILITIES*;

// size 0x98 (3-12-2014)
// size 0x9c 3-18-2015 test see (49A077)
struct [[offsetcomments]] RaidPlayer
{
/*0x00*/ char      Name[EQ_MAX_NAME];
/*0x40*/ char      RaidNote[MAX_RAID_NOTE];
/*0x80*/ int       nLevel;
/*0x84*/ int       nClass;
/*0x88*/ bool      RaidLeader;
/*0x89*/ bool      GroupLeader;
/*0x8a*/ bool      RaidMainAssist;
/*0x8b*/ bool      RaidMarker;
/*0x8c*/ int       MasterLooter;
/*0x90*/ int       GroupNumber;
/*0x94*/ BYTE      Unknown0x94[0x8];            // i guess new master looter is in here...
/*0x9c*/
};
using EQRAIDMEMBER = RaidPlayer;
using PEQRAIDMEMBER = RaidPlayer*;

enum eRaidLootType : int32_t
{
	RaidLootUnknown = 0,
	RaidLootLeaderOnly = 1,
	RaidLootLeaderAndGroupLeader = 2,
	RaidLootAssignments = 3,
};

enum eRaidState : int32_t
{
	RaidStateNotInRaid = 1,
	RaidStateInvited = 2,
	RaidStateInRaid = 4
};

// sizeof(_EQRAID) is 0x3668 (12-09-2009)
// is size calculated by doing instCGuild_x - 4 - instCRaid_x ? 366C
// 0x3668 is locked so if its 4 byte aligned size should be /*0x366c*/ - eqmule Aug 10 2016
// instCRaid_x
// push    13C6h
// mar 18 2015 Test CRaid__ResetRaid eqgame.exe - eqmule
// as for the size... I have no idea...
// maybe 3544h? see 48055F                 mov     [esi+3544h], bl (jun 11 2014)
// 392C in mar 18 205 test? not sure...

// CRaid
struct [[offsetcomments]] EQRAID
{
/*0x0000*/ BYTE              Unknown0x0000[0xe0];
/*0x00e0*/ bool              RaidMemberUsed[MAX_RAID_SIZE];
/*0x0128*/ RaidPlayer        RaidMember[MAX_RAID_SIZE];
/*0x2d08*/ BYTE              Unknown0x2d08[0x4];
/*0x2d0c*/ int               RaidMemberCount;
/*0x2d10*/ char              RaidLeaderName[EQ_MAX_NAME];
/*0x2d50*/ char              RaidMOTD[MAX_RAID_MOTD];
/*0x3150*/ char              Inviter[EQ_MAX_NAME];
/*0x3190*/ eRaidState        Invited;
/*0x3194*/ int               RaidID;                       // not sure
/*0x3198*/ bool              bCreateRaidInvite;
/*0x3199*/ bool              IsRaidLeader;
/*0x319a*/ BYTE              Filler0x319a[0x2];
/*0x319c*/ DWORD             RaidTarget;
/*0x31a0*/ eRaidLootType     LootType;
/*0x31a4*/ char              RaidLooters[MAX_RAID_LOOTERS][EQ_MAX_NAME];
/*0x3664*/ DWORD             TotalRaidMemberLevels;        // TotalRaidMemberLevels/RaidMemberCount=RaidAvgLevel
/*0x3668*/ bool              Locked;
/*0x3669*/ BYTE              Unknown0x3669[0x7];
/*0x3670*/ // <- im sure this is not right but whatever... we got what we came for...
};
using PEQRAID = EQRAID*;

// size 0x19C 3-23-2005
struct [[offsetcomments]] EQGROUP
{
	FORCE_SYMBOLS;

/*0x000*/ BYTE         MemberExists[5];
/*0x005*/ char         MemberName[5][EQ_MAX_NAME];
/*0x145*/ BYTE         Unused[3];
/*0x148*/ SPAWNINFO*   pMember[5];
/*0x15c*/ char         LeaderName[EQ_MAX_NAME];
/*0x19c*/
};
using PEQGROUP = EQGROUP*;

// size 0x08
struct [[offsetcomments]] EQSTRING {
/*0x00*/ DWORD ID;
/*0x04*/ char* String;
/*0x08*/
};
using PEQSTRING = EQSTRING*;

// size 0x10 4-28-2004 lax
struct [[offsetcomments]] EQSTRINGTABLE
{
/*0x00*/ EQSTRING** StringItems;
/*0x04*/ DWORD      Size;
/*0x08*/ int        Count;
/*0x0c*/ DWORD      Unknown0x0c;
/*0x10*/
};

inline namespace deprecated {
	using PEQSTRINGTABLE DEPRECATE("Use EQSTRINGTABLE* instead of PEQSTRINGTABLE") = EQSTRINGTABLE*;
}

// updated by eqmule
// see 7B000C in eqgame.exe dated jul 16 2014
// not sure about size... oh and this is __gWorld_x
struct [[offsetcomments]] connection_t
{
/*0x000*/ void* vtable;
/*0x004*/ BYTE  Unknown0x4[0x110];
/*0x114*/ DWORD Master;
/*0x118*/ DWORD Average;
/*0x11c*/ DWORD Low;
/*0x120*/ DWORD High;
/*0x124*/ DWORD Last;
/*0x128*/
};

inline namespace deprecated {
	using CONNECTION_T DEPRECATE("Use connection_t instead of CONNECTION_T") = connection_t;
	using PCONNECTION_T DEPRECATE("Use connection_t instead of PCONNECTION_T") = connection_t*;
}

enum eDynamicZoneType
{
	eDZT_Unknown,
	eDZT_Expedition,
	eDZT_Tutorial,
	eDZT_Task,
	eDZT_Mission,
	eDZT_Quest
};

struct [[offsetcomments]] DynamicZoneData
{
/*0x00*/ int                DynamicZoneID;
/*0x04*/ int                SetID;
/*0x08*/ eDynamicZoneType   Type;
/*0x0c*/
};

struct [[offsetcomments]] DynamicZoneTimerData
{
/*0x00*/ int                   DataSetID;
/*0x04*/ __time32_t            TimerExpiration;
/*0x08*/ int                   EventID;
/*0x0c*/ int                   DynamicZoneID;
/*0x10*/ DynamicZoneTimerData* pNext;
/*0x14*/
};

struct [[offsetcomments]] DynamicZoneClientTimerData
{
/*0x000*/ char         ExpeditionName[0x80];
/*0x080*/ char         EventName[0x100];
/*0x180*/ __time32_t   TimeStamp;                      // TimeStamp - Util__FastTime = time left
/*0x184*/ int          TimerID;
/*0x188*/ DynamicZoneClientTimerData* pNext;
/*0x18c*/
};

inline namespace deprecated {
	using DZTIMERINFO DEPRECATE("Use DynamicZoneClientTimerData instead of DZTIMERINFO") = DynamicZoneClientTimerData;
	using PDZTIMERINFO DEPRECATE("Use DynamicZoneClientTimerData* instead of PDZTIMERINFO") = DynamicZoneClientTimerData*;
}

enum eDyanicZonePlayerStatus
{
	eStatusUnknown = 0,
	eStatusOnline,
	eStatusOffline,
	eStatusInZone,
	eStatusLinkDead,
};

struct [[offsetcomments]] DynamicZonePlayerInfo
{
/*0x00*/ char                     Name[0x40];                // The usual name length
/*0x40*/ eDyanicZonePlayerStatus  Status;
/*0x44*/ DynamicZonePlayerInfo*   pNext;
/*0x48*/ bool                     bFlagged;                  // Do we meet the requirements?
/*0x49*/ bool                     bCheckedZoneReqs;          // Zone reqs serverside checked?
/*0x4c*/
};

inline namespace deprecated {
	using DZMEMBER DEPRECATE("Use DynamicZonePlayerInfo instead of DZMEMBER") = DynamicZonePlayerInfo;
	using PDZMEMBER DEPRECATE("Use DynamicZonePlayerInfo* instead of PDZMEMBER") = DynamicZonePlayerInfo*;
}

enum eSharedTaskPlayerRole
{
	eSharedTaskRoleNone = 0,
	eSharedTaskRoleLeader
};

// Shared Task Member Info
struct [[offsetcomments]] SharedTaskPlayerInfo
{
/*0x00*/ char                     Name[0x40];
/*0x40*/ int                      ShroudID;
/*0x44*/ eSharedTaskPlayerRole    Role;
/*0x48*/ SharedTaskPlayerInfo*    pNext;
/*0x4c*/

	ALT_MEMBER_GETTER(DWORD, Role, IsLeader);
};

inline namespace deprecated {
	using TASKMEMBER DEPRECATE("Use SharedTaskPlayerInfo instead of TASKMEMBER") = SharedTaskPlayerInfo;
	using PTASKMEMBER DEPRECATE("Use SharedTaskPlayerInfo* instead of PTASKMEMBER") = SharedTaskPlayerInfo*;
}

struct [[offsetcomments]] DynamicZoneSwitchInfo
{
/*0x00*/ int          DZID;
/*0x04*/ int          Type;
/*0x08*/ int          DZSwitchID;
/*0x0c*/ float        SwitchX;
/*0x10*/ float        SwitchY;
/*0x14*/ float        SwitchZ;
/*0x18*/
};

inline namespace deprecated {
	using DZSWITCHINFO DEPRECATE("Use DynamicZoneSwitchInfo instead of DZSWITCHINFO") = DynamicZoneSwitchInfo;
	using PDZSWITCHINFO DEPRECATE("Use DynamicZoneSwitchInfo* instead of PDZSWITCHINFO") = DynamicZoneSwitchInfo*;
	using _DZSWITCHINFO DEPRECATE("Use DynamicZoneSwitchInfo instead of _DZSWITCHINFO") = DynamicZoneSwitchInfo;
}

struct [[offsetcomments]] DynamicZoneCompass
{
/*0x00*/ int          R;
/*0x04*/ int          G;
/*0x08*/ int          B;
/*0x0c*/ float        X;
/*0x10*/ float        Y;
/*0x14*/ float        Z;
/*0x18*/ bool         bVisible;
/*0x1c*/ int          PixelOffset;
/*0x20*/ bool         bInWindow;
/*0x24*/
};

inline namespace deprecated {
	using DZCOMPASS DEPRECATE("Use DynamicZoneCompass instead of DZCOMPASS") = DynamicZoneCompass;
	using PDZCOMPASS DEPRECATE("Use DynamicZoneCompass* instead of PDZCOMPASS") = DynamicZoneCompass*;
}

struct [[offsetcomments]] DynamicZoneClientSwitchInfo : public DynamicZoneSwitchInfo
{
/*0x18*/ DynamicZoneCompass* pCompass;
/*0x1c*/
};

inline namespace deprecated {
	using DZSWITCH DEPRECATE("Use DynamicZoneCompass instead of DZCOMPASS") = DynamicZoneClientSwitchInfo;
	using PDZSWITCH DEPRECATE("Use DynamicZoneCompass instead of DZCOMPASS") = DynamicZoneClientSwitchInfo*;
}

// CDynamicZone size: 0x128
struct [[offsetcomments]] CDynamicZone : public PopDialogHandler
{
	/*0x004*/ uint32_t     NewMemberDZID;
	/*0x008*/ char         NewMemberName[0x40];
	/*0x048*/ bool         bNewSwap;
	/*0x049*/ bool         bNewAssignedToDZ;
	/*0x04a*/ char         LeaderName[0x40];
	/*0x08a*/ char         DZName[0x80];
	/*0x10c*/ int          MaxPlayers;
	/*0x110*/ DynamicZonePlayerInfo* pFirstMember;
	/*0x114*/ DynamicZoneClientTimerData* pFirstTimer;
	/*0x118*/ HashTable<DynamicZoneClientSwitchInfo> Switches;
/*0x128*/
	ALT_MEMBER_GETTER_ARRAY(char, 0x40, LeaderName, Name);
	ALT_MEMBER_GETTER_ARRAY(char, 0x80, DZName, ExpeditionName);
	ALT_MEMBER_GETTER(DynamicZonePlayerInfo*, pFirstMember, pMemberList);
};

inline namespace deprecated {
	using DYNAMICZONE DEPRECATE("Use CDynamicZone instead of DYNAMICZONE") = CDynamicZone;
	using PDYNAMICZONE DEPRECATE("Use CDynamicZone* instead of PDYNAMICZONE") = CDynamicZone*;
}

class UniversalChatProxyHandler;

constexpr int ChatProxy_MaxNameLen = 48;

class [[offsetcomments]] UniversalChatProxy
{
public:
	virtual ~UniversalChatProxy() {}

	EQLIB_OBJECT char* GetChannelName(int channelNumber);

	enum class BuddyStatus
	{
		eFriendRemoved,
		eFriendOffline,
		eFriendOnline,
		eFriendOnlineAway,
		eFriendOnlineInvisible,
		eFriendInGame,
		eFriendInGameAway,
		eFriendInGameInvisible
	};

	struct [[offsetcomments]] BuddyEntry
	{
	/*0x00*/ char          Name[ChatProxy_MaxNameLen];
	/*0x30*/ BuddyStatus   Status;
	/*0x34*/ bool          bInMyNamespace;
	/*0x38*/
	};

	// FIXME: This is off and needs to update updated (members don't align with the functions)
/*0x04*/ UniversalChatProxyHandler* pChatProxyHandler;
/*0x08*/ void*             pUdpManager;             // UdpLibrary::UdpManager
/*0x0c*/ char**            ChannelList;
/*0x10*/ int               ActiveChannels;          // number of channels joined, aka channelcount
/*0x14*/ bool              mAuthenticated;
/*0x15*/ bool              bLoginSent;
/*0x16*/ bool              bInvisible;
/*0x17*/ bool              bFullNotifyMode;
/*0x18*/ void*             UdpConnection;           // UdpLibrary::UdpConnection
/*0x1c*/ char              ChatID[ChatProxy_MaxNameLen];              // "ServerName.CharName"
/*0x4c*/ char              ChatPass[ChatProxy_MaxNameLen];
/*0x7c*/ char              ServerName[ChatProxy_MaxNameLen];          // "ServerName."
/*0xac*/ int               ServerNameLen;
/*0xb0*/ char              Locale[16];
/*0xc0*/ const char*       ChatPrefix;
/*0xc4*/ int               LastDisconnectCheckTime;
/*0xc8*/ BuddyEntry**      BuddyList;
/*0xcc*/ int               BuddyListCount;
/*0xd0*/ ArrayClass<CXStr> IgnoreList;
/*0xe0*/

	EQLIB_OBJECT int GetNumberOfFriends();
	EQLIB_OBJECT const char* GetFriendName(int);
};

using CChatService = UniversalChatProxy;

inline namespace deprecated {
	using FriendEntry DEPRECATE("Use UniversalChatProxy::BuddyEntry instead of FriendEntry") = UniversalChatProxy::BuddyEntry;
	using PCHATSERVICE DEPRECATE("Use UniversalChatProxy* instead of PCHATSERVICE") = UniversalChatProxy*;
	using CHATSERVICE DEPRECATE("Use UniversalChatProxy instead of PCHATSERVICE") = UniversalChatProxy;
}

class [[offsetcomments]] PickZoneTimerHandler
{
public:
	struct PickZoneRecord
	{
		CXStr  ZoneName;
		int    Time;
	};

/*0x00*/ SoeUtil::Array<PickZoneRecord> Records;
/*0x10*/
};

struct [[offsetcomments]] PetitionStatus
{
/*0x00*/ int           ID;
/*0x04*/ int           Priority;                 // todo: check
/*0x08*/ int           State;                    // todo: figure out.
/*0x0c*/ DWORD         ArrivalTime;
/*0x10*/ char          User[0x20];
/*0x30*/ char          Player[0x40];
/*0x70*/ int           NumActive;
/*0x74*/ char          Player2[0x40];
/*0xb4*/ DWORD         TimeStamp;                // not sure what its for
/*0xb8*/
};

inline namespace deprecated {
	using PPETITIONSTATUS DEPRECATE("Use PetitionStatus* instead of PPETITIONSTATUS") = PetitionStatus*;
	using PETITIONSTATUS DEPRECATE("Use PetitionStatus instead of PETITIONSTATUS") = PetitionStatus;
}

// size is 0x170 see 4467A5 in Sep 18 2017 Live
struct [[offsetcomments]] CSINFO
{
/*0x000*/ char         Name[0x40];
/*0x040*/ int          Class;
/*0x044*/ int          Race;
/*0x048*/ BYTE         Level;
/*0x04c*/ int          Class2;
/*0x050*/ int          Race2;
/*0x054*/ int          CurZoneID;
/*0x058*/ BYTE         Sex;
/*0x059*/ BYTE         Face;
/*0x05c*/ ArmorProperties ArmProp[9];            // size /*0x14*/ * 9 = 0xB4
/*0x110*/ DWORD        Tint[9];                  // size 0x24
/*0x134*/ char         TextureType;
/*0x135*/ char         ArmorMaterial;
/*0x136*/ char         ArmorVariation;
/*0x137*/ char         HeadType;
/*0x138*/ int          TattooIndex;
/*0x13c*/ int          FacialAttachmentIndex;
/*0x140*/ int          Deity;
/*0x144*/ int          PrimActor;
/*0x148*/ int          SecdActor;
/*0x14c*/ BYTE         HairColor;
/*0x14d*/ BYTE         BeardColor;
/*0x14e*/ BYTE         LeftEye;
/*0x14f*/ BYTE         RightEye;
/*0x150*/ BYTE         Hair;
/*0x151*/ BYTE         Beard;
/*0x152*/ bool         bCanGoHome;
/*0x153*/ bool         bCanTutorial;
/*0x154*/ int          ParentId;
/*0x158*/ bool         bTooHighLevel;
/*0x159*/ bool         bPreFTP;
/*0x15c*/ long         SomethingLogin;
/*0x160*/ bool         bUseable;
/*0x161*/ bool         bHeroicCharacter;
/*0x162*/ bool         bShrouded;
/*0x164*/ int          Unknown0x164;
/*0x168*/ int          Unknown0x168;
/*0x16c*/ int          Unknown0x16c;
/*0x170*/
};

inline namespace deprecated {
	using PCSINFO DEPRECATE("Use CSINFO* instead of PCSINFO") = CSINFO*;
}

// this struct is actually part of EverQuestInfo struct
struct MQMouseInfo
{
	int X = 0;
	int Y = 0;
	int SpeedX = 0;
	int SpeedY = 0;
	int Scroll = 0;
};

inline namespace deprecated {
	using MOUSEINFO DEPRECATE("Use MQMouseInfo instead of MOUSEINFO") = MQMouseInfo;
	using PMOUSEINFO DEPRECATE("Use MQMouseInfo* instead PMOUSEINFO") = MQMouseInfo*;
}

struct [[offsetcomments]] EVERQUEST
{
/*0x00000*/ BYTE             Unknown[0x2a4];
/*0x002a4*/ UniversalChatProxy* ChatService;
/*0x002a8*/ BYTE             Unknown0x2a8[0x8];
/*0x002b0*/ bool             bJoinedChannel;
/*0x002b1*/ char             ChannelPlayerName[0x100];
/*0x003b1*/ char             ChannelName[0xa][0x30];
/*0x00591*/ BYTE             Unknown0x591[0x3];
/*0x00594*/ DWORD            ChannelNumber[0xa];
/*0x005bc*/ int              ChannelQty;
/*0x005c0*/ void*            pFreeTargetRing;              // PTARGETRING
/*0x005c4*/ DWORD            WorldState;                   // 0 everything is fine, 1 we are getting disconnected 2 player not released from zone
/*0x005c8*/ int              GameState;
/*0x005cc*/ bool             bStopAreaProcessing;
/*0x005cd*/ bool             bRAFEnabled;
/*0x005d0*/ int              ClientOutOfDate;              // I think string ID of popupdialog text (4BAD8A), is client out of date? this func checks it: 4ACD10 see May 12 2020 test exe
/*0x005d8*/ int64_t          ServerTimeSync;
/*0x005e0*/ int64_t          ServerTimeBase;
/*0x005e8*/ int64_t          ServerTimeLastReported;
/*0x005f0*/ bool             bServerTimeHasWrapped;
/*0x005f4*/ float            TargetCameraDistance;
/*0x005f8*/ bool             bUnknown0x5f0;
/*0x005fc*/ int              TotalCharacterSlots;
/*0x00600*/ int              MarketplaceCharacterSlots;
/*0x00604*/ int              Unknown0x5fc;
/*0x00608*/ void*            CampDialog;                   // CPopDialogWnd
/*0x0060c*/ PickZoneTimerHandler pickZoneTimerHandler;     // size 0x10?
/*0x0061c*/ USINGSKILL       UsingSkill;                   // size 0x8
/*0x00624*/ PetitionStatus   PetitionStatus[0x200];        // size 0xb8 * 0x200 = 0x17000
/*0x17624*/ int              TotalQ;                       // see 760EE8 in Sep 18 2017
/*0x17628*/ int              TotalClientPetitions;
/*0x1762c*/ char             ChatText[0x840];
/*0x17e6c*/ int              TrimIdx;                      // correct
/*0x17e70*/ char             ChatChanged;                  // 1 or 0?
/*0x17e71*/ char             Trim[0x40][0x840];            // correct. size 0x40*0x840= 0x21000
/*0x38e74*/ BOOL             bChat;
/*0x38e78*/ int              Unknown0x38E70;
/*0x38e7c*/ int              Red;                          // for sure see 564105 in spe 18 2017 exe
/*0x38e80*/ int              Green;
/*0x38e84*/ int              Blue;
/*0x38e88*/ ArrayClass<CSINFO> pCharSelectPlayerArray;
/*0x38e98*/ // more data
};

inline namespace deprecated {
	using _EVERQUEST DEPRECATE("Use EVERQUEST instead of _EVERQUEST") = EVERQUEST;
	using PEVERQUEST DEPRECATE("Use EVERQUEST* instead of PEVERQUEST") = EVERQUEST*;
}

// EQ Refers to Auras as SOI or "sphere of influence", but we'll just call them Auras.
struct [[offsetcomments]] AuraData
{
/*0x00*/ char         Name[EQ_MAX_NAME];
/*0x40*/ uint32_t     SpawnID;
/*0x44*/ int          Cost;
/*0x48*/ int          IconID;
/*0x4c*/
};

inline namespace deprecated {
	using AURAINFO DEPRECATE("Use AuraData instead of AURAINFO") = AuraData;
	using PAURAINFO DEPRECATE("Use AuraData* instead of PAURAINFO") = AuraData*;
}

struct [[offsetcomments]] ClientAuraManager
{
	FORCE_SYMBOLS;

/*0x00*/ ArrayClass2<AuraData> Auras;
};

inline namespace deprecated {
	using AURAMGR DEPRECATE("Use ClientAuraManager instead of AURAMGR") = ClientAuraManager;
	using PAURAMGR DEPRECATE("Use ClientAuraManager& instead of PAURAMGR") = ClientAuraManager*;
}

struct [[offsetcomments]] MERCSTANCEDATA
{
/*0x00*/ DWORD nStance;
/*0x04*/ DWORD nDbStance;
/*0x08*/
};

struct [[offsetcomments]] MERCSINFO
{
/*0x00*/ DWORD         Unknown0x00;
/*0x04*/ DWORD         nMercCategory;
/*0x08*/ DWORD         nMercDesc;
/*0x0c*/ DWORD         Purchase;                 // in copper
/*0x10*/ DWORD         Upkeep;                   // in copper
/*0x14*/ BYTE          Unknown0x14[0x2c];
/*0x40*/ char          Name[0xC];
/*0x4c*/ BYTE          Unknown0x4c[0x88];
/*0xd4*/
};

// Size 0xD4 in eqgame.exe dated 01 22 2015
struct [[offsetcomments]] MERCSLIST
{
/*0x000*/ MERCSINFO     mercinfo[7];              // is 7 max, even with slots u can buy for sc?
/*0x5cc*/
};

// Actual Size: 0x2fc (See 57117F in eqgame dated dec 10 2013) - eqmule
// CMercenaryInfo__CMercenaryInfo
// this is CMercenaryClientManager
struct [[offsetcomments]] MERCENARYINFO
{
/*0x000*/ BYTE               Unknown0x0[0x110];
/*0x110*/ DWORD              HaveMerc;
/*0x114*/ DWORD              MercState;          // 1 = suspended, 5 = active
/*0x118*/ BYTE               Unknown0x118[0x30];
/*0x148*/ DWORD              ActiveStance;
/*0x14c*/ BYTE               Unknown0x14c[0x10];
/*0x15c*/ char               MercName[0x18];
/*0x174*/ BYTE               Unknown0x174[0x7c];
/*0x1f0*/ int                MercenaryCount;     // how many mercenaries we have
/*0x1f4*/ MERCSLIST*         pMercsList;
/*0x1f8*/ BYTE               Unknown0x1f8[0xc];
/*0x204*/ DWORD              MaxMercsCount;      // max you can have
/*0x208*/ BYTE               Unknown0x208[0x10];
/*0x218*/ DWORD              CurrentMercIndex;
/*0x21c*/ BYTE               Unknown0x21c[0x8];
/*0x224*/ DWORD              MercSpawnId;        // yes its the spawnID of the mercenary
/*0x228*/ BYTE               Unknown0x228[0x30];
/*0x258*/ int                NumStances;
/*0x25c*/ MERCSTANCEDATA**   pMercStanceData;
/*0x260*/ BYTE               Unknown0x260[0x9c];
/*0x2fc*/
};

inline namespace deprecated {
	using PMERCENARYINFO DEPRECATE("Use MERCENARYINFO* instead of PMERCENARYINFO") = MERCENARYINFO*;
}

struct [[offsetcomments]] MERCENARYSTATS
{
	FORCE_SYMBOLS;

/*0x00*/ DWORD        MaxHP;
/*0x04*/ DWORD        CurrHP;
/*0x08*/ DWORD        MaxMana;
/*0x0c*/ DWORD        CurrMana;
/*0x10*/ DWORD        MaxEndurance;
/*0x14*/ DWORD        CurrEndurance;
/*0x18*/ DWORD        AC;
/*0x1c*/ DWORD        Attack;
/*0x20*/ DWORD        Haste;
/*0x24*/ DWORD        STR;
/*0x28*/ DWORD        STA;
/*0x2c*/ DWORD        INT;
/*0x30*/ DWORD        WIS;
/*0x34*/ DWORD        AGI;
/*0x38*/ DWORD        DEX;
/*0x3c*/ DWORD        CHA;
/*0x40*/ DWORD        CombatHPRegen;
/*0x44*/ DWORD        CombatManaRegen;
/*0x48*/ DWORD        CombatEnduranceRegen;
/*0x4c*/ DWORD        HealAmount;
/*0x50*/ DWORD        SpellDamage;
/*0x54*/
};

inline namespace deprecated {
	using PMERCENARYSTATS DEPRECATE("Use MERCENARYSTATS* instead of PMERCENARYSTATS") = MERCENARYSTATS*;
}

enum XTargetTypes
{
	XTARGET_EMPTY_TARGET,
	XTARGET_AUTO_HATER,
	XTARGET_SPECIFIC_PC,
	XTARGET_SPECIFIC_NPC,
	XTARGET_TARGETS_TARGET,
	XTARGET_GROUP_TANK,
	XTARGET_GROUP_TANKS_TARGET,
	XTARGET_GROUP_ASSIST,
	XTARGET_GROUP_ASSIST_TARGET,
	XTARGET_GROUP_PULLER,
	XTARGET_GROUP_PULLER_TARGET,
	XTARGET_GROUP_MARK1,
	XTARGET_GROUP_MARK2,
	XTARGET_GROUP_MARK3,
	XTARGET_RAID_ASSIST1,
	XTARGET_RAID_ASSIST2,
	XTARGET_RAID_ASSIST3,
	XTARGET_RAID_ASSIST1_TARGET,
	XTARGET_RAID_ASSIST2_TARGET,
	XTARGET_RAID_ASSIST3_TARGET,
	XTARGET_RAID_MARK1,
	XTARGET_RAID_MARK2,
	XTARGET_RAID_MARK3,
	XTARGET_MY_PET,
	XTARGET_MY_PET_TARGET,
	XTARGET_MY_MERCENARY,
	XTARGET_MY_MERCENTARY_TARGET
};

inline namespace deprecated {
	using xTargetTypes DEPRECATE("Use XTargetTypes instead of xTargetTypes") = XTargetTypes;
}

constexpr int MAX_XTARGETS = 20;

struct [[offsetcomments]] AGGRODATA
{
	FORCE_SYMBOLS;

/*0x00*/ DWORD         Unknown0x0;
/*0x04*/ BYTE          AggroPct;
/*0x05*/ BYTE          padding[3];
/*0x08*/
};

inline namespace deprecated {
	using PAGGRODATA DEPRECATE("Use AGGRODATA* instead of PAGGRODATA") = AGGRODATA*;
}

// size 0xe4 11-28-12 - ieatacid (in GetAggroInfo)
// size 0xfc see 422F94 in 20 Aug 2015
struct [[offsetcomments]] AGGROINFO
{
	FORCE_SYMBOLS;

/*0x00*/ AGGRODATA     aggroData[0x1e];
/*0xf0*/ DWORD         AggroLockID;              // this can be 0, I dont know what it is...
/*0xf4*/ DWORD         AggroTargetID;            // this is id of whoever we are fighting
/*0xf8*/ DWORD         AggroSecondaryID;         // this is id of whoever the npc is fighting
/*0xfc*/
};

inline namespace deprecated {
	using PAGGROINFO DEPRECATE("Use AGGROINFO* instead of PAGGROINFO") = AGGROINFO*;
}

enum AggroDataTypes
{
	AD_Player,
	AD_Secondary,
	AD_Group1,
	AD_Group2,
	AD_Group3,
	AD_Group4,
	AD_Group5,
	AD_xTarget1,
	AD_xTarget2,
	AD_xTarget3,
	AD_xTarget4,
	AD_xTarget5,
	AD_xTarget6,
	AD_xTarget7,
	AD_xTarget8,
	AD_xTarget9,
	AD_xTarget10,
	AD_xTarget11,
	AD_xTarget12,
	AD_xTarget13,
	AD_xTarget14,
	AD_xTarget15,
	AD_xTarget16,
	AD_xTarget17,
	AD_xTarget18,
	AD_xTarget19,
	AD_xTarget20,
};

struct [[offsetcomments]] GROUPAGGRO
{
/*0x00*/ DWORD         Unknown0x00;
/*0x04*/ DWORD         Unknown0x04;
/*0x08*/ DWORD         GroupMemberAggro[6];      // player is ALWAYS the 6th member...
/*0x20*/
};

inline namespace deprecated {
	using PGROUPAGGRO DEPRECATE("Use GROUPAGGRO* instead of PGROUPAGGRO") = GROUPAGGRO*;
}

struct [[offsetcomments]] BenefitSelection
{
/*0x00*/ int BenefitID;
/*0x04*/ int BenefitTier;
/*0x08*/
};

struct [[offsetcomments]] EQLogin
{
/*0x000*/ uint8_t     Unknown0x00[0x6b4];
/*0x6b4*/ char        station_name[32];
};

constexpr uint32_t EQ_ASSIST_CALC     = 0x020c0f19;
constexpr uint32_t EQ_ASSIST_COMPLETE = 0x24AB;        // aMsgTimeStampRe
constexpr uint32_t EQ_ASSIST          = 0x0DD2;        // do_assist(PlayerClient *,char const *)+399 20160212 live (see 52C319)

} // namespace eqlib
