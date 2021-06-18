/*
 * MacroQuest: The extension platform for EverQuest
 * Copyright (C) 2002-2021 MacroQuest Authors
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

#include "Common.h"
#include "Constants.h"
#include "Containers.h"
#include "CXStr.h"
#include "GraphicsEngine.h"
#include "Items.h"
#include "Spells.h"

// This is the home of all things related to what used to be called SPAWNINFO,
// plus a few extra things until they find a home of their own.
//
// Class hierarchies:
//
// SPAWNINFO:
//   PlayerClient -> PlayerZoneClient -> PlayerBase

namespace eqlib {

class CLightInterface;
class CParticlePointInterface;
class EQObject;
class EQSwitch;
class EQPlacedItem;
class PlayerAnimationBase;
class PlayerBase;
class PlayerClient;
class PcClient;
class MissileBase;

inline namespace deprecated {
	struct EQC_INFO;
}
struct LaunchSpellData;
struct chngForm;

using SPAWNINFO = PlayerClient;
using PSPAWNINFO = PlayerClient *;

//============================================================================
// Misc
//============================================================================

enum GravityBehavior
{
	Ground,
	Flying,
	Levitating,
	Water,
	Floating,//boat
	LevitateWhileRunning
};

class [[offsetcomments]] CPhysicsInfo
{
public:
/*0x00*/ float               Y;
/*0x04*/ float               X;
/*0x08*/ float               Z;
/*0x0c*/ float               SpeedY;
/*0x10*/ float               SpeedX;
/*0x14*/ float               SpeedZ;
/*0x18*/ float               SpeedRun;
/*0x1c*/ float               Heading;
/*0x20*/ float               Angle;
/*0x24*/ float               AccelAngle;
/*0x28*/ float               SpeedHeading;
/*0x2c*/ float               CameraAngle;
/*0x30*/
};

struct [[offsetcomments]] SDoCollisionMovementStats
{
/*0x00*/ CPhysicsInfo        Source;
/*0x30*/ float               DestY;
/*0x34*/ float               DestX;
/*0x38*/ float               DestZ;
/*0x3c*/ float               SourceFloor;
/*0x40*/ float               DestFloor;
/*0x44*/ CPhysicsInfo        Dest;
/*0x74*/
};

class [[offsetcomments]] CLineBase
{
public:
/*0x00*/ float OriginY;
/*0x04*/ float OriginX;
/*0x08*/ float OriginZ;
/*0x0c*/ float DirectionY;
/*0x10*/ float DirectionX;
/*0x14*/ float DirectionZ;
/*0x18*/
};

class CLineSegment : public CLineBase
{
};

class [[offsetcomments]] CCapsule : public CLineSegment
{
public:
/*0x18*/ float Radius;
/*0x1c*/
};

struct [[offsetcomments]] PhysicsEffect
{
/*0x00*/ int SpellID;
/*0x04*/ int CasterID;
/*0x08*/ int EffectID;
/*0x0c*/ int BaseEffect;
/*0x10*/
};

// Mar 09 2020
struct [[offsetcomments]] SFellowshipMember
{
/*0x00*/ EqGuid       UniqueEntityID;
/*0x08*/ char         Name[EQ_MAX_NAME];
/*0x48*/ int          ZoneID;
/*0x4c*/ int          Level;
/*0x50*/ int          Class;
/*0x54*/ int          LastOn;
/*0x58*/
};

inline namespace deprecated {
	using FELLOWSHIPMEMBER DEPRECATE("Use SFellowshipMember instead of FELLOSWHIPMEMBER") = SFellowshipMember;
	using PFELLOWSHIPMEMBER DEPRECATE("Use SFellowshipMember* instead of PFELLOWSHIPMEMBER") = SFellowshipMember*;
}

struct FSDATA
{
	char Strings[0x20];   // need to check what these are...
};

constexpr int MAX_FELLOWSHIP_MEMBERS = 12;
constexpr int MAX_FELLOWSHIP_MOTD = 1024;

// Mar 09 2020 - 0xa80 see 8CB990
struct [[offsetcomments]] SFellowship
{
/*0x000*/ unsigned int      Version;
/*0x004*/ unsigned int      Version2;
/*0x008*/ unsigned int      Version3;
/*0x00c*/ unsigned int      Version4;
/*0x010*/ EqGuid            FellowshipGUID;
/*0x018*/ char              MotD[MAX_FELLOWSHIP_MOTD];
/*0x418*/ int               Members;
/*0x420*/ SFellowshipMember FellowshipMember[MAX_FELLOWSHIP_MEMBERS];
/*0x840*/ unsigned int      Sync;
/*0x844*/ bool              bExpSharingEnabled[MAX_FELLOWSHIP_MEMBERS];
/*0x850*/ bool              bSharedExpCapped[MAX_FELLOWSHIP_MEMBERS];
/*0x85c*/ int               Unknown0x85C;
/*0x860*/

	inline const char* get_Leader() { return Members > 0 ? FellowshipMember[0].Name : ""; }
	__declspec(property(get = get_Leader)) const char* Leader;

	inline uint32_t get_FellowshipID() { return FellowshipGUID.UniqueEntityID; }
	__declspec(property(get = get_FellowshipID)) uint32_t FellowshipID;
};

inline namespace deprecated {
	using FELLOWSHIPINFO DEPRECATE("Use SFellowship instead of FELLOWSHIPINFO") = SFellowship;
	using PFELLOWSHIPINFO DEPRECATE("Use SFellowship* instead of PFELLOWSHIPINFO") = SFellowship*;
}

