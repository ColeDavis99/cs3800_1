#include "processor.h"
using namespace Computer;

// Constructor with list of instructions
Process::Process(const std::vector<Instruction> & inst)
{
  //Make shallow copy of inst
  instructions = vector<Instruction> (inst);
}


// Copy Constructor
Process::Process(const Process & copy)
{
  //processIds = copy.processIds  //Do we touch static vars?
  id = copy.id;
  processState = copy.processState;
  instructions = copy.instructions;
  currInstruction = copy.currInstruction;
}


// Mark process as stopping processing
//Only changes state
void Process::StartProcessing()
{
  processState = Running;
  return;
}


// Mark process as stopping processing
// Only changes state
void Process::StopProcessing()
{
  processState = NotRunning;
  return;
}


// Process for <pu> PUs
// returns wether or not it finished
bool ProcessUnit(unsigned long pu)
{

}




//BROKEN << OVERLOAD OPERATOR BELOW
// Ostream to print a process
// Hint: to write in the cpp, you will need to scope to the namespace for operator<<
std::ostream & Computer::operator<<(std::ostream& out, const Process& p)
{
  cout << "WIZZER" << endl;
  
  return out;
}
