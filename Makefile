# Variáveis de compilação
CXX      = g++
CXXFLAGS = -Wall -std=c++17 -I. -Imodels

# Nome do executável final
TARGET = programa.exe

# Arquivos .cpp do projeto
SRCS = main.cpp \
       service/HistoricDoublyLinkedList.cpp \
       service/Order.cpp \
       service/KitchenLinkedQueue.cpp \
       service/ActionsLinkedStack.cpp \

# Gerar automaticamente a lista de arquivos .o
OBJS = $(SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Linkar os objetos e gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compilar .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos temporários
clean:
	rm -f $(OBJS) $(TARGET)

# Compilar e executar
run: all
	./$(TARGET)
