#include "knight2.h"

//=====* BEGIN implementation of class BaseItem *=====//
bool BaseBag::canUse (BaseKnight* knight, ItemType itemType) 
{
    int maxHP     = knight->getMaxHP();
    int currentHP = knight->getHP();
    switch (itemType)
    {
        case PHOENIX_I: 
            if (currentHP <= 0) return true;
        case PHOENIX_II:
            if (currentHP < (maxHP / 4) )
                return true;
        case PHOENIX_III:
            if (currentHP < (maxHP / 3) )
                return true;
        case PHOENIX_IV:
            if (currentHP < (maxHP / 2) )
                return true;

        default: return false;
    }
}

void PhoenixDown::use (BaseKnight* knight)
{
    int maxHP     = knight->getMaxHP();
    int currentHP = knight->getHP();
    switch (itemType)
    {
        case PHOENIX_I:
            if (currentHP <= 0)
            {
                knight->setHP(maxHP);
                if (knight->getHP() > knight->getMaxHP())
                    knight->setHP(knight->getMaxHP());
                knight->bag->removeOne(PHOENIX_I);
            }
            return;

        case PHOENIX_II:
            if (currentHP < (maxHP / 4) )
            {
                knight->setHP(maxHP);
                if (knight->getHP() > knight->getMaxHP())
                    knight->setHP(knight->getMaxHP());
                knight->bag->removeOne(PHOENIX_II);
            }
            return;

        case PHOENIX_III:
            if (currentHP < (maxHP / 3) )
            {
                (currentHP <= 0)? knight->setHP(maxHP/3) : 
                                knight->setHP(currentHP + (maxHP / 4));
                if (knight->getHP() > knight->getMaxHP())
                    knight->setHP(knight->getMaxHP());
                knight->bag->removeOne(PHOENIX_III);
            }
            return;

        case PHOENIX_IV:
            if (currentHP < (maxHP / 2) )
            {
                (currentHP <= 0)? knight->setHP(maxHP/2) : 
                                knight->setHP(currentHP + (maxHP / 5));
                if (knight->getHP() > knight->getMaxHP())
                    knight->setHP(knight->getMaxHP());
                knight->bag->removeOne(PHOENIX_IV);
            }
            return;
            
        default: return;
    }
}
//=====* END implementation of class BaseItem *=====//





//=====* BEGIN implementation of class BaseBag *=====//

// toString() methods for Knight's Bag
string BaseBag::toString () const
{
    stringstream ssBag;
    string typeString[] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    ssBag << "Bag[count=" << (((antidoteCount + phoenixCount)  > maxCapacity)? 
                                maxCapacity : (antidoteCount + phoenixCount) ) << ";";
    BaseItem * current = head;
    int count = 0;
    while(current && (count < maxCapacity) && (antidoteCount + phoenixCount))
    {
        BaseItem * item = current;
        ssBag << typeString[item->getItemType()];
        current = current->next;

        if (current && (count < maxCapacity - 1)) ssBag << ",";
        count++;
    }
    ssBag << "]"; return ssBag.str();
}

