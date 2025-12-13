#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROOMS 20
#define MAX_ITEMS 10
#define MAX_DESCRIPTION 256
#define MAX_COMMAND 50

// Room structure
typedef struct {
    int id;
    char description[MAX_DESCRIPTION];
    int north, south, east, west;  // Room connections (-1 = no exit)
    int item_ids[MAX_ITEMS];       // Items in room (-1 = empty slot)
    int item_count;
} Room;

// Item structure
typedef struct {
    int id;
    char name[30];
    char description[100];
    int can_take;  // 1 = can take, 0 = cannot take
} Item;

// Player state
typedef struct {
    int current_room;
    int inventory[MAX_ITEMS];
    int inventory_count;
    int health;
    int score;
    int game_over;
} Player;

// Game state
Room rooms[MAX_ROOMS];
Item items[50];
Player player;
int room_count = 0;
int item_count = 0;

// Function prototypes
void init_game();
void load_rooms();
void load_items();
void game_loop();
void print_room();
void print_inventory();
void parse_command(char* command);
void move_player(int direction);
void take_item(char* item_name);
void drop_item(char* item_name);
void look_at_item(char* item_name);
void save_game();
void load_game();
void print_help();

int main() {
    printf("Welcome to the Text-Based Adventure Game!\n");
    printf("Type 'help' for a list of commands.\n\n");
    
    init_game();
    game_loop();
    
    return 0;
}

// Initialize game state
void init_game() {
    // Initialize player
    player.current_room = 0;
    player.inventory_count = 0;
    player.health = 100;
    player.score = 0;
    player.game_over = 0;
    
    // Load game data
    load_rooms();
    load_items();
}

// Load rooms from data
void load_rooms() {
    // Room 0: Entrance Hall
    rooms[0].id = 0;
    strcpy(rooms[0].description, "You are in a grand entrance hall. There's a large door to the north and a hallway to the east.");
    rooms[0].north = 1;
    rooms[0].south = -1;
    rooms[0].east = 2;
    rooms[0].west = -1;
    rooms[0].item_count = 0;
    
    // Room 1: Library
    rooms[1].id = 1;
    strcpy(rooms[1].description, "You are in a dusty library filled with ancient books. There's a desk with a key on it.");
    rooms[1].north = -1;
    rooms[1].south = 0;
    rooms[1].east = 3;
    rooms[1].west = -1;
    rooms[1].item_ids[0] = 0;  // Key
    rooms[1].item_count = 1;
    
    // Room 2: Kitchen
    rooms[2].id = 2;
    strcpy(rooms[2].description, "You are in a kitchen. There's a rusty sword on the counter and a door to the north.");
    rooms[2].north = 3;
    rooms[2].south = -1;
    rooms[2].east = -1;
    rooms[2].west = 0;
    rooms[2].item_ids[0] = 1;  // Sword
    rooms[2].item_count = 1;
    
    // Room 3: Treasure Room
    rooms[3].id = 3;
    strcpy(rooms[3].description, "You are in a treasure room! A chest sits in the corner, but it's locked.");
    rooms[3].north = -1;
    rooms[3].south = 2;
    rooms[3].east = -1;
    rooms[3].west = 1;
    rooms[3].item_ids[0] = 2;  // Chest
    rooms[3].item_count = 1;
    
    room_count = 4;
}

// Load items from data
void load_items() {
    // Item 0: Key
    items[0].id = 0;
    strcpy(items[0].name, "key");
    strcpy(items[0].description, "An old brass key. It might unlock something.");
    items[0].can_take = 1;
    
    // Item 1: Sword
    items[1].id = 1;
    strcpy(items[1].name, "sword");
    strcpy(items[1].description, "A rusty but sturdy sword. Good for protection.");
    items[1].can_take = 1;
    
    // Item 2: Chest
    items[2].id = 2;
    strcpy(items[2].name, "chest");
    strcpy(items[2].description, "A wooden chest. It appears to be locked.");
    items[2].can_take = 0;
    
    item_count = 3;
}

// Main game loop
void game_loop() {
    char command[MAX_COMMAND];
    
    print_room();
    
    while (!player.game_over) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        
        // Remove newline character
        command[strcspn(command, "\n")] = 0;
        
        parse_command(command);
    }
}

