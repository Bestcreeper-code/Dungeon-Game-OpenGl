CXX := g++
EXE := Game.exe

OBJ_DIR := build

INCLUDES := -I"./libs/freeglut/include" -I"./"
LIBDIRS := -L"./libs/freeglut/lib/x64"
LIBS := -lopengl32 -lglu32 -lfreeglut -lwinmm 

SRCS := Main.cpp \
        Gameplay/Game.cpp \
        Graphics/Graphics.cpp \
        Types/Types.cpp \
        Tiles/Tiles.cpp \
        Ui/Menus/Menus.cpp \
        Ui/Messages/Messages.cpp \
        Player/Player.cpp \
        FightManager/FightManager.cpp \
        Imagemanager/ImageManager.cpp \
        Sound/Sound.cpp

# Convert source file paths to object file paths in build folder
OBJS := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS_DEBUG := -std=c++17 -O0 -g
CXXFLAGS_RELEASE := -std=c++17 -Os -s -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti

.PHONY: all debug release

all: debug

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: $(EXE)
	$(EXE)

release: CXXFLAGS := $(CXXFLAGS_RELEASE)
release: $(EXE)
	$(EXE)

# Link executable from object files
$(EXE): $(OBJS)
	@$(CXX) $^ -o $@ $(LIBDIRS) $(LIBS) 

# Compile .cpp files into build folder, create subdirs as needed
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

