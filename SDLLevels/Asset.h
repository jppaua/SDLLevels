#ifndef ASSET_H
#define ASSET_H

// Code for WEEK 4 for ASSET MANAGEMENT

#include "StandardIncludes.h"
#include "ObjectPool1.h"

class Asset
{
public:
    // Constructors / Destructors
    Asset();
    virtual ~Asset() {}

    // Accessors
    string GetGUID() { return m_GUID; }
    int GetDataSize() { return m_dataSize; }
    void SetDataSize(int _size) { m_dataSize = _size; }
    byte* GetData() { return m_data; }
    void SetData(byte* _data) { m_data = _data; }
    // Code for Serilializing and Deserializing the resources composed of assets
    // This process will fix-up asset pointers
    void SetGUID(string _guid) { m_GUID = _guid; }

    // Methods
    static ObjectPool1<Asset>* Pool;
    // Code for Serilializing and Deserializing the resources composed of assets
    // This process will fix-up asset pointers
    void ToString();

private:
    // Members
    string m_GUID;
    int m_dataSize;
    byte* m_data;
};

#endif // ASSET_H