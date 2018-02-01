/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Bytecode
*
*
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <vector>
#include <string>

namespace Lania
{
	enum opcodes
	{
		INC,
		DEC,
		ADD,
		ADDI,
		SUB,
		SUBI,
		MUL,
		MULI,
		DIV,
		DIVI
	};

	typedef struct Instruction
	{
		int opcode;
		int destination;
		int source1;
		int source2;
		double immediateValue;
		std::string immediateString;
	}Instruction;

	typedef struct Bytecode
	{
		std::vector<Instruction> instructions;
	}Bytecode;
}