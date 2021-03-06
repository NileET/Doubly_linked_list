#ifndef DEVICE_HPP
#define DEVICE_HPP
#include <string>


class Device {
protected:
    struct Size {
        double  __width,
                __length,
                __high;
    };
public:
    Device();

    Device(const std::string   modelName,
           const int           portCount,
           const Size          modelSize);

    Device(const Device& rhs);

    Device& operator=(const Device& rhs);

    virtual ~Device();

    friend std::ostream& operator<<(std::ostream& stream, const Device& item);

    void setModelName(const std::string& modelName);
    std::string getModelName() const;

    void setPortCount(const int& portCount);
    int getPortCount() const;

    void setModelSize(const Size& modelSize);
    Size getModelSize() const;

private:
    std::string _modelName;
    int _portCount;
    Size _modelSize;
};


#endif //DEVICE_HPP
