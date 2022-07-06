#include "headers.h"
#include "EditorState.h"

//============= PRIVATE =================//
// Initializers
void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/press-start.ttf"))
        std::cout << "Error loading editor font!" << std::endl;
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/editorstate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void EditorState::initButtons()
{
}

//============= CONSTRUCTOR =============//
EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

// ============= DESTRUCTOR =================//
EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for (it; it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

//============= PUBLIC ==================//
void EditorState::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

void EditorState::updateButtons()
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget *target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    this->renderButtons(target);
}
