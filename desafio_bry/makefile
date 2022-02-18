include ./makedefs

CRYPTO_SRC_FILES = $(wildcard $(CRYPTO)/*.cpp)
CRYPTO_OBJ_FILES = $(patsubst $(CRYPTO)/%.cpp, $(CRYPTO)/%.o, $(CRYPTO_SRC_FILES))
OBJ_FILES        = $(CRYPTO_OBJ_FILES)
	
all: reader

reader: $(OBJ_FILES) $(SRC)/desafio_bry_reader_cert.o
	$(CXX) -o $@ $(OBJ_FILES) $(SRC)/desafio_bry_reader_cert.o $(CXXFLAGS)
	
%.o: %.cpp  %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(OBJ_FILES):
	$(MAKE) -C $(CRYPTO)

.PHONY: clean

clean:
	$(MAKE) -C $(CRYPTO) clean
	rm -f $(SRC)/*.o reader core resources/generatedSignatures/* $(SRC)/*~ $(INCLUDE)/*~
