#pragma once
#include "baseTile.h"
class caveBasic :
    public baseTile
{

public:


    caveBasic(int type = NULL) {
        isSolid = false;
        init(type);
    }

    void init(int type = NULL) override;


};


