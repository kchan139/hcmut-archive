#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__
#include "main.h"

// #define DEBUG

enum ItemType   { ANTIDOTE, PHOENIX_I, PHOENIX_II, PHOENIX_III, PHOENIX_IV };
enum KnightType { PALADIN, LANCELOT, DRAGON, NORMAL };

enum eventID { MadBear              = 1,   Bandit               = 2,   LordLupin        = 3,  Elf                  = 4, 
               Troll                = 5,   Tornbery             = 6,   QueenOfCards     = 7,  NinaDeRings          = 8, 
               DurianGarden         = 9,   OmegaWeapon          = 10,  Hades            = 11, pickupPaladinsShield = 95, 
               pickupLancelotsSpear = 96,  pickupGuineveresHair = 97,  pickupExcalibur  = 98, UltimeciaBoss        = 99, 
               lootPhoenixII        = 112, lootPhoenixIII       = 113, lootPhoenixIV    = 114 };

class BaseItem; class Phoenix; class Antidote; class BaseKnight; class Events;

static bool encounteredOmegaWeapon = false;
static bool encounteredHades       = false;
static bool defeatedHades          = false;


//==========* ITEMS *==========//
class BaseItem
{
    protected:
        ItemType   itemType;

    public:
        BaseItem * next;
        BaseItem          () { this->next = nullptr; }
        virtual ~BaseItem () = default;
        virtual void     use         (BaseKnight *) { return; };
        virtual ItemType getItemType () const { return itemType; }
};
class Antidote : public BaseItem
    { public: Antidote () { this->itemType = ANTIDOTE; } };
class PhoenixDown : public BaseItem
{
    public:
        PhoenixDown (ItemType phoenixType) 
            { this->itemType = phoenixType; }
        void use    (BaseKnight *);
};


//==========* INVENTORY *==========//
class BaseBag 
{
    protected:
        BaseKnight * knight;
        BaseItem   * head        = nullptr;
        int maxCapacity          = UINT16_MAX;
        int antidoteCount        = 0,
            phoenixCount         = 0;

    public:
        virtual BaseItem * getPhoenix  (BaseKnight * knight);
        virtual bool       insertFirst (BaseItem * item);
        virtual bool       removeFirst ();
        virtual bool       removeOne   (ItemType itemType);
        virtual bool       removeAll   ();
        virtual bool       canUse      (BaseKnight *, ItemType);
        int getNumberOfItems () const { return antidoteCount + phoenixCount; }
        int getMaxCapacity   () const { return maxCapacity; }
        int getPhoenixCount  () const { return phoenixCount; }
        int getAntidoteCount () const { return antidoteCount; }
        void setHead         (BaseItem * head) { this->head = head; }
        string toString      () const;
};
class PaladinBag : public BaseBag
{
    public:
        PaladinBag (int phoenixdown, int antidote) 
        {
            BaseItem * item;
            for (int i = 0; i < phoenixdown; i++) 
                { item = new PhoenixDown (PHOENIX_I); insertFirst (item); }
            for (int i = 0; i < antidote; i++) 
                { item = new Antidote (); insertFirst (item); }
        }
        ~PaladinBag () 
        {
            BaseItem * current = head;
            while (current != nullptr) 
            {
                BaseItem * next = current->next;
                delete [] current; current = nullptr;
                current = next;
            }
        }
};
class LancelotBag : public BaseBag
{
    public:
        LancelotBag (int phoenixdown, int antidote) 
        {
            this->maxCapacity       = 16;
            BaseItem * item;
            for (int i = 0; i < phoenixdown; i++) 
            {
                if ((antidoteCount + phoenixCount) < maxCapacity)
                { item = new PhoenixDown (PHOENIX_I); insertFirst (item); }
            }
            for (int i = 0; i < antidote; i++) 
            {
                if ((antidoteCount + phoenixCount)  < maxCapacity)
                { item = new Antidote (); insertFirst (item); }
            }
        }
        ~LancelotBag () 
        {
            BaseItem * current = head;
            while (current != nullptr) 
            {
                BaseItem * next = current->next;
                delete [] current; current = nullptr;
                current = next;
            }
        }
};
class DragonBag : public BaseBag 
{
    public:
        DragonBag (int phoenixdown, int antidote) 
        {
            this->maxCapacity       = 14;
            BaseItem * item;
            for (int i = 0; i < phoenixdown; i++) 
            {
                if ((antidoteCount + phoenixCount) < maxCapacity)
                { item = new PhoenixDown (PHOENIX_I); insertFirst (item); }
            }
        }
        ~DragonBag () 
        {
            BaseItem * current = head;
            while (current != nullptr) 
            {
                BaseItem * next = current->next;
                delete [] current; current = nullptr;
                current = next;
            }
        }
};
class NormalBag : public BaseBag
{
    public:
        NormalBag (int phoenixdown, int antidote) 
        {
            this->maxCapacity       = 19;
            BaseItem * item;
            for (int i = 0; i < phoenixdown; i++) 
            {
                if ((antidoteCount + phoenixCount) < maxCapacity)
                { item = new PhoenixDown (PHOENIX_I); insertFirst (item); }
            }
            for (int i = 0; i < antidote; i++) 
            {
                if ((antidoteCount + phoenixCount)  < maxCapacity)
                { item = new Antidote (); insertFirst (item); }
            }
        }
        ~NormalBag () 
        {
            BaseItem * current = head;
            while (current != nullptr) 
            {
                BaseItem * next = current->next;
                delete [] current; current = nullptr;
                current = next;
            }
        }
};


