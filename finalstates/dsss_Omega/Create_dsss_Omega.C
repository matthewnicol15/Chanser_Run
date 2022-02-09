{
  auto FS = matthewn::dsss_Omega::Make("ALL","ALL");
  FS->AddTopology("Electron:Kaonp1:Kaonp2:Kaonp3");
  // FS->AddTopology(OTHER_TOPOLOGY);

  ////Save TreeDatadsss_Omega
  FS->UseOutputRootTree();
  //FS->UseOutputHipoNtuple();

  /////Make particle trees first in case want to add cut flags
  //ParticleDataManager pdm{"particle",1};
  //pdm.SetParticleOut(new CLAS12ParticleOutEvent0);
  //FS->RegisterPostTopoAction(pdm);

  ////
  //ParticleCutsManager pcm{"EBCuts",1};
  //pcm.AddParticleCut("e-",new EventBuilderCut());
  //pcm.AddParticleCut("proton",new EventBuilderCut());
  //pcm.AddParticleCut("pi+",new EventBuilderCut());
  //pcm.AddParticleCut("pi-", new DeltaTimeCut(2));//Apply a Delta Time cut of 2ns
  // FS->RegisterPostTopoAction(pcm);

  // Perform cuts on delta time of all detected particles
  // ParticleCutsManager pcm_dt{"DeltaTimeVerCut",1};
  // pcm_dt.AddParticleCut("e-",new DeltaTimeVerCut(1));//Apply a Delta Time cut of 1ns
  // pcm_dt.AddParticleCut("K+",new DeltaTimeVerCut(0.1));//Apply a Delta Time cut of 0.5ns
  // FS->RegisterPostTopoAction(pcm_dt);

  // Selecting events where these particles are in the FD
  ParticleCutsManager pcm_FD{"FD_Cut",1};
  pcm_FD.AddParticleCut("e-",new FD_Cut()); // Apply to e-
  FS->RegisterPostTopoAction(pcm_FD);

  ///StartTime
  // StartTimeAction st("EBStartTime",new C12StartTimeFromVt()); // Using EB start time
  StartTimeAction st("StartTime",new C12StartTimeFromParticle("Electron"));
  FS->RegisterPreTopoAction(st);  //PRETOPO

  ////Write to file for later processing
  FS->WriteToFile("Configurations/ALLALL_electron_Start_Time_ElectronFD_3Kp.root");

  FS->Print();


  //Delete the final state rather than let ROOT try
  FS.reset();
}
