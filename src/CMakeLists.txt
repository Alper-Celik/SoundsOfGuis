# backtracing and error handling helpers and clases, enums etc.
add_subdirectory(Utils) # mostly header only and seperated look at headers for
                        # all the things in module

# for loading sounds, managing sound at 3d space, managing sound list
add_subdirectory(SoundCode)

# platform spesific code for getting and setting mouse pos, getting element at
# position, getting element type etc.
add_subdirectory(GuiCollector)

# config loading and required functions for mainloop
add_subdirectory(MainLoop)

# start of program (main()) , cli parsing ,gui
add_subdirectory(UserInterface)
