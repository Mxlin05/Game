#pragma once

class IndexBuffer{
public:
    
    unsigned int count;
    IndexBuffer();
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    unsigned int getCount() const { return count; }
    void setData(const void* data, unsigned int count);

private:
    unsigned int renderID;
};