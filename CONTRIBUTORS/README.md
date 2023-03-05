#How to contribute  
Welcome to our project! We're excited to have you as a contributor. Here are some guidelines to help you get started and make your contributions as valuable as possible.

##Getting Started  
Before you start contributing, you should take the following steps:

Fork the repository and clone it to your local machine.  
Compile with your .so and the docker container [Link to compilation](../)  
Familiarize yourself with the codebase by reading through the documentation and reviewing any open issues or pull requests.  

##Making Contributions  
Once you're ready to start contributing, here are some general guidelines to follow:

Create a new branch for each contribution you make. This makes it easier to isolate changes and revert them if necessary.  
Keep your code clean and well-organized. Follow the existing code style and conventions, and comment your code as necessary to make it understandable to others.  
Test your changes thoroughly before submitting them. Make sure they don't introduce any new bugs or break existing functionality.  
Submit your changes as a pull request. Provide a clear description of what you've changed and why, and be open to feedback and suggestions from other contributors.  

##create a graphic .so

if you want to create a graphic .so and implemente your librarie, follow this instruction:  

First, your librarie class need to be a child to ```IGraphic``` interface, and implemente some basic function, they are some examples:

sound_system is the function where you handle the sound
```
virtual void sound_system(sparse_array<SoundEffect> &sound) = 0;
```

draw_system is the function where you will draw all your asset
```
virtual void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles, 
```

animation_system is where you will anime your asset  
```
virtual void animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables) = 0;
```

clique_system is the function where you handle the clic of the window
```
virtual void clique_system(sparse_array<Cliquable> &cliquables, sparse_array<Drawable> &drawables) = 0;
```

run_graphic is a function called in the engine each loop of the game. You can pass the event from this function
```
virtual Events run_graphic(registry &r) = 0;
```

then, create a function that return a pointer to your librarie class. 
```
extern "C" std::shared_ptr<IGame> createLibrary()
{
    return std::make_shared<Rtype>();
}
```
this function will be called when the .so of your gaphic librarie is loaded.

You need to add your asset to a json a call the function ```constructFromJson```:
```
{
    "asset": [
        {
            "type": 0,
            "texture" : "ressources/Raylib/shipTexture.png",
            "animation" : "ressources/Raylib/shipAnim.iqm",
            "model": "ressources/Raylib/ship.iqm"
        },
        {
            "type": 1,
            "texture" : "ressources/Raylib/palette.png",
            "animation" : "",
            "model": "ressources/Raylib/water.obj"
        },
        {
            "type": 2,
            "texture" : "ressources/Raylib/palette.png",
            "animation" : "",
            "model": "ressources/Raylib/flag.obj"
        },
        ......
```

##create a game .so  

If you want to create a game. so follow this steps:  

your librairie class should be a child of ```IGame``` interface and implemente a function wich return a pointer to your class like so:
```
extern "C" std::shared_ptr<IGame> createLibrary()
{
    return std::make_shared<Rtype>();
}
```

then implemente the different system you need, they are some example:  

this function update the registry from the informations receive from the server
```
void updateRegistry(registry &r, const GameData &data) 
```

this function basically create a player
```
void create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);
```


##Code of Conduct  
As a contributor, you're expected to follow our code of conduct at all times. This means treating others with respect, avoiding offensive or harmful language, and working to create a safe and welcoming environment for everyone. If you encounter any behavior that violates our code of conduct, please report it to the project maintainer.  

##Getting Help  
If you have any questions or need help with anything related to the project, don't hesitate to reach out to the project maintainer or other contributors. We're here to help and support each other.

##Thank You  
We appreciate your contributions to our project, and we're excited to see what you'll bring to the table. Thank you for helping make our project the best it can be!
