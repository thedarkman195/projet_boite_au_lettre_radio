#ifndef PCF8591_H
#define PCF8591_H

class PCF8591 {
public:
    PCF8591(int address);
    int readAIN1();
    ~PCF8591();

private:
    int fd;
    static const int AIN0 = 0;
};

#endif // PCF8591_H