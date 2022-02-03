{
  // Add the databases
  clas12databases::SetCCDBLocalConnection("/work/clas12/mesonex/chanser/ccdb.sqlite");
  clas12databases::SetRCDBRootConnection("/work/clas12/mesonex/chanser/rcdb.root");

  clas12root::HipoChain chain;
  // Input data file path
  chain.Add("/home/matthewn/links/RGA_Fall_2018_Outbending_dst/rec_clas_005432.evio.01*.hipo");
  chain.SetReaderTags({0});
  chain.GetC12Reader()->useFTBased(); //if you want to use FT PiD


  // First points to final state and configurations, next output directory
  chanser::HipoProcessor processor(&chain,"finalstate.txt","/volatile/clas12/matthewn/Output_RGA_FALL2018_5432_test_030222_06");

  //Load database for run conditions and parameters
  processor.AddOption("HIPOPROCESSOR_ANADB","$CHANSER/rga_actions/anadb/RGA_ACTIONS_PASS1.db:$CHANSER/anadbs/RunPeriodPass1.db");
  // Set the run period
  processor.AddOption("HIPOPROCESSOR_RUNPERIOD","fall_2018");
  // Load the RGA actions


  // Process all files
  gProof->Process(&processor,chain.GetNRecords());
}
