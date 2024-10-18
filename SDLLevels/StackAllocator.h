#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

// Code for Stack Based Allocator for Dynamic Memory Allocation
class StackAllocator
{
public:
	// Constructors and Destructors
	StackAllocator();
	virtual ~StackAllocator();

	// Accessors
	unsigned char* GetMarker() { return m_marker; }
	int GetBytesUsed() { return m_stackPosition - m_stackStart; }

	// Methods
	void AllocateStack(unsigned int _stackSizeBytes);
	unsigned char* GetMemory(unsigned int _sizeBytes);
	void Mark();
	void FreeToMarker();
	void ClearMemory();

private:
	// Members
	unsigned char* m_marker;
	unsigned char* m_stackStart;
	unsigned char* m_stackPosition;
	unsigned char* m_stackEnd;
};
#endif // STACK_ALLOCATOR_H

