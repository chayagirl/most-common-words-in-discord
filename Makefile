parse-csv:
	cp ./rapidcsv/src/rapidcsv.h .
	g++ -o parse-csv parse-csv.cpp

clean:
	rm parse-csv rapidcsv.h