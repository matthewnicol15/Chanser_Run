{


  // Skeleton code maker
  FSSkeleton s;


  // Give your class a name
  s.SetFinalState("dsss_Omega");


  // Define possible detected particles in the final state
  s.SetFinalStateParts("Electron:e-,Proton:proton,Pim1:pi-,Pim2:pi-,Kaonp1:k+,Kaonp2:k+,Kaonp3:k+");

  // Define possible topologies for this final state
  // ',' separates different topologies
  // ':' separates different particles within a topology

  s.SetFinalStateTopo("Electron:Proton:Kaonp:Kaonp:Kaonp:Pim:Pim");

  // Define short live parent particles which decay to detected particles
  // Should not include broad resonances, but things like omega, Lambda and K0
  // ':' separate parent name from type
  // ';' separates child particles
  // ',' separates different parents

  s.SetFinalStateParents("Lambda:Lambda0;Proton;Pim1,Omega:Omega-;Proton;Pim1;Pim2");

  // Produce the code

  s.MakeCode();

}
