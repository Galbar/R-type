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
git clone https://github.com/Galbar/Hummingbird2D.git Hum2D
git clone https://github.com/Galbar/tiled-map.git tiled
git clone https://github.com/Galbar/Hummingbird2D-MOGL.git MOGL
git clone https://github.com/g-truc/glm.git
git clone https://github.com/xaviermariaconejo/R-type.git

# Compile framework
cd Hum2D
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
 
