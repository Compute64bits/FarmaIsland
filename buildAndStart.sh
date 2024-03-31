mkdir -p out 

rm out/main
g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o out/main
./out/main