/*
 * Written by: Josh Cash
 * Reviewed by: Richard Kell
 * Purpose: Provide a simple challenge in regards to processes and multi-threading
 */
#ifndef COMP_PROCESSOR_H
#define COMP_PROCESSOR_H

#include <queue>
#include <array>
#include "process.h"
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
namespace Computer
{
  // Number of threads to process
  const unsigned long NUM_THREADS = 3;
  // Processor Class
  class Processor
  {
  private:
      // seed to seed the random num generator
      unsigned long seed;
      //Process queue, holds all processes until their instruction count reaches zero.
      queue<Process> processQueue;
      //Holds the (up to) three processes to be ran on the threads
      vector<Process> processHolder;

    public:
      // Constructor with filename of input file
      Processor(const std::string & filename);
      // Copy Constructor
      Processor(const Processor & copy);
      // Copy Assignment Operator
      Processor & operator=(const Processor & copy);
      // Get the Seed
      unsigned long Seed() const { return seed; }
      // Start the Processor
      void Start();
  };

}
#endif
