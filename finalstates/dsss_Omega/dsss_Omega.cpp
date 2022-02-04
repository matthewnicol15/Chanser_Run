
#include "dsss_Omega.h"

namespace matthewn{

  ///////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$//////////////////////
  void dsss_Omega::Define(){
    //Set final state detected particles
    //Note if particle is added to final with a valid genID it will be used
    //to determine the correct permutation of the simulated event

    AddParticle("Electron",&_electron,kTRUE,-1);
    AddParticle("Kaonp1",&_Kaonp1,kTRUE,-1);
    AddParticle("Kaonp2",&_Kaonp2,kTRUE,-1);
    AddParticle("Kaonp3",&_Kaonp3,kTRUE,-1);
    //AddParticle("Name",particle,true/false you want to write in final vector, genID for linking to generated truth value)
    // AddParticle("PARTICLE",&_PARTICLE,kTRUE,-1);

    //Set final state parents
    // AddParticle("Lambda",&_lambda,kTRUE,-1);
    // ConfigParent(&_lambda,&_proton);
    // ConfigParent(&_lambda,&_pim1);
    // AddParticle("Omega",&_omega,kTRUE,-1);
    // ConfigParent(&_omega,&_proton);
    // ConfigParent(&_omega,&_pim1);
    // ConfigParent(&_omega,&_pim2);


    //Set Possible Topologies
    _doToTopo["Electron:Kaonp1:Kaonp2:Kaonp3"]=[&](){
      //TOPOLOGY Define your topology dedendent code in here
      ///////+++++++++++++++++++++++++++++++++++///////

      // Reconstruct particles
      HSLorentzVector miss3K= _beam + _target - _electron.P4() - _Kaonp1.P4()
      - _Kaonp2.P4() - _Kaonp3.P4();

      TD->Miss3K=miss3K.M();

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


    // Particle kinematics
    // Delta time
    TD->electron_delta_time= _electron.DeltaTimeVer();
    TD->Kaonp_1_delta_time= _Kaonp1.DeltaTimeVer();
    TD->Kaonp_2_delta_time= _Kaonp2.DeltaTimeVer();
    TD->Kaonp_3_delta_time= _Kaonp3.DeltaTimeVer();

    // Momentum
    TD->electron_momentum = _electron.P4().P();
    TD->Kaonp_1_momentum= _Kaonp1.P4().P();
    TD->Kaonp_2_momentum= _Kaonp2.P4().P();
    TD->Kaonp_3_momentum= _Kaonp3.P4().P();

    // Theta
    TD->electron_theta = _electron.P4().Theta();
    TD->Kaonp_1_theta = _Kaonp1.P4().Theta();
    TD->Kaonp_2_theta = _Kaonp2.P4().Theta();
    TD->Kaonp_3_theta = _Kaonp3.P4().Theta();

    // Phi
    TD->electron_Phi = _electron.P4().Phi();
    TD->Kaonp_1_Phi = _Kaonp1.P4().Phi();
    TD->Kaonp_2_Phi = _Kaonp2.P4().Phi();
    TD->Kaonp_3_Phi = _Kaonp3.P4().Phi();
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
