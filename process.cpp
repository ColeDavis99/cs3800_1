#include "processor.h"
using namespace Computer;

// Constructor with list of instructions
Computer::Process::Process(const std::vector<Instruction> & inst)
{
  //Make shallow copy of inst
  instructions = vector<Instruction> (inst);
}


// Copy Constructor
Computer::Process::Process(const Process & copy)
{
  //processIds = copy.processIds  //Do we touch static vars?
  id = copy.id;
  processState = copy.processState;
  instructions = copy.instructions;
  currInstruction = copy.currInstruction;
}
