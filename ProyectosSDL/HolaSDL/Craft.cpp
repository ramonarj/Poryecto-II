#include "Craft.h"


Craft::Craft()
{
	description_.addComponent(new TextNote(Game::Instance(), "ItemDescriptions/StickDescription.txt", 250, 100, nullptr));

	SDL_Color c{ 0,255,100,255 };
	description_.getComponent<TextNote>()->setColor(c);
}


Craft::~Craft()
{
	if (Wep != nullptr) delete Wep;
	if (cinta != nullptr) delete cinta;
}

void Craft::update(Entity * e, Uint32 time)
{
}

void Craft::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
	if (inv == nullptr)
		inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>();

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		if ((event.button.x >= RepareButton.x && event.button.x <= RepareButton.x + 200)
			&& (event.button.y >= RepareButton.y && event.button.y <= RepareButton.y + 150)) {
			if (Wep != nullptr && cinta != nullptr)
				repare();
		}
		else if ((event.button.x >= craftSlotsclick[0].x && event.button.x <= craftSlotsclick[0].x + craftSlotsclick[0].w)
			&& (event.button.y >= craftSlotsclick[0].y && event.button.y <= craftSlotsclick[0].y + craftSlotsclick[0].h)) {
			slotCraftClicked = 0;
		}
		else if ((event.button.x >= craftSlotsclick[1].x && event.button.x <= craftSlotsclick[1].x + craftSlotsclick[1].w)
			&& (event.button.y >= craftSlotsclick[1].y && event.button.y <= craftSlotsclick[1].y + craftSlotsclick[1].h)) {
			slotCraftClicked = 1;
		}
		else if ((event.button.x >= craftSlotsclick[2].x && event.button.x <= craftSlotsclick[2].x + craftSlotsclick[2].w)
			&& (event.button.y >= craftSlotsclick[2].y && event.button.y <= craftSlotsclick[2].y + craftSlotsclick[2].h)) {
			slotCraftClicked = 2;
		}
		else if ((event.button.x >= craftSlotsclick[3].x && event.button.x <= craftSlotsclick[3].x + craftSlotsclick[3].w)
			&& (event.button.y >= craftSlotsclick[3].y && event.button.y <= craftSlotsclick[3].y + craftSlotsclick[3].h)) {
			slotCraftClicked = 3;
		}
		else if ((event.button.x >= craftButton.x && event.button.x <= craftButton.x + craftButton.w)
			&& (event.button.y >= craftButton.y && event.button.y <= craftButton.y + craftButton.h)) {
			craft();
		}
	}
}

