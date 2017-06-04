#ifndef DXARRAY_H
#define DXARRAY_H

template <class type, int dimision> class DxArray
{
public:
    DxArray() { memset(m_array, 0, sizeof(m_array)); }
    DxArray(type* array, int dimision)
    {
        for(int i = 0; i < dimision; i++)
        {
            this->m_array[i] = array[i];
        }
    }
    DxArray(const DxArray<type, dimision>& other)
    {
        for(int i = 0; i < dimision; i++)
        {
            m_array[i] = other.m_array[i];
        }
    }
    virtual ~DxArray(){};

public:
    DxArray<type, dimision>& operator=(const DxArray<type, dimision>& other)
    {
        for(int i = 0; i < dimision; i++)
        {
            m_array[i] = other.m_array[i];
        }
        return *this;
    }

    type& operator[](int index) { return m_array[index]; }

    const type& operator[](int index) const { return m_array[index]; }

    bool operator==(const DxArray<type, dimision>& other) const
    {
        for(int i = 0; i < dimision; i++)
        {
            if(m_array[i] != other.m_array[i])
            {
                return false;
            }
        }
        return true;
    }

    type* GetPointer() { return m_array; }
    const type* GetPointer() const { return m_array; }

protected:
    type m_array[dimision];
};
#endif
