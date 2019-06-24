/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Bytecode
*
* The list of instructions that controls the scripting engine
* virtual machine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../Utilities/DataStructures/Vector.hpp"
#include "../../Utilities/DataStructures/String.hpp"
#include <stdint.h>

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
		uint32_t opcode;
		uint32_t destination;
		uint32_t source1;
		uint32_t source2;
		double immediateValue;
		String immediateString;
		Instruction():
			opcode(0),
			destination(0),
			source1(0),
			source2(0),
			immediateValue(0.0)
		{}
	}Instruction;

	typedef struct Bytecode
	{
		Vector<Instruction> instructions;
	}Bytecode;
}
