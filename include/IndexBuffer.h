#pragma once

class IndexBuffer{
public:
    
    unsigned int count;
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    unsigned int getCount() const { return count; }

private:
    unsigned int renderID;
};