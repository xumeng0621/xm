If you have Visual Studio 2010 installed, you should be able to launch the project by running CityConnect.sln.

Inside this project, it contains the following important files:
- CityConnect.cpp
- CityConnect.h
- input.txt
- expected.txt
(Note: input.txt and expected.txt files are located in the Debug folder.)


Follow the instructions below to automated testing:
1) Compile the program in Visual Studio 2012.
2) Open up command prompt.
3) Change the directory to the Debug folder using "cd" command. (eg. cd Debug).
4) Run the following command:

	CityConnect.exe < input.txt > output.txt
	
5) Compare the file different between the output file you have just generated, and the expected file:
	
	fc output.txt expected.txt
	
6) If the testing passed, the program should display the following message:

	FC: no differences encountered
	

This guide and the C++ code are written by Loke Yan Hao.