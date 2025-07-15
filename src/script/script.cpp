extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include <cstring> // for strcmp
#include <iostream>
#include <string>
#include <ctime>
#include <sys/stat.h>

#include "physics.h" 
#include "objects.h"
#include "global_var.h"
float health=0.1f;


extern "C" int lua_CREATE_ELEM(lua_State* L);

void run_lua_script(const char* filename) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);
luaopen_string(L);
luaopen_table(L);
luaopen_math(L);
luaopen_debug(L);
// lua_register(L, "CREATE_ELEM", lua_CREATE_ELEM);

//     if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 1, 0)) {
//         std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
//         lua_close(L);
//         return;
//     }

lua_register(L, "CREATE_ELEM", lua_CREATE_ELEM);

// Load & run the script
if (luaL_dofile(L, filename)) {
    std::cerr << "Error loading Lua file: " << lua_tostring(L, -1) << "\n";
    lua_close(L);
    return;
}


    // Optional: Access fields from returned table
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "version");
        if (lua_isstring(L, -1)) {
            std::cout << "Script version: " << lua_tostring(L, -1) << std::endl;
        }
        lua_pop(L, 1);

        lua_getfield(L, -1, "say_hello");
        if (lua_isfunction(L, -1)) {
            lua_pushstring(L, "C++");
            if (lua_pcall(L, 1, 0, 0)) {
                std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
            }
        }

        lua_getfield(L, -1, "Init_elements");
        if (lua_isfunction(L, -1)) {
            if (lua_pcall(L, 0, 0, 0) != 0) {
                std::cerr << "Lua error calling print_health: " << lua_tostring(L, -1) << std::endl;
            }

        }

        lua_getfield(L, -1, "print_health");
        if (lua_isfunction(L, -1)) {
            if (lua_pcall(L, 0, 0, 0) != 0) {
                std::cerr << "Lua error calling print_health: " << lua_tostring(L, -1) << std::endl;
            }
        }

        


    }

    lua_close(L);
}





void load_config(const char* filename) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, filename)) {
        std::cerr << "Error loading Lua file: " << lua_tostring(L, -1) << "\n";
        lua_close(L);
        return;
    }

    // Get string variable: title
    lua_getglobal(L, "title");
    if (lua_isstring(L, -1)) {
        const char* title = lua_tostring(L, -1);
        std::cout << "Title: " << title << "\n";
    }
    lua_pop(L, 1); // remove value from stack

    // Get number variable: width
    lua_getglobal(L, "width");
    if (lua_isnumber(L, -1)) {
        int width = lua_tointeger(L, -1);
        std::cout << "Width: " << width << "\n";
    }
    lua_pop(L, 1);

    // Get number variable: height
    lua_getglobal(L, "height");
    if (lua_isnumber(L, -1)) {
        int height = lua_tointeger(L, -1);
        std::cout << "Height: " << height << "\n";
    }
    lua_pop(L, 1);


    // playerMoveSpeed

    //test
    lua_getglobal(L,"health");
    if(lua_isnumber(L,-1)){
        int healthh = lua_tointeger(L,-1);
        health = healthh;
    }
    lua_pop(L,1);


    lua_getglobal(L,"playerMovementSpeed");
    if(lua_isnumber(L,-1)){
        float pmspeed = lua_tointeger(L,-1);
        playerMoveSpeed = pmspeed;
    }
    lua_pop(L,1);

    // Get boolean variable: fullscreen
    lua_getglobal(L, "fullscreen");
    if (lua_isboolean(L, -1)) {
        bool fullscreen = lua_toboolean(L, -1);
        std::cout << "Fullscreen: " << (fullscreen ? "true" : "false") << "\n";
    }
    lua_pop(L, 1);

    lua_close(L);
}


#include <sys/stat.h>   // for stat()
#include <ctime>        // for time_t
#include <string>

time_t getFileLastModifiedTime(const std::string& path) {
    struct stat attr;
    if (stat(path.c_str(), &attr) == 0)
        return attr.st_mtime;
    return 0;
}



int lua_CREATE_ELEM(lua_State* L) {
    const char* typeStr = luaL_checkstring(L, 1); // Get 1st arg (element type)

    ElementType type;
    std::cout<<"argument : "<<typeStr<<"\n";

    // Map string to ElementType enum
    if (strcmp(typeStr, "BOX") == 0) {
        type = ElementType::BOX;
        // return 0;
    }else {
        std::cerr << "Unknown element type: " << typeStr << std::endl;
        return 0;
    }

    try {


        if (dynamicsWorld) {
            Elements* newElem = new Elements(type, dynamicsWorld);
            std::cout << "Created element of type: " << typeStr << "\n";
            std::cout << "Mass: " << newElem->mass << "\n";

            if (newElem->body) {
                dynamicsWorld->addRigidBody(newElem->body);
                elementList.push_back(newElem);
                std::cout << "Rigid body added\n";
            } else {
                std::cerr << "Element body is null\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0; // No return values to Lua
}
