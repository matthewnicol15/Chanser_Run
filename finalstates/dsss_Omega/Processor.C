{

  clas12databases::SetCCDBLocalConnection("/work/clas12/mesonex/chanser/ccdb.sqlite");
  clas12databases::SetRCDBRootConnection("/work/clas12/mesonex/chanser/rcdb.root");

  clas12root::HipoChain chain;

  chain.Add("/home/matthewn/links/RGA_Fall_2018_Outbending_dst/*.hipo");
  //  chain.Add("/cache/clas12/rg-a/production/recon/fall2018/torus+1/pass1/v0/dst/recon/005423/rec_clas_005423.evio.*.hipo");
  // for(int i=0;i<100;i++)
    // chain.Add(Form("/work/clas12/dglazier/simulation/p3pi/output/simu_%d/dst.hipo",i));

  chain.SetReaderTags({0});
  //  chain.GetC12Reader()->useFTBased();

  //  chanser::HipoProcessor processor(&chain,"finalstate.txt","/work/clas12/dglazier/chanser_out");
  //  chanser::HipoProcessor processor(&chain,"finalstate.txt","/scratch/dglazier/chanser_out");
  chanser::HipoProcessor processor(&chain,"finalstate.txt","/volatile/clas12/matthewn/Output_RGA_FALL2018_Processor_040222_04");

  // processor.AddOption("HIPOPROCESSOR_MAXPARTICLES","6");

  //Filter if any loaded finalstate returns true for WasGoodEvent()
  //WasGoodEvent is true if valid topology with no rejectEvent
  //processor.AddOption("HIPOPROCESSOR_FILTERHIPO","filtered.hipo");
  //Load database for run conditions and parameters
  processor.AddOption("HIPOPROCESSOR_ANADB","$CHANSER/rga_actions/anadb/RGA_ACTIONS_PASS1.db:$CHANSER/anadbs/RunPeriodPass1.db");
  //Set run period for particular data set you are processing
  //All data must be from the same run period
  processor.AddOption("HIPOPROCESSOR_RUNPERIOD","fall_2018");

  //chain.GetNRecords();
  gProof->Process(&processor,chain.GetNRecords());
  //gProof->Process(&processor,1000);

}
