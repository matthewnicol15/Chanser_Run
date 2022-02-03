{
  auto FS = matthewn::kpkm::Make("ALL","ALL");
  // auto FS = matthewn::kpkm::Make("ALL","ALL");
  FS->AddTopology("Electron:Proton:Kaonp:Kaonm");
  // FS->AddTopology("Electron:Proton:Kaonp");
  // FS->AddTopology("Electron:Proton:Kaonm");
  // FS->AddTopology("Electron:Kaonp:Kaonm");
  // FS->AddTopology(OTHER_TOPOLOGY);

  ////Save TreeDatakpkm
  FS->UseOutputRootTree();
  //FS->UseOutputHipoNtuple();

  /////Make particle trees first in case want to add cut flags
  //ParticleDataManager pdm{"particle",1};
  //pdm.SetParticleOut(new CLAS12ParticleOutEvent0);
  //FS->RegisterPostTopoAction(pdm);

  // Forward tagger electron energy correction
  // Apply this to data but not simulation as the correction is far less significant
  ParticleCorrectionManager pcorrm{"FTelEnergyCorrection"};
  pcorrm.AddParticle("e-",new FTel_pol4_ECorrection());
  FS->RegisterPreTopoAction(pcorrm); //PRETOPO

  ////
  ParticleCutsManager pcm_dt{"DeltaTimeCuts2",1};
  pcm_dt.AddParticleCut("e-",new DeltaTimeCut(1));//Apply a Delta Time cut of 1ns
  pcm_dt.AddParticleCut("K+",new DeltaTimeCut(0.5));//Apply a Delta Time cut of 0.5ns
  pcm_dt.AddParticleCut("K-",new DeltaTimeCut(0.5));//Apply a Delta Time cut of 0.5ns
  pcm_dt.AddParticleCut("proton",new DeltaTimeCut(0.5));//Apply a Delta Time cut of 0.5ns
  FS->RegisterPostTopoAction(pcm_dt);

  // Selecting events where both kaons are in the FD
  ParticleCutsManager pcm_Kaon_FD{"Kaon_FD_Cut",1};
  pcm_Kaon_FD.AddParticleCut("K+",new Kaon_FD_Cut()); // Just apply to K+
  pcm_Kaon_FD.AddParticleCut("K-",new Kaon_FD_Cut()); // Just apply to K+
  FS->RegisterPostTopoAction(pcm_Kaon_FD);

  // Selecting events where the electron is in the FT
  ParticleCutsManager pcm_Electron_FT{"Electron_FT_Cut",1};
  pcm_Kaon_FD.AddParticleCut("e-",new Electron_FT_Cut()); // Just apply to e-
  FS->RegisterPostTopoAction(pcm_Electron_FT);

  ///StartTime
  StartTimeAction st("EBStartTime",new C12StartTimeFromVtFTB());
  // StartTimeAction st("StartTime",new C12StartTimeFromParticle("Electron"));
  FS->RegisterPreTopoAction(st);  //PRETOPO


  ParticleCorrectionManager pVz{"FTelVz"};
  pVz.AddParticle("e-", new FTel_VzCorrection(0.0));//Value set in db!
  FS->RegisterPreTopoAction(pVz);

  ////Write to file for later processing
  FS->WriteToFile("Configurations/ALLALL_Delta_Time_Cut_EB_starttime_Electron_Energy_And_Vertex_Correction_ElectronFT_KaonsFD_03022022.root");

  FS->Print();


  //Delete the final state rather than let ROOT try
  FS.reset();
}
