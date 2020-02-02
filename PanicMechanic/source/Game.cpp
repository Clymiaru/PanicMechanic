#include "Core.h"
#include "Debug.h"
#include "Game.h"
#include "Managers/TextureManager.h"
#include "Managers/SFXManager.h"
#include "Managers/BGMManager.h"
#include "Managers/FontManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/SceneManager.h"
#include "Managers/ScoreManager.h"

#include "Scenes/MenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/ResultScene.h"



#include <sstream>
#include <iomanip>
#include <utility>
Game::Game() :
    m_Window(CreateRef<sf::RenderWindow>(sf::VideoMode(WindowWidth, WindowHeight),
                                         WindowName,
                                         sf::Style::Close)),
    m_Event(CreateRef<sf::Event>())
{
    Debug::Init();
    Debug::Info("Game is initialized.");

    TextureManager::GetInstance()->LoadAll();
    SFXManager::GetInstance()->LoadAll();
    BGMManager::GetInstance()->LoadAll();
    FontManager::GetInstance()->LoadAll();

    //BGMManager::GetInstance()->GetBGM("test")->play();

    SceneManager::GetInstance()->RegisterScene(CreateRef<MenuScene>());
    SceneManager::GetInstance()->RegisterScene(CreateRef<GameScene>());
    SceneManager::GetInstance()->RegisterScene(CreateRef<ResultScene>());

    m_GameTitle.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_GameTitle.setFillColor(sf::Color::White);
    m_GameTitle.setCharacterSize(84);
    m_GameTitle.setString(WindowName);
    m_GameTitle.setPosition(1280 / 2 - m_GameTitle.getGlobalBounds().width / 2, 100);

    m_PressToPlay.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_PressToPlay.setFillColor(sf::Color::White);
    m_PressToPlay.setCharacterSize(30);
    m_PressToPlay.setString("Press ENTER to Play");
    m_PressToPlay.setPosition(1280 / 2 - m_PressToPlay.getGlobalBounds().width / 2, 450);


    m_PressToExit.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_PressToExit.setFillColor(sf::Color::White);
    m_PressToExit.setCharacterSize(30);
    m_PressToExit.setString("Press ESCAPE to Quit");
    m_PressToExit.setPosition(1280 / 2 - m_PressToExit.getGlobalBounds().width / 2, 550);

    m_Prompt.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_Prompt.setFillColor(sf::Color::White);
    m_Prompt.setCharacterSize(84);
    m_Prompt.setString("Game Over!");
    m_Prompt.setPosition(1280 / 2 - m_Prompt.getGlobalBounds().width / 2, 100);


    m_ElapsedTimeLabel.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_ElapsedTimeLabel.setFillColor(sf::Color::White);
    m_ElapsedTimeLabel.setCharacterSize(48);
    m_ElapsedTimeLabel.setPosition(100, 0);

    m_ScoreText.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_ScoreText.setFillColor(sf::Color::White);
    m_ScoreText.setCharacterSize(30);
    m_ScoreText.setString("0");
    m_ScoreText.setPosition(1280 / 2 - m_ScoreText.getGlobalBounds().width / 2, 600);

    m_Cooldown.setFont(*FontManager::GetInstance()->GetFont("sansation"));
    m_Cooldown.setFillColor(sf::Color::White);
    m_Cooldown.setCharacterSize(26);


    m_BGMinimap.setPosition(0, 0);
    m_BGMinimap.setFillColor(sf::Color(112, 66, 20, 200));
    m_BGMinimap.setSize(sf::Vector2f(1280, 720 + 32));

    m_DefaultView = m_Window->getDefaultView();
    m_MiniMapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
    
	m_BackGround.setTexture(*TextureManager::GetInstance()->GetTexture("background"));
	//m_BackGround.setScale({1280, 720});

    m_GameView.zoom(0.5f);
    m_GameView.setCenter({245, 600});
    SceneManager::GetInstance()->LoadScene("MenuScene");

}

Game::~Game()
{

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_Window->isOpen())
    {
        ProcessEvents();

        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            ProcessEvents();
            Update(TimePerFrame);
        }

        Render();
    }
}

