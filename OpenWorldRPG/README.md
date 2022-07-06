##### Compile

`./compile.sh`

`g++ -g main.cpp Game.cpp Entity.cpp GameState.cpp State.cpp MainMenuState.cpp Button.cpp Player.cpp MovementComponent.cpp AnimationComponent.cpp headers.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network`