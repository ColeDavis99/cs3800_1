#include "processor.h"
using namespace Computer;


//Static variable scope enable
unsigned long Process::processIds=0;


//Default constructor
Process::Process()
{
  id=processIds;
  processIds++;
  processState = NotRunning;
  currInstruction = 0;
}

// Constructor with list of instructions
Process::Process(const std::vector<Instruction> & inst)
{
  //Make shallow copy of inst
  id=processIds;
  instructions = vector<Instruction> (inst);
  currInstruction = 0;
  processIds++;
}


// Copy Constructor
Process::Process(const Process & copy)
{
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
// returns whether or not it finished, this processes instructions in a process
bool Process::ProcessUnit(unsigned long pu)
{
  StartProcessing();

  cout<<"Process - "<<this->Id()<<" processing..."<<endl;

  //Keep processing only if we have pu's left to use, AND there's still instructions left to process
  while(currInstruction < instructions.size() && pu > 0)
  {
    pu = instructions[currInstruction].Process(pu);

    if(instructions[currInstruction].TimeLeft() <= 0)
      currInstruction++;
  }

  StopProcessing();


  //We had more pu's passed in than was needed to complete the process
  if(pu > 0)
    return true;

  //Check the last element in the instruction vector to see if the whole process needs more pu's to be completed
  else if(instructions[instructions.size()-1].TimeLeft() > 0)
    return false;

}


// Gets remaining time to process instructions
unsigned long Process::RemainingInstructionTime() const
{
	unsigned long remainingProcessTime = 0;

	//Loop through the vector and return sum of all of instruction objects remaining time
  for(int i=0; i<instructions.size(); i++)
		remainingProcessTime += instructions[i].TimeLeft();


	return remainingProcessTime;
}


// Gets the number of pu's needed to complete the process
unsigned long Process::TotalInstructionTime() const
{
	unsigned long originalTime = 0;

	//Loop through the vector and return sum of all of instruction
	for(int i=0; i<instructions.size(); i++)
		originalTime += instructions[i].ProcessTime();

	return originalTime;
}


// Ostream to print a process
std::ostream & Computer::operator<<(std::ostream& out, const Process& p)
{
  cout << "Process - " << p.id << ": " << p.NumInstructionsLeft() << " " << p.RemainingInstructionTime() << "/" << p.TotalInstructionTime();
  return out;
}


//Copy Assignment operator
Process& Process::operator=(const Process & copy)
{
  id = copy.id;
  processState = copy.processState;
  instructions.clear();
  instructions = copy.instructions;
  currInstruction = copy.currInstruction;
  return *this;
}
