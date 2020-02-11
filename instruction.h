/*
 * Written by: Josh Cash
 * Reviewed by: Richard Kell
 * Purpose: Provide a simple challenge in regards to processes and multi-threading
 */
#ifndef COMP_INSTRUCTION_H
#define COMP_INSTRUCTION_H

namespace Computer
{
  // DO NOT MODIFY THIS FILE
  /* 
   * Instruction class
   * Purpose: represent an instruction and its process time
   */
  class Instruction
  {
    private:
      // total time to process this instruction
      unsigned long timeToProcess;
      // the current amount of time processed so far
      unsigned long currentProcessTime;
      // instruction id
      unsigned long id;
      // static var to keep track of ids
      static unsigned long instructionIds;
    public:
      // default constructor
      Instruction();
      // Param Constructor
      Instruction(const unsigned long processTime);
      // Copy Constructor
      Instruction(const Instruction & copy);
      // Copy assignment
      Instruction & operator=(const Instruction & copy);
      // Total Process Time
      unsigned long ProcessTime() const;
      // Time left to process
      unsigned long TimeLeft() const;
      // Process this Instruction for <time> PUs
      unsigned long Process(const unsigned long time = 0);
      // Id of this Instruction
      unsigned long Id() { return id; }
  };
}

#endif
