class PhysicsEngine
{

    std::vector<Object *> *objects; //pointer to scene objects
    Scene *scene;

    std::vector<Object *> collisions;
    std::vector<Object *> CleanUpCrew;

    float SearchRadius;
    float WideCheckRange;
    bool Debug = false;
    const int NEARLIMIT = 5; //How many objects are we going to test nearby

  public:
    PhysicsEngine(std::vector<Object *> *_o = {nullptr}, std::vector<Object *> *_c = {nullptr}) : objects(_o), collisions({}) {}
    void WideSort();
    void NearHandle();
    void AddToCleanUpCrew(Object *o);
    void RemoveFromCleanUp(Object *o);
    void CleanUp();
    void PhysicsDebug(Object *o, bool condition);
    void CollisionsDebug();
    std::vector<Object *> GetCollisions() { return collisions; }
    //const std::vector<Object*> *GetCollisions() const {return collisions;}
    void SetObjectCollisionRefrence();
    void Update()
    {
        WideSort();
        NearHandle();
    }
    void RemoveCollisions(Object *o);
    //void AddCollisions(Object* o);
    inline void SetDebug(bool b) { Debug = b; }
    inline bool RangeCheck(Object *l, Object *r, float max);
    //void SetWorldTransform(Vector2& t){WorldTransform = &t;}
    inline void SetObjects(std::vector<Object *> *o) { objects = o; }
    inline std::vector<Object *> *GetObjects() { return objects; }
    inline CoreEngine *GetEngine() { return Engine; }
    inline void SetEngine(CoreEngine *e) { this->Engine = e; }
    inline void SetUI(UIEngine *ui) { this->UI = ui; }

    ~PhysicsEngine()
    {
        delete objects;
        delete Engine;
        delete UI;
        
        if (collisions.size() != 0)
        {
            for (int i = 0; i < collisions.size(); i++)
            {
                delete collisions.at(i);
            }
        }

        if (CleanUpCrew.size() != 0)
        {
            for (int i = 0; i < CleanUpCrew.size(); i++)
            {
                delete CleanUpCrew.at(i);
            }
        }
    }

  protected:
    CoreEngine *Engine;
    UIEngine *UI;

  private:
};

#include "PhysicsEngine.cpp"
#include "PhysicsEngine.inl"
