#include "splashkit.h"
#include <string>
#include <vector>

using std::vector;
using namespace std;


//using structs to create knights own data types to represent those entities
struct knight_data 
{
    string name;
    string tool;
    vector<string> tools;
    int age;
};

struct kingdom_data
{
    string name;
    vector<knight_data> knights;
};

//enum, titling each value
enum knight_update_option
{
    UPDATE_NAME, //updating name of the knight
    UPDATE_AGE, //updatinng age of the knight
    ADD_TOOL,
    DELETE_TOOL,
    FINISH_UPDATE //quit function from the update menu
};

enum update_kingdom
{
    UPDATE, //UPDATE OPTION
    DELETE_KNIGHT,  //DELETING A KNIGHT
    ADD_KNIGHT,  //ADDING KNIGHTS
    QUERY, //selecting a knight
    SUMMERY,  //summery of kingdom
    FINISH
};

//readING strings
string read_string( string prompt )
{
    string result;

    write(prompt);
    result = read_line();

    return result;
}

//reading integers
int read_integer( string prompt )
{
    string line;
    int result;

    line = read_string(prompt);

    while ( not is_integer(line) )
    {
        write_line("Please enter a whole number...");
        line = read_string(prompt);
    }

    result = convert_to_integer(line);

    return result;
}

//gathering users input for the knight
knight_data read_knight()
{
    knight_data result;
    result.name = read_string("Enter name: ");
    result.age = read_integer("Enter age: ");
    return result;
}


//kingdom name
kingdom_data read_kingdom()
{
    kingdom_data result;
    result.name = read_string("Enter kingdom name: ");
    return result;
}

//menu for updating the knights information
knight_update_option read_knight_update_option()
{
    int result;
    
    //displaying options in the menu
    write_line("1: Update name");
    write_line("2: Update age");
    write_line("3: Add tool");
    write_line("4: Delete tool");
    write_line("5: Finish update");
    write_line("=================");
    result = read_integer("Select Option: ");

    return static_cast<knight_update_option>(result - 1);
}

void write_tools(const knight_data &knights)
{
    write_line(to_uppercase(knights.tool));
}

//displaying user inputs in a form of sentences.
void write_knight(const knight_data &knights)
{
    int i;

    write_line("Sir " + knights.name + ", aged " + to_string(knights.age) + "."); 
    for( i = 0; i < knights.tools.size(); i++ )
    {
        write_line(knights.tools[i]);
    }
   
}

//function to select a certain knight
int select_knight(const kingdom_data &kingdom)
{
    int result;
    int i;

    for(i = 0; i < kingdom.knights.size(); i++)
    {
        write_line("KNIGHT " + std::to_string(i + 1));
        write_knight(kingdom.knights[i]);
    }

    result = read_integer("Which knight would you like to select? ");
    
    while (result > kingdom.knights.size())
    {
        write_line("Please enter a knight from the options.");
        result = read_integer("Which knight would you like to select? ");
        
    }
    
    for (int i = 0; i < kingdom.knights.size(); i++)
    {
        if (result - 1 == i)
        {
            write_line("You have selected " + std::to_string(i + 1));
        }
    }

    return result - 1;
}

int select_tool(const knight_data &knights)
{
    int result;
    int i;

    //outputting all tools on hand
    for( i = 0; i < knights.tools.size(); i++ )
    {
        write_line("Tool " + std::to_string( i + 1 ));
        write_tools(knights.tools[i]);
    }

    if ( i == 0 )
    {
        write_line("No tool on hand.");
        result = 0;
    }
    else
    {
        result = read_integer("Select a tool from the options above: ");

        while (result > knights.tools.size() )
        {
            write_line("Please enter a number from the menu.");
            result = read_integer("Which tool would you like to select? ");
        }
    }

    for ( i = 0; i <  knights.tools.size(); i++ )
    {
        if ( result - 1 == i)
        {
            write_line("You have selected " + std::to_string(i + 1));
        }
    }

    return result - 1;
}

void add_tool(knight_data &knights)
{
    knight_data new_tool;
    new_tool = read_tool();

    //adding in a new tool
    knights.tools.push_back(new_tool);

}

//procedure to delete tool
void delete_tool(knight_data &knights, int index)
{
    if ( index >= 0 and index < knights.tools.size() )
    {
        int last_idx;
        last_idx = knights.tools.size() - 1;
        knights.tools[index] = knights.tools[last_idx];
        knights.tools.pop_back();
    }
}

