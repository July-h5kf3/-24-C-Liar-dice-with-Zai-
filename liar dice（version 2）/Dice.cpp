#include "Dice.h"

Dice::Dice() :rd(), gen(rd()), dis(1, 6)
{
	face_value = 6;
}

void Dice::Roll()
{
	face_value = dis(gen);
}

unsigned int Dice::GetFaceValue() const
{
	return face_value;
}
