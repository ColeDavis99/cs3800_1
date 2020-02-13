#include "processor.h"
using namespace Computer;

// Constructor with filename of input file
Computer::Processor::Processor(const std::string & filename)
{

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
  fin.close();
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

  //std::thread(&<class>::<member function>, std::ref(<class instance>), ...args);
  std::vector<std::thread> threadVec;
  unsigned long pu = 0;
  queue<Process> coutQueue;

  /*===================================
    Prepare for next run cycle
  ==================================*/
  //This is the main driver for the program.
  while(processQueue.size() > 0)
  {
    threadVec.clear();

    //Generate random PU value
    processHolder.clear();
    pu = rand() % 100 + 1;
    cout<<"----- "<<pu<<" Pus ------"<<endl;

    //This is very storage inefficient, but it's too late to change my decision to use a queue.
    coutQueue = processQueue;
    for(int i=0; i<processQueue.size(); i++)
    {
      cout<<coutQueue.front()<<endl;
      coutQueue.pop();
    }


    /*=========================================================================================================================================
        Execute next run cycle (I've got three hardcodey cases depending on the number of processes left in the queue. 1,2, or 3 processes.)
    ========================================================================================================================================*/
    //Now execute 1,2, or 3 processes from the "queue" processHolder (it's actually a vector)
    if(processQueue.size() == 1)
    {
      cout<<endl; //Match output format

      //Get the processes we need to run
      processHolder.push_back(processQueue.front());  //1 of 1 processes added to be processed
      processQueue.pop();

      //Run the threads
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[0]), pu));

      //Join the threads back
      threadVec[0].join();

      //Check and see if the process got finished
      if(! processHolder[0].Finished())
        processQueue.push(processHolder[0]);

    }
    else if(processQueue.size() == 2)
    {
      cout<<endl; //Match output format

      //Get the processes we need to run
      processHolder.push_back(processQueue.front());  //1 of 2 processes added to be processed
      processQueue.pop();
      processHolder.push_back(processQueue.front());  //2 of 2 processes added to be processed
      processQueue.pop();


      //Run the threads
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[0]), pu));
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[1]), pu));

      //Join the threads back
      threadVec[0].join();
      threadVec[1].join();

      //Check and see if the process got finished
      if(! processHolder[0].Finished())
        processQueue.push(processHolder[0]);

      if(! processHolder[1].Finished())
        processQueue.push(processHolder[1]);
        

    }
    else if(processQueue.size() >= 3)
    {
      cout<<endl; //Match output format

      //Get the processes we need to run
      processHolder.push_back(processQueue.front());  //1 of 3 processes added to be processed
      processQueue.pop();
      processHolder.push_back(processQueue.front());  //2 of 3 processes added to be processed
      processQueue.pop();
      processHolder.push_back(processQueue.front());  //3 of 3 processes added to be processed
      processQueue.pop();

      //Run the threads
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[0]), pu));
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[1]), pu));
      threadVec.push_back(std::thread(&Process::ProcessUnit,std::ref(processHolder[2]), pu));


      //Join the threads back
      threadVec[0].join();
      threadVec[1].join();
      threadVec[2].join();


      //Check and see if the process got finished
      if(! processHolder[0].Finished())
        processQueue.push(processHolder[0]);



      if(! processHolder[1].Finished())
        processQueue.push(processHolder[1]);



      if(! processHolder[2].Finished())
        processQueue.push(processHolder[2]);



    }
    else
      cout<<"processHolder is too big I bet. It should only hold three"<<endl;
  }
}
