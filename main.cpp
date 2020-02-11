/*
 * Written by: Josh Cash
 * Reviewed by: Richard Kell
 * Purpose: Provide a simple challenge in regards to processes and multi-threading
 */
#include "processor.h"
#include <iostream>
#include <exception>
#include <stdexcept>
// DO NOT MODIFY THIS FILE
int main(int argc, char** argv)
{
  // Check for file name command line argument 
  if(argc != 2)
  {
    throw std::invalid_argument("No input file given");
  }

  // construct the processor
  Computer::Processor p(argv[1]);
  // seed the generator
  srand(p.Seed());
  // start the processor
  p.Start();
  
  return 0;
}
