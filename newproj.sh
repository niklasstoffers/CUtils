echo "Creating project: $1";
mkdir $1;

mkdir $1/bin
touch $1/bin/.gitkeep
mkdir $1/include
touch $1/include/.gitkeep
mkdir $1/lib
touch $1/lib/.gitkeep
mkdir $1/src
touch $1/src/.gitkeep

cat <<EOF >$1/src/main.c
int main() {
	return 0;
}
EOF

cat <<EOF >$1/Makefile
CC := gcc
SRCDIR := src
BUILDDIR := build
TARGET := bin/$1
SRCEXT := c
SOURCES := \$(shell find \$(SRCDIR) -type f -name *.\$(SRCEXT))
OBJECTS := \$(patsubst \$(SRCDIR)/%,\$(BUILDDIR)/%,\$(SOURCES:.\$(SRCEXT)=.o))
CFLAGS := 
LIB := -L lib
INC := -I include

\$(TARGET): \$(OBJECTS)
	@echo " Linking..."
	@echo " \$(CC) \$^ -o \$(TARGET) \$(LIB)"; \$(CC) \$^ -o \$(TARGET) \$(LIB) -O3

\$(BUILDDIR)/%.o: \$(SRCDIR)/%.\$(SRCEXT)
	@echo " Building..."
	@mkdir -p \$(BUILDDIR)
	@echo " \$(CC) \$(CFLAGS) \$(INC) -c -o \$@ \$<"; \$(CC) \$(CFLAGS) \$(INC) -c -o \$@ \$< -O3

clean:
	@echo " Cleaning..."; 
	@echo " \$(RM) -r \$(BUILDDIR) \$(TARGET)"; \$(RM) -r \$(BUILDDIR) \$(TARGET)

.PHONY: clean
EOF

cat <<EOF >$1/README.md
# $1
New project
EOF

echo "Creating clang config";
(cd $1 && make clean && bear make);
echo " ";

echo "Project creation successfull";
