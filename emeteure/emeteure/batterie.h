#pragma once
#ifndef batterie_h
#define batterie_h

class batterie {
public:
    batterie(int address);
    int readAIN1();
    ~batterie();

private:
    int fd;
    static const int AIN0 = 0;
};

#endif // batterie_h
