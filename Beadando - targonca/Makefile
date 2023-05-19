all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/forklift.c src/wheels.c src/light.c src/boundingbox.c src/pallet.c src/timer.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o forklift.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/forklift.c src/wheels.c src/light.c src/boundingbox.c src/pallet.c src/timer.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o forklift -Wall -Wextra -Wpedantic
