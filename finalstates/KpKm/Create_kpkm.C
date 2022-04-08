{
   auto useEBPidFor = "ALL"; //or "NONE"
   // auto useInclusiveFilterFor = "ALL";
   auto useInclusiveFilterFor = "proton:K+:K-";
   auto FS = matthewn::kpkm::Make(useEBPidFor,useInclusiveFilterFor);

  // auto FS = matthewn::kpkm::Make("ALL","ALL");
  FS->AddTopology("Electron:Proton:Kaonp:Kaonm");
  // FS->AddTopology("Electron:Proton:Kaonp");
  // FS->AddTopology("Electron:Proton:Kaonm");
  FS->AddTopology("Electron:Kaonp:Kaonm");
  // FS->AddTopology(OTHER_TOPOLOGY);

  ////Save TreeDatakpkm
  FS->UseOutputRootTree();
  //FS->UseOutputHipoNtuple();

  /////Make particle trees first in case want to add cut flags
  //ParticleDataManager pdm{"particle",1};
  //pdm.SetParticleOut(new CLAS12ParticleOutEvent0);
  //FS->RegisterPostTopoAction(pdm);

  ///StartTime
  // StartTimeAction st("EBStartTime",new C12StartTimeFromVtFTB());
  StartTimeAction st("StartTime",new C12StartTimeFromParticle("Electron"));
  FS->RegisterPreTopoAction(st);  //PRETOPO

  // Forward tagger electron energy correction
  ParticleCorrectionManager pcorrm{"FTelEnergyCorrection"};
  pcorrm.AddParticle("e-",new FTel_pol4_ECorrection());
  FS->RegisterPreTopoAction(pcorrm); //PRETOPO
  ParticleCorrectionManager pVz{"FTelVz"};//1=> for simulation too
  pVz.AddParticle("e-",new FTel_VzCorrection(-0.05));//5cm shift
  FS->RegisterPreTopoAction(pVz); //PRETOPO

  ////
  // ParticleCutsManager pcm_dt{"DeltaTimeVerCut",1};
  // pcm_dt.AddParticleCut("e-",new DeltaTimeVerCut(1));//Apply a Delta Time cut of 1ns
  // pcm_dt.AddParticleCut("K+",new DeltaTimeVerCut(0.1));//Apply a Delta Time cut of 0.5ns
  // pcm_dt.AddParticleCut("K-",new DeltaTimeVerCut(0.1));//Apply a Delta Time cut of 0.5ns
  // pcm_dt.AddParticleCut("proton",new DeltaTimeVerCut(0.1));//Apply a Delta Time cut of 0.5ns
  // FS->RegisterPostTopoAction(pcm_dt);

  // Selecting events where both kaons are in the FD
  ParticleCutsManager pcm_FD{"FD_Cut",1};
  pcm_FD.AddParticleCut("K+",new FD_Cut()); // Just apply to K+
  pcm_FD.AddParticleCut("K-",new FD_Cut()); // Just apply to K+
  FS->RegisterPostTopoAction(pcm_FD);

  // Selecting events where these particles are in the FT
  ParticleCutsManager pcm_FT{"FT_Cutter",1};
  pcm_FT.AddParticleCut("e-",new FT_Cutter()); // Just apply to e-
  FS->RegisterPostTopoAction(pcm_FT);


  ////Write to file for later processing
  FS->WriteToFile("Configurations/ALL_OneElec_Elec_Start_Time_ElecFT_PKpKm.root");

  FS->Print();


  //Delete the final state rather than let ROOT try
  FS.reset();
}
