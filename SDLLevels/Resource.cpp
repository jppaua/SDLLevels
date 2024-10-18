#include "Resource.h"

// Code for Object pooling Allocator for Composition Pattern
ObjectPool1<Resource>* Resource::Pool;

Resource::Resource()
{
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	m_val1 = 0;
	m_val2 = 0.0f;
	m_val3 = { };
	// Code for Object pooling Allocator for Composition Pattern
	m_subResource = nullptr;
	// Code for Serilializing and Deserializing the resources composed of assets
	// This process will fix-up asset pointers
	m_asset = nullptr;
	*/

}

Resource::~Resource()
{
}

void Resource::AssignNonDefaultValues()
{
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	m_val1 = 2;
	m_val2 = 2.0f;
	m_val3 = '2';
	// Code for Object pooling Allocator for Composition Pattern
	m_subResource = Resource::Pool->GetResource();
	m_subResource->m_val1 = 3;
	m_subResource->m_val2 = 3.0;
	m_subResource->m_val3 = '3';
	// Code for Serilializing and Deserializing the resources composed of assets
	// This process will fix-up asset pointers
	m_asset = AssetController::Instance().GetAsset("1.jpg");
	*/
}

void Resource::ToString()
{
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	cout << "m_val1: " << m_val1 << " ";
	cout << "m_val2: " << m_val2 << " ";
	cout << "m_val3: " << m_val3 << " " << endl;
	// Code for Object pooling Allocator for Composition Pattern
	if (m_subResource != nullptr)
	{
		m_subResource->ToString();
	}
	// Code for Serilializing and Deserializing the resources composed of assets
	// This process will fix-up asset pointers
	if (m_asset != nullptr)
	{
		m_asset->ToString();
	}
	*/
	//cout << "BASE RESOURCE" << endl;
}

// Code for Serilializing and Deserializing the resources composed of assets
// This process will fix-up asset pointers
void Resource::SerializeAsset(std::ostream& _stream, Asset* _asset)
{
	byte guidLength = 0;
	if (_asset != nullptr)
	{
		guidLength = _asset->GetGUID().length();
	}
	_stream.write(reinterpret_cast<char*>(&guidLength), sizeof(guidLength));
	if (guidLength > 0)
	{
		_stream.write(_asset->GetGUID().c_str(), guidLength);
	}
}

void Resource::DeserializeAsset(std::istream& _stream, Asset* _asset)
{
	byte guidLength = 0;
	_stream.read(reinterpret_cast<char*>(&guidLength), sizeof(byte));
	if (guidLength > 0)
	{
		char guid[300];
		_stream.read(guid, guidLength);
		guid[guidLength] = 0;	// null terminate string
		_asset = AssetController::Instance().GetAsset(string(guid));
	}
}

// End of Code for Week 4

void Resource::Serialize(std::ostream& _stream)
{
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	_stream.write(reinterpret_cast<char*>(&m_val1), sizeof(m_val1));
	_stream.write(reinterpret_cast<char*>(&m_val2), sizeof(m_val2));
	_stream.write(reinterpret_cast<char*>(&m_val3), sizeof(m_val3));
	//SerializePointer(_stream, m_subResource);
	SerializeAsset(_stream, m_asset);
	/*
	// Code for Object pooling Allocator for Composition Pattern
	byte exists = 1;
	if (m_subResource != nullptr)
	{
		_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
		m_subResource->Serialize(_stream);
	}
	else
	{
		exists = 0;
		_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
	}
	*/
}

void Resource::Deserialize(std::istream& _stream)
{
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	_stream.read(reinterpret_cast<char*>(&m_val1), sizeof(m_val1));
	_stream.read(reinterpret_cast<char*>(&m_val2), sizeof(m_val2));
	_stream.read(reinterpret_cast<char*>(&m_val3), sizeof(m_val3));
	//DeserializePointer(_stream, m_subResource);
	DeserializeAsset(_stream, m_asset);
	/*
	// Code for Object pooling Allocator for Composition Pattern
	byte exists = 0;
	_stream.read(reinterpret_cast<char*>(&exists), sizeof(byte));
	if (exists == 1)
	{
		m_subResource = Resource::Pool->GetResource();
		m_subResource->Deserialize(_stream);
	}
	*/
}