// insertFirst(), removeItem() and get() methods for Knight's Bag
bool BaseBag::insertFirst (BaseItem * item)
{
    if (!item)  return false;
    if (!head)  head = item;
    else
    {
        item->next = head;
        head       = item;
    }
    if (item->getItemType() == ANTIDOTE) 
         antidoteCount++;
    else phoenixCount++;

    return true;
}
bool BaseBag::removeFirst ()
{
    if (!head) return false;
    (head->getItemType() == ANTIDOTE)? antidoteCount-- : phoenixCount--;
    BaseItem * temp = head;
    head = head->next;
    delete temp;
    return true;
}
bool BaseBag::removeOne(ItemType itemType)
{
    if (!head)  return false;
    BaseItem * current = head;
    BaseItem * prev    = nullptr;
    while (current)
    {
        if (current->getItemType() == itemType)
        {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;

            if (itemType == ANTIDOTE) antidoteCount--;
            else phoenixCount--;
            return true;
        }
        prev    = current;
        current = current->next;
    }
    return false;
}
bool BaseBag::removeAll ()
{
    if (!head) return false;
    BaseItem * current = head;
    while (current)
    {
        BaseItem * temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    antidoteCount = 0;
    phoenixCount  = 0;
    return true;
}
BaseItem * BaseBag::getPhoenix(BaseKnight * knight) // returns the first item in the bag
{
    if (!head) return nullptr;
    BaseItem * item = head;
    while ( item && !(knight->bag->canUse(knight, item->getItemType() )) )
        item = item->next;
    return item;
}
//=====* END implementation of class BaseBag *=====//





//=====* BEGIN implementation of class BaseKnight *=====//
string BaseKnight::toString () const 
{
    string typeString[] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    return "[Knight:id:"      + to_string(id) 
         + ",hp:"             + to_string(hp) 
         + ",maxhp:"          + to_string(maxhp)
         + ",level:"          + to_string(level)
         + ",gil:"            + to_string(gil)
         + ","                + bag->toString()
         + ",knight_type:"    + typeString[knightType]
         + "]";
}

BaseKnight * BaseKnight::create (int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight * knight = nullptr;
    if (isPrime(maxhp))
        knight = new 
            Paladin(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (maxhp == 888)
        knight = new 
            Lancelot(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (isPythagoreanTriple(maxhp))
        knight = new 
            DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else
        knight = new 
            NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    return knight;
}

bool BaseKnight::isAlive()
{
    BaseItem * item = bag->getPhoenix(this);
    if (item) { item->use(this); return true; }

    if (this->hp <= 0)
    {
        if (this->gil >= 100)
        {
            this->hp   = this->maxhp / 2;
            this->gil -= 100;
        }
        else return false;
    }
    return true;
}

// fight() methods for BaseKnight
bool Paladin::fight (BaseOpponent * opponent)
{
    int typeO      = opponent->getTypeO();
    int levelO     = opponent->getLevelO();

    if (typeO <= Troll)    // if the knight encounters any of the first 5 minions
        { this->gil += opponent->getGilO(); return true; }
    if (typeO == Tornbery)  // witch
    {
        if (this->level >= levelO)
        {
            this->level++;
            if (this->level > 10) this->level = 10;
            return true;
        }
        else
        {
            if (antidote) this->bag->removeOne(ANTIDOTE);
            else 
            {
                if (this->bag->getNumberOfItems() <= 3)
                    this->bag->removeAll(); 
                else for (int i = 0; i < 3; i++)
                    this->bag->removeFirst();
                this->hp -= 10; isAlive();
                return true;
            }
        }
    }
    if (typeO == QueenOfCards) // nhaCaiSoMotChauAu
    {
        if (this->level >= levelO) this->gil *= 2;
        return true;
    }
    if (typeO == NinaDeRings) // wandering trader
    {
        if (this->hp < this->maxhp / 3)
        {
            this->hp += this->maxhp / 5;
            if (this->gil >= 50) this->gil -= 50;
            return true;
        }
    }
    if (typeO == DurianGarden) // cloud garden
        { this->hp = this->maxhp; return true; }
    if (typeO == OmegaWeapon && !encounteredOmegaWeapon) // powerful ancient monster, has been around since the beginning of time
    {
        encounteredOmegaWeapon = true;
        if (this->level == 10 && this->hp == this->maxhp)
            { this->gil = 999; return true; }
        else { this->hp = 0; return this->isAlive(); }
    }
    if (typeO == Hades && !encounteredHades) // the god of Death
    {
        encounteredHades = true; 
        if (this->level >= 8) 
            { defeatedHades = true; return true; } 
        else { this->hp = 0;  return this->isAlive(); }
    }
    return true;
}

bool Lancelot::fight (BaseOpponent * opponent)
{
    int typeO      = opponent->getTypeO();
    int levelO     = opponent->getLevelO();

    if (typeO <= Troll)    // if the knight encounters any of the first 5 minions
        { this->gil += opponent->getGilO(); return true; }
    if (typeO == Tornbery)  // witch
    {
        if (this->level >= levelO)
        {
            this->level++;
            if (this->level > 10) this->level = 10;
            return true;
        }
        else
        {
            if (antidote) this->bag->removeOne(ANTIDOTE);
            else 
            {
                if (this->bag->getNumberOfItems() <= 3)
                    this->bag->removeAll(); 
                else for (int i = 0; i < 3; i++)
                    this->bag->removeFirst();
                this->hp -= 10; isAlive();
                return true;
            }
        }
    }
    if (typeO == QueenOfCards) // nhaCaiSoMotChauAu
    {
        if (this->level >= levelO) this->gil *= 2;
        else this->gil /= 2;
        return true;
    }
    if (typeO == NinaDeRings) // wandering trader
    {
        if (this->gil < 50) return true;
        if (this->hp < this->maxhp / 3)
        {
            this->gil -= 50;
            this->hp  += this->maxhp / 5;
            if (this->hp > this->maxhp) this->hp = this->maxhp;
            return true;
        }
    }
    if (typeO == DurianGarden) // cloud garden
        { this->hp = this->maxhp; return true; }
    if (typeO == OmegaWeapon && !encounteredOmegaWeapon) // powerful ancient monster, has been around since the beginning of time
    {
        encounteredOmegaWeapon = true;
        if (this->level == 10 && this->hp == this->maxhp)
            { this->gil = 999; return true; }
        else { this->hp = 0; return this->isAlive(); }
    }
    if (typeO == Hades && !encounteredHades) // the god of Death
    {
        encounteredHades = true; 
        if (this->level == 10) 
            { defeatedHades = true; return true; }
        else { this->hp = 0;  return this->isAlive(); }
    }
    return true;
}

bool DragonKnight::fight (BaseOpponent * opponent)
{
    int typeO      = opponent->getTypeO();
    int levelO     = opponent->getLevelO();

    if (typeO <= Troll)    // if the knight encounters any of the first 5 minions
    {
        if (this->level >= levelO)
            { this->gil += opponent->getGilO(); return true; }
        else
        {
            int baseDmgO = opponent->getBaseDamageO();
            this->hp -= baseDmgO * (levelO - this->level);
            return this->isAlive();
        }
    }
    if (typeO == Tornbery)  // witch
    {
        if (this->level >= levelO)
        {
            this->level++;
            if (this->level > 10) this->level = 10;
            return true;
        }
    }
    if (typeO == QueenOfCards) // nhaCaiSoMotChauAu
    {
        if (this->level >= levelO) this->gil *= 2;
        else this->gil /= 2;
        return true;
    }
    if (typeO == NinaDeRings) // wandering trader
    {
        if (this->gil < 50) return true;
        if (this->hp < this->maxhp / 3)
        {
            this->gil -= 50;
            this->hp  += this->maxhp / 5;
            if (this->hp > this->maxhp) this->hp = this->maxhp;
            return true;
        }
    }
    if (typeO == DurianGarden) // cloud garden
        { this->hp = this->maxhp; return true; }
    if (typeO == OmegaWeapon && !encounteredOmegaWeapon) // powerful ancient monster, has been around since the beginning of time
    {
        encounteredOmegaWeapon = true;
        this->level = 10;
        this->gil   = 999; return true;
    }
    if (typeO == Hades && !encounteredHades) // the god of Death
    {
        encounteredHades = true; 
        if (this->level == 10) 
            { defeatedHades = true; return true; } 
        else { this->hp = 0;  return this->isAlive(); }
    }
    return true;
}

bool NormalKnight::fight (BaseOpponent * opponent)
{
    int typeO      = opponent->getTypeO();
    int levelO     = opponent->getLevelO();

    if (typeO <= Troll)    // if the knight encounters any of the first 5 minions
    {
        if (this->level >= levelO)
            { this->gil += opponent->getGilO(); return true; }
        else
        {
            int baseDmgO = opponent->getBaseDamageO();
            this->hp -= baseDmgO * (levelO - this->level);
            return this->isAlive();
        }
    }
    if (typeO == Tornbery)  // witch
    {
        if (this->level >= levelO)
        {
            this->level++;
            if (this->level > 10) this->level = 10;
            return true;
        }
        else
        {
            if (antidote) this->bag->removeOne(ANTIDOTE);
            else 
            {
                if (this->bag->getNumberOfItems() <= 3)
                    this->bag->removeAll(); 
                else for (int i = 0; i < 3; i++)
                    this->bag->removeFirst();
                this->hp -= 10; isAlive();
                return true;
            }
        }
    }
    if (typeO == QueenOfCards) // nhaCaiSoMotChauAu
    {
        if (this->level >= levelO) this->gil *= 2;
        else this->gil /= 2;
        return true;
    }
    if (typeO == NinaDeRings) // wandering trader
    {
        if (this->gil < 50) return true;
        if (this->hp < this->maxhp / 3)
        {
            this->gil -= 50;
            this->hp  += this->maxhp / 5;
            if (this->hp > this->maxhp) this->hp = this->maxhp;
            return true;
        }
    }
    if (typeO == DurianGarden) // cloud garden
        { this->hp = this->maxhp; return true; }
    if (typeO == OmegaWeapon && !encounteredOmegaWeapon) // powerful ancient monster, has been around since the beginning of time
    {
        encounteredOmegaWeapon = true;
        if (this->level == 10 && this->hp == this->maxhp)
            { this->gil = 999; return true; }
        else { this->hp = 0; return this->isAlive(); }
    }
    if (typeO == Hades && !encounteredHades) // the god of Death
    {
        encounteredHades = true; 
        if (this->level == 10) 
            { defeatedHades = true; return true; }
        else { this->hp = 0;  return this->isAlive(); }
    }
    return true;
}
//=====* END implementation of class BaseKnight *=====//





//=====* BEGIN implementation of class Events *=====//
Events::Events (const string & file_events)
{
    ifstream file (file_events);
    if (file.is_open())
    {
        file >> e; eventID = new int[e];       // allocating memory for 'e' events
        for (int i = 0; i < e; i++) 
            file >> eventID[i];
        file.close();
    } 
}
Events::~Events () 
    { delete [] eventID; eventID = nullptr; }

int Events::count () const
    { return e; }
int Events::get (int i) const 
    { return eventID[i]; }

//=====* END implementation of class Events *=====//




//=====* BEGIN implementation of class ArmyKnights *=====//

void ArmyKnights::printInfo() const 
{
    cout << "No. knights: " << this->count();
    if (this->count()) 
    {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:"  << this->hasPaladinShield()
         << ";LancelotSpear:"  << this->hasLancelotSpear()
         << ";GuinevereHair:"  << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
                               << endl
         << string(50, '-')    << endl;
}

ArmyKnights::ArmyKnights (const string & file_armyknights)
{
    ifstream file (file_armyknights);
    if (!file.is_open()) return;

    file >> numberOfKnights;
    knight = new BaseKnight * [numberOfKnights];

    for (int id = 1; id <= numberOfKnights; id++)
    {
        int     maxhp,   level,   phoenix,   gil,   antidote;
        file >> maxhp >> level >> phoenix >> gil >> antidote;
        knight[id-1] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenix);
    }
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < numberOfKnights; i++) delete knight[i];
    delete [] knight; knight = nullptr;
}

int ArmyKnights::count () const
    { return numberOfKnights; }

BaseKnight * ArmyKnights::lastKnight () const
{ 
    if (!numberOfKnights) return nullptr;
    return knight [numberOfKnights - 1]; 
}

void ArmyKnights::removeKnight(int position)
{
    if (!numberOfKnights || position < 0 || position > numberOfKnights-1) return;
    delete knight[position];
    for (int i = position; i < numberOfKnights - 1; i++)
        knight[i] = knight[i+1];
    numberOfKnights--;
}

bool ArmyKnights::adventure(Events * events)
{
    int evCount = events->count();
    for (int i = 0; i < evCount; i++)
    {
        if (!this->count()) return false;
        fight(events->get(i), i);
        printInfo();
    }
    return this->numberOfKnights;
}

bool ArmyKnights::fight (int eventID, int eventOrder)
{
    if (eventID == pickupPaladinsShield) { hasShield    = true; return true; } 
    if (eventID == pickupLancelotsSpear) { hasSpear     = true; return true; }
    if (eventID == pickupGuineveresHair) { hasHollyHair = true; return true; }
    if (eventID == pickupExcalibur)
    {
        if (hasShield && hasSpear && hasHollyHair)
            hasExcalibur = true; return true;
    }
    if (eventID == lootPhoenixII)  { lootItem(this->numberOfKnights - 1, PHOENIX_II); }
    if (eventID == lootPhoenixIII) { lootItem(this->numberOfKnights - 1, PHOENIX_III); }
    if (eventID == lootPhoenixIV)  { lootItem(this->numberOfKnights - 1, PHOENIX_IV); }

    BaseOpponent * opponent;
    int typeO        = eventID;
    int levelO       = (eventOrder + typeO) % 10 + 1;
    int gilsO     [] = { 0, 100, 150, 450, 750, 800 };
    int baseDmgsO [] = { 0, 10,  15,  45,  75,  95 };

    if (typeO >= MadBear && typeO <= Troll)
        opponent = new BaseOpponent (levelO, typeO, gilsO[eventID], baseDmgsO[eventID]);
    else opponent = new BaseOpponent (levelO, typeO, gilsO[0], baseDmgsO[0]);

    if (typeO == UltimeciaBoss)
    {
        if (hasExcalibur) return true;
        if (hasShield && hasSpear && hasHollyHair)
        {
            int bossHP = 5000;
            for (int i = numberOfKnights - 1; i >= 0; i--)
            {
                bossHP -= knight[i]->getHP() * knight[i]->getLevel() * knight[i]->getBaseDmg();
                if (bossHP > 0 && isElite(knight[i]) ) removeKnight(i);
                else if (bossHP <= 0) return true; 
            }
        }
        numberOfKnights = 0; return false;
    }

    // for (int i = numberOfKnights - 1; i >= 0; i--)
    // {
        int i = numberOfKnights - 1; if (i < 0) return false;
        bool knightAlive = knight[i]->fight(opponent);
        (knightAlive)?  passGil(i) : removeKnight(i);
        if (knightAlive && typeO == Hades && defeatedHades) 
            this->hasShield = true;
    // }
    return false;
}

void ArmyKnights::passGil (int position)
{
    if (!position && knight[position]->getGil() > 999)  
        { knight[position]->setGil(999); return; }
    for (int p = position; p > 0; p--)
    {
        if (knight[p]->getGil() > 999)
        {
            int extraGil = knight[p]->getGil() - 999;
            knight[p - 1]->setGil(knight[p - 1]->getGil() + extraGil);
            knight[p]->setGil(999);
        }
    }
}

void ArmyKnights::lootItem (int position, ItemType itemType)
{
    BaseItem * item;
        if (itemType == ANTIDOTE)    return;
                            else     item = new PhoenixDown (itemType);

    if (!position) { knight[position]->bag->insertFirst(item); return; }
    for (int p = position; p > 0; p--)
    {
        if (knight[p]->bag->getNumberOfItems() >= knight[p]->bag->getMaxCapacity())
        {
            if (!position) return;
            knight[p - 1]->bag->insertFirst(item);
        }
        else { knight[p]->bag->insertFirst(item); return; }
    }
    return;
}

void ArmyKnights::printResult(bool win) const 
    { cout << (win ? "WIN" : "LOSE") << endl; }
//=====* END implementation of class ArmyKnights *=====//





//=====* BEGIN implementation of class KnightAdventure *=====//
KnightAdventure::KnightAdventure () 
{ armyKnights = nullptr; events = nullptr; }

void KnightAdventure::loadArmyKnights (const string & file_armyknights)
{ armyKnights = new ArmyKnights(file_armyknights); }    

void KnightAdventure::loadEvents (const string & file_events)
{ events = new Events(file_events); }

void KnightAdventure::run ()
{
    if (armyKnights && events) armyKnights->adventure(events);
    armyKnights->printResult(armyKnights->count());
}

KnightAdventure::~KnightAdventure ()
{
    if (armyKnights) { delete armyKnights; armyKnights = nullptr; }
    if (events)      { delete events;      events = nullptr; }
}
//===== END implementation of class KnightAdventure =====//




//==========* USEFUL - FUNCTIONS *==========//
bool isPrime (int hp)
{
    if (hp < 2) return false;
    for (int i = 2; i * i <= hp; i++)
        if (!(hp % i))   return false;
    return true;
}

bool isPythagoreanTriple (int hp) // only works with 0 < knight's HP < 1000 (guaranteed constraint)
{
    string digits = to_string(hp);
    if (digits.length() != 3) return false;
    else if (digits.find("3") != string::npos &&
             digits.find("4") != string::npos &&
             digits.find("5") != string::npos)  return true;
    return false;
}

bool isElite (BaseKnight * knight)
{
    return (knight->getTypeK() == PALADIN ||
            knight->getTypeK() == LANCELOT ||
            knight->getTypeK() == DRAGON);
}
//==========* USEFUL - FUNCTIONS *==========//