// Size: 0x150, 0x69B040 @ 2021-05-14
struct chngForm {
/*0x000*/ int             spawnID;
/*0x004*/ char            name[EQ_MAX_NAME];
/*0x044*/ int             race;                // GetRace()
/*0x048*/ char            gender;              // mActorClient.Gender
/*0x049*/ char            textureType;         // mActorClient.TextureType
/*0x04a*/ char            armorVariation;      // mActorClient.Variation
/*0x04b*/ char            armorMaterial;       // mActorClient.Material
/*0x04c*/ char            head;                // mActorClient.HeadType
/*0x050*/ int             faceStyle;           // mActorClient.FaceStyle
/*0x054*/ uint8_t         hairStyle;           // mActorClient.HairStyle
/*0x055*/ uint8_t         hairColor;           // mActorClient.HairColor
/*0x056*/ uint8_t         facialHair;          // mActorClient.FacialHair
/*0x057*/ uint8_t         facialHairColor;     // mActorClient.FacialHairColor
/*0x058*/ float           height;              // Height
/*0x05c*/ uint32_t        npcTintIndex;        // NpcTintIndex
/*0x060*/ bool            keepArmorProperties;
/*0x064*/ ArmorProperties armorProperties[9];  // mActorClient.ActorEquipment
/*0x118*/ int             armorTint[9];        // mActorClient.ArmorColor
/*0x13c*/ int             Class;               // mActorClient.Class
/*0x144*/ int             heritage;            // mActorClient.Heritage
/*0x148*/ int             tattoo;              // mActorClient.Tattoo
/*0x14c*/ int             facialAttachment;    // mActorClient.Details
/*0x150*/

	chngForm()
		: spawnID(0)
		, race(-1)
		, gender(-1)
		, textureType(-1)
		, armorVariation(-1)
		, armorMaterial(-1)
		, head(-1)
		, faceStyle(-1)
		, hairStyle(255)
		, hairColor(255)
		, facialHair(255)
		, facialHairColor(255)
		, height(-1.0f)
		, npcTintIndex(0)
		, keepArmorProperties(false)
		, Class(-1)
		, heritage(0)
		, tattoo(-1)
		, facialAttachment(-1)
	{
		memset(armorTint, 0, sizeof(armorTint));
		memset(name, 0, sizeof(name));
	}
};

// size 0x58 see 442783 in eqgame.exe 2017 04 11 test
struct [[offsetcomments]] LaunchSpellData
{
/*0x00*/ uint32_t       SpellETA;                // Calculated TimeStamp when current spell being cast will land. 0 while not casting.
/*0x04*/ int            SpellID;                 // -1 = not casting a spell
/*0x08*/ uint8_t        SpellSlot;               // 0xFF if not casting, otherwise it's the spell gem number (0 - 8)
/*0x09*/ uint8_t        SpellLevel;
/*0x0c*/ ItemGlobalIndex ItemLocation;
/*0x18*/ ItemSpellTypes ItemCastType;
/*0x1c*/ int            ItemID;
/*0x20*/ float          CastingY;
/*0x24*/ float          CastingX;
/*0x28*/ int            DamageID;
/*0x2c*/ uint32_t       TargetID;
/*0x30*/ bool           bDetrimental;
/*0x31*/ bool           bResetMeleeTimers;
/*0x32*/ bool           bResetAAOnNotTakeHold;
/*0x33*/ bool           bFreeTarget;
/*0x34*/ float          TargetPosY;
/*0x38*/ float          TargetPosX;
/*0x3c*/ float          TargetPosZ;
/*0x40*/ bool           bTwinCast;
/*0x41*/ bool           bLanded;
/*0x42*/ bool           bNPCTarget;
/*0x43*/ bool           bHasHitRecourse;
/*0x44*/ float          AnchorPosY;
/*0x48*/ float          AnchorPosX;
/*0x4c*/ float          AnchorPosZ;
/*0x50*/ bool           bIgnoreRange;
/*0x51*/ bool           bResetAAOnNotTakeHoldSuccess;
/*0x54*/ int            Unknown0x54;
/*0x58*/

	bool IsCasting() const
	{
		return SpellID != -1;
	}
};

inline namespace deprecated {
	using LAUNCHSPELLDATA DEPRECATE("Use LaunchSpellData instead of LAUNCHSPELLDATA") = LaunchSpellData;
	using PLAUNCHSPELLDATA DEPRECATE("Use LaunchSpellData* instead PLAUNCHSPELLDATA") = LaunchSpellData*;
}

//============================================================================
// PhysicsBase & PlayerPhysics
//============================================================================

class [[offsetcomments]] PhysicsBase
{
public:
/*0x00*/ void* vtable2;
/*0x04*/ bool  bApplyGravity;
/*0x08*/
};

class [[offsetcomments]] PlayerPhysics : public PhysicsBase
{
public:
/*0x08*/ PlayerClient*    pSpawn;
/*0x0c*/ GravityBehavior  Levitate;
// bobbing control
/*0x10*/ int              UpDownIndex;
/*0x14*/ int              LeftRightIndex;
/*0x18*/ int              UpDownSpeed;
/*0x1c*/ int              LeftRightSpeed;
/*0x20*/ float            LeftRightDist;
/*0x24*/ float            UpDownDist;
/*0x28*/
};

class PlayerPhysicsClient : public PlayerPhysics
{
public:
/*0x1Fb8*/
};

struct [[offsetcomments]] PZCPhysicsInfo
{
// @start: PZCPhysicsInfo Members
/*0x10*/ float Z;
/*0x20*/ int ZHeading : 12;
/*0x14*/ int Heading : 12;
/*0x04*/ float Y;
/*0x0c*/ int DeltaHeading : 10;
/*0x08*/ float DeltaX;
/*0x18*/ float DeltaY;
/*0x20*/ int Acceleration : 10;
/*0x24*/ float DeltaZ;
/*0x00*/ float X;

// @end: PZCPhysicsInfo Members
};

struct HASHENTRY
{
	PlayerClient* spawn;
	DWORD         key;                             // same as SpawnID for spawns
	HASHENTRY*    next;
};
using PHASHENTRY = HASHENTRY*;

struct HASHTABLE
{
    HASHENTRY** table;
    int size;
};
using PHASHTABLE = HASHTABLE*;

class [[offsetcomments]] PlayerManagerBase
{
public:
	virtual ~PlayerManagerBase() {}

/*0x04*/ DWORD         random;                   // rand() % 20000
/*0x08*/ PlayerClient* FirstSpawn;
/*0x0c*/ PlayerClient* LastSpawn;
/*0x10*/ DWORD         unknown10;
/*0x14*/ HASHTABLE*    SPHash;
/*0x18*/
};

