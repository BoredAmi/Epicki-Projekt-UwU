
#ifndef ENTITY_H
#define ENTITY_H

class entity
{
public:
    int getX() const;
    int getY() const;
    int getHp() const;
    void setPosition(int x, int y);
     entity(int x, int y, int hp) : x(x), y(y), hp(hp) {}
    virtual ~entity();
protected:
    int x;
    int y;
    int hp;
};

#endif // ENTITY_H
