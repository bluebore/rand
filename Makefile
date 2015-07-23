


all: tera_coprocessor output

tera_coprocessor: rand.cc
	g++ -Wall -Werror -g $< -o $@ -lpthread

output: tera_coprocessor
	mkdir -p output/bin output/conf output/log
	cp tera_coprocessor ./output/bin/

clean:
	rm -rf *processor
	rm -rf output
