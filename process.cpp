#include "processor.h"
using namespace Computer;

//Static variable scope enable
unsigned long Process::processIds=0;



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
// returns whether or not it finished, this processes instructions in a process
bool Process::ProcessUnit(unsigned long pu)
{
	StartProcessing();
	
	//Keep processing only if we have pu's left to use, AND there's still instructions left to process
	while(pu > 0 && instructions.size() > 0)
	{
		pu = instructions.back().Process(pu);
		
		//We just completed a single instuction
		if(pu > 0)
			instructions.pop_back();
	}

	StopProcessing();
	
	
	//We've got some extra pu's left and have finished processing all instructions
	if(pu > 0)
		return true;
		
	//Exactly the amount of pu's needed to complete the process was given  
	else if(pu == 0 && instructions.size() == 0)
		return true;
	
	//The process did not complete
	else
		return false;
}


// Gets remaining time to process instructions
unsigned long Process::RemainingInstructionTime() const
{
	unsigned long remainingProcessTime = 0;
	//Loop through the vector and return sum of all of instruction objects remaining time
	for(int i=0; i<instructions.size(); i++)
	{
		remainingProcessTime += instructions[i].TimeLeft();
	}
	
	return remainingProcessTime;
}


// gets the total time that was needed to process all intructions when process was first created
unsigned long Process::TotalInstructionTime() const
{
	unsigned long originalTime = 0;
	//Loop through the vector and return sum of all of instruction 
	for(int i=0; i<instructions.size(); i++)
	{
		originalTime += instructions[i].ProcessTime();
	}
	
	return originalTime;
}


// Ostream to print a process
std::ostream & Computer::operator<<(std::ostream& out, const Process& p)
{
  cout << "Process - " << p.processIds << ": "<< p.NumInstructionsLeft() << " " <<p.RemainingInstructionTime() << "/" << p.TotalInstructionTime()<<endl;
  return out;
}