class PlayerManagerClient : public PlayerManagerBase
{
public:
	//PlayerClient* GetPlayerFromPartialName(const char* szName, PlayerBase* = nullptr);
	//PlayerClient* GetPlayerFromName(const char* szName);

	EQLIB_OBJECT PlayerClient* GetSpawnByID(int);
	EQLIB_OBJECT PlayerClient* GetSpawnByName(const char*);
	EQLIB_OBJECT PlayerClient* GetPlayerFromPartialName(const char*, PlayerBase*);
};

inline namespace deprecated {
	using EQPlayerManager DEPRECATE("Use PlayerManagerClient instead of EQPlayerManager") = PlayerManagerClient;
	using SPAWNMANAGER DEPRECATE("Use PlayerManagerClient instead SPAWNMANAGER") = PlayerManagerClient;
	using PSPAWNMANAGER DEPRECATE("Use PlayerManagerClient* instead PSPAWNMANAGER") = PlayerManagerClient*;
}

//============================================================================
// PlayerBase
//============================================================================

// this is the size of EQPlayer__EQPlayer_x
// actual size 0x2020 in Feb 20 2016 Live (see 64B6A0) - eqmule
// A.k.a. SPAWNINFO
class [[offsetcomments]] PlayerBase : public TListNode<PlayerClient>, public CActorApplicationData
{
public:
/*0x010*/ float             JumpStrength;
/*0x014*/ float             SwimStrength;
/*0x018*/ float             SpeedMultiplier;
/*0x01c*/ float             AreaFriction;
/*0x020*/ float             AccelerationFriction;
/*0x024*/ EActorType        CollidingType;                // when we collide with something this gets set.
/*0x028*/ float             FloorHeight;
/*0x02c*/ bool              bSinksInWater;
/*0x030*/ unsigned int      PlayerTimeStamp;              // doesn't update when on a Vehicle (mounts/boats etc)
/*0x034*/ unsigned int      LastTimeIdle;
/*0x038*/ char              Lastname[0x20];
/*0x058*/ float             AreaHPRegenMod;               // from guild hall pools etc.
/*0x05c*/ float             AreaEndRegenMod;
/*0x060*/ float             AreaManaRegenMod;
/*0x064*/ float             Y;
/*0x068*/ float             X;
/*0x06c*/ float             Z;
/*0x070*/ float             SpeedY;
/*0x074*/ float             SpeedX;
/*0x078*/ float             SpeedZ;
/*0x07c*/ float             SpeedRun;
/*0x080*/ float             Heading;
/*0x084*/ float             Angle;
/*0x088*/ float             AccelAngle;
/*0x08c*/ float             SpeedHeading;
/*0x090*/ float             CameraAngle;
/*0x094*/ unsigned int      UnderWater;                   // LastHeadEnvironmentType
/*0x098*/ unsigned int      LastBodyEnvironmentType;
/*0x09c*/ unsigned int      LastFeetEnvironmentType;
/*0x0a0*/ uint8_t           HeadWet;                      // these really are environment related, like lava as well for example
/*0x0a1*/ uint8_t           FeetWet;
/*0x0a2*/ uint8_t           BodyWet;
/*0x0a3*/ uint8_t           LastBodyWet;
/*0x0a4*/ char              Name[EQ_MAX_NAME];            // ie priest_of_discord00
/*0x0e4*/ char              DisplayedName[EQ_MAX_NAME];   // ie Priest of Discord
/*0x124*/ uint8_t           PossiblyStuck;                // never seen this be 1 so maybe it was used a a point but not now...
/*0x125*/ uint8_t           Type;
/*0x128*/ unsigned int**    BodyType;                     // this really should be renamed to charprops or something its broken anyway
/*0x12c*/ uint8_t           CharPropFiller[0xc];          // well since the above is a CharacterPropertyHash we have to pad here...
/*0x138*/ float             AvatarHeight;                 // height of avatar from groundwhen standing for sure see 5C06A0 in Jun 10 2019 test
/*0x13c*/ float             Height;
/*0x140*/ float             Width;
/*0x144*/ float             Length;
/*0x148*/ int               Unknown0x0148;
/*0x14c*/ int               Unknown0x014C;
/*0x150*/ unsigned int      SpawnID;
/*0x154*/ unsigned int      PlayerState;                  // 0=Idle 1=Open 2=WeaponSheathed 4=Aggressive 8=ForcedAggressive 0x10=InstrumentEquipped 0x20=Stunned 0x40=PrimaryWeaponEquipped 0x80=SecondaryWeaponEquipped
/*0x158*/ PlayerClient*     Vehicle;                      // NULL until you collide with a vehicle (boat,airship etc)
/*0x15c*/ PlayerClient*     Mount;                        // NULL if no mount present
/*0x160*/ PlayerClient*     Rider;                        // the mount's rider
/*0x164*/ unsigned int      Unknown0x0164;
/*0x168*/ bool              Targetable;                   // true if mob is targetable
/*0x169*/ bool              bTargetCyclable;
/*0x16a*/ bool              bClickThrough;
/*0x16b*/ bool              bBeingFlung;
/*0x16c*/ unsigned int      FlingActiveTimer;
/*0x170*/ unsigned int      FlingTimerStart;
/*0x174*/ bool              bFlingSomething;
/*0x178*/ float             FlingY;
/*0x17c*/ float             FlingX;
/*0x180*/ float             FlingZ;
/*0x184*/ bool              bFlingSnapToDest;
/*0x188*/ int               SplineID;
/*0x18c*/ int               SplineRiderID;
/*0x190*/

	EQLIB_OBJECT unsigned int GetId() const { return SpawnID; }

