compile: dbuild run

main = main.cpp
output = ramen
test = test.ramen

dbuild: $(main) $(output)
	clang++ $(main) -std=c++20 -Wall -Werror -v -g -fsanitize=address -o $(output)

build: $(main) $(output)
	clang++ $(main) -std=c++20 -Wall -Werror -v -o $(output)

run: $(output) $(test)
	./$(output) $(test)

debug: build check

check: $(output) $(test)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(output) $(test)

verify:
	clang++ output.cpp -std=c++20 && ./a.out

