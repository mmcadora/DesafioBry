include ../../makedefs

INCLUDE = $(TOP)/include
CRYPTO  = $(SRC)/crypto

CXX_MINIMUM_FLAGS = -Wall -I$(INCLUDE) -std=$(CXX_VERSION)

CRYPTO_FILES = $(wildcard $(CRYPTO)/*.cpp)
OBJ_FILES = $(patsubst $(CRYPTO)/%.cpp, ./%.o, $(CRYPTO_FILES))

object_files: $(OBJ_FILES)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXX_MINIMUM_FLAGS)

.PHONY: clean

clean:
	rm -f $(CRYPTO)/*.o $(CRYPTO)/*~