#ifndef IDATA_H
#define IDATA_H

template<typename T>
class IData
{
public:
    IData() = default;

    virtual ~IData() = default;

    virtual T toDTO() = 0;
};

#endif // IDATA_H
