#ifndef RESOURCE_H
#define RESOURCE_H

#include "Serializable.h"
// Code for Object pooling Allocator for Composition Pattern
#include "ObjectPool1.h"
// Code for Serilializing and Deserializing the resources composed of assets
// This process will fix-up asset pointers
#include "AssetController.h"

class Resource
{
public:
	// Constructors and Destructors
	Resource();
	virtual ~Resource();

	// Methods
	virtual void Serialize(std::ostream& _stream);
	virtual void Deserialize(std::istream& _stream);
	/*
	void AssignNonDefaultValues();
	void ToString();
	*/
	// Code for WEEK 4 for LEVEL MANAGEMENT
	virtual void AssignNonDefaultValues();
	virtual void ToString();

	// Code for Object pooling Allocator for Composition Pattern
	// Members
	static ObjectPool1<Resource>* Pool;

	// Code for Serilializing and Deserializing the resources composed of assets
	// This process will fix-up asset pointers

protected:

	// Code for WEEK 4 for LEVEL MANAGEMENT
	// Members
	template<class T>
	void SerializePointer(std::ostream& _stream, Resource* _pointer)
	{
		byte exists = 1;
		if (_pointer != nullptr)
		{
			_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
			_pointer->Serialize(_stream);
		}
		else
		{
			exists = 0;
			_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
		}
	}

	// Code for WEEK 4 for LEVEL MANAGEMENT
	template<class T>
	void DeserializePointer(std::istream& _stream, Resource* _pointer)
	{
		byte exists = 0;
		_stream.read(reinterpret_cast<char*>(&exists), sizeof(exists));
		if (exists == 1)
		{
			_pointer = T::Pool->GetResource();
			_pointer->Deserialize(_stream);
		}
	}

	//protected:
		//void SerializePointer(std::ostream& _stream, Resource* _pointer);
		//void DeserializePointer(std::istream& _stream, Resource* _pointer);
	void SerializeAsset(std::ostream& _stream, Asset* _asset);
	void DeserializeAsset(std::istream& _stream, Asset* _asset);

private:
	/*
	// Comment the this section of code for WEEK 4 for LEVEL MANAGEMENT
	int m_val1;
	double m_val2;
	char m_val3;
	// Code for Object pooling Allocator for Composition Pattern
	Resource* m_subResource;
	// Code for Serilializing and Deserializing the resources composed of assets
	// This process will fix-up asset pointers
	Asset* m_asset;
	*/
};

#endif // !RESOURCE_H
