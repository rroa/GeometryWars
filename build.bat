echo "==================================================="
echo "CLEANUP"
echo "==================================================="
make clean
make -f Makefile.emscripten clean
echo ""

echo "==================================================="
echo "BUILDING NATIVELY"
echo "==================================================="
make
echo ""

echo "==================================================="
echo "BUILDING FOR THE WEB"
echo "==================================================="
make -f Makefile.emscripten
echo ""
