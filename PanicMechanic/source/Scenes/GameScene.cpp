#include "Debug.h"
#include "Core.h"
#include "GameScene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Terrain.h"
#include "GameObjects/Equipment.h"

GameScene::GameScene() :
	Scene("GameScene")
{

}

GameScene::~GameScene()
{
}

void GameScene::LoadResources()
{
}

void GameScene::LoadObjects()
{
	auto generatePosition = []() -> sf::Vector2f
	{
		int temp = std::rand() % 6;
		switch (temp)
		{
		case 0: return sf::Vector2f(32, 32);
		case 1: return sf::Vector2f(32, 425);
		case 2: return sf::Vector2f(32, 658);
		case 3: return sf::Vector2f(32 * 29, 32);
		case 4: return sf::Vector2f(32 * 29, 425);
		case 5: return sf::Vector2f(32 * 29, 658);
		}
	};
	
	auto player = CreateRef<Player>("Player");
	player->SetPosition(generatePosition());
	RegisterObject(player);

	auto createPlatform = [&](int i, int j) -> void
	{
		std::string tile_name = "platform";
		auto platform = CreateRef<Terrain>(tile_name, sf::Vector2f(-32 + 32 * i, 720 - 32 * j), sf::Vector2f(32, 32));
		RegisterObject(platform);

	};


	int col = 8;
	for (int j = 0; j < col * 4; j++)
	{
		for (int i = 0; i < 32; i++)
		{
			if (i == 0 || i == 31)
			{
				createPlatform(i, j);
			}
			if (j == col * 0)
			{
				createPlatform(i, j);
			}

			if (j == col * 1)
			{
				if (i >= 0 && i < 3)
				{
					createPlatform(i, j);
				}

				if (i > 4 && i < 14)
				{
					createPlatform(i, j);
				}

				if (i > 16 && i < 24)
				{
					createPlatform(i, j);
				}

				if (i > 25)
				{
					createPlatform(i, j);
				}
			}

			if (j == col * 2)
			{
				if (i >= 0 && i < 2)
				{
					createPlatform(i, j);
				}

				if (i > 4 && i < 22)
				{
					createPlatform(i, j);
				}

				if (i > 24)
				{
					createPlatform(i, j);
				}

			}

			if (j == col * 3)
			{
				createPlatform(i, j);
			}

		}
	}

	auto createEquipment = [&](std::string name, sf::Keyboard::Key key, bool state, Equipment::Equipment_Type type, sf::Vector2f position) -> void
	{
		auto equipment = CreateRef<Equipment>(name, key, state, type, position);
		RegisterObject(equipment);
	};

	auto generateRandomVector = []() -> std::vector<bool>
	{
		std::vector<bool> list;
		int ctr = 0;
		do
		{
			ctr = 0;
			list.clear();
			for (int i = 0; i < 9; i++)
			{
				if (ctr == 4)
					list.push_back(false);
				else
				{
					auto temp = (std::rand() % 2);
					if (temp == 0)
						list.push_back(false);
					else 
						list.push_back(true);

					
					if (list.back() == true)
						ctr++;
				}
			}

		} while (ctr < 4);

		return list;
	};
	auto listTemp = generateRandomVector();
	//randomizer thing for the state, imma set it false muna
	createEquipment("grinder", sf::Keyboard::J, listTemp[0], Equipment::Equipment_Type::Grinder,							{ 32.0f * 3,  658 - (32 * 2)});
	createEquipment("conveyor_belt", sf::Keyboard::J , listTemp[1], Equipment::Equipment_Type::Conveyor_Belt,				{ 32.0f * 14, 658 - (32 * 2) });
	createEquipment("forge", sf::Keyboard::K, listTemp[2], Equipment::Equipment_Type::Forge,								{ 32.0f * 24, 658 - (32 * 2) });

	createEquipment("magnet", sf::Keyboard::L, listTemp[3], Equipment::Equipment_Type::Magnet,							{ 32.0f * 9,  658 - (32 * 10) });
	createEquipment("grinder", sf::Keyboard::J, listTemp[4], Equipment::Equipment_Type::Grinder,							{ 32.0f * 18, 658 - (32 * 10) });

	createEquipment("forge", sf::Keyboard::K, listTemp[5], Equipment::Equipment_Type::Forge,								{ 32.0f * 5,  658 - (32 * 18) });
	createEquipment("ballistic_separator", sf::Keyboard::L, listTemp[6], Equipment::Equipment_Type::Ballistic_Separator,	{ 32.0f * 11, 658 - (32 * 18) });
	createEquipment("magnet", sf::Keyboard::L, listTemp[7], Equipment::Equipment_Type::Magnet,							{ 32.0f * 17, 658 - (32 * 18) });
	createEquipment("fuse_box", sf::Keyboard::K, listTemp[8], Equipment::Equipment_Type::Fuse_Box,						{ 32.0f * 25, 658 - (32 * 18) });
	
}

void GameScene::UnloadObjects()
{
	Scene::UnloadObjects();
}

void GameScene::UnloadResources()
{
}