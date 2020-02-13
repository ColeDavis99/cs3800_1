/*
 * Written by: Josh Cash
 * Reviewed by: Richard Kell
 * Purpose: Provide a simple challenge in regards to processes and multi-threading
 */
#ifndef COMP_PROCESS_H
#define COMP_PROCESS_H

#include <vector>
#include <ostream>
#include "instruction.h"

// DO NOT MODIFY THIS FILE

namespace Computer
{
  enum ProcessState {Running, NotRunning};

  // Process class
  class Process
  {
  private:
      // static var to keep track of current ids
      static unsigned long processIds;
      // current Processes id
      unsigned long id;
      // The state of the current process
      ProcessState processState;
      // The list of instructions
      std::vector<Instruction> instructions;
      // The current instruction
      unsigned long currInstruction;
    public:
      // Default Constructor
      Process();
      // Constructor with list of instructions
      Process(const std::vector<Instruction> & inst);
      // Copy Constructors
      Process(const Process & copy);
      // Copy Assignment operator
      Process & operator=(const Process & copy);
      // Ostream to print a process
      // Hint: to write in the cpp, you will need to scope to the namespace for operator<<
      friend std::ostream & operator<<(std::ostream & out, const Process & p);
      // get Process Id
      unsigned long Id() const { return id; }
      // get Process State
      ProcessState State() const { return processState; }
      // Get Current Instruction
      const Instruction & CurrentInstruction() const {return instructions[currInstruction]; }
      // Get total number of instructions
      unsigned long NumInstructions() const { return instructions.size(); }
      // Get number of instructions left
      unsigned long NumInstructionsLeft() const { return instructions.size() - currInstruction; }
      // get whether or not the process is finished
      bool Finished() const { return currInstruction >= instructions.size(); }
      // Mark process as starting to process
      // Only changes state
      void StartProcessing();
      // Mark process as stopping processsing
      // Only changes state
      void StopProcessing();
      // Process for <pu> PUs
      // returns wether or not it finished
      bool ProcessUnit(unsigned long pu);
      // gets remaining time to process instructions
      unsigned long RemainingInstructionTime() const;
      // gets the total time needed to profcess all intructions
      unsigned long TotalInstructionTime() const;
  };

  // Needed in order to be able to do the extraction operator
  // don't need to worry about this
  std::ostream & operator<<(std::ostream & out, const Process & p);
}

#endif