	// These are methods that originated from EQPlayer. They might not
	// all still exist.
	EQLIB_OBJECT bool IsAMount();
	EQLIB_OBJECT bool MyFeetAreOnGround();
	EQLIB_OBJECT bool HasProperty(unsigned int, int, int);
	EQLIB_OBJECT bool IsTargetable();
	EQLIB_OBJECT bool CanSee(const PlayerBase&);
	EQLIB_OBJECT bool CanSee(const CVector3& pos);
	EQLIB_OBJECT CLineSegment GetVisibilityLineSegment(const PlayerBase& other, unsigned int index = 0);

private:
	virtual void Dummy() {} // force a vtable
};

//============================================================================
// PlayerZoneClient
//============================================================================

class [[offsetcomments]] PlayerZoneClient : public PlayerBase
{
public:
/*0x0190*/ unsigned int                 LastIntimidateUse;

// @start: PlayerZoneClient Members
/*0x0194*/ bool                     bStationary;
/*0x0198*/ int                      ManaMax;
/*0x019c*/ int                      AFK;
/*0x01a0*/ unsigned int             TimeStamp;                    // updates all the time including when on a mount
/*0x01a4*/ uint8_t                  Level;
/*0x01a8*/ unsigned int             Zone;
/*0x01ac*/ unsigned int             MinuteTimer;
/*0x01b0*/ uint8_t                  HmmWhat;
/*0x01b1*/ char                     Suffix[0x80];
/*0x0234*/ unsigned int             SpellCooldownETA;
/*0x0238*/ uint8_t                  Type2;
/*0x023c*/ unsigned int             CorpseDragCount;
/*0x0240*/ bool                     bOfflineMode;
/*0x0241*/ bool                     bAnimationOnPop;
/*0x0244*/ int                      WarCry;
/*0x0248*/ int64_t                  HPCurrent;
/*0x0250*/ float                    AnimationSpeedRelated;
/*0x0254*/ uint8_t                  FishingEvent;
/*0x0258*/ int                      IsAttacking;                  // need to investigate
/*0x025c*/ unsigned int             CombatSkillUsed[0x2];
/*0x0264*/ bool                     bBetaBuffed;
/*0x0268*/ unsigned int             LastCastTime;
/*0x026c*/ bool                     Mercenary;
/*0x0270*/ void*                    pRaceGenderInfo;              // todo this is not a void* so... map the CRaceGenderInfo class
/*0x0274*/ unsigned int             SitStartTime;
/*0x0278*/ unsigned int             CombatSkillTicks[0x2];
/*0x0280*/ int                      SecondaryTintIndex;
/*0x0284*/ unsigned int             LastPrimaryUseTime;
/*0x0288*/ unsigned int             LastSecondaryUseTime;
/*0x028c*/ uint8_t                  LastAttack;
/*0x028d*/ uint8_t                  HoldingAnimation;             // todo: create enum for this byte. Holding: Nothing=0 A RightHand Weapon=1 A Shield=2 Dual Wielding Two Weapons=3 A Spear=4 A LeftHand Weapon=5 A Two Handed Weapon=6 A bow=7
/*0x028e*/ char                     DraggingPlayer[0x40];
/*0x02d0*/ int                      HideMode;
/*0x02d4*/ bool                     bAlwaysShowAura;
/*0x02d5*/ uint8_t                  Light;
/*0x02d8*/ unsigned int             LastTimeStoodStill;
/*0x02dc*/ uint8_t                  TitleVisible;
/*0x02dd*/ uint8_t                  IsPassenger;                  // if u are on a boat or airship or whatever
/*0x02e0*/ unsigned int             LastResendAddPlayerPacket;
/*0x02e4*/ uint8_t                  GMRank;
/*0x02e8*/ CharacterZoneClient*     pCharacter;
/*0x02ec*/ bool                     bTempPet;
/*0x02f0*/ unsigned int             Meditating;
/*0x02f4*/ uint8_t                  StandState;
/*0x02f5*/ bool                     PvPFlag;
/*0x02f6*/ uint8_t                  FindBits;
/*0x02f8*/ int                      AARank;                       // this really is the title id
/*0x02fc*/ int                      PetID;
/*0x0300*/ int                      PrimaryTintIndex;
/*0x0304*/ int                      NpcTintIndex;
/*0x0308*/ int64_t                  GuildID;
/*0x0310*/ float                    MissileRangeToTarget;
/*0x0314*/ int                      DontKnowYet;
/*0x0318*/ int                      SomethingElse;
/*0x031c*/ int                      AltAttack;
/*0x0320*/ void*                    pTouchingSwitch;              // need to get that in here : struct _EQSWITCH
/*0x0324*/ unsigned int             NextIntimidateTime;
/*0x0328*/ uint8_t                  CharClass;                    // Im pretty sure this isnt working
/*0x032c*/ int                      DoSpecialMelee;
/*0x0330*/ float                    BearingToTarget;
/*0x0334*/ char                     GM;
/*0x0335*/ char                     Handle[0x20];
/*0x0358*/ int                      RealEstateID;
/*0x035c*/ float                    GetMeleeRangeVar1;            // used by GetMeleeRange (fScaleFactor)
/*0x0360*/ int                      Deity;
/*0x0364*/ unsigned int             LastRefresh;                  // last 18 sec tick
/*0x0368*/ unsigned int             RespawnTimer;                 // its actually TimeOfDeath...TimeStamp of when RespawnWnd will close - 0 when you're alive
/*0x036c*/ int                      ManaCurrent;
/*0x0370*/ unsigned int             StunTimer;
/*0x0374*/ float                    MerchantGreed;
/*0x0378*/ int                      EnduranceCurrent;
/*0x0380*/ int64_t                  HPMax;
/*0x0388*/ unsigned int             ACounter;                     // not sure what this one is for (m_uHibernatingCount)
/*0x038c*/ uint8_t                  FD;
/*0x0390*/ int                      RealEstateItemId;
/*0x0394*/ bool                     LFG;
/*0x0398*/ unsigned int             LastRangedUsedTime;
/*0x039c*/ int                      Buyer;
/*0x03a0*/ float                    RunSpeed;                     // 0.70 on runspeed 5...
/*0x03a4*/ bool                     Sneak;
/*0x03a5*/ char                     LoginRelated[0x20];
/*0x03c8*/ int                      LastCastNum;
/*0x03cc*/ bool                     bBuffTimersOnHold;            // no you can't control this client side so unless you want to get banned leave it alone
/*0x03d0*/ unsigned int             LastTrapDamageTime;
/*0x03d4*/ EqItemGuid               realEstateItemGuid;
/*0x03e6*/ bool                     bAttackRelated;
/*0x03e8*/ unsigned int             LastMealTime;                 // last time we eat or drank
/*0x03ec*/ unsigned int             EnduranceMax;
/*0x03f0*/ LaunchSpellData          CastingData;                  // size: 0x58
/*0x0448*/ unsigned int             NextSwim;
/*0x044c*/ unsigned int             LoginSerial;
/*0x0450*/ bool                     bSummoned;                    // by a PC or by anyone? need to investigate
/*0x0454*/ float                    MyWalkSpeed;
/*0x0458*/ int                      berserker;
/*0x045c*/ float                    FallingStartZ;
/*0x0460*/ unsigned int             LastTick;
/*0x0464*/ unsigned int             MasterID;
/*0x0468*/ float                    CameraOffset;
/*0x046c*/ char                     Title[0x80];
/*0x04ec*/ bool                     Linkdead;
/*0x04f0*/ CPhysicsInfo             LastCollision;
/*0x0520*/ float                    ViewHeight;
/*0x0524*/ SPAWNINFO*               pViewPlayer;
/*0x0528*/ int                      Anon;                         // found in EQPlayer__SetNameSpriteTint_x
/*0x052c*/ int                      SomeData[0x2];
/*0x0534*/ char                     DragNames[0x2][0x40];
/*0x05b4*/ uint8_t                  Blind;
/*0x05b8*/ int                      Trader;                       // found in CEverQuest__RightClickedOnPlayer_x
/*0x05bc*/ unsigned int             FishingETA;
/*0x05c0*/ uint8_t                  IntimidateCount;
/*0x05c4*/ int                      CurrIOState;
/*0x05c8*/ unsigned int**           ppUDP;                        // UdpLibrary::UdpConnection
/*0x05cc*/ int                      Stuff;
/*0x05d0*/ bool                     bShowHelm;
/*0x05d4*/ int                      Dontknowyet2;
/*0x05d8*/ bool                     bSwitchMoved;                 // true when a door moves near the spawn
/*0x05dc*/ unsigned int             SpellGemETA[0xf];             // InnateETA is now the last member in this array
/*0x0618*/ uint8_t                  InPvPArea;                    // are we in a PvP area?

// @end: PlayerZoneClient Members

/*0x061c*/ TCircularBuffer<SDoCollisionMovementStats, MAX_MOVEMENT_STATS> MovementStats; // size (0x74 * 0x14) +8 = 0x918
/*0x0f34*/ PlayerClient*      WhoFollowing;                       // NULL if autofollow off
/*0x0f38*/ unsigned int       GroupAssistNPC[MAX_GROUP_ASSISTS];
/*0x0f3c*/ unsigned int       RaidAssistNPC[MAX_RAID_ASSISTS];
/*0x0f48*/ unsigned int       GroupMarkNPC[MAX_GROUP_MARK_TARGETS];
/*0x0f54*/ unsigned int       RaidMarkNPC[MAX_RAID_MARK_TARGETS];
/*0x0f60*/ unsigned int       TargetOfTarget;
/*0x0f64*/ PZCPhysicsInfo     PZCLastPhysics;
/*0x0f88*/ unsigned int       ParticleCastStartTime;
/*0x0f8c*/ unsigned int       ParticleCastDuration;
/*0x0f90*/ int                ParticleVisualSpellNum;
/*0x0f94*/ ActorClient        mActorClient;
/*0x1150*/ PlayerAnimationBase* pAnimation;
/*0x1154*/ float              MeleeRadius;                        // used by GetMeleeRange
/*0x1158*/ unsigned int       CollisionCounter;
/*0x115c*/ float              CachedFloorLocationY;
/*0x1160*/ float              CachedFloorLocationX;
/*0x1164*/ float              CachedFloorLocationZ;
/*0x1168*/ float              CachedFloorHeight;
/*0x116c*/ float              CachedCeilingLocationY;
/*0x1170*/ float              CachedCeilingLocationX;
/*0x1174*/ float              CachedCeilingLocationZ;
/*0x1178*/ float              CachedCeilingHeight;
/*0x117c*/ CCapsule           StaticCollision;
/*0x1198*/ ArrayClass<PhysicsEffect> mPhysicsEffects;
/*0x11a8*/ ArrayClass<bool>   PhysicsEffectsUpdated;
/*0x11b8*/
	EQLIB_OBJECT bool LegalPlayerRace();

