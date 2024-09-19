CXX := g++
CXXFLAGS := -Iinclude
SRCDIR := src
OBJDIR := obj
BINDIR := bin

CORE_SRCS := $(wildcard $(SRCDIR)/core/*.cpp)
FERMION_SRCS := $(wildcard $(SRCDIR)/fermions/*.cpp)
BOSON_SRCS := $(wildcard $(SRCDIR)/bosons/*.cpp)
UTILITY_SRCS := $(wildcard $(SRCDIR)/utilities/*.cpp)
MAIN_SRC := $(wildcard $(SRCDIR)/main/*.cpp)

SRCS := $(CORE_SRCS) $(FERMION_SRCS) $(BOSON_SRCS) $(UTILITY_SRCS) $(MAIN_SRC)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS := $(OBJS:/=\)
TARGET := $(BINDIR)/particle_catalogue.exe

all: build $(TARGET)

build:
	@if not exist "$(OBJDIR)\core" mkdir "$(OBJDIR)\core"
	@if not exist "$(OBJDIR)\fermions" mkdir "$(OBJDIR)\fermions"
	@if not exist "$(OBJDIR)\bosons" mkdir "$(OBJDIR)\bosons"
	@if not exist "$(OBJDIR)\utilities" mkdir "$(OBJDIR)\utilities"
	@if not exist "$(OBJDIR)\main" mkdir "$(OBJDIR)\main"
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(BINDIR)" rmdir /s /q "$(BINDIR)"

.PHONY: all build clean
