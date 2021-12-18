#pragma once
#include "baseTile.h"
class caveBasic :
    public baseTile
{

public:


    caveBasic(int xVal, int yVal ,int type = NULL) : baseTile(xVal, yVal, type) {
        isSolid = false;
        init(type);
    }

    void init(int type = NULL) override;


};