	EQLIB_OBJECT bool LegalPlayerRace(int race)
	{
		if (race == -1)
			return LegalPlayerRace();

		return race <= EQR_GNOME
			|| race == EQR_IKSAR
			|| race == EQR_VAHSHIR
			|| race == EQR_FROGLOCK
			|| race == EQR_DRAKKIN;
	}

	// Some methods that were from EQPlayer in the past
	EQLIB_OBJECT bool AllowedToAttack(PlayerZoneClient*, int);
	EQLIB_OBJECT bool CanChangeForm(int Race, unsigned char Sex, float Height);
	EQLIB_OBJECT bool CanIFitHere(const CVector3& pos, bool ignoreHeight = false);
	EQLIB_OBJECT bool CanIHit(const PlayerZoneClient*, int);
	EQLIB_OBJECT bool IsFlyer();
	EQLIB_OBJECT bool IsInvisible(PlayerZoneClient*, bool = false);
	EQLIB_OBJECT bool IWasHit(EQMissileHitinfo*, LaunchSpellData*, int = 0);
	EQLIB_OBJECT bool UpdatePlayerActor();
	EQLIB_OBJECT float GetDefaultHeight(int race, unsigned char);
	EQLIB_OBJECT float GetPlayerFloorHeight(float, float, float, unsigned char);
	EQLIB_OBJECT int AimAtTarget(PlayerZoneClient*, EQMissile*);
	EQLIB_OBJECT int CheckForJump();
	EQLIB_OBJECT int GetArmorType(int, char*);
	EQLIB_OBJECT int GetGuild() const;
	EQLIB_OBJECT bool IsValidTeleport(float X, float Y, float Z, float Heading, float Distance);
	EQLIB_OBJECT int Levitating();
	EQLIB_OBJECT int MountableRace();
	EQLIB_OBJECT int MovePlayer();
	EQLIB_OBJECT int NotOnSameDeity(const PlayerZoneClient*, const EQ_Spell*);
	EQLIB_OBJECT static void ComputeSpecialHeights(int, float*, float*, float*, float*, bool);
	EQLIB_OBJECT unsigned char DoTeleport(char*, int);
	EQLIB_OBJECT unsigned char DoTeleportB(int, float, float, float, float, char*, int);
	EQLIB_OBJECT unsigned char GetNearestActorTag(char*, EActorType);
	EQLIB_OBJECT unsigned char HandleAmmo();
	EQLIB_OBJECT static unsigned char SkillUsed(unsigned char);
	EQLIB_OBJECT unsigned int ModifyAttackSpeed(unsigned int, int);
	EQLIB_OBJECT unsigned long GetArmorTint(int);
	EQLIB_OBJECT void BodyEnvironmentChange(unsigned char);
	EQLIB_OBJECT void ChangeHeight(float);
	EQLIB_OBJECT void ChangePosition(unsigned char);
	EQLIB_OBJECT void CheckForUnderFloor();
	EQLIB_OBJECT void CleanUpVehicle();
	EQLIB_OBJECT void DeleteMyMissiles();
	EQLIB_OBJECT void DoFloorCheck();
	EQLIB_OBJECT void FacePlayer(PlayerZoneClient*);
	EQLIB_OBJECT void FeetEnvironmentChange(unsigned char);
	EQLIB_OBJECT void GetActorTag(char*);
	EQLIB_OBJECT void GetConscious();
	EQLIB_OBJECT void HeadEnvironmentChange(unsigned char);
	EQLIB_OBJECT void IDied(EQPlayerDeath*);
	EQLIB_OBJECT void IHaveFallen(float);
	EQLIB_OBJECT void InitSneakMod();
	EQLIB_OBJECT void KnockedOut();
	EQLIB_OBJECT void MakeRiderMountUp();
	EQLIB_OBJECT void PositionOnFloor();
	EQLIB_OBJECT void PushAlongHeading(float);
	EQLIB_OBJECT void PutPlayerOnFloor();
	EQLIB_OBJECT void ResetVariables();
	EQLIB_OBJECT void SetAnimVariation();
	EQLIB_OBJECT void SetArmorTint(int, unsigned long);
	EQLIB_OBJECT void SetHeights();
	EQLIB_OBJECT void SetRace(int);
	EQLIB_OBJECT unsigned char GetLevel() const;

