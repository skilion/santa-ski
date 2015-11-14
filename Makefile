LDLIBS = -lsfml-graphics -lsfml-system -lsfml-window

SOURCES = \
	decal.cpp \
	dune.cpp \
	entity.cpp \
	game.cpp \
	global.cpp \
	jump.cpp \
	main.cpp \
	player.cpp \
	rock.cpp \
	tree.cpp \
	util.cpp

game: $(SOURCES)
	$(CXX) -o $@ $(SOURCES) $(LDLIBS)
