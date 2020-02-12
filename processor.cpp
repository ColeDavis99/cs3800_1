#include "processor.h"
using namespace Computer;

// Constructor with filename of input file
Computer::Processor::Processor(const std::string & filename)
{
  cout<<"Processor constructor called"<<endl;

  //Read in ALL of the process info into a vector
  ifstream fin(filename);
  int num;
  vector<int> raw_process_data;

  while (fin >> num)
    raw_process_data.push_back(num);

  // cout << "count = " << raw_process_data.size() << endl;
  // cout << "seed = " << raw_process_data[0] << endl;
  // cout << "numProcesses = " << raw_process_data[1] << endl;

  //One time value reads
  seed = raw_process_data[0];
  int numProcesses = raw_process_data[1];

  //Reverse the vector so I can shrink it faster as I loop
  reverse(raw_process_data.begin(), raw_process_data.end());
  raw_process_data.pop_back(); // Lil chop 1 of 2
  raw_process_data.pop_back(); // Lil chop 2 of 2


  /*==============================================================
    READ IN DATA TO CORRECT CLASSES, shrinking the vector as we go
  ================================================================*/
  //Number of instructions in a process
  int num_instr = 0;
  //Will be passed in to each process' constructor
  vector<Instruction> vec_instr;
  //Holds most granular value, the value of an instruction in a process
  int instr_val = 0;

  for(int i=numProcesses; i>0; i--)
  {
    num_instr = raw_process_data[raw_process_data.size() -1];
    raw_process_data.pop_back();

    for(int q=0; q<num_instr; q++)
    {
      instr_val = raw_process_data[raw_process_data.size() -1];
      //Add instructions to vec_instr
      vec_instr.push_back(Instruction(instr_val));
      raw_process_data.pop_back();
    }

    //Create a process, then push that process into our processor's queue
    processQueue.emplace(Process(vec_instr));
    vec_instr.clear();

  }
  //cout<<"That should be all of the data to read in."<<endl;

  // TESTING BELOW
  // cout<<endl<<endl<<"LETS LOOP THROUGH QUEUE"<<endl;
  // while (!processQueue.empty())
  // {
  //  cout<<endl<<"Here's a process"<<endl;
  //  cout<<"Num instructions: "<<processQueue.front().NumInstructions()<<endl;
  //  cout<<"ProcessID: "<<processQueue.front().id<<endl;
  //
  //  for(int e=0; e<processQueue.front().instructions.size(); e++)
  //  {
  //    cout<<"instruction "<<e<<": "<<processQueue.front().instructions[e].timeToProcess<<endl;
  //  }
  //
  //  processQueue.pop();
  // }
  // TESTING ABOVE
}


// Copy Constructor
Computer::Processor::Processor(const Processor & copy)
{
  cout<<"Processor copy const"<<endl;
  seed = copy.seed;

  //Loop through queue to shallow copy
  queue<Process> temp = copy.processQueue;
  for(unsigned int i=0; i<copy.processQueue.size(); i++)
  {
    processQueue.push(temp.front());
    // cout<<"Pushing another process with instructions: "<<endl;
    // for(int q=0; q<temp.front().instructions.size(); q++)
    // {
    //   cout<<temp.front().instructions[q].timeToProcess<<endl;
    // }
    temp.pop();
  }
}



// Copy Assignment Operator (NOT TESTED)
Processor& Processor::operator=(const Processor & copy)
{
  seed = copy.Seed();

  //Delete the queue to be replaced
  while (!processQueue.empty())
  {
    processQueue.pop();
  }

  //Now re-fill the queue with the new values
  queue<Process> temp = copy.processQueue;
  for(unsigned int i=0; i<temp.size(); i++)
  {
    processQueue.push(temp.front());
    temp.pop();
  }

  //Yay, we're doing shallow copy
  // cout<<"lhs: "<<seed<<"  "<<&seed<<endl;
  // cout<<"rhs: "<<copy.seed<<"  "<<&copy.seed<<endl<<endl;
  // cout<<"lhs: "<<seed<<"  "<<&seed<<endl;
  // cout<<"rhs: "<<copy.seed<<"  "<<&copy.seed<<endl;
  return *this;
}



// Start the Processor
void Computer::Processor::Start()
{
  cout<<"Still need to implement processor::Start()."<<endl;
  
  
}
