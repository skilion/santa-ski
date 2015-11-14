LDLIBS = -lsfml-graphics -lsfml-system -lsfml-window

SOURCES = \
	entity.cpp \
	global.cpp \
	main.cpp \
	player.cpp \
	util.cpp

game: $(SOURCES)
	$(CXX) -o $@ $(SOURCES) $(LDLIBS)
