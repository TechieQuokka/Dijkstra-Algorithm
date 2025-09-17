# Dijkstra Algorithm Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
OPTFLAGS = -O2
SRCDIR = src
INCDIR = include
TESTDIR = tests
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/graph.c $(SRCDIR)/priority_queue.c $(SRCDIR)/dijkstra.c
MAIN_SRC = $(SRCDIR)/main.c
TEST_SRC = $(TESTDIR)/test_dijkstra.c

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJ = $(OBJDIR)/main.o
TEST_OBJ = $(OBJDIR)/test_dijkstra.o

# Target executables
TARGET = $(BINDIR)/dijkstra
TEST_TARGET = $(BINDIR)/test_dijkstra

# Default target
all: directories $(TARGET) $(TEST_TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Main executable
$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $@ $^

# Test executable
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $@ $^

# Object files compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/test_dijkstra.o: $(TEST_SRC)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Run the main program
run: $(TARGET)
	$(TARGET)

# Run tests
test: $(TEST_TARGET)
	$(TEST_TARGET)

# Debug build
debug: CFLAGS += -DDEBUG -g3 -O0
debug: clean $(TARGET) $(TEST_TARGET)

# Release build
release: CFLAGS += -DNDEBUG
release: OPTFLAGS = -O3 -march=native
release: clean $(TARGET)

# Performance analysis
profile: CFLAGS += -pg
profile: clean $(TARGET)

# Memory check (requires valgrind on Unix systems)
memcheck: $(TARGET)
	@echo "Memory checking requires valgrind (Unix/Linux systems)"
	@echo "On Windows, use Dr. Memory or Application Verifier"

# Clean build artifacts
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)

# Show help
help:
	@echo Available targets:
	@echo   all      - Build both main program and tests (default)
	@echo   run      - Build and run the main program
	@echo   test     - Build and run tests
	@echo   debug    - Build debug version with symbols and no optimization
	@echo   release  - Build optimized release version
	@echo   profile  - Build with profiling support
	@echo   clean    - Remove all build artifacts
	@echo   help     - Show this help message

# Installation (copy to system directory)
install: release
	@echo "Installation would copy $(TARGET) to system directory"
	@echo "Modify this target according to your system requirements"

# Uninstallation
uninstall:
	@echo "Uninstallation would remove dijkstra from system directory"
	@echo "Modify this target according to your system requirements"

# Static analysis (requires cppcheck)
analyze:
	@echo "Running static analysis..."
	@echo "This requires cppcheck to be installed"
	cppcheck --enable=all --std=c99 $(SRCDIR)/ $(INCDIR)/

# Documentation generation (requires doxygen)
docs:
	@echo "Generating documentation..."
	@echo "This requires doxygen to be installed"
	doxygen Doxyfile

# Phony targets
.PHONY: all directories run test debug release profile memcheck clean help install uninstall analyze docs

# Dependencies
$(OBJDIR)/graph.o: $(INCDIR)/graph.h
$(OBJDIR)/priority_queue.o: $(INCDIR)/priority_queue.h
$(OBJDIR)/dijkstra.o: $(INCDIR)/dijkstra.h $(INCDIR)/graph.h $(INCDIR)/priority_queue.h
$(OBJDIR)/main.o: $(INCDIR)/graph.h $(INCDIR)/dijkstra.h
$(OBJDIR)/test_dijkstra.o: $(INCDIR)/graph.h $(INCDIR)/dijkstra.h $(INCDIR)/priority_queue.h