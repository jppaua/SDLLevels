#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H

#include "StandardIncludes.h"
#include "StackAllocator.h"
#include "Asset.h"

// Code for WEEK 4 for ASSET MANAGEMENT

class AssetController : public Singleton<AssetController>
{
public:
    // Constructors/Destructors
    AssetController();
    virtual ~AssetController();

    // Methods
    void Initialize(int _stackSize);
    Asset* GetAsset(string _guid);
    // Code for WEEK 4 for LEVEL MANAGEMENT
    void Clear();

    // Members
    static StackAllocator* Stack;

private:
    // Members
    map<string, Asset*> m_assets;
};

#endif // ASSET_CONTROLLER_H