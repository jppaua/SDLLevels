#include "SpriteAnim.h"
#include <iostream>

ObjectPool1<SpriteAnim>* SpriteAnim::Pool;

SpriteAnim::SpriteAnim()
{
    ClearMemory();
}

SpriteAnim::~SpriteAnim()
{
}

void SpriteAnim::Create(short _clipStart, short _clipCount, float _clipSpeed)
{
    m_clipStart = _clipStart;
    m_clipCount = _clipCount;
    m_clipSpeed = _clipSpeed;
    m_clipCurrent = _clipStart;
    m_clipEnd = m_clipStart + m_clipCount;
    m_timeAccumulator = 0.0f; 
}

void SpriteAnim::ClearMemory()
{
    m_clipStart = 0;
    m_clipCount = 0;
    m_clipCurrent = 0;
    m_timeAccumulator = 0.0f;
}

void SpriteAnim::Update(float _deltaTime) {
    
    if (_deltaTime > 0.1f) {
        _deltaTime = 0.1f;
    }

    std::cout << "Updating animation, deltaTime: " << _deltaTime
        << ", clipSpeed: " << m_clipSpeed
        << ", accumulated time: " << m_timeAccumulator << std::endl;

    m_timeAccumulator += _deltaTime;

    
    float frameDuration = 1.0f / m_clipSpeed;

    while (m_timeAccumulator >= frameDuration) {
        m_timeAccumulator -= frameDuration;
        m_clipCurrent += 1;

        if (m_clipCurrent >= m_clipEnd) {
            m_clipCurrent = m_clipStart;
        }

        std::cout << "Frame advanced to: " << m_clipCurrent
            << ", time remaining in accumulator: " << m_timeAccumulator << std::endl;
    }
}

void SpriteAnim::Serialize(std::ostream& _stream)
{
    _stream.write(reinterpret_cast<char*>(&m_clipStart), sizeof(m_clipStart));
    _stream.write(reinterpret_cast<char*>(&m_clipCount), sizeof(m_clipCount));
    _stream.write(reinterpret_cast<char*>(&m_clipSpeed), sizeof(m_clipSpeed));
    Resource resourceInstance;
    resourceInstance.Serialize(_stream);
}

void SpriteAnim::Deserialize(std::istream& _stream)
{
    _stream.read(reinterpret_cast<char*>(&m_clipStart), sizeof(m_clipStart));
    _stream.read(reinterpret_cast<char*>(&m_clipCount), sizeof(m_clipCount));
    _stream.read(reinterpret_cast<char*>(&m_clipSpeed), sizeof(m_clipSpeed));
    m_clipEnd = m_clipStart + m_clipCount;
    Resource resourceInstance;
    resourceInstance.Deserialize(_stream);
}

void SpriteAnim::ToString()
{
    std::cout << "SPRITE ANIMATION: ";
    std::cout << " Clip Start: " << m_clipStart;
    std::cout << " Clip Count: " << m_clipCount << std::endl;
    Resource resourceInstance;
    resourceInstance.ToString();
}
