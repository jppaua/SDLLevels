#include "Asset.h"

// Code for WEEK 4 for ASSET MANAGEMENT

ObjectPool1<Asset>* Asset::Pool;

Asset::Asset()
{
	m_GUID = "";
	m_dataSize = 0;
	m_data = nullptr;
}

// Code for Serilializing and Deserializing the resources composed of assets
// This process will fix-up asset pointers

void Asset::ToString()
{
	cout << "Asset GUID: " << m_GUID << endl;
	cout << "Asset Data Size: " << m_dataSize << endl;
}