//removing tool from the array
void remove_tool(knight_data &knights)
{
    int i;
    
    i = select_tool(knights);
    if( i + 1 > 0 )
    {
        write_tools(to_uppercase(knights.tools[i]));
        delete_tool(knights, i);
    }
}

//updating knights information with a do while loop and a switch case embedded inside
void update_knight(kingdom_data &kingdom)
{
    knight_update_option option;
    knight_data knights;
    int i;
    //slecting knight
    i = select_knight(kingdom);
    if (i + 1 > 0 )
    {
        write_knight(kingdom.knights[i]);
    }
    //do while loop for updating the knights data, using the enums created before within the switch case
    do
    {
        write_line("============ Update Knight ============");
        write_line("KINGDOM: " + kingdom.name);
        write_knight(kingdom.knights[i]);
        for (int i = 0; i < knights.tools.size(); i++)
        {
            write_tools(knights.tools[i]);
        }
        write_line("=================");
        option = read_knight_update_option();

        switch(option)
        {
            case UPDATE_NAME:
                //reading new user input and replacing it with the old
                kingdom.knights[i].name = read_string("Enter new name: ");
                break;
            case UPDATE_AGE:
                //reading new user input and replacing it with the old
                kingdom.knights[i].age = read_integer("Enter new age: ");
                break;
            case ADD_TOOL:
                add_tool(knights);
                break;
            case DELETE_TOOL:
                remove_tool(knights);
                break;
            case FINISH_UPDATE:
                break;
            default:
                write_line("Please select a valid option.");
        }
    } while ( option != FINISH_UPDATE );
    
}

//add a knight into the array
void add_knight(kingdom_data &kingdom)
{
    knight_data new_knight;
    new_knight = read_knight();

    kingdom.knights.push_back(new_knight);
}

//writing the kingdom
void write_kingdom(const kingdom_data &kingdom)
{
    write_line("===================");
    write_line("      " + kingdom.name);
    write_line("===== Knights =====");
    for(int i = 0; i < kingdom.knights.size(); i++)
    {
        write_knight(kingdom.knights[i]);
    }
    write_line("===================");
}

//procedure to remove knights
void delete_knight(kingdom_data &kingdom, int index)
{
    if ( index >= 0 and index < kingdom.knights.size() )
    {
        int last_idx;
        last_idx = kingdom.knights.size() - 1;
        kingdom.knights[index] = kingdom.knights[last_idx];
        kingdom.knights.pop_back();
    }
}

//procedure to remove a knight from the kingdom/array
void remove_knight(kingdom_data &kingdom)
{
    int i;

    i = select_knight(kingdom);
    if (i + 1 > 0 )
    {
        write_knight(kingdom.knights[i]);
        delete_knight(kingdom, i);
    }

    write_kingdom(kingdom);
}

//menu for kingdom creation
update_kingdom read_update_kingdom()
{
    int result;
    
    write_line("1: Update Knight");
    write_line("2: Delete Knight");
    write_line("3: Add a knight");
    write_line("4: Query a knight");
    write_line("5: Kingdom details");
    write_line("6: Quit");
    write_line("=================");
    result = read_integer("Select Option: ");

    return static_cast<update_kingdom>(result - 1);
}

//displaying a certain knight
void query_knight(kingdom_data &kingdom)
{
    int i;

    i = select_knight(kingdom);
    if (i + 1 > 0 )
    {
        write_knight(kingdom.knights[i]);
    }

}

//switch case for the menu of kingdom creation
void update_kingdom_option()
{
    update_kingdom option;
    kingdom_data kingdom = read_kingdom();
    knight_data my_knight;
    
    add_knight(kingdom);

    do
    {
        write_line("===================");
        write_line("Welcome to kingdom creation!");
        write_line("===================");
        option = read_update_kingdom();
        
        switch (option)
        {
        case UPDATE:
            update_knight(kingdom);
            break;
        case DELETE_KNIGHT:
            remove_knight(kingdom);
            break;
        case ADD_KNIGHT:
            add_knight(kingdom);
            break;
        case QUERY:
            query_knight(kingdom);
            break;
        case SUMMERY:
            write_line(" Kingdom Summery ");
            write_kingdom(kingdom);
            break;
        case FINISH:
            break;
        default:
            write_line("Please select a valid option.");
        }
        
    } while (option != FINISH);
    
}

int main()
{
    
    update_kingdom_option();


    return 0;
}