// Print current room description
void print_room() {
    Room* current = &rooms[player.current_room];
    printf("\n%s\n", current->description);
    
    // List items in room
    if (current->item_count > 0) {
        printf("Items here: ");
        for (int i = 0; i < current->item_count; i++) {
            int item_id = current->item_ids[i];
            printf("%s", items[item_id].name);
            if (i < current->item_count - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
    
    // List exits
    printf("Exits: ");
    int exit_count = 0;
    if (current->north != -1) {
        printf("north");
        exit_count++;
    }
    if (current->south != -1) {
        if (exit_count > 0) printf(", ");
        printf("south");
        exit_count++;
    }
    if (current->east != -1) {
        if (exit_count > 0) printf(", ");
        printf("east");
        exit_count++;
    }
    if (current->west != -1) {
        if (exit_count > 0) printf(", ");
        printf("west");
        exit_count++;
    }
    if (exit_count == 0) {
        printf("none");
    }
    printf("\n");
}

// Print player inventory
void print_inventory() {
    if (player.inventory_count == 0) {
        printf("Your inventory is empty.\n");
        return;
    }
    
    printf("Inventory: ");
    for (int i = 0; i < player.inventory_count; i++) {
        int item_id = player.inventory[i];
        printf("%s", items[item_id].name);
        if (i < player.inventory_count - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Parse and execute player command
void parse_command(char* command) {
    // Convert to lowercase
    for (int i = 0; command[i]; i++) {
        command[i] = tolower(command[i]);
    }
    
    // Parse command
    if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
        player.game_over = 1;
        printf("Thanks for playing!\n");
    }
    else if (strcmp(command, "help") == 0) {
        print_help();
    }
    else if (strcmp(command, "look") == 0) {
        print_room();
    }
    else if (strcmp(command, "inventory") == 0 || strcmp(command, "i") == 0) {
        print_inventory();
    }
    else if (strcmp(command, "north") == 0 || strcmp(command, "n") == 0) {
        move_player(0);  // North
    }
    else if (strcmp(command, "south") == 0 || strcmp(command, "s") == 0) {
        move_player(1);  // South
    }
    else if (strcmp(command, "east") == 0 || strcmp(command, "e") == 0) {
        move_player(2);  // East
    }
    else if (strcmp(command, "west") == 0 || strcmp(command, "w") == 0) {
        move_player(3);  // West
    }
    else if (strncmp(command, "take ", 5) == 0) {
        take_item(command + 5);
    }
    else if (strncmp(command, "drop ", 5) == 0) {
        drop_item(command + 5);
    }
    else if (strncmp(command, "look at ", 8) == 0) {
        look_at_item(command + 8);
    }
    else if (strncmp(command, "examine ", 8) == 0) {
        look_at_item(command + 8);
    }
    else if (strcmp(command, "save") == 0) {
        save_game();
    }
    else if (strcmp(command, "load") == 0) {
        load_game();
    }
    else {
        printf("I don't understand that command. Type 'help' for assistance.\n");
    }
}

// Move player in specified direction
void move_player(int direction) {
    Room* current = &rooms[player.current_room];
    int new_room = -1;
    
    switch (direction) {
        case 0: new_room = current->north; break;  // North
        case 1: new_room = current->south; break;  // South
        case 2: new_room = current->east;  break;  // East
        case 3: new_room = current->west;  break;  // West
    }
    
    if (new_room == -1) {
        printf("You can't go that way.\n");
    } else {
        player.current_room = new_room;
        print_room();
        
        // Win condition
        if (player.current_room == 3) {  // Treasure room
            // Check if player has key
            int has_key = 0;
            for (int i = 0; i < player.inventory_count; i++) {
                if (player.inventory[i] == 0) {  // Key ID
                    has_key = 1;
                    break;
                }
            }
            
            if (has_key) {
                printf("\nCongratulations! You unlocked the chest and found the treasure!\n");
                printf("You win the game with a score of %d!\n", player.score + 100);
                player.game_over = 1;
            }
        }
    }
}

// Take an item from the current room
void take_item(char* item_name) {
    // Trim leading spaces
    while (*item_name == ' ') item_name++;
    
    Room* current = &rooms[player.current_room];
    
    // Find item in room
    int item_index = -1;
    int item_id = -1;
    
    for (int i = 0; i < current->item_count; i++) {
        int id = current->item_ids[i];
        if (strcmp(item_name, items[id].name) == 0) {
            item_index = i;
            item_id = id;
            break;
        }
    }
    
    if (item_index == -1) {
        printf("I don't see that item here.\n");
        return;
    }
    
    if (!items[item_id].can_take) {
        printf("You can't take that.\n");
        return;
    }
    
    // Add to inventory
    if (player.inventory_count >= MAX_ITEMS) {
        printf("Your inventory is full.\n");
        return;
    }
    
    player.inventory[player.inventory_count] = item_id;
    player.inventory_count++;
    
    // Remove from room
    for (int i = item_index; i < current->item_count - 1; i++) {
        current->item_ids[i] = current->item_ids[i + 1];
    }
    current->item_count--;
    
    printf("You take the %s.\n", item_name);
    player.score += 10;
}

// Drop an item in the current room
void drop_item(char* item_name) {
    // Trim leading spaces
    while (*item_name == ' ') item_name++;
    
    // Find item in inventory
    int item_index = -1;
    int item_id = -1;
    
    for (int i = 0; i < player.inventory_count; i++) {
        int id = player.inventory[i];
        if (strcmp(item_name, items[id].name) == 0) {
            item_index = i;
            item_id = id;
            break;
        }
    }
    
    if (item_index == -1) {
        printf("You don't have that item.\n");
        return;
    }
    
    // Add to room
    Room* current = &rooms[player.current_room];
    if (current->item_count >= MAX_ITEMS) {
        printf("This room is too cluttered to drop anything else.\n");
        return;
    }
    
    current->item_ids[current->item_count] = item_id;
    current->item_count++;
    
    // Remove from inventory
    for (int i = item_index; i < player.inventory_count - 1; i++) {
        player.inventory[i] = player.inventory[i + 1];
    }
    player.inventory_count--;
    
    printf("You drop the %s.\n", item_name);
}

// Look at/examine an item
void look_at_item(char* item_name) {
    // Trim leading spaces
    while (*item_name == ' ') item_name++;
    
    // Check inventory first
    for (int i = 0; i < player.inventory_count; i++) {
        int id = player.inventory[i];
        if (strcmp(item_name, items[id].name) == 0) {
            printf("%s\n", items[id].description);
            return;
        }
    }
    
    // Check room
    Room* current = &rooms[player.current_room];
    for (int i = 0; i < current->item_count; i++) {
        int id = current->item_ids[i];
        if (strcmp(item_name, items[id].name) == 0) {
            printf("%s\n", items[id].description);
            return;
        }
    }
    
    printf("I don't see that item.\n");
}

// Save game state to file
void save_game() {
    FILE* file = fopen("savegame.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not save game.\n");
        return;
    }
    
    fwrite(&player, sizeof(Player), 1, file);
    fwrite(&room_count, sizeof(int), 1, file);
    fwrite(rooms, sizeof(Room), room_count, file);
    
    fclose(file);
    printf("Game saved successfully.\n");
}

// Load game state from file
void load_game() {
    FILE* file = fopen("savegame.dat", "rb");
    if (file == NULL) {
        printf("Error: No saved game found.\n");
        return;
    }
    
    fread(&player, sizeof(Player), 1, file);
    fread(&room_count, sizeof(int), 1, file);
    fread(rooms, sizeof(Room), room_count, file);
    
    fclose(file);
    printf("Game loaded successfully.\n");
    print_room();
}

// Print help information
void print_help() {
    printf("\nAvailable commands:\n");
    printf("  look/l                 - Look around the current room\n");
    printf("  north/n, south/s, east/e, west/w - Move in a direction\n");
    printf("  take <item>            - Pick up an item\n");
    printf("  drop <item>            - Drop an item from your inventory\n");
    printf("  inventory/i            - Check your inventory\n");
    printf("  look at <item>         - Examine an item\n");
    printf("  examine <item>         - Same as 'look at'\n");
    printf("  save                   - Save the current game\n");
    printf("  load                   - Load a saved game\n");
    printf("  help                   - Show this help message\n");
    printf("  quit/exit              - Quit the game\n");
}