void Game::ProcessEvents()
{
    while (m_Window->pollEvent(*m_Event))
    {
        switch (m_Event->type)
        {
        case sf::Event::Closed:
        {
            m_Window->close();
            Debug::Info("Window has been closed by the close button.");
        } break;
        default:
        {
            #ifdef DEBUG
            HandleWindowCloseByEscapeKey(m_Event->key.code);
            #endif

            GameObjectManager::GetInstance()->ProcessInput(m_Event);

            if (SceneManager::GetInstance()->IsSceneLoaded("MenuScene"))
            {
                if (m_Event->type == sf::Event::KeyPressed)
                {
                    if (m_Event->key.code == sf::Keyboard::Enter)
                    {
                        SceneManager::GetInstance()->LoadScene("GameScene");
                        m_Window->setView(m_GameView);
                        ScoreManager::Reset();
                        ScoreManager::StartClock();

                    }

                    if (m_Event->key.code == sf::Keyboard::Escape)
                    {
                        HandleWindowCloseByEscapeKey(m_Event->key.code);
                    }
                }

            }

            else if (SceneManager::GetInstance()->IsSceneLoaded("GameScene"))
            {
                if (m_Event->type == sf::Event::KeyReleased || !GameObjectManager::GetInstance()->FindObjectByName("Player")->GetCondition()){
                    m_Cooldown.setFillColor(sf::Color::Transparent);
                }
                else
                    if (m_Event->key.code == sf::Keyboard::J || m_Event->key.code == sf::Keyboard::K || m_Event->key.code == sf::Keyboard::L) {
                        CD_Timer.restart();
                        m_Cooldown.setFillColor(sf::Color::White);
                     }

            }

            else if (SceneManager::GetInstance()->IsSceneLoaded("ResultScene"))
            {
                if (m_Event->type == sf::Event::KeyPressed)
                {
                    if (m_Event->key.code == sf::Keyboard::Enter)
                    {
                        SceneManager::GetInstance()->LoadScene("MenuScene");
                    }

                    if (m_Event->key.code == sf::Keyboard::Escape)
                    {
                        HandleWindowCloseByEscapeKey(m_Event->key.code);
                    }
                }

            }

            
        } break;
        }
    }
}

void Game::Update(const sf::Time& deltaTime)
{
    GameObjectManager::GetInstance()->Update(deltaTime);

    if (SceneManager::GetInstance()->IsSceneLoaded("MenuScene"))
    {
        m_PressToPlay.setString("Press ENTER to Play");
        m_PressToPlay.setPosition(1280 / 2 - m_PressToPlay.getGlobalBounds().width / 2, 450);
    }
    if (SceneManager::GetInstance()->IsSceneLoaded("GameScene"))
    {
        float time = ScoreManager::GetElapsedTime();

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << time;
        std::string s = stream.str();

         
        sf::Vector2f playerPosition = GameObjectManager::GetInstance()->FindObjectByName("Player")->GetPosition();
        

        m_GameView.setCenter(std::clamp<float>(playerPosition.x, 250, 1280 - 576), 
                             std::clamp<float>(playerPosition.y + 64, 200 + 64, 650));
        

        m_ElapsedTimeLabel.setString(s);
        m_ElapsedTimeLabel.setPosition(1280 / 2 - m_ElapsedTimeLabel.getGlobalBounds().width / 2, 0);

        m_ScoreText.setString(std::to_string(ScoreManager::GetScore()));
        m_ScoreText.setPosition(1280 / 2 - m_ScoreText.getGlobalBounds().width / 2, 600);

        float cdtime = CD_Timer.getElapsedTime().asMilliseconds();
        
        std::stringstream sstream;
        sstream << cdtime;
        std::string ss = sstream.str();

        m_Cooldown.setString(ss);
        
        sf::Vector2i cdPos = m_Window->mapCoordsToPixel(playerPosition, m_GameView);
        m_Cooldown.setPosition(cdPos.x - m_Cooldown.getGlobalBounds().width / 2, cdPos.y - 60.f);

        if (time > 19.999999f || ScoreManager::IsAllFixed())
        {
            SceneManager::GetInstance()->LoadScene("ResultScene");
            m_ScoreText.setCharacterSize(48);
            m_ScoreText.setPosition(1280 / 2 - m_ScoreText.getGlobalBounds().width / 2, 300);

            m_PressToPlay.setString("Press ENTER to Go Back to Main Menu");
            m_PressToPlay.setPosition(1280 / 2 - m_PressToPlay.getGlobalBounds().width / 2, 500);
        }

    }
}

void Game::Render()
{
    m_Window->clear();

    if (SceneManager::GetInstance()->IsSceneLoaded("MenuScene"))
    {
        m_Window->draw(m_GameTitle);
        m_Window->draw(m_PressToPlay);
        m_Window->draw(m_PressToExit);
    }

	if (SceneManager::GetInstance()->IsSceneLoaded("GameScene"))
	{
		m_Window->setView(m_DefaultView);
		m_Window->draw(m_BackGround);

	}
    if (SceneManager::GetInstance()->IsSceneLoaded("GameScene"))
    {
        m_Window->setView(m_GameView);
        GameObjectManager::GetInstance()->Draw(m_Window);
    }
    else
    {
        GameObjectManager::GetInstance()->Draw(m_Window);
    }

    if (SceneManager::GetInstance()->IsSceneLoaded("GameScene"))
    {
        m_Window->setView(m_DefaultView);

        m_Window->draw(m_ElapsedTimeLabel);
        m_Window->draw(m_Cooldown);
        m_Window->draw(m_ScoreText);

        m_Window->setView(m_MiniMapView);
        m_Window->draw(m_BGMinimap);
        GameObjectManager::GetInstance()->Draw(m_Window); 
    }

    if (SceneManager::GetInstance()->IsSceneLoaded("ResultScene"))
    {
        m_Window->setView(m_DefaultView);
        m_Window->draw(m_Prompt);
        m_Window->draw(m_ScoreText);
        m_Window->draw(m_PressToPlay);
        m_Window->draw(m_PressToExit);
    }
    
    m_Window->display();
}

void Game::HandleWindowCloseByEscapeKey(const sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Escape)
    {
        m_Window->close();
        Debug::Info("Window has been closed by the 'ESC' key.");
    }
}
