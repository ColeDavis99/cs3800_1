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

  cout << "count = " << raw_process_data.size() << endl;
  cout << "seed = " << raw_process_data[0] << endl;
  cout << "numProcesses = " << raw_process_data[1] << endl;

  //One time value reads
  seed = raw_process_data[0];
  int numProcesses = raw_process_data[1];

  //Reverse the vector so I can shrink it faster as I loop
  reverse(raw_process_data.begin(), raw_process_data.end());
  raw_process_data.pop_back(); // Lil chop 1 of 2
  raw_process_data.pop_back(); // Lil chop 2 of 2

  /*================================
    READ IN DATA TO CORRECT CLASSES, shrinking the vector as we go
  ==================================*/
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
  cout<<"That should be all of the data to read in."<<endl;




  // TESTING BELOW
  
  // TESTING ABOVE




}



// Start the Processor
void Computer::Processor::Start()
{
  cout<<"Processor started up!"<<endl;
}
