
APP_NAME = physics
BUILD_DIR = /Users/yianniKir/Desktop/physics/
APP_DEFINES:=
APP_INCLUDES:= -I./src/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit 
APP_LINKERS:= -L./src/vendors/GLFW/lib -lglfw3
C_FILES := ./src/main.cpp ./src/vendors/glad/glad.c ./src/particle.cpp ./src/pfgen.cpp


build:
	g++ -Wno-deprecated -Wno-c++11-extensions $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)