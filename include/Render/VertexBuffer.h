#pragma once

class VertexBuffer{
public:
    VertexBuffer();
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    void setData(const void* data, unsigned int size);


private:
    unsigned int renderID;
};