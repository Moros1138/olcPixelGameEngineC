#include "engine.h"

bool OnUserCreate()
{
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    return true;
}

bool OnUserDestroy()
{
    return true;
}


int main(int argc, char* argv[])
{
    if(Construct(320, 240, 3, 3, false, false))
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}
