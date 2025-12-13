# Text-Based Adventure Game

## Description
A classic text-based adventure game where players explore rooms, collect items, and solve puzzles through text commands. The game features room navigation, item management, save/load functionality, and a simple win condition. Players must find a key, take it, and use it to unlock a chest in the treasure room.

## Features
- Room-based navigation system with cardinal directions
- Item collection and inventory management
- Save and load game state functionality
- Text parsing for player commands
- Win condition with scoring system
- Persistent game state using binary file I/O

## Game Concept
Players start in an entrance hall and must explore connected rooms to find a key, take it, and use it to unlock a chest in the treasure room. The game includes:
- Entrance Hall (starting room)
- Library (contains key)
- Kitchen (contains sword)
- Treasure Room (win condition location)

## Standard Library Functions Used
- `stdio.h` - For input/output operations and file handling
- `stdlib.h` - For standard library functions
- `string.h` - For string manipulation
- `ctype.h` - For character handling functions

## How to Compile and Run

### Compilation
```bash
gcc -o adventure main.c
```

### Execution
```bash
./adventure
```

On Windows:
```bash
adventure.exe
```

## How to Play
1. Run the program to start the game
2. Use text commands to interact with the game world:
   - Navigation: `north`, `south`, `east`, `west` (or `n`, `s`, `e`, `w`)
   - Examination: `look`, `look at <item>`, `examine <item>`
   - Inventory: `inventory`, `i`, `take <item>`, `drop <item>`
   - Game management: `save`, `load`, `help`, `quit`
3. Find the key in the library
4. Take the key
5. Navigate to the treasure room
6. Win the game by unlocking the chest

## Sample Gameplay
```
Welcome to the Text-Based Adventure Game!
Type 'help' for a list of commands.

You are in a grand entrance hall. There's a large door to the north and a hallway to the east.
Items here: 
Exits: north, east

> north

You are in a dusty library filled with ancient books. There's a desk with a key on it.
Items here: key
Exits: south, east

> take key
You take the key.

> east

You are in a treasure room! A chest sits in the corner, but it's locked.
Items here: chest
Exits: south, west

Congratulations! You unlocked the chest and found the treasure!
You win the game with a score of 110!
```

## Game Data Structure
The game uses several data structures:
1. **Room Structure**: Contains room ID, description, connections, and items
2. **Item Structure**: Represents items with names, descriptions, and properties
3. **Player Structure**: Tracks current location, inventory, health, and score

## Educational Value
This implementation demonstrates:
1. Complex state management in games
2. Text parsing and command interpretation
3. File I/O for save/load functionality
4. Data structure design for game entities
5. User interface design for text-based games
6. Game logic implementation with win conditions