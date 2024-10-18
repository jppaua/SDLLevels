#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include "TGAReader.h"

class Asset;

class Texture : public Resource
{
public:
    // Constructors/Destructors
    Texture();
    virtual ~Texture();

    // Accessors
    Asset* GetData() { return m_texture; }
    ImageInfo* GetImageInfo() { return &m_imageInfo; }

    // Methods
    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;
    void ToString() override;
    void Load(string guid);

    // Members
    static ObjectPool1<Texture>* Pool;

private:
    ImageInfo m_imageInfo;
    Asset* m_texture;
};

#endif // TEXTURE_H