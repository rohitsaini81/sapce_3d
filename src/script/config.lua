title = "My Rick and Morty"
width = 800
height = 600
health = 1400
playerMovementSpeed = 100
fullscreen = false

-- say_hello_rohit = function(name)
--     print("Hello you rohit this is ----->, " .. name .. "!")
-- end


-- say_hello_rohit("Lua World")
return {
    version = "1.0.0",

    say_hello = function(name)
        print("Hello you from Lua, " .. name .. "!")
    end,
    print_health = function()
        print("Current health is: " .. tostring(health))
        -- print("creating a new object in world")

    end,

    Init_elements = function()
        print("creating a new object in world")
        for i = 1, 0 do
        print("i = " .. i)
        CREATE_ELEM("CUBE","path","/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/gltf/test.glb")
        CREATE_ELEM("BOX","heightxwidth","xy")

        end
  

    end,
}

