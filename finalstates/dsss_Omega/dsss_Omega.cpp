
#include "dsss_Omega.h"

namespace mnicol{

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void dsss_Omega::Define(){
    //Set final state detected particles
    //Note if particle is added to final with a valid genID it will be used
    //to determine the correct permutation of the simulated event

    AddParticle("Electron",&_electron,kTRUE,-1);
    AddParticle("Proton",&_proton,kTRUE,-1);
    AddParticle("Pim1",&_pim1,kTRUE,-1);
    AddParticle("Pim2",&_pim2,kTRUE,-1);
    AddParticle("Kaonp1",&_kaonp1,kTRUE,-1);
    AddParticle("Kaonp2",&_kaonp2,kTRUE,-1);
    AddParticle("Kaonp3",&_kaonp3,kTRUE,-1);
    //AddParticle("Name",particle,true/false you want to write in final vector, genID for linking to generated truth value)
    // AddParticle("PARTICLE",&_PARTICLE,kTRUE,-1);

    //Set final state parents
    AddParticle("Lambda",&_lambda,kTRUE,-1);
    ConfigParent(&_lambda,&_proton);
    ConfigParent(&_lambda,&_pim1);
    AddParticle("Omega",&_omega,kTRUE,-1);
    ConfigParent(&_omega,&_proton);
    ConfigParent(&_omega,&_pim1);
    ConfigParent(&_omega,&_pim2);


    //_doToTopo["TOPOLOGY"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////
    ////auto miss= _beam + _target - _electron.P4() - _proton.P4()
    ////  -_pip1.P4()-_pim1.P4();
    ////TD->MissMass=miss.M();
    ////TD->MissMass2=miss.M2();

      ///////------------------------------------///////
    // };

    //Set Possible Topologies
    _doToTopo["Electron:Proton:Kaonp:Kaonp:Kaonp:Pim:Pim"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////

      // Setting the lorentzvector for the parent particles
      Lambda.FixP4(_proton.P4() + _pim1.P4());
      Omega.FixP4(_proton.P4() + _pim1.P4() + _pim2.P4());

      TD->Lambda_Mass = Lambda.M();
      TD->Omega_Mass = Omega.M();

      ///////------------------------------------///////
    };

  }


  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void dsss_Omega::Kinematics(){
    //Define reaction specific kinematic calculations here
    //Assign to tree data TD.var=

    //Use Kinematics to calculate electron variables
    //Note this assumes you called your electron "electron" or "Electron"
    _kinCalc.SetElecsTarget(_beam,_electron.P4(),_target);
    TD->W=_kinCalc.W(); //photon bem energy
    TD->Q2=_kinCalc.Q2();
    TD->Pol=_kinCalc.GammaPol();
    TD->Egamma=_kinCalc.GammaE();

  }

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void dsss_Omega::UserProcess(){
    //Optional additional steps
    //This is called after the Topo function
    //and before the kinematics function
    _counter++;


    //Must call the following to fill Final trees etc.
    //Fill Final data output at the end
    FinalState::UserProcess();

  }


}
