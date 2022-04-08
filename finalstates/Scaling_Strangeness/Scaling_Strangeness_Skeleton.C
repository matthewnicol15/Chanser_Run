{

  // Skeleton code maker

  FSSkeleton s;

  // Give your class a name

  s.SetFinalState("Scaling_Strangeness");

  // Define possible detected particles in the final state
  s.SetFinalStateParts("Electron:e-,Kaonp1:K+,Kaonp2:K+,Kaonp3:K+");


  // Define possible topologies for this final state
  // ',' separates different topologies
  // ':' separates different particles within a topology

  s.SetFinalStateTopo("Electron:Kaonp1,Electron:Kaonp1:Kaonp2,Electron:Kaonp1:Kaonp2:Kaonp3");

  // Define short live parent particles which decay to detected particles
  // Should not include broad resonances, but things like omega, Lambda and K0
  // ':' separate parent name from type
  // ';' separates child particles
  // ',' separates different parents

  // s.SetFinalStateParents("");

  // Produce the code

  s.MakeCode();

}