//==========* OPPONENTS *==========//
class BaseOpponent
{
    protected:
        int levelO; int typeO; int gilO; int baseDmgO;

    public:
        BaseOpponent (int levelO, int typeO, int gilO, int baseDmgO) : 
            levelO (levelO), typeO (typeO), gilO (gilO), baseDmgO (baseDmgO) {}
        int getLevelO      ()    { return levelO; }
        int getTypeO       ()    { return typeO; }
        int getGilO        ()    { return gilO; }
        int getBaseDamageO ()    { return baseDmgO; }
};


//==========* KNIGHTS *==========//
class BaseKnight 
{
    protected:
        int id;     int hp;     int maxhp;
        int level;  int gil;    int antidote, phoenixdown;
        KnightType knightType;

    public:
        BaseBag * bag;
        double baseDmg = 0.0;
        static BaseKnight * create (int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
        virtual ~BaseKnight  () = default;
        virtual bool fight   (BaseOpponent *) = 0;
        virtual bool isAlive ();
        string toString      () const;

        KnightType getTypeK ()               { return knightType; }
        int    getHP        ()               { return hp; }
        int    getMaxHP     ()               { return maxhp; }
        int    getLevel     ()               { return level; }
        int    getGil       ()               { return gil; }
        double getBaseDmg   ()               { return baseDmg; }
        void setHP     (int updatedHP)       { this->hp    = updatedHP; }
        void setLevel  (int updatedLevel)    { this->level = updatedLevel; }
        void setGil    (int updatedGil)      { this->gil   = updatedGil; }
};
class Paladin : public BaseKnight
{
    public:
        Paladin (int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
        {
            this->id          = id;          this->maxhp       = maxhp;
            this->hp          = maxhp;       this->level       = level;
            this->gil         = gil;         this->antidote    = antidote;
            this->phoenixdown = phoenixdown; this->knightType  = PALADIN;
            this->bag         = new PaladinBag(phoenixdown, antidote);
            baseDmg           = 0.06;
        }
        bool fight (BaseOpponent *);
};
class Lancelot : public BaseKnight
{
    public:
        Lancelot (int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
        {
            this->id          = id;          this->maxhp       = maxhp;
            this->hp          = maxhp;       this->level       = level;
            this->gil         = gil;         this->antidote    = antidote;
            this->phoenixdown = phoenixdown; this->knightType  = LANCELOT;
            this->bag         = new LancelotBag(phoenixdown, antidote);
            baseDmg           = 0.05;
        }
        bool fight (BaseOpponent *);
};
class DragonKnight : public BaseKnight
{
    public:
        DragonKnight (int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
        {
            this->id          = id;          this->maxhp       = maxhp;
            this->hp          = maxhp;       this->level       = level;
            this->gil         = gil;         this->antidote    = antidote;
            this->phoenixdown = phoenixdown; this->knightType  = DRAGON;
            this->bag         = new DragonBag(phoenixdown, antidote);
            baseDmg           = 0.075;
        }
        bool fight (BaseOpponent *);
};
class NormalKnight : public BaseKnight
{
    public:
        NormalKnight (int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
        {
            this->id          = id;          this->maxhp       = maxhp;
            this->hp          = maxhp;       this->level       = level;
            this->gil         = gil;         this->antidote    = antidote;
            this->phoenixdown = phoenixdown; this->knightType  = NORMAL;
            this->bag         = new NormalBag(phoenixdown, antidote);
        }
        bool fight (BaseOpponent *);
};


//==========* ARMYKNIGHTS *==========//
class ArmyKnights 
{
    BaseKnight ** knight;
    int numberOfKnights;
    bool hasShield    = false; bool hasSpear     = false;
    bool hasHollyHair = false; bool hasExcalibur = false;

    public:
        ArmyKnights (const string &);;
        ~ArmyKnights();
        BaseKnight * lastKnight () const;
        int  count              () const;
        bool fight              (int, int);
        bool adventure          (Events *);
        void lootItem           (int, ItemType);
        void passGil            (int);
        void removeKnight       (int);
        bool hasPaladinShield   ()     const { return hasShield; }
        bool hasLancelotSpear   ()     const { return hasSpear; }
        bool hasGuinevereHair   ()     const { return hasHollyHair; }
        bool hasExcaliburSword  ()     const { return hasExcalibur; }
        void printInfo          ()     const;
        void printResult        (bool) const;
};


//==========* EVENTS *==========//
class Events 
{
    int   e;      // number of events
    int * eventID;      // event code

    public:
        Events    (const string &);
        ~Events   ();
        int count ()    const;
        int get   (int) const;
};

class KnightAdventure
{
    ArmyKnights * armyKnights;
    Events      * events;

    public:
        KnightAdventure      ();
        ~KnightAdventure     ();
        void loadArmyKnights (const string &);
        void loadEvents      (const string &);
        void run             ();
};

//==========* USEFUL - FUNCTIONS *==========//

bool isPrime (int);
bool isPythagoreanTriple (int);
bool isElite (BaseKnight *);

#endif // __KNIGHT2_H__