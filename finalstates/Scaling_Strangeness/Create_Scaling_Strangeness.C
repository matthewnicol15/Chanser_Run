{
  auto FS = matthewn::Scaling_Strangeness::Make("ALL","NONE");
  FS->AddTopology("Electron:Kaonp1");
  FS->AddTopology("Electron:Kaonp1:Kaonp2");
  FS->AddTopology("Electron:Kaonp1:Kaonp2:Kaonp3");

  ////Save TreeDataScaling_Strangeness
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

  // Selecting events where these particles are in the FD
  ParticleCutsManager pcm_FD{"FD_Cutter",1};
  pcm_FD.AddParticleCut("e-",new FD_Cutter()); // Apply to e-
  pcm_FD.AddParticleCut("K+",new FD_Cutter()); // Apply to e-
  FS->RegisterPostTopoAction(pcm_FD);

  ///StartTime
  // StartTimeAction st("EBStartTime",new C12StartTimeFromVt()); // Using EB start time
  StartTimeAction st("StartTime",new C12StartTimeFromParticle("Electron"));
  FS->RegisterPreTopoAction(st);  //PRETOPO

  ////Write to file for later processing
  FS->WriteToFile("Configurations/ALLNONE_electron_Start_Time_ElectronKaonpFD_Strangeness.root");

  FS->Print();


  //Delete the final state rather than let ROOT try
  FS.reset();
}
