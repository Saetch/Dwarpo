#include "BaseCreature.h"
void BaseCreature::roam()
{
}



void BaseCreature::tick()
{
	printf_s("tick of BaseCreature called! Fix this!\n");
	throw ERROR_CALL_NOT_IMPLEMENTED;
}

