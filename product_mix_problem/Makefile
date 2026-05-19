# 1. Caminhos Base do CPLEX instalados na sua máquina
CPLEXDIR   = /opt/ibm/ILOG/CPLEX_Studio2211/cplex
CONCERTDIR = /opt/ibm/ILOG/CPLEX_Studio2211/concert

# 2. Compilador e Flags Obrigatórias
CXX        = g++
# -DIL_STD é obrigatório para o CPLEX usar o namespace std do C++ moderno
CXXFLAGS   = -O2 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

# 3. Onde encontrar os arquivos .h (Includes)
INCLUDES   = -I$(CPLEXDIR)/include -I$(CONCERTDIR)/include

# 4. Onde encontrar os arquivos de biblioteca (.a)
# O formato padrão para Linux x86-64 é a pasta static_pic
LIBPATHS   = -L$(CPLEXDIR)/lib/x86-64_linux/static_pic -L$(CONCERTDIR)/lib/x86-64_linux/static_pic

# 5. As bibliotecas que o autor do AUR mencionou (A ordem importa no C++)
LIBS       = -lconcert -lilocplex -lcplex -lm -lpthread -ldl

# 6. Seu código
SRC        = product_mix.cpp
TARGET     = product_mix

# Regras de compilação
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBPATHS) $(LIBS)

clean:
	rm -f $(TARGET)