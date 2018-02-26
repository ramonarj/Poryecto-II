#pragma once
#include "LogicComponent.h"
enum ItemType{Palo, Plancha, Tuberia, Hacha, Alcohol, Vendas, Botiquin, QuimicoGenerico, QuimiciAcido,
				Acido, Biocida, PiezaPuzzle, Tarjeta, Llave, CintaAislante, Foto};

class Item : public LogicComponent//, public Observable
{
public:
	Item(ItemType type);
	virtual ~Item();
	virtual void update();
private:
	ItemType type;
};

