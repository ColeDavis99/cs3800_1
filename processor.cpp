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
  int num_instr = 0;
  int TEST_total = 0;
  for(int i=numProcesses; i>0; i--)
  {
    cout<<"Total: "<<TEST_total<<endl;
    TEST_total = 0;
    num_instr = raw_process_data[raw_process_data.size() -1];
    raw_process_data.pop_back();
    cout<<endl<<"Loop: "<<num_instr<<endl;
    for(int q=0; q<num_instr; q++)
    {
      cout<<"Val: "<<raw_process_data[raw_process_data.size() -1]<<endl;
      TEST_total += raw_process_data[raw_process_data.size() -1];
      raw_process_data.pop_back();
    }
  }

  cout<<"That should be all"<<endl;

}



// Start the Processor
void Computer::Processor::Start()
{
  cout<<"Processor started up!"<<endl;
}