	EQLIB_OBJECT bool DoAttack(BYTE slot, BYTE skill, PlayerZoneClient* Target, bool bSomething = false, bool bAuto = false, bool bDontknow = false);

	EQLIB_OBJECT static PlayerZoneClient* GetClosestPlayerFromPartialName(const char* name, PlayerZoneClient* player, int maxPlayerType = 1);
};

//============================================================================
// PlayerClient
//============================================================================

// @sizeof(PlayerClient) == 0x1ea8 :: 2021-06-10 (live) @ 0x69108b
constexpr size_t PlayerClient_size = 0x1ea8;

class [[offsetcomments]] PlayerClient : public PlayerZoneClient
{
public:
/*0x11b8*/ int               Animation;                    // Current Animation Playing. see 5671F1 in feb 14 2019 test
/*0x11bc*/ int               NextAnim;
/*0x11c0*/ int               CurrLowerBodyAnim;
/*0x11c4*/ int               NextLowerBodyAnim;
/*0x11c8*/ int               CurrLowerAnimVariation;
/*0x11cc*/ int               CurrAnimVariation;
/*0x11d0*/ int               CurrAnimRndVariation;

	// Beginning of sound ids
/*0x11d4*/ int               Loop3d_SoundID;               // see 567254 in feb 14 2019 test
/*0x11d8*/ int               Step_SoundID;;
/*0x11dc*/ int               CurLoop_SoundID;
/*0x11e0*/ int               Idle3d1_SoundID;
/*0x11e4*/ int               Idle3d2_SoundID;
/*0x11e8*/ int               Jump_SoundID;
/*0x11ec*/ int               Hit1_SoundID;
/*0x11f0*/ int               Hit2_SoundID;
/*0x11f4*/ int               Hit3_SoundID;
/*0x11f8*/ int               Hit4_SoundID;
/*0x11fc*/ int               Gasp1_SoundID;
/*0x1200*/ int               Gasp2_SoundID;
/*0x1204*/ int               Drown_SoundID;
/*0x1208*/ int               Death_SoundID;
/*0x120c*/ int               Attk1_SoundID;
/*0x1210*/ int               Attk2_SoundID;
/*0x1214*/ int               Attk3_SoundID;
/*0x1218*/ int               Walk_SoundID;
/*0x121c*/ int               Run_SoundID;
/*0x1220*/ int               Crouch_SoundID;
/*0x1224*/ int               Swim_SoundID;
/*0x1228*/ int               TreadWater_SoundID;
/*0x122c*/ int               Climb_SoundID;
/*0x1230*/ int               Sit_SoundID;
/*0x1234*/ int               Kick_SoundID;
/*0x1238*/ int               Bash_SoundID;
/*0x123c*/ int               FireBow_SoundID;
/*0x1240*/ int               MonkAttack1_SoundID;
/*0x1244*/ int               MonkAttack2_SoundID;
/*0x1248*/ int               MonkSpecial_SoundID;
/*0x124c*/ int               PrimaryBlunt_SoundID;
/*0x1250*/ int               PrimarySlash_SoundID;
/*0x1254*/ int               PrimaryStab_SoundID;
/*0x1258*/ int               Punch_SoundID;
/*0x125c*/ int               Roundhouse_SoundID;
/*0x1260*/ int               SecondaryBlunt_SoundID;
/*0x1264*/ int               SecondarySlash_SoundID;
/*0x1268*/ int               SecondaryStab_SoundID;
/*0x126c*/ int               SwimAttack_SoundID;
/*0x1270*/ int               TwoHandedBlunt_SoundID;
/*0x1274*/ int               TwoHandedSlash_SoundID;
/*0x1278*/ int               TwoHandedStab_SoundID;
/*0x127c*/ int               SecondaryPunch_SoundID;
/*0x1280*/ int               JumpAcross_SoundID;
/*0x1284*/ int               WalkBackwards_SoundID;
/*0x1288*/ int               CrouchWalk_SoundID;

/*0x128c*/ unsigned int      LastHurtSound;                // see 5E96E0 in feb 14 2019 test
/*0x1290*/ unsigned int      LastWalkTime;                 // used for animations
/*0x1294*/ int               ShipRelated;                  // ID? look into.
/*0x1298*/ int               RightHolding;                 // Nothing=0 Other/Weapon=1 shield=2
/*0x129c*/ int               LeftHolding;                  // old Holding
/*0x12a0*/ unsigned int      DeathAnimationFinishTime;
/*0x12a4*/ bool              bRemoveCorpseAfterDeathAnim;  // 0x1274 for sure used by /hidecorpse
/*0x12a8*/ unsigned int      LastBubblesTime;
/*0x12ac*/ unsigned int      LastBubblesTime1;
/*0x12b0*/ unsigned int      LastColdBreathTime;
/*0x12b4*/ unsigned int      LastParticleUpdateTime;
/*0x12b8*/ unsigned int      MercID;                       // IT IS 0x1288      //if the spawn is player and has a merc up this is it's spawn ID - 16 jul 2014
/*0x12bc*/ unsigned int      ContractorID;                 // if the spawn is a merc this is its contractor's spawn ID - 16 jul 2014
/*0x12c0*/ float             CeilingHeightAtCurrLocation;
/*0x12c4*/ void*             MobileEmitter;                // todo: change and map to EqMobileEmitter*
/*0x12c8*/ bool              bInstantHPGaugeChange;
/*0x12cc*/ unsigned int      LastUpdateReceivedTime;
/*0x12d0*/ float             MaxSpeakDistance;
/*0x12d4*/ float             WalkSpeed;                    // how much we will slow down while sneaking
/*0x12d8*/ bool              bHideCorpse;
/*0x12d9*/ char              AssistName[0x40];
/*0x1319*/ bool              InvitedToGroup;
/*0x131c*/ int               GroupMemberTargeted;          // 0xFFFFFFFF if no target, else 1 through 5
/*0x1320*/ bool              bRemovalPending;              // see 5E0763 in feb 14 2019 test
/*0x1324*/ void*             pCorpse;
/*0x1328*/ float             EmitterScalingRadius;
/*0x132c*/ int               DefaultEmitterID;
/*0x1330*/ bool              bDisplayNameSprite;
/*0x1331*/ bool              bIdleAnimationOff;
/*0x1332*/ bool              bIsInteractiveObject;
/*0x1333*/ uint8_t           InteractiveObjectModelName[0x80];
/*0x13b3*/ uint8_t           InteractiveObjectOtherName[0x80];
/*0x1433*/ uint8_t           InteractiveObjectName[0x40];
/*0x1474*/ CPhysicsInfo      PhysicsBeforeLastPort;        // size IS /*0x30*/ see 5E617B in feb 14 2019 test
/*0x14a4*/ unsigned int      notsure;                      // could be part of CPhysicsInfo?
/*0x14a8*/ SFellowship       Fellowship;                   // IT IS AT 0x1498 see 63BEDD in feb 14 2019 test // size 0x9e8
/*0x1d08*/ float             CampfireY;
/*0x1d0c*/ float             CampfireX;
/*0x1d10*/ float             CampfireZ;
/*0x1d14*/ int               CampfireZoneID;               // zone ID where campfire is
/*0x1d18*/ int               CampfireTimestamp;            // CampfireTimestamp-FastTime()=time left on campfire
/*0x1d1c*/ int               CampfireTimestamp2;
/*0x1d20*/ int               FellowShipID;
/*0x1d24*/ int               FellowShipID2;
/*0x1d28*/ int               CampType;
/*0x1d2c*/ bool              Campfire;
/*0x1d30*/ TSafeArrayStatic<int, 3> SeeInvis;              // for sure see 63E23F or 63BD35 in feb 14 2019 test
/*0x1d3c*/ EQUIPMENT         Equipment;                    // size 0xb4 see 63BF44 in feb 14 2019 test
/*0x1df0*/ bool              bIsPlacingItem;               // for sure see 543626 in feb 14 2019 test
/*0x1df1*/ bool              bGMCreatedNPC;
/*0x1df4*/ int               ObjectAnimationID;
/*0x1df8*/ bool              bInteractiveObjectCollidable;
/*0x1dfc*/ int               InteractiveObjectType;
/*0x1e00*/ int               SoundIDs[0xa];                // 0x28 bytes for sure see 648AB2 in feb 14 2019 test
/*0x1e28*/ unsigned int      LastHistorySentTime;          // for sure see 648E7E in feb 14 2019 test
/*0x1e2c*/ ArrayClass2<unsigned int> BardTwistSpells;      // size 0x18
/*0x1e44*/ int               CurrentBardTwistIndex;
/*0x1e48*/ int               CurrentBardTwistIndex2;
/*0x1e4c*/ PlayerPhysicsClient mPlayerPhysicsClient;       // size 0x28
/*0x1e74*/ int               SpawnStatus[6];               // todo: look closer at these i think they can show like status of mobs slowed, mezzed etc, but not sure
/*0x1e8c*/ int               BannerIndex0;                 // guild banners
/*0x1e90*/ int               BannerIndex1;
/*0x1e94*/ ARGBCOLOR         BannerTint0;
/*0x1e98*/ ARGBCOLOR         BannerTint1;
/*0x1e9c*/ int               MountAnimationRelated;
/*0x1ea0*/ bool              bGuildShowAnim;               // or sprite? need to check
/*0x1ea1*/ bool              bWaitingForPort;              // for sure see 5C5445 in feb 14 2019 test
/*0x1ea4*/ int               Unknown0x201C;
/*0x1ea8*/