void Craft::render(Entity * e, Uint32 time)
{
	if(pRenderer==nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = width / 2 - ancho / 2;
	int posY = height / 2 - alto / 2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	resource->getTexture("Inventory")->render(pRenderer, dest);

	ancho = width - width / 10;
	alto = height - height / 10;
	posX = 0 + (width / 10) / 2;
	posY = 0 + (height / 10) / 2;

	dest = { posX,posY, ancho,alto };
	resource->getTexture("Craft")->render(pRenderer, dest);

	renderItem(Wep, repareSlots[WeaponSlot]);
	renderItem(cinta, repareSlots[InsulationTapeSlot]);

	//RENDER DE LOS OBJETOS A CRAFTEAR
	dest = RECT(craftSlots[0].x - slotWidth / 2, craftSlots[0].y - slotWidth / 2, slotWidth * 2, slotWidth * 2);
	resource->getTexture("Firstaid")->render(pRenderer, dest, &clip);
	dest = RECT(craftSlots[1].x - slotWidth / 2, craftSlots[1].y - slotWidth / 2, slotWidth * 2, slotWidth * 2);
	resource->getTexture("Acid")->render(pRenderer, dest, &clip);
	dest = RECT(craftSlots[2].x - slotWidth / 2, craftSlots[2].y - slotWidth / 2, slotWidth * 2, slotWidth * 2);
	resource->getTexture("Circuit")->render(pRenderer, dest, &clip);

	if (controllerActive && renderMark) {
		if (selectedSlot < 3 && !craftButtonSelected && !repairButtonSelected) {
			SDL_Rect DestRect = { craftSlots[selectedSlot].x - slotWidth / 2 + 5, craftSlots[selectedSlot].y - slotWidth / 2 + 4, slotWidth * 2 - 8, slotWidth * 2 - 8 };
			renderSlotMark(DestRect);
		}
		else if (selectedSlot < 5 && !craftButtonSelected && !repairButtonSelected) {
			SDL_Rect DestRect = { repareSlots[selectedSlot - 3].x - slotWidth / 2 + 4, repareSlots[selectedSlot - 3].y - slotWidth / 2 + 2, slotWidth * 2 - 6, slotWidth * 2 - 6 };
			renderSlotMark(DestRect);
		}
		else if (craftButtonSelected) {
			renderSlotMark(craftButton);
		}
		else if (repairButtonSelected) {
			renderSlotMark(repairButtonRect);
		}
	}

	if (controllerActive) {
		if (selectedSlot == 0) {		//DEBUG ESE 2 ES PORQUE SOLO SE CRAFTEAN DOS OBJETOS
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/FirstAidDescription.txt");
		}
		else if(selectedSlot==1) {
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/AcidDescription.txt");
		}
		else if(selectedSlot == 2)
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/CircuitDescription.txt");		//PONER EL NOMBRE DEL ARCHIVO
		else
			description_.getComponent<TextNote>()->changeString("");
	}
	else {
		if (slotCraftClicked == 0) {		//DEBUG ESE 2 ES PORQUE SOLO SE CRAFTEAN DOS OBJETOS
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/FirstAidDescription.txt");
		}
		else if (slotCraftClicked == 1) {		//DEBUG ESE 2 ES PORQUE SOLO SE CRAFTEAN DOS OBJETOS
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/AcidDescription.txt");
		}
		else if(slotCraftClicked == 2){
			description_.getComponent<TextNote>()->changeString("ItemDescriptions/CircuitDescription.txt");		//PONER EL NOMBRE DEL ARCHIVO
		}
		else
			description_.getComponent<TextNote>()->changeString("");
	}

	description_.getComponent<TextNote>()->render(nullptr, time);

}

void Craft::repare()
{
	Wep->getComponent<Weapon>()->repare(REPARE_VAR);
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
	inv->addItem(Wep);
	Game::Instance()->getStateMachine()->currentState()->removeInteractibleOfStage(cinta);
	Wep = nullptr;
	cinta = nullptr;
}

void Craft::wepSwitch()
{
	
}

void Craft::moveMarkSlot(int a)
{
	if (!craftButtonSelected && !repairButtonSelected) {
		if (a == 1) {
			if (selectedSlot == 3 || selectedSlot == 4)
				selectedSlot = 2;
			else if (selectedSlot == 1)
				selectedSlot = 0;
			else if (selectedSlot == 2)
				selectedSlot = 1;
		}
		else if (a == 3) {
			if (selectedSlot == 0)
				selectedSlot = 1;
			else if (selectedSlot == 1)
				selectedSlot = 2;
			else if (selectedSlot == 2)
				selectedSlot = 3;
		}
		else if (a == 2) {
			if (selectedSlot == 3)
				selectedSlot = 4;
		}
		else if (a == 4) {
			if (selectedSlot == 4)
				selectedSlot = 3;
		}
	}
	else if(craftButtonSelected) {
		if (a == 1)
			selectedSlot = 2;
		else if (a == 3)
			selectedSlot = 3;
	}
	else if (repairButtonSelected) {
		if (a == 1)
			selectedSlot = 2;
		else if (a == 4)
			selectedSlot = 4;
	}
}

void Craft::tryCraftingRepair()
{
	if (!craftButtonSelected && !repairButtonSelected) {		//Cuando pulsemos la X/A del mando comprobamos si estamos en el bot�n de crafteo ya o no
		switch (selectedSlot)
		{
		case 0:
			if ((inv->checkItem(ItemType::ALCOHOL) && inv->checkItem(ItemType::BANDAGES)) || (inv->checkIdemItems(ItemType::GENERICCHEMICAL,2)))
			{
				craftButtonSelected = true;
			}
			break;
		case 1:
			if (inv->checkIdemItems(ItemType::ACIDCHEMICAL, 2))	
			{
				craftButtonSelected = true;
			}
			break;	
		case 2:
			if (inv->checkIdemItems(ItemType::PIECEPUZZLE, 4))
			{
				craftButtonSelected = true;
			}
			break;
		default:
			break;
		}
	}
	else if(craftButtonSelected)
	{
		slotCraftClicked = selectedSlot;	//Ya sabemos que podemos crearlo, y lo ajustamos y creamos
		craft();	//Crafteamos
		craftButtonSelected = false;
		slotCraftClicked = -1;
		selectedSlot = 0;	//Colocamos la marca en el de arriba
	}
	else if (repairButtonSelected) {
		repare();
		repairButtonSelected = false;
		selectedSlot = 0;
}

}

void Craft::retireBlock()
{
	if (craftButtonSelected) {
		selectedSlot = 0;
		craftButtonSelected = false;
	}
	else if (repairButtonSelected) {
		selectedSlot = 2;
		returnToInv();
		selectedSlot = 3;
		returnToInv();
		selectedSlot = 0;
		repairButtonSelected = false;
		//Devolver objetos al inventario
	}
	else {
		//cerrar mesa de crafteo
	}
}

void Craft::returnToInv()
{
	if (!inv->fullInventory()) {
		if (selectedSlot == 2 && Wep!=nullptr) {
			inv->addItem(Wep);
			Wep = nullptr;
		}
		else if (selectedSlot == 3 && cinta!=nullptr) {
			inv->addItem(cinta);
			cinta = nullptr;
		}
	}
}

bool Craft::checkRepair()
{
	if (Wep != nullptr && cinta != nullptr) {
		repairButtonSelected = true;
	}
	else return false;
}

void Craft::renderSlotMark(SDL_Rect DestRect)
{
	
	resource->getTexture("InventoryCursor")->render(pRenderer, DestRect);
}

void Craft::renderItem(Entity* e, coord pos)
{	
	if (e != nullptr) {
		SDL_Rect DestRect = { pos.x - slotWidth / 2, pos.y - slotWidth / 2, slotWidth*2, slotWidth*2 };
		if (e->getComponent<InsulationTape>())
		{
			resource->getTexture("insulationTape")->render(pRenderer, DestRect, &clip);
		}
		else if (e->getComponent<Weapon>())
		{
			Weapon* weaponComp = e->getComponent<Weapon>();
			if (weaponComp->getType() == ItemType::STICK)
				resource->getTexture("Stick")->render(pRenderer, DestRect, &clip);

			else if (weaponComp->getType() == ItemType::PIPE)
				resource->getTexture("Crowbar")->render(pRenderer, DestRect, &clip);

			else if (weaponComp->getType() == ItemType::AXE)
				resource->getTexture("Axe")->render(pRenderer, DestRect, &clip);

			else if (weaponComp->getType() == ItemType::CROWBAR)
				resource->getTexture("Crowbar")->render(pRenderer, DestRect, &clip);
		}
		else if (e->getComponent<FirstAid>())
		{
			resource->getTexture("Firstaid")->render(pRenderer, DestRect, &clip);
		}
		else if (e->getComponent<Key>())
		{
			resource->getTexture("Key")->render(pRenderer, DestRect, &clip);
		}
	}
}

void Craft::craft()
{
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
	switch (slotCraftClicked)
	{
	case 0:
		if (inv->checkItem(ItemType::ALCOHOL) && inv->checkItem(ItemType::BANDAGES))
		{
			inv->objectCrafted(ItemType::CROWBAR, ItemType::STICK);
			Entity* e = new Entity(0, 0);
			e->addComponent(new FirstAid("Firstaid"));
			inv->addItem(e);
		}
		break;
	case 1:
		if (inv->checkIdemItems(ItemType::ACIDCHEMICAL, 2))
		{
			inv->objectCrafted(ItemType::ACIDCHEMICAL, ItemType::ACIDCHEMICAL);
			Entity* e = new Entity(0, 0);
			e->addComponent(new Item(ItemType::ACID, "AcidDescription")); //cambiar
			inv->addItem(e);
		}
		break;
	case 2:
		if (inv->checkIdemItems(ItemType::PIECEPUZZLE, 4))
		{
			inv->objectCrafted(ItemType::PIECEPUZZLE, ItemType::PIECEPUZZLE);
			inv->objectCrafted(ItemType::PIECEPUZZLE, ItemType::PIECEPUZZLE);
			Entity* e = new Entity(0, 0);
			e->addComponent(new FirstAid("Firstaid")); //cambiar
			inv->addItem(e);
		}
		break;
	case 3:
		break;
	default:
		break;
	}

}

void Craft::setWep(Entity* e)
{
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
	if(Wep != nullptr)
	{
		Entity* aux = Wep;
		Wep = e;
		inv->addItem(aux);
	}
	else
	{
		Wep = e;
	}
	

}

void Craft::setCinta(Entity* e)
{
	cinta = e;
}

void Craft::restoreObjects()
{
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }

	if(Wep != nullptr) { 
		inv->addItem(Wep); 
		Wep = nullptr;
	}
	if (cinta != nullptr) { 
		inv->addItem(cinta); 
		cinta = nullptr;
	}
}
