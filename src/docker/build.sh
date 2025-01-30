#!/bin/bash

dos2unix "$0" 2>/dev/null || true

if ! command -v docker &> /dev/null; then
    echo "Docker is not installed. Please install Docker first."
    exit 1
fi

PROJECT_ROOT="$(dirname "$(pwd)")"

TEMP_DIR=$(mktemp -d)
echo "Creating temporary working directory: $TEMP_DIR"

echo "Copying required files..."
cp -r \
    "$PROJECT_ROOT"/*.cpp \
    "$PROJECT_ROOT"/*.h \
    "$PROJECT_ROOT/sdk" \
    "$TEMP_DIR/"

mkdir -p "$TEMP_DIR/cmake"

cp "$PROJECT_ROOT/cmake/CMakeLists.txt" "$TEMP_DIR/cmake/"

cp Dockerfile "$TEMP_DIR/"

cat > "$TEMP_DIR/cmake/compile.sh" << 'EOF'
#!/bin/bash
set -e
mkdir -p build
cd build
cmake ../cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
strip -s spc-integration.so
echo "Checking binary dependencies:"
ldd spc-integration.so
chmod -R 777 .
EOF

chmod +x "$TEMP_DIR/cmake/compile.sh"

cd "$TEMP_DIR"

echo "Cleaning Docker environment..."
docker rm -f samp-plugin-builder 2>/dev/null || true
docker rmi -f samp-plugin-builder 2>/dev/null || true

echo "Building Docker image..."
docker build --no-cache -t samp-plugin-builder .

if [ $? -ne 0 ]; then
    echo "Error during Docker image build!"
    exit 1
fi

rm -rf "$PROJECT_ROOT/build"
mkdir -p "$PROJECT_ROOT/build"

echo "Compiling plugin..."
docker run --rm \
    --name samp-plugin-builder \
    -v "$TEMP_DIR:/build" \
    samp-plugin-builder

if [ $? -ne 0 ]; then
    echo "Error during compilation!"
    exit 1
fi

if [ -f "$TEMP_DIR/build/spc-integration.so" ]; then
    cp -r "$TEMP_DIR/build/"* "$PROJECT_ROOT/build/"
    echo "Compilation completed! Files have been copied to the build folder in the project root!"
else
    echo "Error: The file spc-integration.so was not generated!"
    exit 1
fi

chmod -R 755 "$PROJECT_ROOT/build"
rm -rf "$TEMP_DIR"