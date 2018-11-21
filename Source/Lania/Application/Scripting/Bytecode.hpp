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
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/String.hpp>

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
		List<Instruction> instructions;
	}Bytecode;
}
