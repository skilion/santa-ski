LDLIBS = -lsfml-graphics -lsfml-system -lsfml-window

SOURCES = \
	decal.cpp \
	entity.cpp \
	game.cpp \
	global.cpp \
	main.cpp \
	player.cpp \
	util.cpp

game: $(SOURCES)
	$(CXX) -o $@ $(SOURCES) $(LDLIBS)