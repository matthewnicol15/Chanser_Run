{

  // Skeleton code maker

  FSSkeleton s;

  // Give your class a name

  s.SetFinalState("kpkm");

  // Define possible detected particles in the final state

  s.SetFinalStateParts("Electron:e-,Proton:proton,Kaonp:k+,Kaonm:k-");

  // Define possible topologies for this final state
  // ',' separates different topologies
  // ':' separates different particles within a topology
  // Here are 3 topologies, exclusive, missing pion and missing proton

  s.SetFinalStateTopo("Electron:Proton:Kaonp:Kaonm");

  // Define short live parent particles which decay to detected particles
  // Should not include broad resonances, but things like omega, Lambda and K0
  // ':' separate parent name from type
  // ';' separates child particles
  // ',' separates different parents

  // s.SetFinalStateParents("");

  // Produce the code

  s.MakeCode();

}
