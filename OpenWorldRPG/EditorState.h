#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "Button.h"

class EditorState : public State
{
private:
  sf::Font font;

  std::map<std::string, Button *> buttons;

  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initButtons();

public:
  EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
  virtual ~EditorState();

  void updateInput(const float &dt);
  void updateButtons();
  void update(const float &dt);

  void renderButtons(sf::RenderTarget &target);
  void render(sf::RenderTarget *target = NULL);
};

#endif