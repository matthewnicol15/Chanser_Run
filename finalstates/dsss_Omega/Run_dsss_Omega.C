{
  // Pointing to the databases
  clas12databases::SetCCDBLocalConnection("/work/clas12/mesonex/chanser/ccdb.sqlite");
  clas12databases::SetRCDBRootConnection("/work/clas12/mesonex/chanser/rcdb.root");

  ////Set hipo file to be analysed
  HipoData hdata;
  hdata.AddFile("/home/matthewn/links/RGA_Fall_2018_Outbending_dst/rec_clas_005432.evio.01*.hipo");
  hdata.LoadAnaDB("$CHANSER/anadbs/RunPeriodPass1.db");
  hdata.LoadAnaDB("$CHANSER/rga_actions/anadb/RGA_ACTIONS_PASS1.db");
  hdata.SetRunPeriod("fall_2018");


  ////create FinalStateManager
  ////we can load as many saved final states as we like
  FinalStateManager fsm;
 fsm.SetBaseOutDir("/volatile/clas12/matthewn/dsss_Output_RGA_FALL2018_Outbending_test_040222_01/");
  ////Connect the data to the manager
  fsm.LoadData(&hdata);

  ////load one or more FinalStates
  fsm.LoadFinalState("dsss_Omega",
		     "Configurations/ALLALL_Delta_Time_EB_Start_Time_ElectronFD_3Kp.root");
  // fsm.LoadFinalState("dsss_Omega",
  //		     "/dir/fs/file_name_for_this_configuration_2.root");

  //Max number of particles of any 1 species
  //Whole event disgarded if this not met.
  // fsm.GetEventParticles().SetMaxParticles(6);

  ////Run through all events
  fsm.ProcessAll();
  ////Run through N events
  //fsm.ProcessAll(N);


}