	void Initialize(PlayerClient*, unsigned char, unsigned int, unsigned char, char*);
	~PlayerClient();

private:
	struct constructor_key_t {};

public:
	// not allowed to create this class, only use existing instances
	PlayerClient() = delete;
	PlayerClient(constructor_key_t) {} // define a custom constructor to prevent initialization
	PlayerClient(const PlayerClient&) = delete;
	PlayerClient& operator=(const PlayerClient&) = delete;

	inline int GetClass() const { return mActorClient.Class; }
	inline int GetRace() const { return mActorClient.RaceOverride ? mActorClient.RaceOverride : mActorClient.Race; }
	inline BYTE GetCharacterType() const { return Type; }
	inline unsigned int GetId() const { return SpawnID; }
	inline CharacterZoneClient* GetCharacter() const { return (CharacterZoneClient*)GetPcClient(); }
	inline int GetZoneID() const { return Zone; }
	inline int GetCurrentMana() const { return ManaCurrent; }
	inline int GetMaxMana() const { return ManaMax; }
	inline int GetCurrentEndurance() const { return EnduranceCurrent; }
	inline int GetMaxEndurance() const { return EnduranceMax; }
	inline unsigned int GetSpellCooldownETA() const { return SpellCooldownETA; }
	inline bool IsGm() const { return GM; }

