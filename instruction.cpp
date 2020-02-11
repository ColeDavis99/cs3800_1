/*
 * Written by: Josh Cash
 * Reviewed by: Richard Kell
 * Purpose: Provide a simple challenge in regards to processes and multi-threading
 */
#include "instruction.h"
#include <iostream>
#include <thread>
#include <chrono>
// DO NOT MODIFY THIS FILE
unsigned long Computer::Instruction::instructionIds = 0;

Computer::Instruction::Instruction()
{
  timeToProcess = 1;
  currentProcessTime = 0;
  id = Instruction::instructionIds++;
}

Computer::Instruction::Instruction(const unsigned long pTime)
{
  timeToProcess = pTime;
  currentProcessTime = 0;
  id = Instruction::instructionIds++;
}

Computer::Instruction::Instruction(const Computer::Instruction & copy)
{
  timeToProcess = copy.timeToProcess;
  currentProcessTime = copy.currentProcessTime;
  id = copy.id;
}

Computer::Instruction & Computer::Instruction::operator=(const Computer::Instruction & copy)
{
  timeToProcess = copy.timeToProcess;
  currentProcessTime = copy.currentProcessTime;
  id = copy.id;
  return *this;
}

unsigned long Computer::Instruction::ProcessTime() const
{
  return timeToProcess;
}

unsigned long Computer::Instruction::TimeLeft() const
{
  auto remainder = static_cast<long>(timeToProcess) - currentProcessTime;
  return remainder > 0 ? remainder : 0;
}

unsigned long Computer::Instruction::Process(const unsigned long time)
{
  currentProcessTime += time;
  unsigned long remainder = 0;

  if (currentProcessTime >= timeToProcess)
  {
    remainder = currentProcessTime - timeToProcess;
    currentProcessTime = timeToProcess;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds((time - remainder) * 20));
  return remainder;
}













































































/*
 * Secret message:
                   _nnnn_
                  dGGGGMMb     ,"""""""""""""".
                 @p~qp~~qMb    | Linux Rules! |
                 M|@||@) M|   _;..............'
                 @,----.JM| -'
                JS^\__/  qKL
              dZP        qKRb
              dZP          qKKb
            fZP            SMMb
            HZM            MMMM
            FqM            MMMM
          __| ".        |\dS"qML
          |    `.       | `' \Zq
         _)       \.___.,|     .'
         \____    )MMMMMM|   .'
              `-'       `--'
 */
