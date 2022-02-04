{
  clas12databases::SetCCDBLocalConnection("/work/clas12/mesonex/chanser/ccdb.sqlite");
  clas12databases::SetRCDBRootConnection("/work/clas12/mesonex/chanser/rcdb.root");


  ////Set hipo file to be analysed
  HipoData hdata;
  // HipoTruth hdata;
  hdata.AddFile("/lustre19/expphy/volatile/clas12/osg2/matthewn/job_4371/output/simu_1/00060.hipo");
  hdata.Reader()->useFTBased(); // Use FTBased PID


  hdata.LoadAnaDB("$CHANSER/anadbs/RunPeriodPass1.db");
  hdata.LoadAnaDB("$CHANSER/rga_actions/anadb/RGA_ACTIONS_PASS1.db");
  hdata.SetRunPeriod("fall_2018");


  ////create FinalStateManager
  ////we can load as many saved final states as we like
  FinalStateManager fsm;
 fsm.SetBaseOutDir("/volatile/clas12/matthewn/Output_RGA_FALL2018_5432_test_030222_10/");
  ////Connect the data to the manager
  fsm.LoadData(&hdata);

  ////load one or more FinalStates
  fsm.LoadFinalState("kpkm",
		     "Configurations/ALLALL_Delta_Time_Cut_EB_starttime_Electron_Energy_And_Vertex_Correction_ElectronFT_KaonsFD_03022022.root");
  // fsm.LoadFinalState("kpkm",
  //		     "/dir/fs/file_name_for_this_configuration_2.root");

  //Max number of particles of any 1 species
  //Whole event disgarded if this not met.
  // fsm.GetEventParticles().SetMaxParticles(6);

  ////Run through all events
  fsm.ProcessAll();
  ////Run through N events
  //fsm.ProcessAll(N);


}
