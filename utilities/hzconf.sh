#!/usr/bin/env sh
OVERRIDE="../override"
OVERRIDEGL="$(OVERRIDE)/global"
make hz
mkdir -p $(OVERRIDEGL)
echo "hz=$(./bin/gethz)" > "$(OVERRIDEGL)/hz.mk"
cat "$(OVERRIDEGL/hz.mk"
make clean
