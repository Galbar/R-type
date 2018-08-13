R-type videogame

Dependencies
============
* SFML 2.3.2

Compiling & running
===================
```
# Make directory for project
mkdir /root/folder/
cd /root/folder/

# Clone necessary repos
git clone -b hum2d https://github.com/Galbar/hummingbird.git Hum2D
git clone https://github.com/Galbar/tiled-map.git tiled
git clone -b hum2d https://github.com/Galbar/hummingbird-MOGL.git MOGL
git clone -b 0.9.7.4 https://github.com/g-truc/glm.git
git clone -b 5.3.2 https://github.com/lua/lua.git
git clone https://github.com/xaviermariaconejo/R-type.git

curl -R -O http://www.lua.org/ftp/lua-5.3.2.tar.gz
tar zxf lua-5.3.2.tar.gz
cd lua-5.3.2
make linux

# Compile framework
cd ../Hum2D
make

cd ../lua
make

cd ../tiled
make

cd ../MOGL
make

# Compile game
cd ../R-type
make

# Run game
./game
```
 
