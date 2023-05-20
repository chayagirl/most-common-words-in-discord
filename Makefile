parse-csv:
	cp ./rapidcsv/src/rapidcsv.h .
	g++ -o parse-csv parse-csv.cpp
	rm rapidcsv.h

clean:
	rm parse-csv