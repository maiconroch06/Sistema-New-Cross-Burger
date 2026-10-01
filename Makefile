# Variáveis de compilação
CXX      = g++
CXXFLAGS = -Wall -std=c++17 -I. -Imodels

# Nome do executável final (com .exe para Windows)
TARGET = programa.exe

# Listar todos os arquivos .cpp do projeto (REMOVIDA a '\' da última linha ativa)
SRCS = main.cpp \
	service/HistoricDoublyLinkedList.cpp \
	service/Order.cpp
	service/KitchenLinkedQueue.cpp \
	service/ActionsLinkedStack.cpp \
	view/menus.cpp

# Gerar automaticamente a lista de arquivos de objetos (.o)
OBJS = $(SRCS:.cpp=.o)

# Regra principal (padrão)
all: $(TARGET)

# Regra para linkar os objetos e gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regra genérica para compilar os arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos temporários gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para compilar e rodar direto no terminal
run: all
	./$(TARGET)