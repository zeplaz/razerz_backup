

std::unordered_map<std::string,engine_config_pak> engine_pak_map;
std::string terminal_cmd;

simple_engine_cmdz(std::string  in_cmd)
{
if(in_cmd=="init")
{

}
if(in_cmd=="ignite")
{

}

if(in_cmd=="configure")
{
  std::sting config_patch;

  std::cout <<"enter configure patch:";
  std::cint >> config_patch;

}
}

struct engine_config_pak
{

};
enum class Engine_State : unsigned char
{
  INITAL,
  CONFIGURED,
  IGNITION,
  RUNNING,
  SHUTDOWN,
  STALL
};



struct engine
{
  Engine_State engine_state;
  long double run_durration;
  unsigned long long int cycle_count;

  void set_engine_state(Engine_State in_state)
  {
    engine_state = in_state;
  }
  engine()
  {
     engine_state   =Engine_State::INITAL;
     run_durration = 0.0;;
     cycle_count   =0;
  }

  void configure(engine_config_pak& in_pak)
  {
    engine_state= Engine_State::CONFIGURED;
  }

  void ignition()
  {
    engine_state = Engine_State::IGNITION;
  }

  cylce()
  {

    if(engine_state ==Engine_State::CONFIGURED)
    {
      std::cerr << "ERROR_engine is cold. plz run igintion engine is configured but not ignited!" << '\n';
      return;
    }
    else if(engine_state ==Engine_State::STALL)
    {

      cerr<< "###ENGINE IS STALLED"<<'\n';

      std::cout << "enter cmd...{none yet}:" <<'/n';
      std::cin  >> terminal_cmd;
      return;
    }
  //  else if(engine_state ==Engine_State::RUNNING ||engine_state ==Engine_State::IGNITION)

    engine_state=Engine_State::RUNNING;


  }
};
