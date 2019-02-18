//
//  main.cpp
//  FNV-Test
//
//  Created by Daisuke T on 2019/02/18.
//  Copyright © 2019 FNV-Test. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "fnv.h"
#include "fnv-5.0.3/hash_32.c"
#include "fnv-5.0.3/hash_64.c"
#include "fnv-5.0.3/hash_32a.c"
#include "fnv-5.0.3/hash_64a.c"

static int getfilesize(const char *filename);
static void fnv_test_file();

int main(int argc, const char * argv[]) {
	fnv_test_file();
	
	return 0;
}



static int getfilesize(const char *filename)
{
	std::ifstream stream(filename, std::ifstream::ate | std::ifstream::binary);
	int len = (int)stream.tellg();
	stream.close();
	return len;
}

static void fnv_test_file()
{
	std::fstream stream;
	
	stream.open("alice29.txt", std::ios::in);
	if(!stream.is_open())
	{
		std::cout <<  "file open error" << std::endl;
		return;
	}
	
	int filesize = getfilesize("alice29.txt");
	char *buf = new char[filesize]();
	stream.read(buf, sizeof(char) * filesize);
	
	std::cout << "fnv0_32(file) -> 0x" << std::hex << fnv_32_buf(buf, filesize, 0) << std::endl;
	std::cout << "fnv0_64(file) -> 0x" << std::hex << fnv_64_buf(buf, filesize, 0) << std::endl;
	std::cout << "fnv1_32(file) -> 0x" << std::hex << fnv_32_buf(buf, filesize, 2166136261) << std::endl;
	std::cout << "fnv1_64(file) -> 0x" << std::hex << fnv_64_buf(buf, filesize, 14695981039346656037ULL) << std::endl;
	std::cout << "fnv1a_32(file) -> 0x" << std::hex << fnv_32a_buf(buf, filesize, 2166136261) << std::endl;
	std::cout << "fnv1a_64(file) -> 0x" << std::hex << fnv_64a_buf(buf, filesize, 14695981039346656037ULL) << std::endl;

	delete []buf;
	stream.close();
}
