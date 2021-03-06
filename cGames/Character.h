class Class
{

public:
  Class(std::wstring _n = L"Defualt") : className(_n){};
  inline std::wstring GetName() { return className; }

protected:
  std::wstring className;
};

class Warrior : public Class
{
public:
  Warrior() : Class(L"Warroir"){};

private:
protected:
};

class Ranger : public Class
{

public:
  Ranger() : Class(L"Ranger"){};

private:
protected:
};

class Mage : public Class
{

public:
  Mage() : Class(L"Mage"){};

private:
protected:
};

class Paladin : public Class
{

public:
  Paladin() : Class(L"Paladin"){};

private:
protected:
};

class Character : public Component
{
  int Health = 100;
  int Armour = 100;
  int Mana = 100;
  int Energy = 100;

  int Strength;
  int Intellect;
  int Agility;
  int Stamina;
  int InventoryMax = 15;

  Object *Selected = nullptr;

  std::shared_ptr<Class> *ClassType;
  Gear gearslots[5];
  std::vector<Item *> Inventory;

public:
  std::wstring ClassName;

  explicit Character(int _s = 1, int _i = 1, int _a = 1, int _st = 1, std::shared_ptr<Class> _ct = std::make_shared<Class>())
      : Strength(_s), Intellect(_i), Agility(_a), Stamina(_st), ClassType(&_ct), ClassName(_ct->GetName()), Inventory()
  {   
    Inventory = std::vector<Item*>(InventoryMax);
    std::fill(Inventory.begin(), Inventory.end(), new Item());
  };

  Item *GetInventoryAt(int i) { return Inventory[i]; }

  std::vector<Item *> GetInventory() { return Inventory; }

  void PopulateInventory()
  {
    for (int i = 0; i < InventoryMax; i++)
    {
      Inventory.push_back(new Item());
      //Inventory.at(i) = new Item();
    }
  }
  void AddToInventory(Item &item)
  {
    for (int i = 0; i < Inventory.size(); i++)
    {
      if (Inventory.at(i)->Type == Item::ITEMTYPE::EMPTY)
      {
        if (std::find(this->Inventory.begin(), this->Inventory.end(), &item) == this->Inventory.end())
        {
          Inventory.at(i) = &item;
          break;
        }
      }
    }
  }
  //std::vector<Item> GetInventory(){return Inventory;}
  void SetSelected(Object *s) { this->Selected = s; }
  Object *GetSelected() { return Selected; }

  void Update()
  {

    if (object->GetComponent<Collider>() != nullptr)
    {

      Collider c = *object->GetComponent<Collider>();

      for (int i = 0; i < c.GetCollisions().size(); i++)
      {

        if (c.GetCollisions().at(i)->GetComponent<Collider>() != nullptr)
        {
          Collider other = *c.GetCollisions().at(i)->GetComponent<Collider>();

          if (other.object->GetTags().at(0) == "Item")
          {
            //object->GetComponent<cSprite>()->SetCol(0x0009);
            AddToInventory(*other.object->GetComponent<Item>());
            other.object->Destroy();
          }
        }
      }
    }
  }

  void RemoveFromInventory(Item *item)
  {
    Inventory.erase(std::remove(Inventory.begin(), Inventory.end(), item), Inventory.end());
  }

  int GetHealth() { return Health; }
  int GetMana() { return Mana; }
  int GetEnergy() { return Energy; }
  int GetStrength() { return Strength; }
  int GetIntellect() { return Intellect; }
  int GetAgility() { return Agility; }
  int GetStamina() { return Stamina; }
  int GetArmour() { return Armour; }

  ~Character()
  {
    delete ClassType;
    delete Selected;
  }

private:
protected:
};