	EQLIB_OBJECT PcClient* GetPcClient() const;

	// These come from the old EQPlayer class. Not all of these methods still exist.
	EQLIB_OBJECT bool IsInvited();
	EQLIB_OBJECT bool IsRoleplaying();
	EQLIB_OBJECT bool IsUntexturedHorse();
	EQLIB_OBJECT bool const HasInvalidRiderTexture() const;
	EQLIB_OBJECT int CanBeBald();
	EQLIB_OBJECT int SetPlayerPitchType();
	EQLIB_OBJECT int SwapBody(int, int);
	EQLIB_OBJECT int SwapFace(int, int);
	EQLIB_OBJECT int SwapHead(int, int, unsigned long, int);
	EQLIB_OBJECT int SwapMaterial(int, int, int, int, unsigned char);
	EQLIB_OBJECT int SwapNPCMaterials();
	EQLIB_OBJECT static void UpdateAllPlayersVisibility();
	EQLIB_OBJECT CLightInterface* CreateUserLight(CLightDefinitionInterface*, int);
	EQLIB_OBJECT unsigned char GetBaseFaceNbr(int, unsigned char*);
	EQLIB_OBJECT unsigned char HasAttachedBeard();
	EQLIB_OBJECT unsigned char HasAttachedHair();
	EQLIB_OBJECT unsigned char UpdateItemSlot(unsigned char, char*, int);
	EQLIB_OBJECT unsigned int CalcAnimLength(int);
	EQLIB_OBJECT void ChangeLight();
	EQLIB_OBJECT void CleanUpMyEffects();
	EQLIB_OBJECT void CleanUpTarget();
	EQLIB_OBJECT void Dismount();
	EQLIB_OBJECT void DisplayWeaponsAndArmor();
	EQLIB_OBJECT void do_change_form(chngForm*, bool = false, bool = false);
	EQLIB_OBJECT void DoCamAi();
	EQLIB_OBJECT void DoClassRandomAnimation();
	EQLIB_OBJECT void DoItemSlot(int);
	EQLIB_OBJECT void DoSwimJump(unsigned char);
	EQLIB_OBJECT void FollowPlayerAI();
	EQLIB_OBJECT void ForceInvisible(bool);
	EQLIB_OBJECT void HandleMaterialEx(int, unsigned int, unsigned int, unsigned long, int);
	EQLIB_OBJECT void HandoverControlToZoneserver();
	EQLIB_OBJECT void MountEQPlayer(PlayerZoneClient*);
	EQLIB_OBJECT void PlaySound(int);
	EQLIB_OBJECT void SetAccel(float, int);
	EQLIB_OBJECT void SetAfk(int);
	EQLIB_OBJECT void SetCurrentLoopSound(int);
	EQLIB_OBJECT void SetDefaultFacialFeaturesByFace(int, unsigned char, unsigned char);
	EQLIB_OBJECT void SetInvited(bool);
	EQLIB_OBJECT void SetSounds();
	EQLIB_OBJECT void SetToRandomRace();
	EQLIB_OBJECT void TouchingSwitch();
	EQLIB_OBJECT void TriggerSpellEffect(EQMissileHitinfo*);
	EQLIB_OBJECT void TurnOffAutoFollow();
	EQLIB_OBJECT void UpdateAppearance();
	EQLIB_OBJECT void UpdateBonePointers();
	EQLIB_OBJECT void UpdateNameSprite();
	EQLIB_OBJECT void UpdatePlayerVisibility();
	EQLIB_OBJECT void ChangeBoneStringSprite(int bone, const char* spriteText);
	EQLIB_OBJECT int SetNameSpriteState(bool);
	EQLIB_OBJECT bool SetNameSpriteTint();

	EQLIB_OBJECT static PlayerClient* IsPlayerActor(CActorInterface*);

	DEPRECATE("PlayerClient: Use GetNext() instead of pNext")
	__declspec(property(get = GetNext)) PlayerClient* pNext;
	DEPRECATE("PlayerClient: Use GetPrevious() instead of pPrev")
	__declspec(property(get = GetPrevious)) PlayerClient* pPrev;
};

inline namespace deprecated {
	// For compatibility with all the old stuff
	using EQPlayer DEPRECATE("Use PlayerClient instead of EQPlayer") = PlayerClient;
}

static_assert(sizeof(PlayerClient) == PlayerClient_size, "Size of PlayerClient does not match PlayerClient_size");

} // namespace eqlib
