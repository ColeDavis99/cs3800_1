#include "processor.h"
using namespace Computer;

// Constructor with list of instructions
Computer::Process::Process(const std::vector<Instruction> & inst)
{
  //THIS SHOULD BE A SHALLOW COPY, NEED TO TEST ME STILL. &inst is by reference
  instructions = vector<Instruction> (inst);

  //cout<<"*instructions: "<<&instructions<<"  inst: "<<&inst<<endl;
}


// Copy Constructor
Computer::Process::Process(const Process & copy)
{
  cout<<"Im a copy constructor"<<endl<<endl;
}
