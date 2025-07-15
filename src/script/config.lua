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
        for i = 1, 100 do
        print("i = " .. i)
        CREATE_ELEM("BOX")
        end
  

    end,
}

