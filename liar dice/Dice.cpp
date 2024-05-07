#include "Dice.h"

Dice::Dice():rd(),gen(rd()),dis(1,6)
{
	Roll();
}

void Dice::Roll()
{
	facd_value = dis(gen);
}

unsigned int Dice::GetFaceValue() const
{
	return facd_value;
}
