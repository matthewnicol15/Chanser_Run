{
  // Add the databases
  clas12databases::SetCCDBLocalConnection("/work/clas12/mesonex/chanser/ccdb.sqlite");
  clas12databases::SetRCDBRootConnection("/work/clas12/mesonex/chanser/rcdb.root");

  clas12root::HipoChain chain;

  // //-----------------File Chaining----------------------
  // // Pointing to txt file with list of file paths of data
  // string ifname="/home/matthewn/File_Lists/RGA_Fall_2018_Outbending_file_path_list.txt";
  // // Integer to count the number of files
  // // Currently this just shows how many runs for dsts due to the way I produce
  // // file path list
  // int Nfiles = 0;
  // vector < string > ifname_hipo;
  // ifstream ifile(ifname.c_str());
  //
  // while(1){
  //   if(ifile.eof()) break;
  //   string name;
  //   ifile>>name;
  //   ifname_hipo.push_back(name);
  //   Nfiles++;
  // }
  //
  // ifile.close();
  // cout << "There are " << Nfiles << " files to analyse" << endl;
  //
  // for(int ii=0;ii<Nfiles-1;ii++){
  //   cout << "Adding " << ifname_hipo[ii].c_str() << endl;
  //   chain.Add((ifname_hipo[ii]).c_str());
  //
  // }

  // Input data file path
  // chain.Add("/volatile/clas12/matthewn/osg_output/job_4640_Total.hipo");
  chain.Add("/home/matthewn/links/RGA_FALL_2018_Outbending_09022022/54/*.hipo");
  chain.Add("/home/matthewn/links/RGA_FALL_2018_Outbending_09022022/55/*.hipo");
  chain.Add("/home/matthewn/links/RGA_FALL_2018_Outbending_09022022/56/*.hipo");
  chain.SetReaderTags({0});
  chain.GetC12Reader()->useFTBased(); //if you want to use FT PiD


  // First points to final state and configurations, next output directory
  chanser::HipoProcessor processor(&chain,"finalstate.txt","/volatile/clas12/matthewn/Chanser_Output/RGA_FALL2018_Outbending_08042022_01");

  //Load database for run conditions and parameters
  processor.AddOption("HIPOPROCESSOR_ANADB","$CHANSER/rga_actions/anadb/RGA_ACTIONS_PASS1.db:$CHANSER/anadbs/RunPeriodPass1.db");
  // Set the run period
  processor.AddOption("HIPOPROCESSOR_RUNPERIOD","fall_2018");
  // Load the RGA actions


  // Process all files
  gProof->Process(&processor,chain.GetNRecords());
}
